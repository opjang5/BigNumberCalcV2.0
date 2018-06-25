#include<stdio.h>
#include<BigNumberCalc2.h>
#include<time.h>
int strcmp2(char *a,char *b);
long long power(long long a,long long b);
int main(){
	srand(time(0));
	double start=0.0f;
	double finish=0.0f;
	int t=0;
  while(t<10000){
  	t++;
  	char a[1024];
    char b[1024];
    char ans2[1024];
    long long tmpa=(long long)rand();//1069909134
    long long tmpb=(long long)rand()%2+2;//257655783
//    tmpa=2;tmpb=64;
    printf("a:");
    scanf("%lld",&tmpa);
    printf("b:");
    scanf("%lld",&tmpb);
    sprintf(a,"%lld",tmpa);
    sprintf(b,"%lld",tmpb);
//	printf("a:%s\n",a);
//    printf("b:%s\n",b);
//    sprintf(ans2,"%lld",power(tmpa,tmpb));
//    printf("a:");
//    scanf("%s",a);
//    printf("b:");
//    scanf("%s",b);
    Nlink A=BigNumber_Trans(a);
    Nlink B=BigNumber_Trans(b);
    Nlink ans=BigNumber_Power_Positive(A,B);
    char *h=BigNumber_out(ans);
    printf("ans:%s\n",h);
    Nlink C=NULL;
    Nlink one=BigNumber_Long2Nlink(1);
	Nlink two=BigNumber_Long2Nlink(2);
	C=BigNumber_Plus(ans,one);
    start=clock();
    while(true){
    	 C=BigNumber_Rand(ans);
//			C=BigNumber_Plus(C,two);
//		Nlink C=BigNumber_Trans("7");
    	char *h=BigNumber_out(C);
    	int len=strlen(h);
		if(len<=20)continue;
		printf("%s\n",h);
		double ansC=BigNumber_IsPrime_Fermat(C,4);
		if(ansC>0.85){
			finish=clock();
			system("cls");
			printf("ans:%s\n",h);
			printf("找到！");
			printf("用时%.2lf",(finish-start)/CLOCKS_PER_SEC);
			system("pause");
			/* 建立一个质数库 */
		}
		else{
			continue;
		}
    }

    h=BigNumber_out(ans);
    printf("ans:%s\n",h);
    printf("ans2:%s\n",ans2);
    if(strcmp2(ans2,h)!=0){
    	system("pause");
    	Nlink ans=BigNumber_Power_Positive(A,B);
    }
  	printf("%.2lf%%\n",(double)t/10000*100);
  }
  system("pause");
}
int strcmp2(char *a,char *b){
	int lena=strlen(a);
	int lenb=strlen(b);
	if(lena+1!=lenb)
		return -1;
	for(int i=0;i<lena;i++){
		if(a[i]!=b[i+1]){
			return -1;
		}
	}
	return 0;
}
long long power(long long a,long long b){
	long long ans=1;
	for(long long i=0;i<b;i++){
		ans=ans*a;
	}
	return ans;
}
