#!/usr/bin/perl
use strict;
use warnings;

sub mkArray
{
        my $bipfile = "$_[0]";
        open( my $file, '<:encoding(UTF-8)', $bipfile )
                or die "Could not open file $bipfile $!";

        (my $varName = $bipfile) =~ s/\.[^.]+$//;
        $varName =~ s{^}{bip_};

        print "        const char * $varName [] = {";
        for ( my $i=0; $i < 2047; $i ++ )
        {
                my $row = <$file>;
                chomp $row;

                if ( $i % 5 == 0 )
                {
                        print "\n                ";
                } else
                {
                        print " ";
                }
                print "\"$row\",";
                
        }
        my $row = <$file>;
        chomp $row;
        print " \"$row\"\n                };\n";
        close $file;
}

#my $directory = '..';
opendir (DIR, '.') or die $!;

print  "#ifndef BIP39\n#define BIP39\n\nnamespace\n{\n";

while ( my $file = readdir(DIR) )
{
        if ( $file =~m/^czech\.txt/ or $file=~m/^english\.txt/)
        {
                mkArray( $file );
                print  "\n";
        }
}

print  "}\n\n#endif\n";
