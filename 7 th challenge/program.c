#include<stdio.h>
int main(){
int pairs=0,N,tickets[15],i,id,j,missing,missingCount,duplicate,duplicateCount,invalid;
int count=0,R,target;
do
{
        printf("Enter the value of N (5 to 15): \n");
        scanf("%d",&N);
        if(N<5 || N>15)
                {
                printf("Invalid entry: \n");
                }
}while(N<5 || N>15);
for(i=0;i<=N-1;i++)
{
        do
        { 
                printf("Enter the ticket num: \n");
                scanf("%d",&tickets[i]);
        }while(tickets[i]<1 || tickets[i]>N);
}
for(i=0;i<N;i++)
{
        printf("%d",tickets[i]);
}
printf("\n Original scan order");
for(i=0;i<=N-1;i++)
{
        printf("\n");
}
for (id = 1; id <= N; id++)
    {
        count = 0;
        for (j = 0; j < N; j++)
        {
            if (tickets[j] == id)
                count++;
        }
        if (count == 0)
        {
            missing = id;
            missingCount++;
        }
        else if (count == 2)
        {
            duplicate = id;
            duplicateCount++;
        }
        else if (count > 2)
            invalid = 1;
    }
    
if (missingCount != 1 || duplicateCount != 1 || invalid == 1)
    {
        printf("Invalid scan log: it must have exactly one missing ID and exactly one duplicated ID.\n");
        return 0;
    }

    printf("Duplicate ticket ID: %d\n", duplicate);
    printf("Missing ticket ID: %d\n", missing);

for (i = 0; i < N - 1; i++)
{
    for (j = i + 1; j < N; j++)
    {
        if (tickets[i] > tickets[j])
            pairs++;
    }
}
printf("Out-of-order pairs: %d\n", pairs);
target = (R % N) + 1;
    count = 0;
    printf("Target ticket ID: %d\n", target);
    printf("Positions: ");
    for (i = 0; i < N; i++)
    {
        if (tickets[i] == target)
        {
            printf("%d ", i + 1);   
            count++;
        }
    }
    printf("\n");
    printf("Occurrence count: %d\n", count);

    return 0;
}


