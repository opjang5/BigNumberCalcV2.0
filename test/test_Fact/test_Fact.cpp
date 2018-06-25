#include<stdio.h>
#include<BigNumberCalc2.h>
//#include<BigNumberCalc.h>
#include<stdlib.h>
#include<time.h>
int strcmp2(char *a,char *b);
long long Fact(long long n);
int main(){
	srand(time(0));
	int t=0;
  while(true){
  	t++;
  	char a[1024];
    char b[1024];
    char ans2[1024];
    long long tmpa;//(long long)(rand()%10001+60000)*(long long)(rand()%10001+6000);//1002705235
    // long long tmpb=(long long)(rand()%10001+60000)*(long long)(rand()%10001+6000);//1042448616
//    tmpa=1002705235;tmpb=1042448616;
    printf("a:");
    scanf("%lld",&tmpa);
    fflush(stdin);
    sprintf(a,"%lld",tmpa);
    // sprintf(b,"%lld",tmpb);
    sprintf(ans2,"%lld",Fact(tmpa));
//    printf("a:");
//    scanf("%s",a);
//    printf("b:");
//    scanf("%s",b);
    Nlink A=BigNumber_Trans(a);
    Nlink B=BigNumber_Trans(b);
    printf("a:%s\n",a);
//    printf("b:%s\n",b);
    Nlink ans=BigNumber_Fact(tmpa);
    char *h=BigNumber_out(ans);
    printf("ans:%s\n",h);
    printf("ans2:%s\n",ans2);
    if(strcmp2(ans2,h)!=0){
    	system("pause");
    	Nlink ans=BigNumber_Fact(tmpa);
    }
//  	printf("%.2lf%%\n",(double)t/10000*100);
  }
  system("pause");
}
int strcmp2(char *a,char *b){
	int lena=strlen(a);
	int lenb=strlen(b);
	if(a[0]!='-'){
		if(lena+1!=lenb)
			return -1;
		for(int i=0;i<lena;i++){
			if(a[i]!=b[i+1]){
				return -1;
			}
		}
	}
	else{
		if(lena!=lenb)
			return -1;
		for(int i=0;i<lena;i++){
			if(a[i]!=b[i]){
				return -1;
			}
		}
	}
	return 0;
}
long long Fact(long long n){
	if(n==0)return 1;
	return Fact(n-1)*n;
}
