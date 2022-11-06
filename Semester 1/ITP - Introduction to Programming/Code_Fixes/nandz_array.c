#include<stdio.h>
int main(void)
{
   int  array1[10] = { 1,2,3,4,5,6,7,8,9,10} ; 
   int  array2[10] = { 11,22, 33, 44, 55, 66, 77, 88, 99, 100 } ; 
   int i,j;
   int array[20];
   int count=0;

    for(i=0;i<10;i++)
    {
      printf("%d ",array1[i]);
      array[count]=array1[i];
      count++;
    }

    for(j=0;j<10;j++)
    {
        for(i=0;i<10;i++)
        {
           if(array2[j]!=array1[i])
           {
              if(i==9)
                 printf("%d ",array2[j]);
                 array[count]=array2[j];
                 count++;
           }
        }
    }
    for(i=0;i<count;i++)
    {
      printf("%d ", array[i]);
    }
}