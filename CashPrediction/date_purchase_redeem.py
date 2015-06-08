import os
import csv


if __name__=="__main__":
	dates=dict()
	
	with open('test.csv','rb') as csvfile:
		csvReader=csv.reader(csvfile,delimiter=',')
		for row in csvReader:
			if(row[1] not in dates):
				dates[row[1]]=list()
				dates[row[1]].append(0)
				dates[row[1]].append(0)

			dates[row[1]][0]+=int(row[4])
			dates[row[1]][1]+=int(row[8])


	optFile=open("dates.csv",'w+')
	for k,v in dates.iteritems():
		optFile.write(str(k)+","+str(v[0])+","+str(v[1])+"\n")

	optFile.close()