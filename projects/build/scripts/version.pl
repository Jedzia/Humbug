#! /usr/bin/perl
use strict;
use File::Basename;
use Cwd qw(getcwd abs_path);
use File::Spec::Functions qw( abs2rel );
#use File::Find::Rule;
use Path::Class;
use Cwd;

my $mDEBUG = 0;
my $searchstring = "Version=";
#print("Version: 1.0.0 \r\n");
#print("Version=1.0.0 \r\n");

my $dir       = getcwd;
my $scriptdir = dirname(__FILE__);
my $progpath  = abs_path($0);
print "progpath: $progpath \r\n" if ($mDEBUG);
print "basename: " . basename($0) . "\r\n" if ($mDEBUG);
print "dir: " . $dir . "\r\n" if ($mDEBUG);
print "scriptdir: " . $scriptdir . "\r\n" if ($mDEBUG);

chdir($scriptdir);

sub checkFile {
    my $filePath = shift @_;
    my $criteria = shift @_;

    open my $fh, $filePath or die "Could not open $filePath: $!";

    my @lines = sort grep /\Q$criteria/, <$fh>;

    if (@lines) {
        my $mfilePath = basename($filePath);
    	print $mfilePath . "\n";
        my $pathLen = length($mfilePath);
        print "-" x $pathLen . "\r\n";
        
        #print join( "    ", @lines );
        my $verstr = $lines[0];
        my @ver = split($criteria, $verstr);
    	print "    Version = $ver[1]\n";
        #print join( "        Ver: ", @ver );
        # my @values = split('\.', $ver[1]);
        # print join( "|", @values );
    	print "\n";
    }
}

#my @perlfiles = glob  $dir . "\\pe?l/*.p?";
#my @perlfiles = glob  $scriptdir . "/*.*";
print "\r\n";

my @perlfiles;
#my @perlfiles = glob("*.pl *.bat");

#print @perlfiles;
#print join("\r\n", @perlfiles);

dir('.')->recurse(callback => sub {
    my $file = shift;
    #print $file . "\r\n";
    if($file =~ /\.pl$|\.bat$/) {
        push @perlfiles, $file->absolute->stringify;
    }
});

for (@perlfiles) {
    my $abs = abs_path($_);
    #print "HIT: " . $_ . "\r\n";
    #print $abs . "\n";
    if ($abs eq $progpath) {
        #print "Equality: $_\r\n";
        next;
    }
    
    checkFile( $_, $searchstring );
}



