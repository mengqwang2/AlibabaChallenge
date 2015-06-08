#include "math.h"
#include "string.h"
#include "stdlib.h" 
#include "stdio.h"
#include "iostream.h"
#include "time.h"         //ʹ�õ�ǰʱ��������



FILE *fp;
const int usersum = 6040;
const int itemsum = 3952;
const int N = 10;
char datasetfile[100] = "E:\\mytest\\ratings.dat"; 
int train[itemsum][usersum]={0};	//ѵ������user item rate����
int test[itemsum][usersum]={0};    //���Լ���user item rate����
double trainuseritem[usersum][itemsum]={0.0};//ѵ������user item ��Ȥ�̶� ����
int recommend[usersum][N]={0};  //Ϊÿ���û��Ƽ�N����Ʒ
struct simi
{
	double value; //����ֵ 
	int num;	 //������Ʒ�� 
};
simi simiItem[itemsum][itemsum]; //�����������Ծ���

//��һ����������ݼ�Ϊ���Լ�test��ѵ����train������1/mΪ���Լ�,ȡ��ͬ��k<=m-1ֵ ����ͬ���漴�����¿ɵõ���ͬ�Ĳ�/ѵ����
int SplitData(int m, int k);
//Ѱ�����ݼ�ÿ����¼��Ӧ���û��ź���Ʒ��
int Buf_UIR(char* buf,int* user, int* item);
double Simility(int* ItemA, int* ItemB);    //�ڶ�����������Ʒ֮��������ԣ������Ʒ�����Ծ���
int sort(double* simArr, simi* simStruct); //����������Ʒ�����Ծ������򣨸����������ɸߵ�������
double getUserLikeItem(int i,int j,int k); //���Ĳ����õ��û�i����ƷjԤ����Ȥ�̶ȣ�����k�������������
int getRecommend();                       //���岽��ͨ����Ʒ��Ȥ�̶ȣ��Ƽ�ǰN��
double Recall();                           //�������������ٻ��ʡ�׼ȷ�ʺ͸�����
double Precision();
double Coverage();
double Diversity(double **a);//���������

int main()
{
	int i,j;
	double recall,precision,coverage,diversity;
	int k;        //ȥ�û���k������ھ��������Ƽ���Ʒ
	printf("������ȡ����ھ�������ĸ�����k=");
	scanf("%d",&k);
    //1.��ʼ�����ݼ�
	SplitData(8,1); //�漴����1/8Ϊ���Լ�������Ϊѵ����
    //�����ʼ���ľ���	
	/*
	for (i=0;i<5;i++)
 	{
 		cout<<"Item"<<i<<":   "<<endl;
 		for (j=0;j<100;j++)
 		{
 			cout<<train[i][j]<<"  ";
 		}
 		cout<<endl;
 	}
	*/

	//��̬�����ڴ�ռ������Ʒ�����Ծ���
	double **itemsim;
	itemsim = (double**)malloc(sizeof(double*)*itemsum);
    for(i=0; i<itemsum; i++ )
	{
        itemsim[i] = (double*)malloc(sizeof(double)*itemsum);
    }
	//2.������Ʒ֮�������ԣ��õ������Ծ���
	for (i=0;i<itemsum;i++)
	{
		for (j=0;j<itemsum;j++)
		{
			itemsim[i][j] = Simility(train[i],train[j]);
		}
	}
	//�����Ʒ�����Ծ���	
	/*
	for (i=0;i<5;i++)
 	{
 		cout<<"Item"<<i<<":   "<<endl;
 		for (j=0;j<100;j++)
 		{
 			cout<<itemsim[i][j]<<"  ";
 		}
 		cout<<endl;
 	}
	*/

	//3.��Ʒ���ƶ��ɸߵ�������
	for (i=0;i<itemsum;i++)
	{
		//cout<<"Item"<<i<<":   "<<endl;
		sort(itemsim[i],simiItem[i]);
		//cout<<endl;
	}
    //�����������Ʒ�����Ծ���
	/*
	for(i=0;i<5;i++)
	{
		cout<<"item"<<i<<":  "<<endl;
		for(j=0;j<100;j++)
		{
			cout<<simiItem[i][j].num<<","<<simiItem[i][j].value<<"  ";
		}
		cout<<endl;
	}
    */
    //4.�õ��û�����Ʒ��Ȥ�̶ȵľ���
	for(i=0;i<usersum;i++)
	{
		for(j=0;j<itemsum;j++)
		{
			if(train[j][i]==0)            //����û�i����Ʒjû�й���Ϊ���ż���i��j��Ԥ����Ȥ�̶�
		    	trainuseritem[i][j]=getUserLikeItem(i,j,k);
		}
	}
	//����û�����Ʒ��Ȥ�ľ���
	/*
	for (i=0;i<5;i++)
 	{
 		cout<<"User"<<i<<":   "<<endl;
 		for (j=0;j<100;j++)
 		{
 			cout<<trainuseritem[i][j]<<"  ";
 		}
 		cout<<endl;
 	}
	*/

	//5.ͨ����Ʒ��Ȥ�̶ȣ��Ƽ�ǰN��
	getRecommend();
	//����Ƽ�����
	for (i=0;i<5;i++)
 	{
 		cout<<"User"<<i<<":   "<<endl;
 		for (j=0;j<N;j++)
 		{
 			cout<<recommend[i][j]<<"  ";
 		}
 		cout<<endl;
 	}

    recall=Recall();	//�����ٻ���
	printf("�ٻ���recall=%lf ",recall);
	precision=Precision();//����׼ȷ��
	printf("׼ȷ��precision=%lf ",precision);
	coverage=Coverage();//���㸲����
    printf("������coverage=%lf ",coverage);
    diversity=Diversity(itemsim);//���������
	printf("������diversity=%lf ",diversity);

	//�ͷ��ڴ� 
	for( i=0; i<itemsum; i++ )
	{
        free(itemsim[i]);
    }
	free(itemsim);

	return 1;
}

//������ݼ�Ϊ���Լ�test��ѵ����trainuser������1/mΪ���Լ�,ȡ��ͬ��k<=m-1ֵ ����ͬ���漴�����¿ɵõ���ͬ�Ĳ�/ѵ����
int SplitData(int m, int k)
{
	fp=fopen(datasetfile,"r");
	char tmpbuf[100];		//�ݴ��ļ�һ�м�¼
	int usernum;
	int itemnum;

	if (!fp)
	{
		cout<<"open datasetfile failed";
		return 1;
	}
	else
	{
		srand((unsigned)time(NULL));                  //���õ�ǰʱ��Ϊ�������
		while (!feof(fp))
		{
			fgets(tmpbuf,100,fp);                     //��fpָ��ĵ�ǰ��¼�浽tmpbuf[100]
		    Buf_UIR(tmpbuf,&usernum,&itemnum);        //Ѱ�����ݼ�ÿ����¼��Ӧ���û��ź���Ʒ��
			if (usernum<=usersum&&itemnum<=itemsum)
			{
				if(rand()%(m-1)==k)                       //�ж��������0-7֮���������Ƿ����k
				   test[itemnum-1][usernum-1] = 1;        //rateΪ���֣��ٴ�ʵ����ֻ��ͳ���������ֵģ��������۾�������
			    else 
				   train[itemnum-1][usernum-1] = 1;  //�û��ŵ���Ʒ�ž���0��ʼ����
			}
		}
 		fclose(fp);
	}
	return 1;
}
//Ѱ�����ݼ�ÿ����¼��Ӧ���û��ź���Ʒ��
int Buf_UIR(char* buf,int* user, int* item)
{
	char U[20]={0};
	char I[20]={0};
	char R[20]={0};
	char *Temp;
	int curpos;

		//�����û���
		Temp = strchr(buf,':');
		curpos = Temp-buf;
		strncpy(U,buf,curpos);
		*user = atoi(U);
		//����item��
		Temp = strchr(buf+curpos+2,':');
		//curpos = Temp - buf;
		strncpy(I,buf+curpos+2,Temp-buf-curpos-2);
		*item = atoi(I);

	return 1;
}

//����ѵ���������û�֮�����ƶ�
/* ��������ItemA��ItemB�������ԣ�����ֵΪItemA��ItemB�����ƶ� */
double Simility(int* ItemA, int* ItemB)
{
	int comUser = 0;                   //ItemA��ItemB�Ķ����û����۵��û�����
	double simility = 0.0;
	int countIa = 0;
	int countIb = 0;
	
	int i;
	for (i=0;i<itemsum;i++)
	{
		if (ItemA[i]>0&&ItemB[i]>0)
		{
			comUser++;//����ItemA��ItemB�Ķ����û����۵��û�����
		}
		if (ItemA[i]>0){
			countIa++;//����ItemA���û�����
		}
		if (ItemB[i]>0){
			countIb++;//����ItemB���û�����
		}
	}
	double tem = sqrt(countIa*countIb);
	if(tem == 0)
	{
		return 0;
	}
	else
	{
    	simility = comUser/tem;
	    return simility;
	}
}


/*��Ʒ�����Ծ������򣨸����������ɸߵ������򣩣�ÿ�е�һ�����Լ�*/
#include <algorithm>
struct SimiLessComp {
	bool operator () (const simi& a, const simi& b) const {
		return a.value > b.value;
	}
};


int sort(double* simArr,simi* simStruct)
{
#if 1
	for(int i = 0; i < itemsum; ++i)
		(simStruct[i].num = i), (simStruct[i].value = simArr[i]);
	std::sort(simStruct, simStruct + itemsum, SimiLessComp() );

	return 1;

#else
	int finflag[itemsum] = {0};//�Ƿ����ź����ʾ
	int maxnum;//��ǰ�����
	int m=0,t;

		for (int i=0;i<itemsum;i++)
		{ 
			t=0;                  //������Ѱ�ҵ�һ�� û�б�����õ��û���
			while(finflag[t]!=0)  //����ѱ�����
	     		t++;
			maxnum = t;                    //����������ƶ���Ʒ�š�
			for (int j=0;j<itemsum;j++)
			{
				if (simArr[j]>simArr[maxnum] && finflag[j]==0)
				{
					maxnum = j;
				}
			}
			simStruct[m].num = maxnum;
			simStruct[m].value = simArr[maxnum];
			finflag[maxnum] = 1;             //����ѭ��������ƶ���Ʒ����Ѿ�����
			m++;
		  //cout<<i<<":"<<maxnum<<":"<<simArr[maxnum]<<"  ";

		}

	return 1;
#endif
}

//�õ��û�i����ƷjԤ����Ȥ�̶ȣ������Ƽ�
double getUserLikeItem(int i,int j,int k)
{
	for(int x=1;x<=k;x++)//����Ʒj�����Ƶ�k����Ʒ�У��ҳ��û�i�й���Ϊ����Ʒ,��Ϊ��һ��simiItem[][]��ÿ�е�һ����ŵ����Լ������Դӵڶ�����ʼ�㣬x=1
	{
		if(train[simiItem[j][x].num][i]>0)//������û�ͬ����������ƷҲ�й���Ϊ
		{
			trainuseritem[i][j]+=simiItem[j][x].value;
		}
	}
	return trainuseritem[i][j];
}
/*ͨ����Ʒ��Ȥ�̶ȣ��Ƽ�ǰN��*/
int getRecommend()
{
	int maxnum;//��ǰ�����Ȥ��Ʒ��
	for(int i=0;i<usersum;i++)
	{
		int finflag[itemsum] = {0};//�Ƿ����ź����ʾ
		for (int x=0;x<N;x++)//�Ƽ�N��
		{
			maxnum=0;
			while(finflag[maxnum]!=0)  //�жϴ˴�ѭ���ĵ�һ��δ���������Ʒ
				maxnum++;
			for (int j=0;j<itemsum;j++)  //ÿѭ��һ�ξ�Ѱ�Ҵ˴θ���Ȥ������Ʒ
			{
				if (trainuseritem[i][maxnum]<trainuseritem[i][j]&&finflag[j]==0)
				{
					maxnum = j;
				}
			}
			finflag[maxnum] = 1;
			recommend[i][x]=maxnum;//recommend�����0��ʼʹ��
		}
	}
	return 1;
}


//�����ٻ���
double Recall()   //test[usersum][itemsum], recommend[usersum][N],NΪ�Ƽ���
{
	int i,j,k,tnum=0,rnum=0,count[usersum]={0};  //tnumΪ���Լ���ϲ������Ʒ����;count[i]Ϊ��i���û����Ƽ��������Լ������е���Ʒ����������rnumΪ�ܹ����е���Ʒ����
	for(i=0;i<usersum;i++)
	{
		for(j=0;j<itemsum;j++)
		{
			if(test[j][i]!=0)          //����û�i����Ʒj����Ȥ
			{
				tnum++;
			    for(k=0;k<N;k++)
				{
			    	if(recommend[i][k]==j)    //�û�i����Ʒj����Ȥ��ͬʱ����Ʒj���Ǳ��Ƽ�����Ʒ
				    	count[i]++;
				}
			}
		}
		rnum=rnum+count[i];
	}
	return rnum/(tnum*1.0);
}
//����׼ȷ��
double Precision()   //test[usersum][itemsum], recommend[usersum][N],NΪ�Ƽ���
{
	int i,j,k,rnum=0,count[usersum]={0};  //count[i]Ϊ��i���û����Ƽ��������Լ������е���Ʒ������rnumΪ�ܹ����е���Ʒ����
	for(i=0;i<usersum;i++)
	{
		for(j=0;j<itemsum;j++)
		{
			if(test[j][i]!=0)          //����û�i����Ʒj����Ȥ
			{
			    for(k=0;k<N;k++)
				{
			    	if(recommend[i][k]==j)    //�û�i����Ʒj����Ȥ��ͬʱ����Ʒj���Ǳ��Ƽ�����Ʒ
				    	count[i]++;
				}
			}
		}
		rnum=rnum+count[i];
	}
	return rnum/(N*usersum*1.0);
}
//���㸲����
double Coverage()
{
	int i,j,k,sum=0,count[itemsum]={NULL};  ////count[i]��=NULL��ʾ��i����Ʒ��������,sumͳ�Ʊ����ǵ���Ʒ����
	for(i=0;i<usersum;i++)
	{
		for(j=0;j<N;j++)
		{
            k=recommend[i][j];      // k=�Ƽ����û�i�ĵ�j����Ʒ����Ʒ��
			if(count[k]==NULL)      //�жϵ�k����Ʒ�Ƿ��Ѿ�����
			{
				count[k]=1;
				sum++;
			}
		}
	}
	return sum/(itemsum*1.0);
}
//���������
double Diversity(double **a)
{
	double diversity,count=0,sum=0;   //count��Ŷ�ÿһ���û��Ƽ�����Ʒ֮���������ֵ��sum��������Ƽ���Ʒ��������ֵ�ܺ�
	for(int i=0;i<usersum;i++)
	{
		for(int j=0;j<N;j++)
		{
			for(int k=j+1;k<N;k++)
			{
				count=count+a[recommend[i][j]][recommend[i][k]];
			}
		}
		sum=sum+1-2*count/(N*(N-1));  //��ÿ���û��Ķ�����ֵ�ۼӵ�sum
		count=0;
	}
	diversity=sum/usersum;
	return diversity;
}


