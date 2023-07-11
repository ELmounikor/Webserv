#!/usr/bin/perl

use CGI;

my $cgi = CGI->new;

print $cgi->header("text/html");

while (1){  print "h";}
