/*
 * libifupdown/environment.h
 * Purpose: environment variable management
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

#ifndef LIBIFUPDOWN_ENVIRONMENT_H__GUARD
#define LIBIFUPDOWN_ENVIRONMENT_H__GUARD

#include <stdbool.h>

extern bool lif_environment_push(char **env[], const char *name, const char *val);
extern void lif_environment_free(char **env[]);

#endif
