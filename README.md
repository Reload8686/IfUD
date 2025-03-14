# ifupdown-ng

ifupdown-ng is a network device manager that is largely compatible with Debian
ifupdown, BusyBox ifupdown and Cumulus Networks' ifupdown2.

For more information read the [admin guide](doc/ADMIN-GUIDE.md).

## Dependency Resolution

![Dependency resolution example](doc/img/dependency-resolution.png)

ifupdown-ng uses a dependency resolver to determine interface bring-up order
in a deterministic way.

This is accomplished through a combination of manual hinting using the `requires`
keyword and dependency learning using native executors.

For compatibility with some legacy ifupdown executors, we also provide the
`requires` keyword under other environment variables in some cases.

## Caveats

* ifupdown2 python plugins are not supported at this time.  An executor could be
  written to handle them.

* ifupdown-ng retains compatibility with /etc/network/if-X.d scripts, but will
  prefer using executors in /usr/libexec/ifupdown-ng where appropriate.

## Building

On musl systems, simply do `make` and `make install` to build and install.

On glibc systems, you must install `libbsd-dev` or equivalent and additionally define `LIBBSD_CFLAGS` and `LIBBSD_LIBS`:

    # instal packages
    apt install build-essential libbsd0 libbsd-dev

    # build ifupdown-ng
    make LIBBSD_CFLAGS="$(pkg-config --cflags libbsd-overlay)" LIBBSD_LIBS="$(pkg-config --cflags --libs libbsd-overlay)"
    make install

To run the tests, do `make check`. Running the checks requires `kyua` (`apk add kyua` / `apt install kyua`).

To build the documentation, do `make docs` and `make install_docs`.  Building
the documentation requires scdoc (`apk add scdoc` / `apt install scdoc`).

## Discussion

Discuss ifupdown-ng on IRC: irc.oftc.net #ifupdown-ng
