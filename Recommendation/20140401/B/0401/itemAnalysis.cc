#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct iteam{
	int bid;
	int m5[4],m6[4],m7[4],m8[4];
	int sum;
	int sold;
}iteams[100000];

int counts;

int getPos(int bid){
	for(int i=0;i<counts;i++){
		if(iteams[i].bid==bid)
			return i;
	}
	//count++;
	iteams[counts].bid=bid;
	return counts++;
}
int main(int argc,char** argv){
	counts=0;
	for(int i=0;i<100000;i++){
		iteams[i].bid=0;
		iteams[i].sum=0;
		iteams[i].sold=0;
		for(int j=0;j<4;j++){
			iteams[i].m5[j]=0;
			iteams[i].m6[j]=0;
			iteams[i].m7[j]=0;
			iteams[i].m8[j]=0;
		}
	}
	fstream data(argv[1]);
	int bid,type,date,currentPos;
	while(data>>bid>>type>>date){
		
		currentPos=getPos(bid);
		iteams[currentPos].sum++;
		if(type==1)
			iteams[currentPos].sold++;
		if(date<516)
			iteams[currentPos].m5[type]++;
		else if(date<616)
			iteams[currentPos].m6[type]++;
		else if(date<716)
			iteams[currentPos].m7[type]++;
		else if(date<816)
			iteams[currentPos].m8[type]++;
	}
	//cout<<count<<endl;
	for(int i=0;i<counts;i++){
		if(iteams[i].sum>1||iteams[i].sold>0){
			cout<<iteams[i].bid<<" ";
			cout<<iteams[i].m5[0]<<" "<<iteams[i].m5[1]<<" "<<iteams[i].m5[2]<<" "<<iteams[i].m5[3]<<" ";
			cout<<iteams[i].m6[0]<<" "<<iteams[i].m6[1]<<" "<<iteams[i].m6[2]<<" "<<iteams[i].m6[3]<<" ";
			cout<<iteams[i].m7[0]<<" "<<iteams[i].m7[1]<<" "<<iteams[i].m7[2]<<" "<<iteams[i].m7[3]<<" ";	
			cout<<iteams[i].m8[0]<<" "<<iteams[i].m8[1]<<" "<<iteams[i].m8[2]<<" "<<iteams[i].m8[3]<<"\n";
			}
		}
	return 0;
}