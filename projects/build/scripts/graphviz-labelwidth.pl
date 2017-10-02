#!/usr/bin/perl
use strict;

my $usage = "setdotlabelwidth [char-width] < [dotfile]";
my $width = shift() or die("Usage: $usage $!");
my $file  = shift();
my $ignore  = shift();

my $stdin_h = \*STDIN;

if ($file) {
    open( $stdin_h, '<', $file ) or die "Could not open file '$file' $!";
}

if (!$ignore) {
  $ignore = "adfsadfasfasfsdf";
}

while (<$stdin_h>) {
    if ( $_ !~ /$ignore/ ) {

        if (m/label="(.*?)"/) {
            my $labeltext = $1;
            my @words     = split( /\//, $labeltext );
            my @newtext   = ();
            my $newline   = "";
            my $newlabel  = "NOT SET";

            if (0) {
                foreach my $word (@words) {
                    if (    length($newline) > 0
                        and length($newline) + length($word) > $width )
                    {
                        push( @newtext, $newline );
                        $newline = "";
                    }
                    $newline .= " " if ( length($newline) > 0 );
                    $newline .= $word;
                }
                push( @newtext, $newline ) if ( length($newline) > 0 );
                $newlabel = join( "\\n", @newtext );
            }
            else {
                $newlabel = substr( $labeltext, -$width );
            }
            s/label=".*?"/label="$newlabel"/;
        }

        print;
    }
}
