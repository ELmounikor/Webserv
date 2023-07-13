#!/usr/local/bin/perl
$server_software = $ENV{'SERVER_SOFTWARE'};
print "Status: 200 OK", "\r\n";
print "Server: $server_software", "\r\n";
print "Content-type: text/plain", "\r\n\r\n";
print "OK, Here I go. I am going to count from 1 to 50!", "\n";
$| = 1;
for ($loop=1; $loop <= 50; $loop++) {
        print $loop, "\n";
        sleep (2);
}
print "All Done!", "\n";
exit (0);