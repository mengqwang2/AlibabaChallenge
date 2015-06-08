import os
import sys
import csv

def itemSimList(fileName):
	itemList={}
	with open(fileName,"rb") as f:
		csvReader=csv.reader(f,delimiter=",")
		for row in csvReader:
			if row[0] not in itemList:
				itemList[row[0]]=[]
			itemList[row[0]].append(row[1])

	return itemList
