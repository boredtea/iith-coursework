#include<stdio.h>


int Add(int x,int y)
{
    int R; 
    R=x+y;
    return R;
}


int Subtract(int x, int y)
{
    int R;
    R=x-y;
    return R;
}


int Multiply(int x, int y)
{
    int R=0, i;
    for(i=1;i<=y;i++)
    {
        R=R+x;
    }
    return R;
}


int Divide(int x,int y)
{
    int R=x, i=0;
     if(y=0)
    {
        printf("The value of the 2nd number should be positive");
    }
    else
    {
        while(R>=0)
        {
           R=R-y;
           i=i+1;
        }
        printf("The result is: %d",i);
    }
    return 0;
}


int Modulus(int x,int y)
{
    int R=x;
    if(y=0)
    {
        printf("The value of the 2nd number should be positive");
    }
    else
    {
        while(R>=0)
        {
           R=R-y;
        }
        printf("The result is: %d",R);
    }
    return 0;
}


int Square(int x)
{
    int k;
    k=Multiply(x,x);
    return k;
}


int SquareRoot(int x)
{
    int i,k;
    while(k<=x)
    {
       k=Multiply(i,i);
       i=i+1;
    }
    return i;
}


int main(void)
{
    int N, x,y,i,k,R;
    N = 0;
    while(N != 9)
    {
        printf("\nEnter the number corresponding to the opertation you want to perform.");
        printf("\nMENUE: ");
        printf("\n1:Add\n2:Subtract\n3:Multiply\n4:Divide\n5:Modulus\n6:Square\n7: Square Root\n8:Log (Base : 2)\n9:Exit");
        printf("\nYour Choice: ");
        scanf("%d",&N);
        //int Add(int,int)
        if(N==1)
        {
            printf("Enter the first number: ");
            scanf("%d",&x);
            printf("\nEnter the second number: ");
            scanf("%d",&y);
            if(x>=0&&y>=0)
            {
                R=Add(x,y);
                printf("The result is: %d", R);
            }
            else
            {
                printf("Invalid Input");
            }
        }

        
        //int Subtract(int,int)
        else if(N==2)
        {
            printf("Enter the first number: ");
            scanf("%d",&x);
            printf("\nEnter the second number: ");
            scanf("%d",&y);
            if(x>=0&&y>=0)
            {
                R=Subtract(x,y);
                printf("The result is: %d", R);
            }
            else
            {
                printf("Invalid Input");
            }
        }

        
        //int Multiply(int,int)
        else if(N==3)
        {
            printf("Enter the first number: ");
            scanf("%d",&x);
            printf("\nEnter the second number: ");
            scanf("%d",&y);
            if(x>=0&&y>=0)
            {
                R=Multiply(x,y);
                printf("The result is: %d", R);
            }
            else
            {
                printf("Invalid Input");
            }
        }

        
        //int Divide(int,int)
        else if(N==4)
        {
            printf("Enter the first number: ");
            scanf("%d",&x);
            printf("\nEnter the second number: ");
            scanf("%d",&y);
            if(x>=0&&y>=0)
            {
                Divide(x,y);
            }
            else
            {
                printf("Invalid Input");
            }
        }

        
        //int Modulus(int,int)
        else if(N==5)
        {
            printf("Enter the first number: ");
            scanf("%d",&x);
            printf("\nEnter the second number: ");
            scanf("%d",&y);
            if(x>=0&&y>=0)
            {
                Modulus(x,y);
            }
            else
            {
                printf("Invalid Input");
            }
        }

        
        //int Square(int)
        else if(N==6)
        {
            printf("Enter the first number: ");
            scanf("%d",&x);
            if(x>=0)
            {
                k=Square(x);
                printf("The result is: %d", k);
            }
            else
            {
                printf("Invalid Input");
            }
        }


        //int Squareroot(int)
        else if(N==7)

        {
            printf("Enter the first number: ");
            scanf("%d",&x);
            if(x>=0)
            {
                i=SquareRoot(x);
                printf("The result is: %d", i);
            }
            else
            {
                printf("Invalid Input");
            }
        }
    }
    return 0;
}
