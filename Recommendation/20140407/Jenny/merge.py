import os
import sys
import csv
import re

def mergeResult(csv1,csv2):
	userItems1={}
	userItems2={}
	with open(csv1,"r+") as f1:
		line1=csv.reader(f1,delimiter="\t")
		for line in line1:
			user=line[0]
			itemList=line[1]
			items=itemList.split(",")
			if user not in userItems1:
				userItems1[user]=[]
			for item in items:
				userItems1[user].append(item)

	with open(csv2,"r+") as f2:
		line2=csv.reader(f2,delimiter="\t")
		for line in line2:
			user=line[0]
			itemList=line[1]
			items=itemList.split(",")
			if user not in userItems2:
				userItems2[user]=[]
			for item in items:
				userItems2[user].append(item)

	list1=userItems1
	list2=userItems2

	newUserItems={}
	for user,item in list1.items():
		if user not in newUserItems:
			newUserItems[user]=[]
		newUserItems[user]=item

	for user,item in list2.items():
		if user not in newUserItems:
			newUserItems[user]=[]
		newUserItems[user]=list(set(newUserItems[user]+item))

	count=0
	optFile=open("mergeResult.txt","w+")
	for user,item in newUserItems.items():
		if item:
			optFile.write(user+"\t")
			i=0
			for brandid in item:
				if i>=1:
					optFile.write(",")
				optFile.write(brandid)
				count=count+1
				i=i+1
			optFile.write("\n")
	print count


if __name__=="__main__":
	mergeResult(sys.argv[1],sys.argv[2])
			

