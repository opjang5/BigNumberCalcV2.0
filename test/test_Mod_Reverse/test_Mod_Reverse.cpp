#include<stdio.h>
#include<BigNumberCalc2.h>
int strcmp2(char *a,char *b);
long long IsPrime(long long n);
long long GCD(long long a,long long b);
long long LCM(long long a,long long b); 
long long Mod_Reverse(long long a,long long b); 
int main(){
	int t=0;
	char zero[5]="+0";
  while(t<10000){
  	t++;
  	char a[1024];
    char b[1024];
    char ans2[1024];
    long long tmpa=(long long)(rand()%100001+60000)*(long long)(rand()%10001+6000);//1069909134
    long long tmpb=(long long)(rand()%100001+60000)*(long long)(rand()%10001+6000);//257655783
//    tmpa=909796444;tmpb=929265815;
//    printf("a:");
//    scanf("%lld",&tmpa);
//    printf("b:");
//    scanf("%lld",&tmpb);
    sprintf(a,"%lld",tmpa);
    sprintf(b,"%lld",tmpb);
	  printf("a:%s\n",a);
    printf("b:%s\n",b);
    sprintf(ans2,"%lld",Mod_Reverse(tmpa,tmpb));
//    printf("a:");
//    scanf("%s",a);
//    printf("b:");
//    scanf("%s",b);
    Nlink A=BigNumber_Trans(a);
    Nlink B=BigNumber_Trans(b);
    Nlink ans=BigNumber_Mod_Reverse(A,B);
    char *h=NULL;
	if(ans!=NULL)
    	h=BigNumber_out(ans);
    else 
    	h=zero;
    printf("ans:%s\n",h);
    printf("ans2:%s\n",ans2);
    if(strcmp2(ans2,h)!=0){
    	system("pause");
    	Nlink ans=BigNumber_Mod_Reverse(A,B);
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
long long GCD(long long a,long long b){
  long long r=0;
  long long tmpa=a,tmpb=b;
  if(a<b){
    tmpa=b;
    tmpb=a;
  }
  do {
    r=tmpa%tmpb;
    tmpa=tmpb;
    tmpb=r;
  } while(r>0);
  return tmpa;
}
long long LCM(long long a,long long b){
	return a*b/GCD(a,b);
}
long long Mod_Reverse(long long a,long long b){
  long long r=0;
  long long tmpa=a,tmpb=b;
  long long B[3]={0};
  B[1]=1;
  tmpa=b;tmpb=a;
  do {
    r=tmpa%tmpb;
    B[2]=B[0]-B[1]*(tmpa/tmpb);
    tmpa=tmpb;
    B[0]=B[1];
    tmpb=r;
    B[1]=B[2];
  } while(r>0);
  if(tmpa==1){
  	if(B[0]*a%b!=1 && (B[0]*a)%b+b!=1){
  		system("pause");
  		printf("#########################");
  	}
  	return B[0];
  }
  else{
  	return 0;
  }
} 
