#include<stdio.h>
int main(){
int amount,cstype,dist;
int ds,disamt,dcharges=0,finalamount,discount=0;
printf("Enter the amount: \n");
scanf("%d",&amount);
printf("Enter the cstype: \n");
scanf("%d",&cstype);
printf("Enter the distance in km : \n");
scanf("%d",&dist);
if(cstype ==1 && amount >=2000)
{
        discount = 15;
}
else if(cstype ==1 && amount<2000)
{
        discount = 10;
}
else if(cstype ==2 && amount >=3000)
{
        discount = 8;
}
else if(cstype ==2 && amount <3000)
{
        discount = 0;
}
if(dist <=5)
{
        dcharges = 40;
}
else if(dist>5 && dist<=15)
{
        dcharges = 70;
}
else if(dist  > 15)
{
        dcharges = 100;
}
ds=amount*discount/100;
disamt=amount-ds;
finalamount=disamt+dcharges;
printf("Purchase amount :%d\n",amount);
printf("Discount (%d%%):%d\n",discount,ds);
printf("Amount after dicount:%d\n",disamt);
printf("Delivery charges:%d\n",dcharges);
printf("Final payable amount:%d\n",finalamount);
return 0;
}
             
