#include<stdio.h>
#include<BigNumberCalc2.h>
int main(){
  char a[1024];
  printf("a:");
  scanf("%s",a);
  Nlink H=BigNumber_Trans(a);
  char *h=BigNumber_out(H);
  printf("%s\n",h);
  system("pause");
}
