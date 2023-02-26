#include <stdio.h>
#include <stdlib.h>

#define	SIZEOFNODE (sizeof(struct sn))

//Creating a type with named values, to help with simplicity
enum bracketT
        {CURLY, SQUARE, ROUND};
enum bracketP
        {OPEN, CLOSE};

//New struck to hold the character value and what type of bracket it is;
//Refer to the struct defintion below for a better understanding
struct table{
    char ch;
    enum bracketT type;
};

//New new for structure type type
typedef struct table Table, *pTable;

//Table structure - Based on the table defintion that was mentioned beforehand
//Note that the actual bracket value is placed through, along with its
//type
Table	bracketTable [6]	=	{
        {	'{',	CURLY},
        {	'}',	CURLY},
        {	'[',	SQUARE},
        {	']',	SQUARE},
        {	'(',	ROUND},
        {	')',	ROUND}
};

//Essentialy is able to verify whether the bracket is legitimate
//And, if so, will input it acces into the table that is directly above.
pTable lookup (char c){
    int		i;
    pTable	p;
    for (i=0, p=bracketTable; i<6; i++,p++)	{
        if (p->ch == c)	return p;
    }
    return NULL;
}

//Defintion for the nodes in the stack
struct sn {
    struct sn *next;
    enum bracketT brkt;
};

typedef struct sn	StkNode, *pStkNode;
StkNode	*head = NULL;

//Push function for the brackets - Pushes from the given array into the stack
void push (enum bracketT brktype){
    StkNode *p = (StkNode *)malloc(SIZEOFNODE);
    p->brkt = brktype;
    p->next = head;
    head = p;
}

//Function to pop the brackets from the array and returns whether a result is produced
int  pop (enum bracketT *pbrktype){
    int	rslt = 0;
    if ((pbrktype != NULL)){
        StkNode *p = head;
        if (p != NULL)	{
            head = p->next;
            *pbrktype = p->brkt;
            free (p);
            rslt = 1;
        }
    }
    return rslt;
}

int main (){
    //Shorthand - All code that is used to ask user what the input should be and
    //And puts it in format (array) for the stack to access
    printf("How many brackets are needed?");
    int i;
    scanf("%d", &i);
    char array[i];
    printf("What are the brackets?");
    for(int j = 0; i>j; j++){
        scanf("%c", &array[j]);
    }
    //Defines below values to the main function
    enum bracketT brktype;
    Table *pTab;
    //For loop that iterates through the given array
    for(int j = i-1; j == 0; j--){
        //If statement for when the bracket is an open bracket
        //Essentially places it into the stakc via the push function and continues
        if (array[j] == '{' || array[j] == '(' || array[j] == '[')	{
            pTab = lookup(array[j]);
            push (pTab->type);
            continue;
        }
        //From the array, when its a closed bracket, while pop the top value and see if they
        //have the same type - If so, then the for loop continues and
        //No false result is given;
        if (array[j] == '}' || array[j] == ')' || array[j] == ']')	{
            pTab = lookup(array[j]);
            if (pop (&brktype))	{
                if (pTab->type != brktype)	{
                    printf ("Brackets are not matching");
                    return 0;
                }
            } else	{
                printf ("Brackets are not Matching");
                return 0;
            }
            continue;
        }
    }
    //Extra piece of conditionals to check whether the theres an extra open brackets that were left
    //behind, that would produce a negative result
    while (pop (&brktype))	{
        printf ("Brackets are not Matching");
        return 0;
    }
    //If a correct result is placed, then a true false is placed and the code is successfully
    //ran!
    return 1;
}
