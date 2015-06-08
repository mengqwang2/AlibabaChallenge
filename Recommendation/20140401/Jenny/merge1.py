import os
import sys
import csv
import purchaseMorethan1
import userItems

def mergeList(list1,list2):
	newUserItems={}
	for user,item in list1.items():
		if user not in newUserItems:
			newUserItems[user]=[]
		newUserItems[user]=item

	for user,item in list2.items():
		if user not in newUserItems:
			newUserItems[user]=[]
		newUserItems[user]=list(set(newUserItems[user]+item))

	optFile=open("result.txt","w+")
	for user,item in newUserItems.items():
		if item:
			optFile.write(user+"\t")
			i=0
			for brandid in item:
				if i>=1:
					optFile.write(",")
				optFile.write(brandid)
				i=i+1
			optFile.write("\n")


if __name__=="__main__":
	list1=purchaseMorethan1.dupItems(sys.argv[1])
	list2=userItems.userItems(sys.argv[1],"3","userItem3.csv")
	mergeList(list1,list2)