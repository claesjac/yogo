#!/usr/bin/perl

use 5.012;
use warnings;

my $test_c = shift;

die "No test given" unless $test_c;
die "Test doesn't exist" unless -e $test_c;

(my $test_o = $test_c) =~ s/\.c$//;

my @clang_args = (qw(-g -L/opt/local/lib -I/opt/local/include -lJudy -ltap -L. -lyogovm -Iinclude -o), $test_o, $test_c);
my $status = system "clang", @clang_args;

do { local $, = " "; die "clang @clang_args: $!" } if $status;

exec $test_o;