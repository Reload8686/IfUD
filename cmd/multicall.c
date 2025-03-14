/*
 * cmd/multicall.c
 * Purpose: multi-call binary frontend
 *
 * Copyright (c) 2020 Ariadne Conill <ariadne@dereferenced.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * This software is provided 'as is' and without any warranty, express or
 * implied.  In no event shall the authors be liable for any damages arising
 * from the use of this software.
 */

#define _GNU_SOURCE
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "cmd/multicall.h"

char *argv0;

struct if_applet ifupdown_applet;
const struct if_applet *self_applet = NULL;

static struct if_applet **applet_table = NULL;
static size_t applet_count = 0;

static int
applet_cmp(const void *a, const void *b)
{
	const char *key = a;
	const struct if_applet *applet = *(void **)b;

	return strcmp(key, applet->name);
}

static int
applet_scmp(const void *a, const void *b)
{
	const struct if_applet *key = *(void **)a;
	const struct if_applet *applet = *(void **)b;

	return strcmp(key->name, applet->name);
}

void
applet_register(struct if_applet *applet)
{
	++applet_count;
	applet_table = reallocarray(applet_table, applet_count, sizeof (void *));
	applet_table[applet_count - 1] = applet;

	qsort(applet_table, applet_count, sizeof (void *), applet_scmp);
}

void multicall_usage(int status) __attribute__((noreturn));

struct if_applet ifupdown_applet;

int
main(int argc, char *argv[])
{
	argv0 = basename(argv[0]);
	const struct if_applet **app;

	lif_config_load(CONFIG_FILE);

	app = bsearch(argv0, applet_table,
		      applet_count, sizeof (void *),
		      applet_cmp);

	if (app == NULL)
	{
		fprintf(stderr, "%s: applet not found\n", argv0);
		multicall_usage(EXIT_FAILURE);
	}

	self_applet = *app;

	if (self_applet != &ifupdown_applet)
		process_options(*app, argc, argv);

	return self_applet->main(argc, argv);
}

static int
multicall_main(int argc, char *argv[])
{
	if (argc < 2)
		multicall_usage(EXIT_FAILURE);

	return main(argc - 1, argv + 1);
}

void
multicall_usage(int status)
{
	fprintf(stderr,
		PACKAGE_NAME " " PACKAGE_VERSION "\n"
		"usage: ifupdown <applet> [options]\n"
		"\n"
		"Built-in applets:\n");

	for (size_t i = 0; i < applet_count; i++)
	{
		if (applet_table[i] == &ifupdown_applet)
			continue;

		fprintf(stderr, "  %-10s %s\n", applet_table[i]->name, applet_table[i]->desc);
	}

	exit(status);
}

struct if_applet ifupdown_applet = {
	.name = "ifupdown",
	.main = multicall_main,
	.groups = { &global_option_group, NULL }
};

APPLET_REGISTER(ifupdown_applet)
