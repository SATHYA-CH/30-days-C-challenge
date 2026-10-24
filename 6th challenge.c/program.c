include<stdio.h>
int main(){
int arr[12];
int n,N=0,i,sum=0,max,min;
float avg;
int second,peaks=0,current,longest,
k,d,r,count=0,temp;
do 
{
        printf("Enter N(5 to 12):");
        scanf("%d",&N);
        if(N<5 || N>12)
                printf("invalid try again.\n");
}while(N<5 || N>12);
for(i=0;i<N;i++)
{
        arr[i]=-1;
        while(arr[i] <0 || arr[i] > 1000)
        {
        printf("Enter reading %d(0 to 1000):",i+1);
        scanf("%d",&arr[i]);
        if(arr[i]<0 || arr[i] > 1000)
        printf("invalid reading.Try again.\n");
}
}
printf("Readings:");
for(i=0;i<N;i++)
        printf("%d",arr[i]);
printf("\n");

min=arr[0];
max=arr[0];

for(i=0;i<N;i++){
        sum=sum+arr[i];
if(arr[i]<min)
        min = arr[i];
        if(arr[i]>max)
        max=arr[i];
}
avg = (float)sum/N;
printf("Sum=%d\n",sum);
printf("Average=%f\n",avg);
printf("MINIMUN = %d \n,MAXIMUM = %d \n",min,max);
second=-1;
for(i=0;i<N;i++)
{
        if(arr[i]!=max && arr[i] >second)
        second = arr[i];
}
if(second == -1)
        printf("No second largest");
        else
        printf("Second largest =%d\n",second);
for(i=1;i<N-1;i++)
{
        if(arr[i] > arr[i-1] && arr[i] > arr[i+1])
        peaks++;
}
printf("Local peaks =%d\n",peaks);

current=1;
longest=1;
for(i=1;i<N;i++){
        if(arr[i]>arr[i-1])
        current++;
        else
        current=1;
        if(current > longest)
        longest=current;
}
printf("longest increasing = %d\n",longest);

printf("Enter k:");
scanf("%d",&k);
k=k%N;
if(k<0)
   k=k+N;
for(int j=0;j<k;j++)
{
        temp=arr[N-1];
        for(i=N-1;i>=1;i--)
                arr[i]=arr[i-1];
        arr[0]=temp;
}
printf("Rotated array:");
for(i=0;i<N;i++)
        printf("%d",arr[i]);
printf("\n");
printf("Enter two digits of reg no(0 to 99):");
scanf("%d",&r);
d=(r%9)+1;
for(i=0;i<N;i++){
        if(arr[i]%d==0)
                count++;
}
printf("D=%d\n",d);
printf("Values divisible by D =%d\n",count);

return 0;
}


