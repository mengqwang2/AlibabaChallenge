import os
import sys
import csv
import userItems

def userCommonItems(fileName):
	commonItemFile=open("commonItems.csv","w+")
	userItemList=userItems.userItems(fileName,4,"1.log")
	userList=[]
	for users in userItemList:
		userList.append(users)
	i=0
	while (i<len(userList)):
		cur_user=userList[i]
		j=i+1
		while (j<len(userList)):
			commonItemFile.write(cur_user+",")
			cmp_user=userList[j]
			commonItemFile.write(cmp_user)
			for items in userItemList[cur_user]:
				if items in userItemList[cmp_user]:
					commonItemFile.write(","+items)
			commonItemFile.write("\n")
			j=j+1
		i=i+1

if __name__=="__main__":
	userCommonItems(sys.argv[1])
