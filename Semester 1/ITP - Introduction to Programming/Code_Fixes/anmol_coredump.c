#include <stdio.h>
#include <math.h>



void multi(int r1,int c1,int r2,int c2, int A[][c1],int B[][c2], int C[][c2])
{
								// creating array of proper dimensions
	for(int k=0;k<c2;k++)
	{
		for(int j=0;j<r1;j++)
		{
			int sum=0;
			for(int i=0;i<c1;i++)		// multiplication of row with individual column elements
			{
				sum +=A[j][i]*B[i][k];  
			}
			C[j][k] = sum;
		}
	}
}
void scan(int n,int A[][n])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			scanf("%d",&A[i][j]);
		}
	}
}
void minor(int n,int i,int j,int A[][n], int B[][n-1])
{
	int a=0;
	for(int k=0;k!=i && k<n;k++)
	{
		int b=0;
		for(int l=0;l!=j && l<n;l++)
		{
			B[a][b] = A[k][l];
			b++;
		}
		a++;
	}
}
int determinant(int n, int A[][n])
{
	if(n==2)
	{
		return A[0][0]*A[1][1] - A[0][1]*A[1][0];
	}
	else
	{
		int B[n-1][n-1];
		int ans=0;
		for(int i=0;i<n;i++)
		{
			minor(n,0,i,A,B);
			if(i%2 == 0)
			{
				ans += determinant(n-1,B);
			}
			else
			{
				ans -= determinant(n-1,B);
			}
		}
		return ans;
	}
}
void adjoint(int n,int A[][n],int B[][n-1],int C[][n])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			minor(n,i,j,A,B);
			int ans=0;
			if((i+j)%2==0)
			{
				ans +=determinant(n-1,B);
			}
			else
			{
				ans -=determinant(n-1,B);
			}
			C[j][i] = ans;
		}
	}
}
int main(void)
{
	int m = 0,n = 0,p = 0,q = 0;
	while(p<2 && q<2 && m<2 && n<2)
	{
		scanf("%d %d %d %d",&m,&n,&p,&q);
	}
	int A[m][n],B[p][q],C[m][q];
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			int hold1;
			scanf("%d",&hold1);
			A[i][j]=hold1;
		}
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			int hold2;
			scanf("%d",&hold2);
			B[i][j]=hold2;
		}
	}
	if(n==p)
	{
		multi(m,n,p,q,A,B,C);		
	}
	else
	{
		printf("The order of matrices must be suitable");
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<q;j++)
		{
			printf("%3d",C[i][j]);
		}
		printf("\n");
	}
	printf("Enter order of square matrix.\n");
	int x;
	scanf("%d",&x);
	printf("\n");
	int dit[x][x];
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<x;j++)
		{
			scanf("%d",&dit[i][j]);
		}
	}
	return 0;
}
