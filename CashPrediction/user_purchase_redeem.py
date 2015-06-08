import os
import csv


def inSameMonth(date1,date2):
	y1=date1/10000
	y2=date2/10000
	m1=(date1%10000)/100
	m2=(date2%10000)/100
	d1=date1%1000000
	d2=date2%1000000

	if(y1==y2 and m1==m2):
		return 1
	else:
		return 0

def getym(dat):
	return dat/100

if __name__=="__main__":
	users=dict()
	
	with open('test.csv','rb') as csvfile:
		csvReader=csv.reader(csvfile,delimiter=',')
		for row in csvReader:
			if(row[0] not in users):
				users[row[0]]=dict()

			datrec=getym(int(row[1]))
			if (datrec not in users[row[0]]):
				users[row[0]][datrec]=dict()

			if('purchase' not in users[row[0]][datrec]):
				users[row[0]][datrec]['purchase']=list()

			if('redeem' not in users[row[0]][datrec]):
				users[row[0]][datrec]['redeem']=list()
			
			users[row[0]][datrec]['purchase'].append(int(row[4]))
			users[row[0]][datrec]['redeem'].append(int(row[8]))
	
	optFile=open("users.csv",'w+')
	for k,v in users.iteritems():
		for ym,amt in v.iteritems():
			optFile.write(str(k)+","+str(ym)+","+str(sum(amt['purchase']))+","+str(sum(amt['redeem']))+"\n")

	optFile.close()

	
