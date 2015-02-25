#! /bin/sh

# Run this to set up GNU autotools...

cmd()
{
    echo "$1"
    eval "$1"
}

cmd "aclocal -I etc"
cmd "autoheader"
cmd "automake -a -c -f"
cmd "autoconf"
