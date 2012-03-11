#!/usr/bin/env perl

use 5.012;
use warnings;

use IPC::Run3;

my $test_c = shift;

die "No test given" unless $test_c;
die "Test doesn't exist" unless -e $test_c;

(my $test_o = $test_c) =~ s/\.c$//;

my @clang_args = (qw(-g -L/opt/local/lib -I/opt/local/include -ltap -L. -lyogoc -Iinclude -o), $test_o, $test_c);

my ($out, $err);

my $status = run3 ['clang', @clang_args], undef, \$out, \$err;

if ($?) {
    print "Failed to run test because clang failed to compile";
    print $err;
    exit 1;
}

exec $test_o;