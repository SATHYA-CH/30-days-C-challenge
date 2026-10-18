int main()
{
        int choice,n,i,fact;
        float a,b,c,x,D,r1,r2,real,imag;
while(1)
        {
                printf("\n ---Equation sloving--- \n");
                printf("1.Linear equation \n");
                printf("2.Factorial \n");
                printf("3.Quadratic \n");
                printf("0.Exit");
                printf("Enter your choice");
                scanf("%d",&choice);
        if(choice==0)
        {
                printf("....");
                break;
        }
        if(choice<=0 || choice>3)
        {
                printf("invalid Try again");
                continue;
        }
switch(choice)
        {
                case 1:
                printf("Enter the values");
                scanf("%f %f",&a,&b);
                if(a!=0)
                {
                        x=-(b/a);
                        printf("x = %f",x);
                }
                                else if(b == 0){
                        printf("infinite solutions \n");
                }
                else
                {
                        printf("No solution \n");
                }
                break;

                case 2:
                printf("Enter a number (0 to 12)");
                scanf("%d",&n);
                if(n<0||n>12)
                {
                        printf("Invalid enter(0 to 12)");
                        break;
                }
                else
                {
                        fact=1;
                        for(i=1;i<=n;i++)
                        {
                                fact*=i;
                        }
                        printf("Factorial of %d= %d \n",n,fact);
                }
                break;

                case 3:
                printf("Enter the values");
                scanf("%f %f %f",&a,&b,&c);
                if(a==0)
                {
                        printf("not a quadratic");
                        break;
                }
                D=b*b-4*a*c;
                if(D>0)
                {
                        r1=(-b+sqrt(D))/2*a;
                        r2=(-b-sqrt(D))/2*a;
                        printf("Two distinct real roots: %f and %f \n",r1,r2);
                }
                else if(D==0)
                {
                        r1=-b/(2*a);
                        printf("Equal roots:%f and %f \n",r1,r1);

                }
                else
                {
                        printf("no real roots or imaginary roots");
                }
                break;
        }
}
return 0;
}

