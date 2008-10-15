# ifm2web -- convert IFM map to image suitable for the Interweb

require 5.000;
use Getopt::Std;

# Parse arguments.
$0 =~ s-.*/--;
getopts('hm:f:s:to:a:nz:S:', \%opts) || die "Type '$0 -h' for help\n";
usage() if $opts{h};

$maps = $opts{m};
$format = $opts{f} || "png";
$title = $opts{t} ? "true" : "false";
$output = $opts{o};
$alpha = $opts{a} || "white";
$zoom = $opts{z} || 1;
$scale = $opts{s} || 100;
$style = $opts{S};
$whatif = $opts{n};

# Get IFM file.
$file = shift(@ARGV) or moan("no IFM file specified");

$prefix = $file;
$prefix =~ s/\.ifm$//;
$output = $prefix . "." . $format unless $output;

# Build IFM command.
$ifm = "ifm -nowarn";

$ifm .= " -map";
$ifm .= "=$maps" if $maps;
$ifm .= " -format fig";
$ifm .= " -S $style" if $style;
$ifm .= " -s show_map_title=$title";
$ifm .= " -s show_map_border=false";
$ifm .= " -s map_border_colour=$alpha";
$ifm .= " -s map_background_colour=$alpha";

foreach $opt (keys %ifmopts) {
    $ifm .= " -$opt";
    $ifm .= " $ifmopts{$opt}" if $ifmopts =~ /$opt/;
}

# Build conversion command.
$cmd  = "$ifm $file";
$cmd .= " | fig2dev -L $format -m $zoom";
$cmd .= " | convert -transparent $alpha -scale $scale% - $output";

if ($whatif) {
    print $cmd, "\n";
} else {
    system $cmd;
}

# Print an error message and die.
sub moan {
    die "$0: error: ", join(' ', @_), "\n";
}

# Give a usage message and exit.
sub usage {
    print "Usage: $0 [options] [-- ifm-options] file\n";
    print "  -h           this help message\n";
    exit 0;
}
