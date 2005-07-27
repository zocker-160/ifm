dnl AM_CONFIG_LIB(NAME, PREFIX, PROG, [REQUIRED])
dnl 
dnl Test for library using lib-config.  If config file found:
dnl 
dnl    Substitute lib_CFLAGS and lib_LIBS in Makefiles
dnl    Define HAVE_PREFIX macro and shell variable
dnl 
dnl If REQUIRED is "yes", it must be there (any version will do).  If
dnl it's set to anything else, it's the minimum version required.
dnl
AC_DEFUN([AM_CONFIG_LIB],[
AC_REQUIRE([AM_CHECK_VERSION])dnl
AC_PATH_PROG($2_CONFIG, $3, no)

HAVE_$2=
if test $$2_CONFIG != no; then
   # Check version if required.
   if test -n "$4" && test $4 != yes; then
      AC_MSG_CHECKING(for $1 - version >= $4)
      $2_VERSION=`$$2_CONFIG --version`
      AC_MSG_RESULT($$2_VERSION)
      AM_CHECK_VERSION($1 library, $$2_VERSION, $4)
   fi

   # Define HAVE_PREFIX.
   AC_DEFINE(HAVE_$2, 1, [Whether the $1 library is available])
   HAVE_$2=yes

   # Set CFLAGS.
   $2_CFLAGS="`$$2_CONFIG --cflags`"
   AC_SUBST($2_CFLAGS)

   # Set LIBS.
   $2_LIBS="`$$2_CONFIG --libs`"
   AC_SUBST($2_LIBS)
elif test -n "$4"; then
   AC_MSG_ERROR(can't find $1 library)
fi
])
