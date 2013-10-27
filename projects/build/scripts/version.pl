#! /usr/bin/perl
use strict;
use File::Basename;
use Cwd qw(getcwd abs_path);
use File::Spec::Functions qw( abs2rel );
use Cwd;

print("Version: 1.0.0 \r\n");

my $dir = getcwd;
my $scriptdir = dirname(__FILE__);
print "abs_path: " . abs_path($0) . "\r\n";
print "dir: " . $dir . "\r\n";
print "scriptdir: " . $scriptdir . "\r\n";


sub checkFile {
    my $filePath      = shift @_;
    my $criteria = shift @_;


open my $fh, $filePath or die "Could not open $filePath: $!";

my @lines = sort grep /\Q$criteria/, <$fh>;
#print @lines;
print join("    ", @lines);

}


#my @perlfiles = glob  $dir . "\\pe?l/*.p?";
#my @perlfiles = glob  $scriptdir . "/*.*";
print "\r\n";

chdir($scriptdir);
my @perlfiles = glob("*.pl *.bat");
#print @perlfiles;
#print join("\r\n", @perlfiles);

my $searchstring = "Version";

foreach (@perlfiles) {
 	print "--------------------------\n";
 	print $_ . "\n";
        checkFile($_, $searchstring);
 } 


