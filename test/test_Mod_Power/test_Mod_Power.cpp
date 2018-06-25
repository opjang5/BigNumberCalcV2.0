#include<stdio.h>
#include<BigNumberCalc2.h>
int strcmp2(char *a,char *b);
long long Mod_Power(long long a,long long b,long long c); 
int main(){
	int t=0;
  while(t<10000){
  	t++;
  	char a[1024];
    char b[1024];
    char c[1024];
    char ans2[1024];
    long long tmpa=(long long)(rand()%100001+600000)*(long long)(rand()%100);//1069909134
    long long tmpb=(long long)rand()+1;//257655783
    long long tmpc=(long long)rand()%9+1;
//    tmpa=50521676 ;tmpb=22930 ;tmpc=9;
//    tmpa=998;tmpb=500; 
//	printf("a:");
//	scanf("%lld",&tmpa);
//	printf("b:");
//	scanf("%lld",&tmpb);
//	printf("c:");
//	scanf("%lld",&tmpc);
    sprintf(a,"%lld",tmpa);
    sprintf(b,"%lld",tmpb);
    sprintf(c,"%lld",tmpc);
	printf("a:%s\n",a);
    printf("b:%s\n",b);
    printf("c:%s\n",c);
    sprintf(ans2,"%lld",Mod_Power(tmpa,tmpb,tmpc));//tmpa=50521676 tmpb=22930 tmpc=9
//    printf("%s\n",ans2);
//    system("pause");
//    system("cls");
//    continue;
//    printf("a:");
//    scanf("%s",a);
//    printf("b:");
//    scanf("%s",b);
    Nlink A=BigNumber_Trans(a);
    Nlink B=BigNumber_Trans(b);
    Nlink C=BigNumber_Trans(c);
    Nlink ans=BigNumber_Mod_Power(A,B,C);
    char *h=BigNumber_out(ans);
    printf("ans:%s\n",h);
    printf("ans2:%s\n",ans2);
    if(strcmp2(ans2,h)!=0){
    	system("pause");
    	Nlink ans=BigNumber_Mod_Power(A,B,C);
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
long long Mod_Power(long long a,long long b,long long c){
	if(b==1)return a;
	if(b==0)return 1;
	return (Mod_Power(((a%c)*(a%c))%c,b/2,c)*(b%2?a:1))%c;
}
