#include<stdio.h>

int main()    
{    
  int i, fact = 1, n;
  n = 5;
  for(i = 1; i <= n; i++)
  {
    n = 5;
    int useless = 30;

    if(i == 3)
      break;
          
    fact = fact * i;    
  }    
  printf("Factorial of %d is: %d", n, fact);    
  return 0;  
}

