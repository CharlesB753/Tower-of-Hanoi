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
#sends player back if occupied
#after checking csv file



if(occupancy==1):
        print "11"
        print "<form method='post' action = %s+'cgi-bin/room.cgi'>" %(form['URL'].getvalue)
        print "<h2> Room Occupied --- Please Wait </h2>"
        print "<input type='hidden' name='inventory' value='%s'>" %(form['inventory'].getvalue)
        print "<input type='hidden' name='URL' value='http://cs.mcgill.ca/~cbelis3/'>"
        print "<input type= 'submit' name = 'Return to Previous Room'>"
	print "</form>"



#if player enters the room, it updates csv file unoccupied <- occupied, 0 <- 1 and add a mana
if(occupancy==0):
        print "22"
        room_mana=int(resources[0])+1
        room_gold=resources[1]
        room_mana=str(room_mana)
        fw=open('resources.csv','w')
        fw.write(""+room_mana+","+room_gold+",1")
        fw.close()
#then we call success.py of the other team

        success_url = "%s"+"/cgi_bin/success.py" %(form['URL'].getvalue,)
        print "<form action='"+success_url+"' method='post'>"
        print "<input type='hidden' name='inventory' value='%s'>" %(form['inventory'].getvalue)
        print '<input type="hidden" name="URL" value="http://cs.mcgill.ca/~cbelis3/">'
        print '<center><input type="submit" value="Go"></center>'
	print '</form>'
else:
        print "hu-ho"


print "</body></html>"