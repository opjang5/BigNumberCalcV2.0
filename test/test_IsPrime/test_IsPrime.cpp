#include<stdio.h>
#include<BigNumberCalc2.h>
int strcmp2(char *a,char *b);
long long IsPrime(long long n);
int main(){
	int t=0;
  while(t<10000){
  	t++;
  	char a[1024];
    char b[1024];
    char ans2[1024];
    long long tmpa=(long long)(rand()%100001+600000)*(long long)(rand()%10001+60000);//1069909134
//    long long tmpb=(long long)rand()%2+2;//257655783
//    printf("a:");
//    scanf("%lld",&tmpa);
//    printf("b:");
//    scanf("%lld",&tmpb);
    sprintf(a,"%lld",tmpa);
//    sprintf(b,"%lld",tmpb);
	printf("a:%s\n",a);
//    printf("b:%s\n",b);
    sprintf(ans2,"%lld",IsPrime(tmpa));
//    printf("a:");
//    scanf("%s",a);
//    printf("b:");
//    scanf("%s",b);
    Nlink A=BigNumber_Trans(a);
//    Nlink B=BigNumber_Trans(b);
    bool ans=BigNumber_IsPrime(A);
    char h[10];
		if(ans){
			strcpy(h,"0");
		}
		else{
			strcpy(h,"-1");
		}
    printf("ans:%s\n",h);
    printf("ans2:%s\n",ans2);
    if(strcmp2(ans2,h)!=0){
    	system("pause");
    	bool ans=BigNumber_IsPrime(A);
    }
  	printf("%.2lf%%\n",(double)t/10000*100);
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
long long IsPrime(long long n){
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			return -1;
		}
	}
	return 0;
}
