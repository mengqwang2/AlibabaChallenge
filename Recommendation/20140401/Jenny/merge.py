import os
import sys
import csv
import re

def mergeResult(csv1,csv2):
	userItems={}
	with open(csv1,"r+") as f1:
		csvFile1=csv.reader(f1,delimiter=",")
		for line in csvFile1:
			print line[0]
			str1=line[0].split("\t")
			userid=str1[0]
			#print userid
			if userid not in userItems:
				userItems[userid]=[]
			if line[1]:
				i=1
				for brand in line:
					userItems[userid].append(line[i])
					i=i+1
				userItems[userid].append(str1[1])
	#print userItems

if __name__=="__main__":
	mergeResult(sys.argv[1],1)
			

