import os
import sys
import csv

def ratio4actions(filename):
	user_action={}
	userlist={}
	with open(filename,"rb") as f:
		csvFile=csv.reader(f,delimiter=",")
		for row in csvFile:
			if row[0]!="user_id":
				if row[0] not in userlist:
					userlist[row[0]]={}
					user_action={
					't0':0,
					't1':0,
					't2':0,
					't3':0
					}
				keyName='t'+row[2]
				user_action[keyName]=user_action[keyName]+1
				userlist[row[0]]=user_action
	return userlist
	
if __name__=="__main__":
	userlist=ratio4actions(sys.argv[1])
	optFile=open("ratioOf4Actions.csv","w+")
	for key,value in userlist.items():
		optFile.write(key+","+str(value['t0'])+","+str(value['t1'])+","+str(value['t2'])+","+str(value['t3'])+"\n")

					
				
			
