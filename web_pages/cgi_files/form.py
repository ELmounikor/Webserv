#!/usr/bin/python

# Import modules for CGI handling 
import cgi, cgitb 

# Create instance of FieldStorage 
form = cgi.FieldStorage() 

# Get data from fields
first_name = form.getvalue('first_name')
last_name  = form.getvalue('last_name')
print "<html>"
print "<head>"
print "<title>Hello & CGI Program</title>"
print "</head>"
print "<body>"
print "<h2>Hello %s %s</h2><br>" % (first_name, last_name)
print "ELmounikor is HEEEEEEERRRRE\n"
print "</body>"
print "</html>"