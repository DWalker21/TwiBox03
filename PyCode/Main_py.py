__author__ = 'DU'

import feedparser
import serial
import time

titles=['']

#parse feed - google tech news
my_feeds=feedparser.parse('http://news.google.com/news?pz=1&cf=all&ned=us&hl=en&topic=tc&output=rss')
#feed from eugene
#my_feeds=feedparser.parse('http://api.twitter.com/1/statuses/user_timeline.rss?screen_name=e_kaspersky')
print (my_feeds.entries[5].title)
print (len(my_feeds.entries))

#fill in output structure and print to see it
for i in range(len(my_feeds.entries)):
    titles.append(my_feeds.entries[i].title+"\n")
    print (titles[i])

#open serial
#ser = serial.Serial("COM6",9600)
#ser = serial.Serial("COM14",9600)

#output constants
len_byte=1
msg_byte="MSG"
msg_enter=" \n".encode("UTF8")

#OUT
for i in range(len(titles)):
#for i in range(3):
    #ser = serial.Serial("COM6",9600)
    # works with my BT BEE linvor
    ser = serial.Serial("COM15",9600)
    ser.write(msg_byte.encode("ascii"))
    msg=(titles[i]).encode("UTF8")
    len_byte=len(msg)
    print (len_byte)
    len_char=(', {len} '.format(len=len_byte))
    ser.write(len_char.encode("UTF8"))
    ser.write(msg)
    ser.write(msg_enter)
    time.sleep(1)
    ser.close()
    time.sleep(1)

