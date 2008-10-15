#! /usr/bin/env perl

=head1 NAME

ifm2web -- convert IFM maps to images suitable for the Interweb

=head1 SYNOPSIS

ifm2web [options] file

=head1 DESCRIPTION

=head1 OPTIONS

=over 4

=item B<-o> F<file>

Write output to the specified file, instead of stdout.

=item B<-h>

Give a usage message.

=back

=head1 AUTHOR

Glenn Hutchings

=cut

require 5.000;
use Getopt::Std;

# Parse arguments.
$0 =~ s-.*/--;
getopts('hm:f:s:to:a:nz:', \%opts) || die "Type '$0 -h' for help\n";
usage() if $opts{h};

$maps = $opts{m};
$format = $opts{f} || "png";
$title = $opts{t} ? "true" : "false";
$output = $opts{o};
$alpha = $opts{a} || "white";
$zoom = $opts{z} || 5;
$scale = $opts{s} || 100;
$whatif = $opts{n};

# Parse any extra IFM arguments.
$ifmopts = 's:S:I:';
getopt($ifmopts, \%ifmopts);

# Get IFM file.
$file = shift(@ARGV) or moan("no IFM file specified");

$prefix = $file;
$prefix =~ s/\.ifm$//;
$output = $prefix . "." . $format unless $output;

# Build IFM command.
$ifm = "ifm -nowarn";

$ifm .= " -map=$maps" if $maps;
$ifm .= " -format fig";
$ifm .= " -s show_map_title=$title";
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
