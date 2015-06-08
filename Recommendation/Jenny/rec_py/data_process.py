import sys
import os
import csv
import cust

class data_process(object):
	def __init__(self,inputFile,ratio0,ratio1,ratio2,ratio3,ratio999):
		self.__custList={}
		self.__ratioMapping={}
		self.__ratioMapping["0"]=ratio0
		self.__ratioMapping["1"]=ratio1
		self.__ratioMapping["2"]=ratio2
		self.__ratioMapping["3"]=ratio3
		self.__ratioMapping["999"]=ratio999
		self.__input=inputFile
	
	def action2rate(self):
		with open(self.__input,"rb") as f:
			reader=csv.reader(f,delimiter=" ")
			for row in reader:
				if (row[0] not in self.__custList):
					newCust=cust.cust(row[0])
					self.__custList[row[0]]=newCust
				self.__custList[row[0]].addScore(row[1],self.__ratioMapping[row[2]])
	
	def dataOutput(self):
		fileNew=open("../custRating.csv","w+")
		for cust in self.__custList:
			custObj=self.__custList[cust]
			for brand in custObj.getMap():
				fileNew.write(cust+","+brand+","+str(custObj.getMap()[brand])+"\n")

