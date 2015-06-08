import os
import sys


class cust(object):
	def __init__(self,custid):
		self.__custId=custid
		self.__actionScore=0
		self.__brandScore={}

	def addScore(self,brandId,score):
		if (brandId not in self.__brandScore):
			self.__brandScore[brandId]=0
		self.__brandScore[brandId]+=score

	def getMap(self):
		return self.__brandScore
