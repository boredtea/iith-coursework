#include <stdio.h>

int main ()
{ 
	int B,N,i,A;
	char store;
	
	printf("Enter N: ");
	scanf("%d",&N);
	if (N>=0)
	{
		printf("Enter current balance: ");
		scanf("%d",&B);
		for(i=1;i<=N;i++)
		{
			printf("Enter operater (w, a, p): ");
			while((store = getchar()) == '\n');

		 	switch(store)
			 {
		 		case 'w':
				 	printf("Enter amount: ");
					scanf("%d",&A);
					if(B<A)
					{
						printf("error\n");
					}
					else 
					{
						B=B-A;
						printf("WithdrawAmount\n");
						printf("Success\n");
					}
					break;
				case 'a':
					printf("Enter amount: ");
					scanf("%d",&A);
					B=A+B;
					printf("AddAmount\n");
					printf("Success\n");
					break;
				case 'p':
					printf("GetBalance\n");
					printf("%d\n",B);
					break;
				default:
					printf("error\n");
			 }
		}
	}
}


	
	
	
