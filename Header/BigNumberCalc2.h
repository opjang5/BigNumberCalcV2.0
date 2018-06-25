#ifndef _BigNumberCalc_2_H_
#define _BigNumberCalc_2_H_
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
// #include<queue>
#include<stack>
#include<ctype.h>
#include<math.h>
#define LIMIT 1000000000
using namespace std;
typedef struct Number_son{
  long long data;
  int power;
}Num_son,*Nslink;
typedef struct Number{
  char symbol;
  long long data;
  int power;
  struct Number* Next;
  // struct Number* Rear;
}Num,*Nlink;
Nlink BigNumber_DIV_Integer(Nlink a,Nlink b);
Nlink BigNumber_Mod_Son(Nlink a,Nlink b);
Nlink BigNumber_Mul_Son(Nlink a,Nlink b);
char BigNumber_Reverse(char n){
  if(n=='+')
    return '-';
  else if(n=='-')
    return '+';
  return n;
}
void BigNumber_Destory(Nlink a){
  if(a!=NULL){
  	  Nlink H=a;
	  Nlink p=H->Next;
	  while(p!=NULL){
	    Nlink backup=p;
	    p=p->Next;
	    free(backup);
	  }
	  free(H);
  }

}
void BigNumber_Init(Nlink a){
  Nlink ans=a;
  ans->symbol='+';
  ans->data=-1;ans->power=-1;ans->Next=NULL;
}
void BigNumber_Set(Nlink a,long long data,int power){
  Nlink ans=a;
  ans->symbol='+';
  ans->data=data;ans->power=power;ans->Next=NULL;
}
/* 将一个长整型数字转换为Nlink */
Nlink BigNumber_Long2Nlink(long long data){
  Nlink i=(Nlink)malloc(sizeof(Num));
  BigNumber_Init(i);
  long long tmp=data;
  int power=0;
  if(data>=0)
    i->symbol='+';
  else
    i->symbol='-';
  do{
    int A=tmp%LIMIT;
    tmp=tmp/LIMIT;
    Nlink p=(Nlink)malloc(sizeof(Num));
    BigNumber_Set(p,A,power);
    power++;
    p->symbol=i->symbol;
    p->Next=i->Next;
    i->Next=p;
  }while(tmp!=0);
  return i;
}
/* 把b拷贝到a中,a=NULL */
void BigNumber_CPY(Nlink* a,Nlink b){
  *a=(Nlink)malloc(sizeof(Num));
  Nlink p=b->Next;
  Nlink q=*a;
  q->symbol=b->symbol;
  q->data=b->data;
  q->power=b->power;
  q->Next=NULL;
  while(p!=NULL){
    Nlink tmp=(Nlink)malloc(sizeof(Num));
    tmp->symbol=p->symbol;
    tmp->data=p->data;
    tmp->power=p->power;
    tmp->Next=NULL;
    q->Next=tmp;
    q=q->Next;
    p=p->Next;
  }
}
/* 比较两个数字大小 */
int BigNumber_CMP(Nlink a,Nlink b){
  if(a->symbol!=b->symbol){
    if(a->symbol=='+')//a>0 b<0
      return 1;
    else
      return -1;//a<0 b>0
  }
  if(a->Next->power!=b->Next->power){
    if(a->Next->power>b->Next->power){//|a|>|b|
      if(a->symbol=='+')//
        return 1;
      else
        return -1;
    }
    else{//|a|<|b|
      if(a->symbol=='+')
        return -1;
      else
        return 1;
    }
  }
  int end=a->Next->power+1;
  Nlink p=a->Next,q=b->Next;
  for(int i=0;i<end;i++){
    if(p->data>q->data)
      return 1;
    else if(p->data<q->data)
      return -1;
    p=p->Next;q=q->Next;
  }
  return 0;
}
/* 由char*转换为Nlink */
Nlink BigNumber_Trans(char *a){
  Nlink H=(Nlink)malloc(sizeof(Num));
  H->data=-1;H->power=-1;H->Next=NULL;//H->Rear=H;
  char symbol;
  int end=0;
  if(a[0]=='-'){
    symbol='-';
    end=1;
  }
  else{
    symbol='+';
    end=0;
  }
  H->symbol=symbol;
  int lena=strlen(a);
  stack<char> Sc,Sc2;
  int power=0;
  for(int i=lena-1;i>=end;i--){
    Sc.push(a[i]);
    if(Sc.size()==9){
      int tmp=0;
      for(int i=0;i<9 && !Sc.empty();i++){
        char c=Sc.top();Sc.pop();
        if(isdigit(c)){
          tmp=tmp*10+c-'0';
        }
      }
      Nlink p=(Nlink)malloc(sizeof(Num));
      p->symbol=H->symbol;
      p->data=tmp;
      p->power=power;
      p->Next=H->Next;
      H->Next=p;
      // H->Rear->Next=p;
      // H->Rear=p;
      power++;
    }
  }
  // int power=ceil((double)lena/9)-1;
  while(!Sc.empty()){
    long long tmp=0;
    for(int i=0;i<9 && !Sc.empty();i++){
      char c=Sc.top();Sc.pop();
      if(isdigit(c)){
        tmp=tmp*10+c-'0';
      }
    }
    Nlink p=(Nlink)malloc(sizeof(Num));
    p->symbol=H->symbol;
    p->data=tmp;
    p->power=power;
    p->Next=H->Next;
    H->Next=p;
    // H->Rear->Next=p;
    // H->Rear=p;
    power++;
  }
  return H;
}
/* 由Nlink转换为char * */
char *BigNumber_out(Nlink H){
    char **ans=(char **)calloc(H->Next->power+2,sizeof(char*));
    for(int i=0;i<H->Next->power+2;i++){
      ans[i]=(char *)calloc(15,sizeof(char));
    }
    int i=0;
    sprintf(ans[i++],"%c",H->symbol);
    Nlink p=H->Next;
    while (p!=NULL) {
      if(p==H->Next)
      	sprintf(ans[i++],"%lld",p->data);
      else
      	sprintf(ans[i++],"%09lld",p->data);
      p=p->Next;
    }
    char *ans2=(char *)calloc((H->Next->power+2)*9,sizeof(char));
    int ans2num=0;
    for(int j=0;j<i;j++){
      int lentmp=strlen(ans[j]);
      for(int k=0;k<lentmp;k++){
        ans2[ans2num++]=ans[j][k];
      }
    }
    ans2[ans2num]='\0';
    for(int i=0;i<H->Next->power+2;i++){
      free(ans[i]);
    }
    free(ans);
    return ans2;
}
/* 计算绝对值 */
/* 把a改为绝对值 */
void BigNumber_ABS(Nlink a){
  Nlink p=a;
  while(p!=NULL){
    p->symbol='+';
    p=p->Next;
  }
}
/* a>=0 b>=0 a+b */
Nlink BigNumber_Plus_Son(Nlink a,Nlink b){
  Nlink ans=(Nlink)malloc(sizeof(Num));
  ans->symbol='+';
  ans->data=-1;ans->power=-1;ans->Next=NULL;//fans->Rear=ans;
  stack<long long>Sa,Sb;
  Nlink p=a->Next;
  while(p!=NULL){
    Sa.push(p->data);
    p=p->Next;
  }
  p=b->Next;
  while(p!=NULL){
    Sb.push(p->data);
    p=p->Next;
  }
  int lena=a->Next->power+1;
  int lenb=b->Next->power+1;
  int lenans=max(lena,lenb);
  long long A=0;long long B=0;long long C=0;
  long long sum=0;int power=0;
  for(int i=0;i<lenans;i++){
    A=0;B=0;sum=0;
    if(!Sa.empty()){
      A=Sa.top();
      Sa.pop();
    }
    if(!Sb.empty()){
      B=Sb.top();
      Sb.pop();
    }
    sum=A+B+C;
    if(sum<LIMIT){
      Nlink p=(Nlink)malloc(sizeof(Num));
      p->symbol=ans->symbol;
      p->data=sum;
      p->power=power;
      p->Next=NULL;
      p->Next=ans->Next;
      ans->Next=p;
      power++;
      C=0;
    }
    else if(sum>=LIMIT){
      Nlink p=(Nlink)malloc(sizeof(Num));
      p->symbol=ans->symbol;
      p->data=sum-LIMIT;
      p->power=power;
      p->Next=NULL;
      p->Next=ans->Next;
      ans->Next=p;
      power++;
      C=sum/LIMIT;
    }
  }
  if(C>0){
    Nlink p=(Nlink)malloc(sizeof(Num));
    p->symbol=ans->symbol;
    p->data=C;
    p->power=power;
    p->Next=NULL;
    p->Next=ans->Next;
    ans->Next=p;
    power++;
    C=0;
  }
  // p=ans->Next;
  // while(p!=NULL){
  //   if(p->Next==NULL){
  //     ans->Rear=p;
  //   }
  //   p=p->Next;
  // }
  return ans;
}

/* 计算a-b */
/* a>0 b>0 */
Nlink BigNumber_Minus_Son(Nlink a,Nlink b){
  int CMP=0;
  CMP=BigNumber_CMP(a,b);
  Nlink tmpa=NULL,tmpb=NULL;
  Nlink ans=(Nlink)malloc(sizeof(Num));
  ans->data=-1;ans->power=-1;ans->Next=NULL;
  if(CMP==0){
    Nlink zero=(Nlink)malloc(sizeof(Num));
    zero->Next=(Nlink)malloc(sizeof(Num));
    zero->Next->symbol='+';
    zero->Next->data=0;
    zero->Next->power=0;
    zero->Next->Next=NULL;
    zero->symbol='+';
    zero->data=-1;
    zero->power=-1;
    BigNumber_Destory(ans);
    return zero;
  }
  else if(CMP==1){
    /* a>b */
    tmpa=a;
    tmpb=b;
    ans->symbol='+';
  }
  else if(CMP==-1){
    /* a<b */
    tmpa=b;
    tmpb=a;
    ans->symbol='-';
  }
  stack<long long>Sa,Sb;
  Nlink p=tmpa->Next;
  while(p!=NULL){
    Sa.push(p->data);
    p=p->Next;
  }
  p=tmpb->Next;
  while(p!=NULL){
    Sb.push(p->data);
    p=p->Next;
  }
  int end=tmpa->Next->power+1;
  long long A=0;long long B=0;
  int power=0;
  for(int i=0;i<end;i++){
    A=0;B=0;
    if(!Sa.empty()){
      A=Sa.top();
      Sa.pop();
    }
    if(!Sb.empty()){
      B=Sb.top();
      Sb.pop();
    }
    if(A>=B && i!=end-1 || i==end-1 && A>B){
      Nlink p=(Nlink)malloc(sizeof(Num));
      p->symbol=ans->symbol;
      p->data=A-B;
      p->power=power;
      p->Next=NULL;
      p->Next=ans->Next;
      ans->Next=p;
      power++;
    }
    else if(A<B){
      long long *pp=(long long *)calloc(end,sizeof(long long));
      int popnum=0;
      /* 借位计算 */
      long long tmp=Sa.top();Sa.pop();
      if(tmp==0)
        pp[popnum++]=tmp+LIMIT-1;//此位也为0
      else if(tmp>0)//此位不为0
        pp[popnum++]=tmp-1;
      while(tmp==0 && !Sa.empty()){
        /* 循环借位 */
        tmp=Sa.top();Sa.pop();
        if(tmp==0)
          pp[popnum++]=tmp+LIMIT-1;//此位也为0
        else if(tmp>0)//此位不为0
          pp[popnum++]=tmp-1;
      }
      A=A+LIMIT;
      /* 放回借位 */
      for(int j=popnum-1;j>=0;j--){
        /* 高位在栈底 */
        Sa.push(pp[j]);
      }
      Nlink p=(Nlink)malloc(sizeof(Num));
      p->symbol=ans->symbol;
      p->data=A-B;
      p->power=power;
      p->Next=NULL;
      p->Next=ans->Next;
      ans->Next=p;
      power++;
      free(pp);
    }
  }
  return ans;
}
/* BigNumber_Plus */
Nlink BigNumber_Plus(Nlink a,Nlink b){
  /* a>0 b>0 */
  if(a->symbol=='+' && b->symbol=='+'){
    return BigNumber_Plus_Son(a,b);
  }
  /* a>0 b<0 */
  if(a->symbol=='+' && b->symbol=='-'){
    b->symbol='+';
    Nlink ans=BigNumber_Minus_Son(a,b);
    b->symbol='-';
    return ans;
  }
  /* a<0 b>0 */
  /* -a+b=-(a-b) */
  if(a->symbol=='-' && b->symbol=='+'){
    a->symbol='+';
    Nlink ans=BigNumber_Minus_Son(a,b);
    a->symbol='-';
    ans->symbol=BigNumber_Reverse(ans->symbol);
    return ans;
  }
  /* a<0 b<0 */
  /* -a-b=-(a+b) */
  if(a->symbol=='-' && b->symbol=='-'){
    a->symbol='+';b->symbol='+';
    Nlink ans=BigNumber_Plus_Son(a,b);
    ans->symbol=BigNumber_Reverse(ans->symbol);
    a->symbol='-';b->symbol='-';
    return ans;
  }
  /* 四种情况都无法捕捉说明出现错误 */
  return NULL;
}
Nlink BigNumber_Minus(Nlink a,Nlink b){
  /* a>0 b>0 */
  if(a->symbol=='+' && b->symbol=='+'){
    return BigNumber_Minus_Son(a,b);
  }
  /* a>0 b<0 */
  /* a-(-b) */
  /* a+b */
  if(a->symbol=='+' && b->symbol=='-'){
    b->symbol='+';
    Nlink ans=BigNumber_Plus_Son(a,b);
    b->symbol='-';
    return ans;
  }
  /* a<0 b>0 */
  /* -a-b=-(a+b) */
  if(a->symbol=='-' && b->symbol=='+'){
    a->symbol='+';
    Nlink ans=BigNumber_Plus_Son(a,b);
    a->symbol='-';
    ans->symbol=BigNumber_Reverse(ans->symbol);
    return ans;
  }
  /* a<0 b<0 */
  /* -a-(-b)=-a+b=-(a-b) */
  if(a->symbol=='-' && b->symbol=='-'){
    a->symbol='+';b->symbol='+';
    Nlink ans=BigNumber_Minus_Son(b,a);
    // ans->symbol=BigNumber_Reverse(ans->symbol);
    a->symbol='-';b->symbol='-';
    return ans;
  }
  /* 四种情况都无法捕捉说明出现错误 */
  return NULL;
}
/* a>0 b>0 */
Nlink BigNumber_Mul_Son(Nlink a,Nlink b){
  Nlink ans=(Nlink)malloc(sizeof(Num));
  ans->symbol='+';
  ans->data=-1;ans->power=-1;ans->Next=NULL;//fans->Rear=ans;
  stack<Number_son>Sb,Sc;
  Nlink p=NULL;
  int sizea=a->Next->power+1;
  int sizeb=b->Next->power+1;
  Nlink tmpa=NULL;
  Nlink tmpb=NULL;
  if(sizea>=sizeb){
    /* a的项数大于b的 */
    tmpa=a;
    tmpb=b;
//    end=sizeb;
  }
  else{
    /* a的项数小于b的 */
    tmpa=b;
    tmpb=a;
//    end=sizea;
  }
  p=tmpb->Next;
  while(p!=NULL){
    Number_son tmp;
    tmp.data=p->data;
    tmp.power=p->power;
    Sb.push(tmp);
    p=p->Next;
  }
  while(!Sb.empty()){
    Number_son top=Sb.top();Sb.pop();
    p=tmpa->Next;
    while(p!=NULL){
      Number_son tmp;
      tmp.data=top.data*p->data;
      tmp.power=top.power+p->power;
      Sc.push(tmp);
      p=p->Next;
    }
  }
  if(Sc.empty()){
    Nlink zero=(Nlink)malloc(sizeof(Num));
    zero->Next=(Nlink)malloc(sizeof(Num));
    zero->Next->symbol='+';
    zero->Next->data=0;
    zero->Next->power=0;
    zero->Next->Next=NULL;
    zero->symbol='+';
    zero->data=-1;
    zero->power=-1;
    BigNumber_Destory(ans);
    return zero;
  }
  int size=0;
  /* 计算部分积的和，从栈中依次取出 */
  while(!Sc.empty()){
    /* 从栈顶取出一个元素 */
    Number_son top=Sc.top();Sc.pop();
    size++;
    bool flag_Load=false;
    p=ans->Next;
    /* 部分和开始计算 */
    while(p!=NULL){
      if(p->power==top.power){
        /* 存在 */
        flag_Load=true;
        p->data=top.data+p->data;
        break;
      }
      if(p->Next==NULL && flag_Load==false){
        /* 不存在进行插入 */
        Nlink q=(Nlink)malloc(sizeof(Num));
        q->symbol=ans->symbol;
        q->data=top.data;
        q->power=top.power;
        q->Next=NULL;
        Nlink insert=ans->Next;
        /* 不存在而且比最大的还大 */
        if(insert->power<top.power)
        	insert=ans;
        else{
        	/* 寻找插入点 */
	        while(insert!=NULL){
	          if(insert->power>q->power && (insert->Next==NULL || insert->Next->power<q->power))
	            break;
	          if(insert->Next==NULL)
	            break;
	          insert=insert->Next;
	        }
        }
        q->Next=insert->Next;
        insert->Next=q;
        flag_Load=true;
        break;
      }
      p=p->Next;
    }
    if(flag_Load==false){
      Nlink q=(Nlink)malloc(sizeof(Num));
      q->symbol=ans->symbol;
      q->data=top.data;
      q->power=top.power;
      q->Next=ans->Next;
      ans->Next=q;
    }
    p=ans->Next;
    int k=0;
    while(p!=NULL){
      k++;
      p=p->Next;
    }
    Nlink* tmp=(Nlink*)calloc(k,sizeof(Nlink));
    /* 进位问题 */
    p=ans->Next;
    k=0;
    while(p!=NULL){
      tmp[k++]=p;
      p=p->Next;
    }
    /* 由后向前 */
    for(int j=k-1;j>=0;j--){
      p=tmp[j];
      if(p->data>=LIMIT){
        int power=p->power+1;
        int C=p->data/LIMIT;
        p->data=p->data%LIMIT;
        Nlink q=ans->Next;
        /* 开始加上进位 */
        if(power>ans->Next->power){
          /* 比最大还大 */
          q=(Nlink)malloc(sizeof(Num));
          q->symbol=ans->symbol;
          q->data=C;
          q->power=power;
          q->Next=ans->Next;
          ans->Next=q;
        }
        else{
          /* 在内部 */
          q=ans->Next;
          while(q!=NULL && q->power!=power-1){
            if(q->power==power){
              q->data=q->data+C;
              break;
            }
            if(q->power!=power && q->Next->power==power-1){
              Nlink insert=(Nlink)malloc(sizeof(Num));
              insert->symbol=ans->symbol;
              insert->data=C;
              insert->power=power;
              insert->Next=q->Next;
              q->Next=insert;
              break;
            }
            q=q->Next;
          }
        }
      }
    }
    if(size>0 && tmp!=NULL)
    	free(tmp);
  }
  return ans;
}
/* a*b */
Nlink BigNumber_Mul(Nlink a,Nlink b){
  Nlink zero=BigNumber_Long2Nlink(0);
  if(BigNumber_CMP(a,zero)==0){
    return zero;
  }
  if(BigNumber_CMP(b,zero)==0){
    return zero;
  }
  /* assert a!=0 b!=0 */
  /* a>0 b>0 */
  if(a->symbol=='+' && b->symbol=='+'){
    return BigNumber_Mul_Son(a,b);
  }
  /* a>0 b<0 */
  if(a->symbol=='+' && b->symbol=='-'){
    b->symbol='+';
    Nlink ans=BigNumber_Mul_Son(a,b);
    ans->symbol='-';
    b->symbol='-';
    BigNumber_Destory(zero);
    return ans;
  }
  /* a<0 b>0 */
  if(a->symbol=='-' && b->symbol=='+'){
    a->symbol='+';
    Nlink ans=BigNumber_Mul_Son(a,b);
    ans->symbol='-';
    a->symbol='-';
    BigNumber_Destory(zero);
    return ans;
  }
  /* a<0 b<0 */
  if(a->symbol=='-' && b->symbol=='-'){
    a->symbol='+';b->symbol='+';
    Nlink ans=BigNumber_Mul_Son(a,b);
    a->symbol='-';b->symbol='-';
    BigNumber_Destory(zero);
    return ans;
  }
  /* 均无法捕捉情况 */
  return NULL;
}
/* 计算a^b */
/* 未进行free处理 */
Nlink BigNumber_Power_Positive(Nlink a,Nlink b){
  // Nlink i=BigNumber_Long2Nlink(0);
  Nlink one=BigNumber_Long2Nlink(1);
  Nlink two=BigNumber_Long2Nlink(2);
  Nlink zero=BigNumber_Long2Nlink(0);
  if(BigNumber_CMP(b,zero)==0)
    return one;
  if(BigNumber_CMP(b,one)==0)
    return a;
  // Nlink ans=BigNumber_Long2Nlink(1);
  // Nlink backup=NULL;
  // for(;BigNumber_CMP(i,b)==-1;){
  //   backup=ans;
  //   ans=BigNumber_Mul_Son(ans,a);
  //   free(backup);
  //   backup=i;
  //   i=BigNumber_Plus_Son(i,one);
  //   free(backup);
  // }
  // free(i);
  // free(one);
  //a^2
  //b/2

  return BigNumber_Mul_Son(BigNumber_Power_Positive(BigNumber_Mul_Son(a,a),BigNumber_DIV_Integer(b,two)),BigNumber_Power_Positive(a,BigNumber_Mod_Son(b,two)));
}
/* b很小时可用 */
/* 计算a^b */
Nlink BigNumber_Power_Positive_Littleb(Nlink a,Nlink b){
  Nlink i=BigNumber_Long2Nlink(0);
  Nlink one=BigNumber_Long2Nlink(1);
  Nlink two=BigNumber_Long2Nlink(2);
  Nlink zero=BigNumber_Long2Nlink(0);
  if(BigNumber_CMP(b,zero)==0)
     return one;
  if(BigNumber_CMP(b,one)==0){
    Nlink ans;
    BigNumber_CPY(&ans,a);
    return ans;
  }
  Nlink ans=BigNumber_Long2Nlink(1);
  Nlink backup=NULL;
  for(;BigNumber_CMP(i,b)==-1;){
    backup=ans;
    ans=BigNumber_Mul_Son(ans,a);
    BigNumber_Destory(backup);
    backup=i;
    i=BigNumber_Plus_Son(i,one);
    BigNumber_Destory(backup);
  }
  BigNumber_Destory(i);
  BigNumber_Destory(one);
  return ans;
  //a^2
  //b/2
/* 改成非递归 */
  return BigNumber_Mul_Son(BigNumber_Power_Positive(BigNumber_Mul_Son(a,a),BigNumber_DIV_Integer(b,two)),BigNumber_Power_Positive(a,BigNumber_Mod_Son(b,two)));
}
/* 未进行free处理 */
Nlink BigNumber_Fact_Son(Nlink a,Nlink zero,Nlink one){
  if(BigNumber_CMP(a,zero)==0)
    return one;
  return BigNumber_Mul_Son(BigNumber_Fact_Son(BigNumber_Minus_Son(a,one),zero,one),a);
}
Nlink BigNumber_Fact(long long n){
  Nlink one=BigNumber_Long2Nlink(1);
  Nlink zero=BigNumber_Long2Nlink(0);
  Nlink a=BigNumber_Long2Nlink(n);
  return BigNumber_Fact_Son(a,zero,one);
}
/* a>0 b!=0 */
/* 求a mod b */
Nlink BigNumber_Mod_Son(Nlink a,Nlink b){
  char symbol_b=b->symbol;
  b->symbol='+';
  Nlink ten=BigNumber_Long2Nlink(10);
  Nlink one=BigNumber_Long2Nlink(1);
  Nlink ans;BigNumber_CPY(&ans,a);
  // Nlink tmpb;tmpb=BigNumber_CPY(&tmpb,b);
  Nlink backup;
  for(;BigNumber_CMP(ans,b)!=-1;){
    /* 求取幂加速 */
    int power=(ans->Next->power-b->Next->power);
    long long lenpower=9*power;
    if(b->Next->data==ans->Next->data)lenpower--;
    if(lenpower<0)lenpower=0;
    Nlink pp=BigNumber_Power_Positive_Littleb(ten,BigNumber_Long2Nlink(lenpower));
    if(b->Next->data<=ans->Next->data){

  	  long long tmp=ans->Next->data/(b->Next->data+1);
      Nlink tmp2=BigNumber_Long2Nlink(tmp);
      Nlink tmp3=NULL;
	  if(tmp2->Next->data!=0){
	  	tmp3=BigNumber_Mul_Son(tmp2,b);
	  }
      else{
      	tmp3=BigNumber_Mul_Son(one,b);
      }
      Nlink tmp4=BigNumber_Mul_Son(tmp3,pp);
      ans=BigNumber_Minus_Son(ans,tmp4);
      BigNumber_Destory(tmp2);BigNumber_Destory(tmp3);BigNumber_Destory(tmp4);

    }
    else{
    	/* b->Next->data>ans->Next->data */
      char tmpbNdata[30];char tmpansNdata[30];
      sprintf(tmpbNdata,"%lld",b->Next->data);
      sprintf(tmpansNdata,"%lld",ans->Next->data);
      int lentmp=strlen(tmpbNdata)-strlen(tmpansNdata)+1;
      Nlink pp=BigNumber_Power_Positive_Littleb(ten,BigNumber_Long2Nlink(9*power-lentmp));
      Nlink tmp1=BigNumber_Mul_Son(pp,b);
      Nlink tmp2=one;
      Nlink tmp3=NULL;
      if(tmp1->Next->data<=ans->Next->data){
        tmp2=BigNumber_Long2Nlink(ans->Next->data/(tmp1->Next->data+1));
        if(tmp2->Next->data!=0)
        	tmp3=BigNumber_Mul_Son(tmp2,tmp1);
        else
        	tmp3=BigNumber_Mul_Son(one,tmp1);
        ans=BigNumber_Minus_Son(ans,tmp3);
        BigNumber_Destory(tmp2);
      }
      else{
        ans=BigNumber_Minus(ans,tmp1);
      }
      BigNumber_Destory(tmp1);BigNumber_Destory(tmp3);
    }
    BigNumber_Destory(pp);
  }
  b->symbol=symbol_b;
  BigNumber_Destory(ten);
  BigNumber_Destory(one);
//  free(tmpb);
  return ans;
}
/* 计算a mod b */
/* b!=0 */
Nlink BigNumber_Mod(Nlink a,Nlink b){
  Nlink zero=BigNumber_Long2Nlink(0);
  if(BigNumber_CMP(b,zero)==0){
    BigNumber_Destory(zero);
    return NULL;
  }
  /* assert b!=0 */
  int CMP=BigNumber_CMP(a,zero);
  if(CMP==0){
    return zero;
  }
  else if(CMP==1){
    return BigNumber_Mod_Son(a,b);
  }
  else if(CMP==-1){
    /* a<0 */
    a->symbol='+';
    Nlink Mod_P=BigNumber_Mod_Son(a,b);
    a->symbol='-';
    char symbolb=b->symbol;
    b->symbol='+';
    Nlink ans=BigNumber_Minus_Son(b,Mod_P);
    b->symbol=symbolb;
    BigNumber_Destory(zero);
    BigNumber_Destory(Mod_P);
    return ans;
  }
}
/* a>0 b>0 */
/* 计算a/b(整除) */
Nlink BigNumber_DIV_Integer(Nlink a,Nlink b){
  Nlink i=BigNumber_Long2Nlink(0);
  char symbol_b=b->symbol;
  b->symbol='+';
  Nlink ten=BigNumber_Long2Nlink(10);
  Nlink one=BigNumber_Long2Nlink(1);
  Nlink ans;BigNumber_CPY(&ans,a);
  // Nlink tmpb;tmpb=BigNumber_CPY(&tmpb,b);
  Nlink backup;Nlink backupi;
  for(;BigNumber_CMP(ans,b)!=-1;){
    /* 求取幂加速 */
    int power=ans->Next->power-b->Next->power;
    Nlink pp=BigNumber_Power_Positive_Littleb(ten,BigNumber_Long2Nlink(9*power));
    if(b->Next->data<=ans->Next->data){

  	  long long tmp=ans->Next->data/(b->Next->data+1);
      Nlink tmp2=BigNumber_Long2Nlink(tmp);
      Nlink tmp3=NULL;
      if(tmp2->Next->data!=0)
      	tmp3=BigNumber_Mul_Son(tmp2,pp);//pp*tmp
      else
      	tmp3=BigNumber_Mul_Son(one,pp);
      Nlink tmp4=BigNumber_Mul_Son(tmp3,b);//pp*tmp*b
      ans=BigNumber_Minus_Son(ans,tmp4);
      backupi=i;
      i=BigNumber_Plus_Son(i,tmp3);
      BigNumber_Destory(backupi);
      BigNumber_Destory(tmp2);BigNumber_Destory(tmp3);BigNumber_Destory(tmp4);

    }
    else{
    	/* b->Next->data>ans->Next->data */
      char tmpbNdata[30];char tmpansNdata[30];
      sprintf(tmpbNdata,"%lld",b->Next->data);
      sprintf(tmpansNdata,"%lld",ans->Next->data);
      int lentmp=strlen(tmpbNdata)-strlen(tmpansNdata)+1;
      Nlink pp=BigNumber_Power_Positive_Littleb(ten,BigNumber_Long2Nlink(9*power-lentmp));
      Nlink tmp1=BigNumber_Mul_Son(pp,b);
      Nlink tmp2=one;
      Nlink tmp3=NULL;
      if(tmp1->Next->data<=ans->Next->data){
        tmp2=BigNumber_Long2Nlink(ans->Next->data/(tmp1->Next->data+1));
        if(tmp2->Next->data!=0)
        	tmp3=BigNumber_Mul_Son(tmp2,tmp1);
        else
        	tmp3=BigNumber_Mul_Son(one,tmp1);
        ans=BigNumber_Minus_Son(ans,tmp3);
        backupi=i;
        Nlink tmp4=NULL;
		if(tmp2->Next->data!=0)
        	tmp4=BigNumber_Mul_Son(pp,tmp2);
        else
         	tmp4=BigNumber_Mul_Son(pp,one);
        i=BigNumber_Plus_Son(i,tmp4);
        BigNumber_Destory(backupi);
        BigNumber_Destory(tmp2);
        BigNumber_Destory(tmp4);
      }
      else{
        backupi=i;
        i=BigNumber_Plus_Son(i,pp);
        BigNumber_Destory(backupi);
        ans=BigNumber_Minus_Son(ans,tmp1);
      }
      BigNumber_Destory(tmp1);BigNumber_Destory(tmp3);
    }
    BigNumber_Destory(pp);
  }
  b->symbol=symbol_b;
  BigNumber_Destory(ten);
  BigNumber_Destory(one);
  BigNumber_Destory(ans);
//  free(tmpb);
  return i;
}
Nlink BigNumber_DIV(Nlink a,Nlink b){
  Nlink zero=BigNumber_Long2Nlink(0);
  if(BigNumber_CMP(b,zero)==0){
    /* 除数为零 */
    BigNumber_Destory(zero);
    return NULL;
  }
  if(BigNumber_CMP(a,zero)==0){
    return zero;
  }
  /* assert a!=0 b!=0 */
  /* a>0 b>0 */
  if(a->symbol=='+' && b->symbol=='+'){
    BigNumber_Destory(zero);
    return BigNumber_DIV_Integer(a,b);
  }
  /* a>0 b<0 */
  if(a->symbol=='+' && b->symbol=='-'){
    b->symbol='+';
    Nlink ans=BigNumber_DIV_Integer(a,b);
    ans->symbol='-';
    b->symbol='-';
    BigNumber_Destory(zero);
    return ans;
  }
  /* a<0 b>0 */
  if(a->symbol=='-' && b->symbol=='+'){
    a->symbol='+';
    Nlink ans=BigNumber_DIV_Integer(a,b);
    ans->symbol='-';
    a->symbol='-';
    BigNumber_Destory(zero);
    return ans;
  }
  /* a<0 b<0 */
  if(a->symbol=='-' && b->symbol=='-'){
    a->symbol='+';b->symbol='+';
    Nlink ans=BigNumber_DIV_Integer(a,b);
    a->symbol='-';b->symbol='-';
    BigNumber_Destory(zero);
    return ans;
  }
  /* 无法捕捉情况 */
  return NULL;
}
/* n>0 */
bool BigNumber_IsPrime(Nlink n){
  Nlink i=BigNumber_Long2Nlink(2);
  Nlink two=BigNumber_Long2Nlink(2);
  Nlink one=BigNumber_Long2Nlink(1);
  Nlink zero=BigNumber_Long2Nlink(0);
  Nlink tmp=BigNumber_Mul_Son(i,two);
  Nlink backup;Nlink backupi;
  int CMP=BigNumber_CMP(tmp,n);
  for(;CMP!=1;){
//  	printf("%lld\n",i->Next->data);
    tmp=BigNumber_Mod_Son(n,i);
    if(BigNumber_CMP(tmp,zero)==0){
      BigNumber_Destory(two);
      BigNumber_Destory(one);
      BigNumber_Destory(zero);
      BigNumber_Destory(tmp);
      BigNumber_Destory(i);
      return false;
    }
    BigNumber_Destory(tmp);
    backupi=i;
    i=BigNumber_Plus_Son(i,one);
    BigNumber_Destory(backupi);
    tmp=BigNumber_Mul_Son(i,two);
    CMP=BigNumber_CMP(tmp,n);
    BigNumber_Destory(tmp);
  }
  BigNumber_Destory(i);
  BigNumber_Destory(two);
  BigNumber_Destory(one);
  BigNumber_Destory(zero);
  return true;
}
/* a>=0 b>0 */
Nlink BigNumber_GCD_Positive(Nlink a,Nlink b){
  Nlink zero=BigNumber_Long2Nlink(0);
  Nlink backup=NULL;
  Nlink tmp=NULL;
  Nlink tmpa=NULL;
  Nlink tmpb=NULL;
  int CMP=BigNumber_CMP(a,b);
  if(CMP>=0){
    /* a>=b */
    BigNumber_CPY(&tmpa,a);
    BigNumber_CPY(&tmpb,b);
  }
  else{
    /* a<b */
    BigNumber_CPY(&tmpa,b);
    BigNumber_CPY(&tmpb,a);
  }
  /* 辗转相除法求最大公约数 */
  do{
    tmp=BigNumber_Mod_Son(tmpa,tmpb);
    backup=tmpa;
    tmpa=tmpb;
    tmpb=tmp;
    BigNumber_Destory(backup);
  }while(BigNumber_CMP(tmp,zero)==1);
  BigNumber_Destory(zero);
  BigNumber_Destory(tmpb);
  return tmpa;
}
/*  */
Nlink BigNumber_GCD(Nlink a,Nlink b){
  Nlink zero=BigNumber_Long2Nlink(0);
  /* b=0 */
  int CMP=BigNumber_CMP(b,zero);
  if(CMP<=0){
    BigNumber_Destory(zero);
    return NULL;
  }
  /* a=0 */
  CMP=BigNumber_CMP(a,zero);
  if(CMP==0){
    return zero;
  }
  else if(CMP==-1){
    BigNumber_Destory(zero);
    return NULL;
  }
  /* assert a>0 b>0 */
  BigNumber_Destory(zero);
  return BigNumber_GCD_Positive(a,b);
}
/* a>0 b>0 */
/* 计算LCM(a,b)最小公倍数 */
Nlink BigNumber_LCM_Positive(Nlink a,Nlink b){
  Nlink gcd=BigNumber_GCD_Positive(a,b);
  Nlink mul=BigNumber_Mul_Son(a,b);
  Nlink ans=BigNumber_DIV_Integer(mul,gcd);
  BigNumber_Destory(gcd);BigNumber_Destory(mul);
  return ans;
}
Nlink BigNumber_LCM(Nlink a,Nlink b){
  Nlink zero=BigNumber_Long2Nlink(0);
  if(BigNumber_CMP(b,zero)<=0){
    BigNumber_Destory(zero);
    return NULL;
  }
  int CMP=BigNumber_CMP(a,zero);
  if(CMP==0){
    return zero;
  }
  else if(CMP==-1){
    BigNumber_Destory(zero);
    return NULL;
  }
  /* assert a>0 b>0 */
  BigNumber_Destory(zero);
  return BigNumber_LCM_Positive(a,b);
}
/* 求取a^-1 mod b */
/* b!=0 */
Nlink BigNumber_Mod_Reverse(Nlink a,Nlink b){
  Nlink zero=BigNumber_Long2Nlink(0);
  Nlink backup=NULL;Nlink backup2=NULL;
  Nlink tmp=NULL;
  Nlink tmpa=NULL;
  Nlink tmpb=NULL;
  Nlink B[3]={NULL};
  BigNumber_CPY(&tmpa,b);
  BigNumber_CPY(&tmpb,a);
  B[0]=BigNumber_Long2Nlink(0);
  B[1]=BigNumber_Long2Nlink(1);
  B[2]=BigNumber_Long2Nlink(0);
  /* 辗转相除法求最大公约数 */
  do{
    tmp=BigNumber_Mod(tmpa,tmpb);
    Nlink tmp2=BigNumber_DIV_Integer(tmpa,tmpb);
    Nlink tmp4=BigNumber_Mul(B[1],tmp2);
    B[2]=BigNumber_Minus(B[0],tmp4);
    BigNumber_Destory(tmp2);
    BigNumber_Destory(tmp4);
    backup=tmpa;
    backup2=B[0];
    tmpa=tmpb;
    B[0]=B[1];
    tmpb=tmp;
    B[1]=B[2];
    BigNumber_Destory(backup);
    BigNumber_Destory(backup2);
  }while(BigNumber_CMP(tmp,zero)!=0);
  BigNumber_Destory(zero);
  BigNumber_Destory(tmpb);
  Nlink one=BigNumber_Long2Nlink(1);
  int CMP=BigNumber_CMP(tmpa,one);
  if(CMP==0){
    BigNumber_Destory(one);
    BigNumber_Destory(tmpa);
    return B[0];
  }
  else{
    BigNumber_Destory(one);
    BigNumber_Destory(tmpa);
    BigNumber_Destory(B[0]);
    return NULL;
  }
}
/* 计算a^b mod c */
Nlink BigNumber_Mod_Power(Nlink a,Nlink b,Nlink c){
  Nlink zero = BigNumber_Long2Nlink(0);
  Nlink one = BigNumber_Long2Nlink(1);
  Nlink two = BigNumber_Long2Nlink(2);
  Nlink power=NULL;BigNumber_CPY(&power,b);
  Nlink ans = BigNumber_Long2Nlink(1);
  Nlink tmp = NULL;
  Nlink backup=NULL;
  Nlink flag=NULL;
  Nlink tmpa=NULL;
  tmpa=BigNumber_Mod(a,c);
  while(BigNumber_CMP(power,one)>=0){
    tmp=BigNumber_Power_Positive_Littleb(tmpa,two);//a^2
    backup=tmp;
    tmp=BigNumber_Mod(tmp,c);
    BigNumber_Destory(backup);
    flag=BigNumber_Mod(power,two);
    if(BigNumber_CMP(flag,one)==0){
        backup=ans;
        ans=BigNumber_Mul(ans,tmpa);
        BigNumber_Destory(backup);
        backup=ans;
        ans=BigNumber_Mod(ans,c);
        BigNumber_Destory(backup);
    }
    BigNumber_Destory(flag);
    tmpa=tmp;
    backup=power;
    power=BigNumber_DIV(power,two);
    BigNumber_Destory(backup);
    if(BigNumber_CMP(tmpa,one)==0){
      break;
    }
    else if(BigNumber_CMP(tmpa,zero)==0){
      backup=ans;
      BigNumber_CPY(&ans,zero);
      free(backup);
      break;
    }
  }
  BigNumber_Destory(tmpa);
  BigNumber_Destory(zero);
  BigNumber_Destory(one);
  BigNumber_Destory(two);
  BigNumber_Destory(power);
  return ans;
}
/* 返回一个m到n之间的随机数 */
long long BigNumber_Rand_Long_S(long long m,long long n){
  long long a[4]={0};
  a[0]=rand();a[1]=rand();a[2]=rand();a[3]=rand()%32768;//符号位不能为0
  long long ans=0;
  ans|=a[0];
  ans|=a[1]<<16;
  ans|=a[2]<<32;
  ans|=a[3]<<48;
  ans=ans%(m-n+1)+n;
  return ans;
}
/* 返回一个m到n之间的随机数 */
long long BigNumber_Rand_Long(){
  long long a[4]={0};
  a[0]=rand();a[1]=rand();a[2]=rand();a[3]=rand()%32768;//符号位不能为0
  long long ans=0;
  ans|=a[0];
  ans|=a[1]<<16;
  ans|=a[2]<<32;
  ans|=a[3]<<48;
  return ans;
}
/* 生成一个<n的随机数 */
Nlink BigNumber_Rand(Nlink n){
  // Nlink two=BigNumber_Long2Nlink(2);
  Nlink p=n->Next;
  Nlink ans=(Nlink)malloc(sizeof(Num));
  BigNumber_Init(ans);
  Nlink q=(Nlink)malloc(sizeof(Num));
  /* 生成最高位 */
  q->symbol='+';
  /* 生成最高位的power值 */
  q->power=rand()%(p->power+1);
  q->Next=NULL;
  int power=q->power;
  if(p->power==q->power){
    /* 生成最高位 */
    q->data=BigNumber_Rand_Long()%p->data;
    ans->Next=q;
    /* p进入第二位 */
    p=p->Next;
    while(p!=NULL){
      /* 生成data值 */
      long long tmp=BigNumber_Rand_Long()%LIMIT;
      /* 生成新节点 */
      Nlink tmp2=(Nlink)malloc(sizeof(Num));
      tmp2->symbol='+';tmp2->data=tmp;
      tmp2->power=p->power;tmp2->Next=NULL;
      q->Next=tmp2;
      q=q->Next;p=p->Next;
    }
  }
  else if(q->power==0){
    /* 1位数 */
    q->data=BigNumber_Rand_Long()%LIMIT;
    ans->Next=q;
  }
  else if(q->power<p->power){
    /* 生成第一个节点 */
    q->data=BigNumber_Rand_Long()%LIMIT;
    power--;
    ans->Next=q;
    while(power>=0){
      /* 生成data值 */
      long long tmp=BigNumber_Rand_Long()%LIMIT;
      /* 生成新节点 */
      Nlink tmp2=(Nlink)malloc(sizeof(Num));
      tmp2->symbol='+';tmp2->data=tmp;
      tmp2->power=power;tmp2->Next=NULL;
      q->Next=tmp2;
      q=q->Next;
      power--;
    }
  }
  return ans;
}
/* Fermat素性检测算法 */
/* k为精度 */
double BigNumber_IsPrime_Fermat(Nlink n,int k){
  Nlink two=BigNumber_Long2Nlink(2);
  Nlink tmp=BigNumber_Mod(n,two);
  Nlink zero=BigNumber_Long2Nlink(0);
  if(BigNumber_CMP(tmp,zero)==0){
  	BigNumber_Destory(two);
  	BigNumber_Destory(tmp);
  	BigNumber_Destory(zero);
  	return 0.0f;
  }
  Nlink one=BigNumber_Long2Nlink(1);
  Nlink n_1=BigNumber_Minus(n,one);//n-1
  for (int i = 0; i < k; i++) {
//  	printf("%d\n",i);
    Nlink b=NULL;
    b=BigNumber_Rand(n_1);
    while(BigNumber_CMP(b,two)==-1){
      b=BigNumber_Rand(n_1);
    }
    Nlink g=BigNumber_GCD(b,n);
    if(BigNumber_CMP(g,one)!=0){
      BigNumber_Destory(two);
  	  BigNumber_Destory(one);
  	  BigNumber_Destory(n_1);
  	  BigNumber_Destory(tmp);
  	  BigNumber_Destory(zero);
  	  BigNumber_Destory(b);
  	  BigNumber_Destory(g);
	  return 0.0f;
    }
    Nlink r=BigNumber_Mod_Power(b,n_1,n);
    if(BigNumber_CMP(r,one)!=0){
      BigNumber_Destory(b);
      BigNumber_Destory(g);
      BigNumber_Destory(r);
      BigNumber_Destory(two);
      BigNumber_Destory(one);
      BigNumber_Destory(n_1);
      BigNumber_Destory(tmp);
  	  BigNumber_Destory(zero);
      return 0.0f;
    }
    BigNumber_Destory(b);
    BigNumber_Destory(g);
    BigNumber_Destory(r);
  }
  BigNumber_Destory(two);
  BigNumber_Destory(one);
  BigNumber_Destory(n_1);
  BigNumber_Destory(tmp);
  BigNumber_Destory(zero);
  return 1.0f-pow(2,-k);
}
#endif
