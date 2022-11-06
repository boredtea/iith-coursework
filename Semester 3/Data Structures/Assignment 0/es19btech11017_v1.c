#include <stdio.h>

int compare(char A[7], char B[7])
{
  for (int i = 0; i < 7; i++)
  {
    if (A[i] < B[i])
      return 1;
    else if (A[i] >= B[i])
      return 0;
  }
}

int main()
{
  char numberPlate[2][7];
  _Bool act = 0;
  int output;
  while (scanf("%s", numberPlate[act]) != EOF)
  {
    act = 1 - act;
    if (act == 0)
    {
      output = compare(numberPlate[0], numberPlate[1]);
      printf("%d\n", output);
    }
  }
  return (0);
}