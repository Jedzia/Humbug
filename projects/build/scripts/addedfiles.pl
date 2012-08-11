#! /usr/bin/perl
use strict;
use File::Basename;
use Cwd qw(getcwd abs_path);
use File::Spec::Functions qw( abs2rel );
use Data::Dumper;
use Config::Auto;

my $mDEBUG = 0;

# C:\ActivePerl\bin\perl.exe -MData::Dumper -MConfig::Auto -e 'print Dumper Config::Auto::parse("project.cfg")'

#use Time::HiRes qw(usleep);

my $curdir = abs_path( getcwd() );
my ( $volume, $directories, $file ) = File::Spec->splitpath($curdir);
print "volume=$volume \n" if ($mDEBUG);
print "directories=$directories \n" if ($mDEBUG);
print "file=$file\n" if ($mDEBUG);

my $programPath = abs_path($0);
my $cfg = find_cfg( $curdir, 'project.cfg' );
print "programPath=$programPath \n" if ($mDEBUG);
print "curdir=$curdir \n" if ($mDEBUG);
print "CFG=$cfg\n";
my ( $cfgName, $cfgPath, $cfgSuffix ) = fileparse( $cfg, qr/\.[^.]*/ );
print "cfgName = $cfgName, cfgPath = $cfgPath, cfgSuffix = $cfgSuffix \n" if ($mDEBUG);

#my @fields = split /$cfgPath/, $curdir;
my @fields = split /$curdir/, $cfgPath;
print "fields = @fields\n" if ($mDEBUG);

#chdir "$abs_path/../../";

my $command = shift;

my @cmdinput;
my $cmderrlvl;

#print "$0 \n";

# configuration
my @config  = Config::Auto::parse($cfg);
my %hasher  = $config[0];
my $hashes  = $config[0];
my $mainCat = $hashes->{"Main"};
my $extCat  = $hashes->{"AddedExtAssoc"};

#print $mainCat->{"older"},   "\n";
#my $ext_h = $extCat->{"h"}, "\n";

if ( $command eq "" ) {
    print "\nRunning:\n";
    print "=============\n";

    my $command = '"C:\Program Files\SVN\bin\svn.exe"  status ';
    @cmdinput = `$command`;

    print "Output: \n@cmdinput\n" if ($mDEBUG);

    my @data;
    foreach (@cmdinput) {
        my ( $first, $second ) = /(\S+)\s+(\S+)\s+(.*)/;

        print "first: $first, second: $second\n" if ($mDEBUG);

        #only print Added stuff.
        if ( $first eq "A" || $first eq "M" ) {
            chomp($second);
            print "second : $second\n" if ($mDEBUG);

            #my $xxxx = $cfgPath - $second;
            #print "xxxx = $xxxx\n";

            my $testfile = $curdir . "/" . $second;
            print "cfgPath: $cfgPath\n"    if ($mDEBUG);
            print "testfile = $testfile\n" if ($mDEBUG);
            my $diffpath = abs2rel( $testfile, $cfgPath );

     # tr http://mailman.linuxchix.org/pipermail/courses/2003-July/001302.html
            $diffpath =~ tr/\\/\//;    # Replace each "\" with a "/".
            my ( $diffName, $diffPath, $diffSuffix ) = fileparse( $diffpath, qr/\.[^.]*/ );
            print "diffName = $diffName, diffPath = $diffPath, diffSuffix = $diffSuffix \n" if ($mDEBUG);
            push( @data, $diffSuffix . ":" . $diffpath );

         #my @diffs= find_diffs($testfile,$cfgPath);  print "DIFFS: @diffs\n";
        }

    }

    if ($mDEBUG) {
        print "\ndata:\n"; print $_, "\n" foreach (@data); print "\n";
    }

    $_ = @data;
    my @sorted = map { $_->[0] }
        sort customSort
        map { [ $_, split /:/ ] } @data;
@sorted = sort @sorted;
#print "\nsorted data:\n"; print $ext_h . [ $_, split /:/ ]->[2], "\n" foreach (@sorted); print "\n";
    print "\nsorted data:\n", "=" x 80, "\n";
    my $lastExt;
    foreach (@sorted) {
        my $tfileData = [ $_, split /:/ ];
        my $tfileExt;
        my $tfileExtp;
        $_ = $tfileExtp = $tfileExt = $tfileData->[1];
        $tfileExtp =~ s/^\.//;
        my $tfileName = $tfileData->[2];
        print "\nEXT $tfileExt\n--------------------\n" if ( $tfileExt ne $lastExt );
        print "$tfileExtp\n" if ($mDEBUG);
        my $extHash = $extCat->{$tfileExtp};
        print "    ", $extHash . $tfileName, "\n";
        $lastExt = $tfileExt;
    }
    print "\n";
}

# How to get relative path in perl?
# http://www.perlmonks.org/?node_id=817919

#use File::Spec::Functions qw( abs2rel );
#
#print(
#    abs2rel('A:\\B.CD(E)~!@#$%^&\\E\\F.txt',
#        'A:\\B.CD(E)~!@#$%^&'),
#    "\n"
#);

#use Path::Class qw( file );
#
#print(
#    file('A:\\B.CD(E)~!@#$%^&\\E\\F.txt')
#        ->relative('A:\\B.CD(E)~!@#$%^&'),
#    "\n"
#);

#use PDL;
#use PDL::Char;
#$PDL::SHARE=$PDL::SHARE; # keep stray warning quiet
#
#my $source=PDL::Char->new("ATTCCGGG");
#for my $str ( "ATTGCGGG", "ATACCGGC") {
#  my $match =PDL::Char->new($str);
#  my @diff=which($match!=$source)->list;
#  print "@diff\n";
#}

#print Dumper( @config );
#print "\nxxxx:\n"; print $_, "\n" foreach (@config[0]); print "\n";
#print "\nxxxx:\n"; print $_, "\n" foreach (Config::Auto::parse($cfg)); print "\n";
#print $hasher{"Main"};

#print @config[0]{"Main"};
#my @any = $config{"Main"};
#print Dumper( @any );

exit();

sub customSort {

    #print "compare a:$a->[1] b:$b->[1]\n";
    $a->[1] cmp $b->[1];
}

sub find_cfg {
    my $inputPath      = shift @_;
    my $configFileName = shift @_;

    die("find_cfg: No configFileName specified!\n") if ( $configFileName eq "" );

#my ( $prgName, $prgPath, $prgSuffix ) = fileparse( $inputPath, qr/\.[^.]*/ );
#print "prgName = $prgName, prgPath = $prgPath, prgSuffix = $prgSuffix \n";

    #my $prgparrentpath = basename($prgpath);
    #print "[find_cfg] prgName $prgName\n"  if($mDEBUG);
    #print "[find_cfg] prgpath $prgPath\n"  if($mDEBUG);
    #print "[find_cfg] prgSuffix $prgSuffix\n" if($mDEBUG);
    my $cfgfile     = "";
    my $currentPath = $inputPath;
    my $cnt         = 0;

    # move upwards the directory tree and check for 'project.cfg'
    while ($currentPath) {

        print "[find_cfg] currentPath $currentPath\n" if ($mDEBUG);

        my $checkfile = $currentPath . "/" . $configFileName;
        print "[find_cfg] search for $checkfile\n" if ($mDEBUG);
        if ( -e $checkfile )
        {
            print "[find_cfg] >>>> File $checkfile found\n" if ($mDEBUG);
            $cfgfile = $checkfile;
            last;
        }

        $currentPath = dirname($currentPath);
        $cnt++;
        if ( $cnt > 40 )
        {
            last;
        }
        if ( $currentPath =~ /^.:\/$/s )
        {

            #root reached, stop
            last;
        }

#my ( $prgName, $prgPath, $prgSuffix ) = fileparse( $currentPath, qr/\.[^.]*/ );
#print "prgName = $prgName, prgPath = $prgPath, prgSuffix = $prgSuffix \n";
    }

    "$cfgfile";
}

#
sub big_money {
    my $number = sprintf "%.2f", shift @_;

    #Add one comma each time through the do-nothing loop
    1

        while $number = ~s/^(-?\d+)(\d\d\d)/$1,$2/;

    #Put the dollar sign in the right place
    $number = ~s/^(-?)/$1\$/;
    $number;
}

# http://stackoverflow.com/questions/1672782/fastest-way-to-find-mismatch-positions-between-two-strings-of-the-same-length
#use Inline C => <<'END_C';
#
#  void find_diffs(char* x, char* y) {
#    int i;
#    Inline_Stack_Vars;
#    Inline_Stack_Reset;
#    for(i=0; x[i] && y[i]; ++i) {
#      if(x[i] != y[i]) {
#        Inline_Stack_Push(sv_2mortal(newSViv(i)));
#      }
#    }
#    Inline_Stack_Done;
#  }
#
#END_C

