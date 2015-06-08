import os
import sys
import csv

def actionMonth(fileName):
	monthList={}
	monthList["m4"]={}
	monthList["m5"]={}
	monthList["m6"]={}
	monthList["m7"]={}
	monthList["m8"]={}

	for months,actions in monthList.items():
		actions["a0"]=0
		actions["a1"]=0
		actions["a2"]=0
		actions["a3"]=0

	with open(fileName,"rb") as f:
		csvFile=csv.reader(f,delimiter=",")
		for row in csvFile:
			if row[0]!="user_id":
				dateStr=row[3]
				monthStr="m"+dateStr[:1]
				monthObj=monthList[monthStr]
				actionStr="a"+row[2]
				monthObj[actionStr]+=1
		print monthList["m4"]
		print monthList["m5"]
		print monthList["m6"]
		print monthList["m7"]
		print monthList["m8"]

	optFile=open("actionMonth.csv","w+")
	for months,actions in monthList.items():
		optFile.write(months+","+str(actions["a0"])+","+str(actions["a1"])+","+str(actions["a2"])+","+str(actions["a3"])+"\n")

if __name__=="__main__":
	actionMonth(sys.argv[1])
