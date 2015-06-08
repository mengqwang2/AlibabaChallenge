import os
import sys
import csv
import userItems
import collections

def dupItems(fileName):
	p_largerthan1={}
	userItems1=userItems.userItems(fileName,"1","userItem1.csv")
	for user,brand in userItems1.items():
		dupItems=[k for k, v in collections.Counter(brand).items() if v>1]
		p_largerthan1[user]=dupItems

	optFile=open("dupPurchaseItems.txt","w+")
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
	dupItems(sys.argv[1])