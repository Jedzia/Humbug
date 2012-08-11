#! /usr/bin/perl
use strict;
use File::Basename;
use Cwd qw(getcwd abs_path);
use File::Spec::Functions qw( abs2rel );
use Data::Dumper;
use Config::Auto;
use Path::Class qw(dir);  # Export a short constructor
use FileHandle;


my $mDEBUG = 0;

# C:\ActivePerl\bin\perl.exe -MData::Dumper -MConfig::Auto -e 'print Dumper Config::Auto::parse("project.cfg")'

#use Time::HiRes qw(usleep);

my $templExtension1 = ".cpp";
my $templExtension2 = ".h";

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

my $pcfgDir = dir($cfgPath);       # Path::Class::Dir object
my $dir = dir($curdir);       # Path::Class::Dir object
my $abs = $dir->absolute; # Transform to absolute path
my $rel = $abs->relative; # Transform to relative path
my $rel2 = $abs->relative($cfgPath); # Relative to /foo
print $rel2->as_foreign('Unix'); #  foo\bar


#my @fields = split /$cfgPath/, $curdir;
my @fields = split /$curdir/, $cfgPath;
print "fields = @fields\n" if ($mDEBUG);

#chdir "$abs_path/../../";

my $argTemplateName = shift;
my $argSubstitution = shift;

my @cmdinput;
my $cmderrlvl;

#print "$0 \n";

# configuration
my @config  = Config::Auto::parse($cfg);
my %hasher  = $config[0];
my $hashes  = $config[0];
my $mainCat = $hashes->{"Main"};
my $extCat  = $hashes->{"AddedExtAssoc"};
my $templCat  = $hashes->{"Templates"};
my $templRootPath = $templCat->{"RootPath"};
print "$templRootPath \n" if ($mDEBUG);

my $tempd = $templRootPath;
$tempd =~ s/\"//g;
print "tempd: " . $tempd . "\n" if ($mDEBUG); #  remove ""
my $ptemplSearchDir = dir($cfgPath)->subdir($tempd);       # Path::Class::Dir object
#my $rel3 = $abs->relative($ptemplSearchDir); # Relative to /foo
#print $ptemplSearchDir->as_foreign('Unix') . "\n"; #  foo\bar
print $ptemplSearchDir . "\n" if ($mDEBUG); #  foo\bar

#print $mainCat->{"older"},   "\n";
#my $ext_h = $extCat->{"h"}, "\n";

print "\n-----------------------------------------------------------------\n\n";

my $argSubstitutionUC = uc($argSubstitution);
my $templFile = $ptemplSearchDir->file($argTemplateName . $templExtension1 ); # A file in this directory
my $templOutFile = $dir->file($argSubstitution . $templExtension1 ); # A file in this directory

if (-e $templOutFile) {
    print "Output file '" . $templOutFile . "' exists.\n";
}
if (-e $templFile && ! -e $templOutFile) {
    print "templFile: '" . $templFile . "' exists.\n" if ($mDEBUG); #  foo\bar

    my $fh = FileHandle->new;
    my $fhOut = FileHandle->new;
    if (!$mDEBUG) {
        $fhOut->open("> $templOutFile")
            or die("Cannot open output file '$templOutFile'.");
    }
    
    if ($fh->open("< $templFile")) {
        print "Generating '" . $templOutFile . "'\n      from '". $templFile. "'.\n\n"; 
        #print <$fh>;
        while (my $line = <$fh>) {
            my $tmpline = $line;
            $tmpline =~ s/TEMPLATE/$argSubstitutionUC/g;
            $tmpline =~ s/Template/$argSubstitution/g;
            print $tmpline if ($mDEBUG);
            print $fhOut $tmpline if (! $mDEBUG);
        }

        $fh->close;
    }
}
else {
    print "templFile: '" . $templFile . "' does not exist.\n" if ($mDEBUG); #  foo\bar
    #exit 1;
}

$templFile = $ptemplSearchDir->file($argTemplateName . $templExtension2 ); # A file in this directory
$templOutFile = $dir->file($argSubstitution . $templExtension2 ); # A file in this directory

if (-e $templOutFile) {
    print "Output file '" . $templOutFile . "' exists.\n";
}
if (-e $templFile && ! -e $templOutFile) {
    print "templFile: '" . $templFile . "' exists.\n" if ($mDEBUG); #  foo\bar

    my $fh = FileHandle->new;
    my $fhOut = FileHandle->new;
    if (!$mDEBUG) {
        $fhOut->open("> $templOutFile")
            or die("Cannot open output file '$templOutFile'.");
    }
    
    if ($fh->open("< $templFile")) {
        print "Generating '" . $templOutFile . "'\n      from '". $templFile. "'.\n\n"; 
        #print <$fh>;
        while (my $line = <$fh>) {
            my $tmpline = $line;
            $tmpline =~ s/TEMPLATE/$argSubstitutionUC/g;
            $tmpline =~ s/Template/$argSubstitution/g;
            print $tmpline if ($mDEBUG);
            print $fhOut $tmpline if (! $mDEBUG);
        }

        $fh->close;
    }
}
else {
    print "templFile: '" . $templFile . "' does not exist.\n" if ($mDEBUG); #  foo\bar
    exit 1;
}

exit 0;

if ( $argTemplateName eq "TemplateOstream" ) {
    print "\nRunning:\n";
    print "=============\n";

    my $argTemplateName = '"C:\Program Files\SVN\bin\svn.exe"  status ';
    @cmdinput = `$argTemplateName`;

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

