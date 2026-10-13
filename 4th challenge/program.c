#include<stdio.h>
int main(){
int expenses,totalcount=0;
float totalamount=0.0,smalltotal=0.0,largetotal=0.0,mediumtotal=0.0;
int  smallcount=0,mediumcount=0,largecount=0;
while(1)
{
        printf("Enter the expenses");
        scanf("%d",&expenses);
        if(expenses==0)
        {
                break;
        }
        if(expenses<0)
        {
                printf("invalidinput");
        }
        if(expenses<100)
        {
                smallcount++;
                smalltotal+=expenses;
        }
        else if (expenses>=100 && expenses<=500)
        {
                mediumcount++;
                mediumtotal+=expenses;
        }
        else if (expenses>500)
        {
                largecount++;
                largetotal+=expenses;
        }
        totalcount++;
        totalamount+=expenses;
}
printf("expenses : %d \n",totalcount);
printf("total: %f",totalamount);
printf("small:total=%f,count=%d \n",smalltotal,smallcount);
printf("medium:total=%f,count=%d \n",mediumtotal,mediumcount);
printf("largetotal:total=%f,count=%d \n",largetotal,largecount);
}

