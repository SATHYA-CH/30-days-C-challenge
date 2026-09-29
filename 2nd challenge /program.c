#include<stdio.h>
int main(){
int km,kmpl,fpl,rf,tcf;
printf("\n Enter the distance");
scanf("%d",&km);
printf("\n Enter the milage");
scanf("%d",&kmpl);
printf("Ente the prize of the fuel");
scanf("%d",&fpl);
rf=km/kmpl;
tcf=rf*fpl;
printf("the fuel requried is :%d \n , fuel per liter is : %d",rf,tcf);
return 0;
}

