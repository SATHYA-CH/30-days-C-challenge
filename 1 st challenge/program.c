#include<stdio.h>
int main(){
int m1,m2,m3,m4,m5;
float total,avg,per;
printf("Enter marks of 5 subjects");
scanf("%d %d %d %d %d",&m1,&m2,&m3,&m4,&m5);
total=m1+m2+m3+m4+m5;
avg=total/500;
per=(total/500)*100
printf("total is %f \n,avg is %f \n,per is %f",total,avg,per);
return 0;
}
