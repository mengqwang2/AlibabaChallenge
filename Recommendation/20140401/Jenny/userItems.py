import os
import sys
import csv

def userItems(fileName,actionType,opt):
	userItemList={}
	with open(fileName,"rb") as f:
		csvFile=csv.reader(f,delimiter=",")
		for row in csvFile:
			if row[0]!="user_id":
				if row[0] not in userItemList:
					userItemList[row[0]]=[]
				if (row[2]==actionType or actionType==4):
					userItemList[row[0]].append(row[1])

	optFile=open(opt,"w+")
	for users,items in userItemList.items():
		if items:
			optFile.write(users+"\t")
			i=0
			for item in items:
				if i>0:
					optFile.write(",")
				optFile.write(item)
				i=i+1
			optFile.write("\n")
	return userItemList

if __name__=="__main__":
	userItems(sys.argv[1],sys.argv[2],sys.argv[3])
