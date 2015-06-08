import os
import sys
import csv

def itemAction(fileName):
	itemList={}
	with open(fileName,"rb") as f:
		csvFile=csv.reader(f,delimiter=",")
		for row in csvFile:
			if row[0]!="user_id":
				if row[1] not in itemList:
					itemList[row[1]]={
									"a0":0,
									"a1":0,
									"a2":0,
									"a3":0
									}
				actionStr="a"+row[2]
				itemObj=itemList[row[1]]
				itemObj[actionStr]+=1

	optFile=open("itemAction.csv","w+")
	for items,action in itemList.items():
		optFile.write(items+","+str(action["a0"])+","+str(action["a1"])+","+str(action["a2"])+","+str(action["a3"])+"\n")
		if action["a3"]>0:
			print items

if __name__=="__main__":
	itemAction(sys.argv[1])
