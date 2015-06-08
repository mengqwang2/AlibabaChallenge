import sys
import os
import data_process


if __name__=="__main__":
	filepath="/Users/mengqwang/Documents/tMall/clean_t_alibaba_data.csv"
	ratio0=int(sys.argv[1])
	ratio1=int(sys.argv[2])
	ratio2=int(sys.argv[3])
	ratio3=int(sys.argv[4])
	ratio4=int(sys.argv[5])
	dp=data_process.data_process(filepath,ratio0,ratio1,ratio2,ratio3,ratio4)
	dp.action2rate()
	dp.dataOutput()
