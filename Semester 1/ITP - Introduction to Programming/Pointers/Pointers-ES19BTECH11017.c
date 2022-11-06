#include <stdio.h>
#include <string.h>

//function to reverse
void reverseString(char str[])
{
    int length = strlen(str) - 1; //subtracting 1 to account for the '\0' in the string length

    //pointers used to reverse the string
    char *first, *last;

    first = str;
    last = str;

    //finding end of string and pointing to it
    for(int i = 0; i < length; i++)
        last++;

    char temp; //to switch characters
    //loop to switch characters with each other
    //switching starts at the outer edges of the word and ends in the middle
    for(int i = 0; i < (length + 1)/ 2; i++)
    {
        temp = *first;
        *first = *last;
        *last = temp;

        //pointing to the next character after switching
        first++; 
        last--;
    }
}

int main(int argc, char const *argv[])
{
    char str[20]; //character array used to store string input
    int flag = -1; //variable to handle invalid inputs
    int length = 1; //stores length of input

    //loop to keep taking input until valid iniput is given
    while(flag == -1)
    {
        printf("Enter the string to reverse: ");
        fgets(str, 20, stdin);

        length = strlen(str) - 1;

        //checking input validity
        if(length <= 0 || length > 10)
        {
            printf("Invalid input. Enter again.\n\n");
            strcpy(str, ""); //re-assigning str
            flag = -1;
        }
        else
        {
            flag = 0;
        }
        
    }

    //calling function to reverse string
    reverseString(str);

    printf("Reversed string: %s\n", str);

    return 0;
}