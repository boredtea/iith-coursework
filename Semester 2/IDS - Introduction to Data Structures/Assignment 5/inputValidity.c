#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int bracket;
    char token[5]; //stores either a number or an operator or bracket
    struct node *next;
};
typedef struct node Node;

struct stack
{
    Node *start;
    int length; //stores length of stack and helps with indentation while printing
};
typedef struct stack Stack;

Stack *createStack()
{
    Stack *S = (Stack *)malloc(sizeof(Stack));
    S->length = 0;
    Node *fakeStart = (Node *)malloc(sizeof(Node));
    fakeStart->next = NULL;
    S->start = fakeStart;
    return S;
}

void Push(Stack *S, int ch)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->bracket = ch;
    newnode->next = NULL;

    //inserting in the beginning
    Node *current = S->start;
    newnode->next = current->next;
    current->next = newnode;

    S->length++; //incrementing length of the stack
}

Node* Pop(Stack *S)
{
    //deleting from the beginning
    Node *current = S->start;
    Node *helper = current->next;
    current->next = helper->next;

    S->length--; //decrementing length of the stack

    return helper; //returning popped element
}

void Print(Stack *S)
{
    if (S->length > 0)
    {
        Node *current = S->start;
        printf("{"); //start of each line
        for (int i = 0; i < S->length; i++)
        {
            current = current->next;
            printf("%d ", current->bracket);
        }
        printf("\n");
    }
    else
    {
        printf("Empty.\n");
    }
    
}

int validCharacter(char ch)
{
    int flag = -1;
    /*
    Identity numbers:
    - 0 to 9: digits
    - 10 to 14: operators
    - 15 to 20: brackets
    */
    int characters[21] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '^', '*', '/', '+', '-', '[', '{', '(', ')', '}', ']'};

    for(int i = 0; i < 21; i++)
    {
        if(ch == characters[i])
        {
            flag = i;
            break;
        }
    }
    return flag;
}

int expressionValidityCheck(int length, char expression[length])
{
    //checking if all characters present are valid
    int flag = 1;
    int identities[length]; //array to store the identites of each character in the expression as mentioned in validCharacter()
    Stack *brackets = createStack(); //stack to help check for balanced brackets
    Node *popped;

    for(int i = 0; i < length; i++)
    {
        identities[i] = validCharacter(expression[i]);
        if(identities[i] == -1) //checking for correct characters
        {
            flag = -1;
            printf("Invalid expression: invalid character.\n\n");
            return flag;
        }
        else if(identities[i] >= 10 && identities[i] <= 14) //checking for correct operators
        {
            if((i != 0) && (i != length - 1) && (((identities[i-1] >= 0) && (identities[i-1] <= 9)) || ((validCharacter(expression[i-1]) >= 18) && (validCharacter(expression[i-1]) <= 20)))) //checking if the operator is always in front of a number
            {
                //checking if the operator is behind a number
                if(((validCharacter(expression[i+1]) >= 0) && (validCharacter(expression[i+1]) <= 9)) || ((validCharacter(expression[i+1]) >= 15) && (validCharacter(expression[i+1]) <= 17)))
                {
                    flag = 1;
                }
                else
                {
                    flag = -1;
                    printf("Invalid expression: an operator is missing the second operand.\n\n"); //change to operator missing operand
                    return flag;
                }
                
            }
            else
            {
                flag = -1;
                printf("Invalid expression: an operator is missing the first operand.\n\n"); //change to operator missing operand
                return flag;
            }
        }
        else if((identities[i] >= 15) && (identities[i] <= 20))
        {
            
            if(identities[i] <= 17)
            {
                Push(brackets, identities[i]);
            }
            else if(identities[i] >= 18)
            {
                if(brackets->length == 0)
                {
                    flag = -1;
                    printf("Invalid expression: unbalanced brackets.\n\n");
                    return flag;
                }
                popped = Pop(brackets);
                if(popped->bracket + identities[i] != 35)
                {
                    flag = -1;
                    printf("Invalid expression: unbalanced brackets.\n\n");
                    return flag;
                }
            }
        }
    }

    if(brackets->length != 0)
    {
        flag = -1;
        printf("Invalid expression: unbalanced brackets.\n\n");
        return flag;
    }
    
    return flag;
}

int main()
{
    char expression[100];
    printf("Enter infix expression (Note: do NOT use spaces anywhere): \n");
    scanf("%[^\n]%*c", expression);

    int length = strlen(expression);

    int flag = expressionValidityCheck(length, expression);

    if(flag == 1)
    printf("Valid expression!\n\n");
    
}
