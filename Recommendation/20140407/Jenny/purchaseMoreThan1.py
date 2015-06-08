import os
import sys
import csv

def userItems(fileName,actionType,opt):
	purchaseMorethan1={}
	userItemList={}
	with open(fileName,"rb") as f:
		csvFile=csv.reader(f,delimiter=",")
		for row in csvFile:
			if row[0]!="user_id":
				if row[0] not in userItemList:
					userItemList[row[0]]=[]
				if (row[2]==actionType or actionType==4):
					userItemList[row[0]].append(row[1])

		for users,itemList in userItemList.items():
			if users not in purchaseMorethan1:
				purchaseMorethan1[users]=[]
			for item in itemList:
				if itemList.count(item)>1:
					purchaseMorethan1[users].append(item)
			purchaseMorethan1[users]=list(set(purchaseMorethan1[users]))

	optFile=open(opt,"w+")
	count=0
	for users,items in purchaseMorethan1.items():
		if items:
			optFile.write(users+"\t")
			i=0
			for item in items:
				if i>0:
					optFile.write(",")
				optFile.write(item)
				count=count+1
				i=i+1
			optFile.write("\n")
	print count
	return purchaseMorethan1

if __name__=="__main__":
	userItems(sys.argv[1],sys.argv[2],sys.argv[3])
