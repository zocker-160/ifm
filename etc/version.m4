dnl AM_CHECK_VERSION(NAME, VERSION, MIN-REQUIRED)
dnl 
dnl Check for minimum version of something.
dnl
AC_DEFUN([AM_CHECK_VERSION],[
ac_result=`perl -e '
sub canonical {
    $str = shift;
    $str =~ s/\D+/./g;
    join("", map {sprintf("%06s", $_)} split(/\./i, $str));
}

$actual = canonical(shift);
$required = canonical(shift);

print $required <= $actual ? "yes" : "no";
' $2 $3 2> /dev/null`

if test "$ac_result" = "no"; then
   AC_MSG_ERROR($1 version $3 or greater is required)
fi
])
