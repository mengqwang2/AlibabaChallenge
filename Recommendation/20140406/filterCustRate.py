import os
import sys
import csv

def filterCustRate(fileName):
	userItemRateList={}
	userItemList={}
	with open(fileName,"rb") as f:
		csvReader=csv.reader(f,delimiter=",")
		for row in csvReader:
			if row[0] not in userItemRateList:
				userItemRateList[row[0]]={}
			userObj=userItemRateList[row[0]]
			userObj[row[1]]=row[2]

		for user,itemList in userItemRateList.items():
			sorted_itemRate=sorted(itemList,key=itemList.__getitem__,reverse=True)
			if(user not in userItemList):
				userItemList[user]=[]
			userItemList[user]=sorted_itemRate[:3]

		return userItemList

if __name__=="__main__":
	filterCustRate("custRating.csv")