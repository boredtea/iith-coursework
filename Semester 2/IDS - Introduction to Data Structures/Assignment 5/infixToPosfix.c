#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
    
    int identity;
    char character;
    double operand; //stores operands while evaluating the postfix expression
    struct node *next;
};
typedef struct node Node;

struct stack
{
    Node *start;
    int length; //stores length of stack and helps with indentation while printing
};
typedef struct stack Stack;


struct element
{
    char element[50]; //stores one element of the expression
    int flag; //helps keep track of whether element is a number or operator flag = 1: number; flag = 0: operator
    struct element *next;
};
typedef struct element Element;

struct expression
{
    Element *start;
    Element *end;
    int length;
};
typedef struct expression Expression;

Expression* createExpression()
{
    Expression *X = (Expression*)malloc(sizeof(Expression));
    X->length = 0;
    Element *fakeStart = (Element*)malloc(sizeof(Element));
    fakeStart->next = NULL;
    X->start = fakeStart;
    return X;
}

void insertExpression(Expression *X, char element[10], int flag)
{
    Element *newnode = (Element *)malloc(sizeof(Element));
    strcpy(newnode->element, element);
    newnode->flag = flag;
    newnode->next = NULL;

    //inserting in the end
    Element *current;

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


int eject(Expression *X)
{
    //deleting from the beginning
    Element *current = X->start;
    int ejected;
    char operator;
    
    Element *helper = current->next;

    if(helper->flag == 1) //for a number
        ejected = atoi(helper->element);
    else if(helper->flag == 0) //for an operator
    {
        operator = *(helper->element);
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

    return ejected;
}

Stack *createStack()
{
    Stack *S = (Stack *)malloc(sizeof(Stack));
    S->length = 0;
    Node *fakeStart = (Node *)malloc(sizeof(Node));
    fakeStart->next = NULL;
    S->start = fakeStart;
    return S;
}

void Push(Stack *S, int identity, char ch, double operand)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
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

Node* Pop(Stack *S)
{
    //deleting from the beginning
    Node *current = S->start;
    Node *helper = current->next;
    current->next = helper->next;

    S->length--; //decrementing length of the stack

    return helper; //returning popped element
}



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

int expressionValidityCheck(int length, char expression[length], int identities[length])
{
    //checking if all characters present are valid
    int flag = 1;
    //int identities[length]; //array to store the identites of each character in the expression as mentioned in validCharacter()
    Stack *brackets = createStack(); //stack to help check for balanced brackets
    Node *popped;


    for(int i = 0; i < length; i++)
    {
        identities[i] = validCharacter(expression[i]);
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
                    printf("Invalid expression: an operator is missing the second operand near symbol %d.\n\n", i+1); //change to operator missing operand
                    return flag;
                }
                
            }
            else
            {
                flag = -1;
                printf("Invalid expression: an operator is missing an operand near symbol %d.\n\n", i+1); //change to operator missing operand
                return flag;
            }
        }
        else if((identities[i] >= 15) && (identities[i] <= 20))
        {
            if((i != length - 1) && (identities[i] >= 18) && ((identities[i+1] >= 15) && (identities[i+1] <= 17))) //no opening brackets right after closing brackets: (){}
            {
                flag = -1;
                printf("Identites[%d]: %d\n", i+1, identities[i+1]);
                printf("Invalid expression: missing operator near symbol %d.\n\n", i+1);
                return flag;
            }
            /*else if((i != length - 1) && (identities[i] <= 17) && (identities[i+1] >= 18)) //no closing brackets right after opening brackets: ()
            {
                flag = -1;
                printf("Identites[%d]: %d\n", i+1, identities[i+1]);
                printf("Identites[%d]: %d\n", i, identities[i]);
                printf("Invalid expression: missing operand near symbol %d.\n\n", i+1);
                return flag;
            }*/

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


void infixToPostfix(int length, char expression[length], int identities[length], Expression *postfixExpression)
{

    Stack *Operators = createStack();
    Node *popped;
    Node *current = Operators->start; //used to look at the top of the stack

    char token[50]; //stores the current scanned element of the expression 

    int operands = 0; //stores the number of operands to deal with one final case of validity check
    int operators = 0; //stores the number of operators to deal with one final case of validity check

    int k = -1; //for token

    for(int i = 0; i < length; i++)
    {
        if(identities[i] >= 0 && identities[i] <= 9) //operands
        {
            token[++k] = expression[i];
            if((identities[i+1] > 9) || (i == length - 1))
            {
                insertExpression(postfixExpression, token, 1);
                operands++;
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
                    operators++;
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


            current = Operators->start->next;

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
                while(current->identity <= identities[i] && Operators->length > 0) //if the operator in the stack if of equal or of higher preference than the scanned operator, pop it
                {
                    popped = Pop(Operators);

                    //inserting element into the postfix expression linked list
                    token[++k] = popped->character;
                    insertExpression(postfixExpression, token, 0);
                    operators++;
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
        operators++;
        //resetting token and k for the next element
        memset(token, '\0', k+1);
        k = -1;
    }

    
}


void evaluation(Expression *postfix)
{
    Stack *evaluationStack = createStack();
    Element *currentToken;
    Node *poppedOperand;
    int token; //stores a token of the postfix expression, one at a time

    double operand1, operand2, result;

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

    poppedOperand = Pop(evaluationStack);
    result = poppedOperand->operand;

    if(evaluationStack->length == 0)
    printf("The value of the expression is: %lf\n\n", result);
    else
    {
        printf("Invalid expression: missing operand.\n\n");
    }
    
}



int main()
{
    char expression[100];
    printf("Enter infix expression (Note: do NOT use spaces anywhere): \n");
    scanf("%[^\n]%*c", expression);

    int length = strlen(expression);
    int identities[length];

    int flag = expressionValidityCheck(length, expression, identities);

    Expression *postfix = createExpression();

    if(flag == 1)
    {

        printf("\n\n");

        infixToPostfix(length, expression, identities, postfix);
        PrintExpression(postfix);
        evaluation(postfix);
    }
}
