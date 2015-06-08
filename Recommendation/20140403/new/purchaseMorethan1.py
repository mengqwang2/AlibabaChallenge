import os
import sys
import csv
import userItems
import collections
import datetime

def formatPurchase(fileName):
	userItemDate={}
	with open(fileName,"rb") as f:
		csvFile=csv.reader(f,delimiter=",")
		for row in csvFile:
			if row[0]!="user_id":
				dateStr=row[3]
				monStr=int(dateStr[0])
				dayStr=int(dateStr[3:-2])
				dateObj=datetime.datetime(2013,monStr,dayStr,0,0,0)
				if row[2]=="1":
					if row[0] not in userItemDate:
						userItemDate[row[0]]={}
					itemDate=userItemDate[row[0]]
					if row[1] not in itemDate:
						itemDate[row[1]]=[]
					itemDate[row[1]].append(dateObj)

	for user,itemDate in userItemDate.items():
		for item,dateList in itemDate.items():
			itemDate[item]=list(set(dateList))	

	p_largerthan1={}
	for user,itemDate in userItemDate.items():
		if user not in p_largerthan1:
			p_largerthan1[user]=[]
		for item,dateList in itemDate.items():
			if len(dateList)>1:
				p_largerthan1[user].append(item)
	return p_largerthan1
		

def dupItems(p_largerthan1):
	optFile=open("dupPurchaseItems_notSameDay.txt","w+")
	for user,item in p_largerthan1.items():
		if item:
			optFile.write(user+"\t")
			i=0
			for brandid in item:
				if i>=1:
					optFile.write(",")
				optFile.write(brandid)
				i=i+1
			optFile.write("\n")
	return p_largerthan1

if __name__=="__main__":
	dupItems(formatPurchase(sys.argv[1]))
	#formatPurchase(sys.argv[1])