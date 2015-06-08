import os
import sys

def opt(optList,optFile):
	count=0
	optWriter=open(optFile,"w+")
	for user,itemList in optList.items():
		if itemList:
			optWriter.write(user+"\t")
			i=0
			for items in itemList:
				if (i>=1):
					optWriter.write(",")
				optWriter.write(items)
				count=count+1
				i=i+1
			optWriter.write("\n")
	print count
