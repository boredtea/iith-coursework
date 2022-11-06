#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



/**********STRUCTURES**********/

/*NODE
The node struct helps in making individual units of the stack.
One node consists of the identity of each character, the character, 
and an operand. All these data types are used in different places 
as and when required. It also contains a pointer to point to the next unit.
*/

struct node
{
    int identity; //stors the identity of each character present in the expression according to validCharacter()
    char character;
    double operand; //stores operands while evaluating the postfix expression
    struct node *next;
};
typedef struct node Node;


/*STACK
The stack struct helps in building a functioning stack.
It links the nodes together and keeps track of the length of the stack.
*/
struct stack
{
    Node *start;
    int length; //stores length of stack and helps with indentation while printing
};
typedef struct stack Stack;


/*ELEMENT
The element struct helps in making individual units of a functioning 
queue called expression. One element consists of either an operand or an 
operator, and a flag. It also contains a pointer to point to the next unit.
*/
struct element
{
    char element[50]; //stores one element of the expression
    int flag; //helps keep track of whether element is a number or operator flag = 1: number; flag = 0: operator
    struct element *next;
};
typedef struct element Element;


/*EXPRESSION
The expression struct helps in building a functioning queue.
It links the elements together and keeps track of the length of the stack.
*/
struct expression
{
    Element *start;
    Element *end;
    int length;
};
typedef struct expression Expression;



/**********FUNCTIONS**********/

/*
Function to allocate space in memory to the expression and 
return a pointer to the new, empty queue.
*/
Expression* createExpression()
{
    Expression *X = (Expression*)malloc(sizeof(Expression));
    X->length = 0;
    Element *fakeStart = (Element*)malloc(sizeof(Element));
    fakeStart->next = NULL;
    X->start = fakeStart;
    return X;
}

/*
Function to append an element to the expression. It stores the 
element in a character array and flag decides whether it is an 
operand or operator.
*/
void insertExpression(Expression *X, char element[10], int flag)
{
    Element *newnode = (Element *)malloc(sizeof(Element));
    //assigning data to element
    strcpy(newnode->element, element);
    newnode->flag = flag;
    newnode->next = NULL;

    Element *current;

    //inserting in the end
    if(X->length == 0)
    {
        current = X->start;
        newnode->next = current->next;
        current->next = newnode;
        X->end = newnode;
    }
    else
    {
        current = X->end;
        newnode->next = current->next;
        current->next = newnode;
        X->end = newnode;
    }
    
    X->length++; //incrementing length of the queue
}

/*
Function to return the first element of the expression. It is
used during evaluation of the postfix expression.
*/
int eject(Expression *X)
{
    int ejected;
    char operator;
    
    //deleting from the beginning
    Element *current = X->start;
    Element *helper = current->next;

    if(helper->flag == 1) //for a number
        ejected = atoi(helper->element); //converting string to a number
    else if(helper->flag == 0) //for an operator
    {
        operator = *(helper->element);
        //assigning numerical values to each operator
        switch(operator)
        {
            case '^': 
                ejected = 1;
            break;

            case '*':
                ejected = 2;
            break;

            case '/':
                ejected = 3;
            break;

            case '+':
                ejected = 4;
            break;

            case '-':
                ejected = 5;
            break;
        }
    }
    current->next = helper->next;

    X->length--; //decrementing length of the queue

    return ejected; //returning the first element
}


/*
Function to allocate space in memory to a stack and 
return a pointer to the new, empty stack.
*/
Stack *createStack()
{
    Stack *S = (Stack *)malloc(sizeof(Stack));
    S->length = 0;
    Node *fakeStart = (Node *)malloc(sizeof(Node));
    fakeStart->next = NULL;
    S->start = fakeStart;
    return S;
}


/*
Function to push the identity and character, or the operand into a stack.
*/
void Push(Stack *S, int identity, char ch, double operand)
{
    Node *newnode = (Node *)malloc(sizeof(Node));

    //assigning data to the node
    newnode->identity = identity;
    newnode->character = ch;
    newnode->operand = operand;
    newnode->next = NULL;

    //inserting in the beginning
    Node *current = S->start;
    newnode->next = current->next;
    current->next = newnode;

    S->length++; //incrementing length of the stack
}


/*
Function to pop a node from a stack.
*/
Node* Pop(Stack *S)
{
    //deleting from the beginning
    Node *current = S->start;
    Node *helper = current->next;
    current->next = helper->next;

    S->length--; //decrementing length of the stack

    return helper; //returning popped element
}

/*
Function to print the postfix expression.
*/
void PrintExpression(Expression *X)
{
    Element *current = X->start;
    printf("Postfix expression: \n");
    for(int i = 0; i < X->length; i++)
    {
        current = current->next;
        printf("%s ", current->element);
    }
    printf("\n\n");
    
}


/*
Function to check the validity, and assign identities to each character.
*/
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


/*
Function to check the validity of the entered infix expression.
*/
int expressionValidityCheck(int length, char expression[length], int identities[length])
{
    int flag = 1; //keeps track of whether invalidity has been encountered

    //stack and node to help check for balanced brackets
    Stack *brackets = createStack(); 
    Node *popped;

    //loop to go through the entire string array infix expression
    for(int i = 0; i < length; i++)
    {
        identities[i] = validCharacter(expression[i]); //assign identities to each character according to validCharacter()
        if(identities[i] == -1) //checking for correct characters
        {
            flag = -1;
            printf("Invalid expression: invalid character at symbol %d.\n\n", i+1);
            return flag;
        }
        else if(identities[i] >= 10 && identities[i] <= 14) //checking for correct operators
        {
            //checking if the operator is always in front of a number
            if((i != 0) && (i != length - 1) && (((identities[i-1] >= 0) && (identities[i-1] <= 9)) || ((validCharacter(expression[i-1]) >= 18) && (validCharacter(expression[i-1]) <= 20))))
            {
                //checking if the operator is behind a number
                if(((validCharacter(expression[i+1]) >= 0) && (validCharacter(expression[i+1]) <= 9)) || ((validCharacter(expression[i+1]) >= 15) && (validCharacter(expression[i+1]) <= 17)))
                {
                    flag = 1;
                }
                else
                {
                    flag = -1;
                    printf("Invalid expression: an operator is missing the second operand near symbol %d.\n\n", i+1);
                    return flag;
                }
                
            }
            else
            {
                flag = -1;
                printf("Invalid expression: an operator is missing an operand near symbol %d.\n\n", i+1);
                return flag;
            }
        }
        else if((identities[i] >= 15) && (identities[i] <= 20)) //brackets
        {

            if(identities[i] <= 17) //push to stack when opening bracket is encountered
            {
                Push(brackets, identities[i], expression[i], 0);
            }
            else if(identities[i] >= 18) //pop from stack when closing bracket is encountered
            {
                if(brackets->length == 0)
                {
                    flag = -1;
                    printf("Invalid expression: unbalanced brackets near symbol %d.\n\n", i+1);
                    return flag;
                }
                popped = Pop(brackets);

                //the sum of the identities of an opening bracket with it's corresponding closing bracket is 35
                if(popped->identity + identities[i] != 35) 
                {
                    flag = -1;
                    printf("Invalid expression: unbalanced brackets near symbol %d.\n\n", i+1);
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


/*
Function to convert the infix expression to its postfix expression.
*/
void infixToPostfix(int length, char expression[length], int identities[length], Expression *postfixExpression)
{
    //node and operator stack that helps deal with operator precedence
    Stack *Operators = createStack(); 
    Node *popped;
    Node *current = Operators->start; //used to look at the top of the stack

    char token[50]; //stores the current scanned element of the expression 
    int k = -1; //for token

    //loop for going through every character in the infix expression
    for(int i = 0; i < length; i++)
    {
        if(identities[i] >= 0 && identities[i] <= 9) //operands
        {
            token[++k] = expression[i];
            if((identities[i+1] > 9) || (i == length - 1))
            {
                insertExpression(postfixExpression, token, 1);
                //resetting token and k for the next element
                memset(token, '\0', k+1);
                k = -1;
            }
        }
        else if(identities[i] >= 15 && identities[i] <= 20) //brackets
        {
            if(identities[i] <= 17) //opening bracket
            {
                Push(Operators, identities[i], expression[i], 0);
            }
            else //closing brackets
            {
                popped = Pop(Operators);
                while(popped->identity + identities[i] != 35) //pop operators until the corresponding opening bracket is encountered
                {
                    //inserting element into the postfix expression linked list
                    token[++k] = popped->character;
                    insertExpression(postfixExpression, token, 0);
                    //resetting token and k for the next element
                    memset(token, '\0', k+1);
                    k = -1;

                    popped = Pop(Operators);
                }
            }
            
        }
        else if(identities[i] >= 10 && identities[i] <= 14) //checking for operators
        {
            if(identities[i] == 12) //since * and / have the same precedence
            identities[i] = 11;
            else if(identities[i] == 14) //since + and - have the same precedence
            identities[i] = 13;


            current = Operators->start->next; //setting pointer to the top of the operator stack

            if(Operators->length == 0) //if empty stack, push operator
            {
                Push(Operators, identities[i], expression[i], 0);
            }
            else if(current->identity >= 15 && current->identity <= 17) //if stack contains opening bracket
            {
                Push(Operators, identities[i], expression[i], 0);
            }
            else if(identities[i] < current->identity) //if the operator of the top of the stack has precedence lower than the scanned operator
            {
                Push(Operators, identities[i], expression[i], 0);
            }
            else
            {
                current = Operators->start->next;
                //if the operator in the stack is of equal or of higher preference than the scanned operator, pop it
                while(current->identity <= identities[i] && Operators->length > 0)
                {
                    popped = Pop(Operators);

                    //inserting element into the postfix expression linked list
                    token[++k] = popped->character;
                    insertExpression(postfixExpression, token, 0);
                    //resetting token and k for the next element
                    memset(token, '\0', k+1);
                    k = -1;

                    if(current->next == NULL)
                    {
                        break;
                    }
                    else
                    current = Operators->start->next;

                    //according to the identities of the brackets, the scanned operator will automatically be pushed when brackets are encountered
                }
                Push(Operators, identities[i], expression[i], 0);
            }
        }
        
    }
    while(Operators->length != 0)
    {
        popped = Pop(Operators);

        //inserting element into the postfix expression linked list
        token[++k] = popped->character;
        insertExpression(postfixExpression, token, 0);
        //resetting token and k for the next element
        memset(token, '\0', k+1);
        k = -1;
    }

    
}


/*
Function to evaluate the postfix expression and print the result.
*/
void evaluation(Expression *postfix)
{
    Stack *evaluationStack = createStack(); //stack to store all the operands during evaluation
    Element *currentToken;
    Node *poppedOperand;

    int token; //stores a token of the postfix expression, one at a time

    double operand1, operand2, result; //stores current operands and result


    while(postfix->length > 0)
    {
        currentToken = postfix->start->next;
        token = eject(postfix);
        if(currentToken->flag == 1) //if the postfix expression contains an operand
        {
            //push it to the evaluation stack
            Push(evaluationStack, -1, '\0', (double)token);
        }
        else if(currentToken->flag == 0) //if the postfix expression contains an operator
        {
            //pop two operands from the evaluation stack
            poppedOperand = Pop(evaluationStack);
            operand1 = poppedOperand->operand;
            poppedOperand = Pop(evaluationStack);
            operand2 = poppedOperand->operand;


            //use switch case to decide the operation
            switch(token)
            {
                case 1: // ^
                    result = pow(operand2, operand1);
                    break;

                case 2: // *
                    result = operand2 * operand1;
                    break;

                case 3: // /
                    result = operand2 / operand1;
                    break;

                case 4: // +
                    result = operand2 + operand1;
                    break;

                case 5: // -
                    result = operand2 - operand1;
                    break;
            }
            Push(evaluationStack, -1, '\0', result); //push the result back to the evaluation stack
        }
    }

    //popping the final result
    poppedOperand = Pop(evaluationStack);
    result = poppedOperand->operand;

    if(evaluationStack->length == 0)
    printf("The value of the expression is: %lf\n\n", result);
    else
    {
        printf("Invalid expression: missing operand.\n\n");
    }
    
}


/*
Main function.
*/
int main()
{
    //asking user for the infix expression
    char expression[100];
    printf("Enter infix expression (Note: do NOT use spaces anywhere): \n");
    scanf("%[^\n]%*c", expression);

    int length = strlen(expression);
    int identities[length]; //creating array to store identities 

    int flag = expressionValidityCheck(length, expression, identities); //checking if the given infix notation is valid

    Expression *postfix = createExpression(); //creating an expression queue to store and help evaluate postfix expression

    //evaluating the postfix expression only if the infix expression given is valid
    if(flag == 1)
    {
        printf("\n");

        infixToPostfix(length, expression, identities, postfix);
        PrintExpression(postfix);
        evaluation(postfix);
    }
}
