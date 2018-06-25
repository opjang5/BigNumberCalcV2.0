#include<stdio.h>
#include<BigNumberCalc2.h>
int strcmp2(char *a,char *b);
int main(){
	int t=0;
  while(t<10000){
  	t++;
  	char a[1024];
    char b[1024];
    char ans2[1024];
    long long tmpa=(long long)(rand()%100001+600000)*(long long)(rand()%10001+60000);//1069909134
    long long tmpb=(long long)(rand()%100001+600000)*(long long)(rand()%10001+60000);//257655783
    sprintf(a,"%lld",tmpa);
    sprintf(b,"%lld",tmpb);
    sprintf(ans2,"%lld",tmpa+tmpb);
//    printf("a:");
//    scanf("%s",a);
//    printf("b:");
//    scanf("%s",b);
    Nlink A=BigNumber_Trans(a);
    Nlink B=BigNumber_Trans(b);
    Nlink ans=BigNumber_Plus_Son(A,B);
    char *h=BigNumber_out(ans);
    printf("a:%s\n",a);
    printf("b:%s\n",b);
    printf("ans:%s\n",h);
    printf("ans2:%s\n",ans2);
    if(strcmp2(ans2,h)!=0){
    	system("pause");
    	Nlink ans=BigNumber_Plus_Son(A,B);
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
