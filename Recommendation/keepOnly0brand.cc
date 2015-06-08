#include <iostream>
#include <fstream>
#include <string.h> 
using namespace std;

int main(int argc, char** argv){
	ifstream file(argv[1]);
	ifstream data(argv[2]);
	int bids[30000];
	int bid,type;
	memset(bids,0,30000);
	while(file>>bid>>type){
		if(type!=0)
			bids[bid]=1;
	}
	int uid,day;
	while(data>>uid>>bid>>type>>day){
		if(bids[bid]==0)
			cout<<uid<<" "<<bid<<" "<<type<<" "<<day<<endl;
	}
	return 0;
}

