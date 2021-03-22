
#!usr/bin/env python
import cgi
import csv

print "Content-type: text/html\r\n\r\n"

form = cgi.FieldStorage()
print "<html><body>"

fr = open('resources.csv', 'r')
row = fr.readline()
resources = row.split(",")
room_mana = resources[0]
room_gold = resources[1]
occupancy = int(resources[2])
fr.close()

#if player enters the room, it sets our csv 1 <- 0

if occupancy == 1:
        fw = open('resources.csv', 'w')
        fw.write(""+room_mana+","+room_gold+",0")


        fw.close()
print "<form action='%s+/cgi_bin/room.cgi' method='get'>" %(form['URL'].getvalue)
print "<input type='hidden' name='inventory' value='%s'>" %(form['inventory'].getvalue)
print '<input type="submit" value="Continue">'
print '</form>'
print "</body></html>"