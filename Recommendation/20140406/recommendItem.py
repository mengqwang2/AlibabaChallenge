import os
import sys
import csv
import itemSimList
import filterCustRate
import opt

def recommendItem(rateList,rec_itemList):
	rec_userItem={}
	rec_items=[]
	for user,itemList in rateList.items():
		if user not in rec_userItem:
			rec_userItem[user]=[]
		for items in itemList:
			rec_items=rec_itemList[items]
			for rec_item in rec_items:
				rec_userItem[user].append(rec_item)
	return rec_userItem



if __name__=="__main__":
	#sys.argv[1] should be opt file name
	rateList=filterCustRate.filterCustRate("custRating.csv")
	rec_itemList=itemSimList.itemSimList("itemSim.csv")
	rec_userItem=recommendItem(rateList,rec_itemList)
	#print rec_userItem
	opt.opt(rec_userItem,sys.argv[1])