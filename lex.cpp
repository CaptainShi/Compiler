
#include "general.h"
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include "symbolTable.h"

Symbol_table table;

using namespace std;


int main ()
{
   getChar();
   do 
   {
      lex();
      int value = expr();
      cout << "MAIN" << value << endl;
   }
   while(nextToken != 'q');

   return 0;

//NEED TO ADD MORE HERE

}


/*****************************************************/
/* lookup - a function to lookup operators and parentheses
 and return the token */
 int lookup(char ch)
{
 switch (ch) {
 case '(':
 addChar();
 nextToken = LEFT_PAREN;
 break;
 case ')':
 addChar();
 nextToken = RIGHT_PAREN;
 break;
 case '+':
 addChar();
 nextToken = ADD_OP;
 break;
 case '-':
 addChar();
 nextToken = SUB_OP;
 break;
 case '*':
 addChar();
 nextToken = MULT_OP;
 break;
 case '/':
 addChar();
 nextToken = DIV_OP;
 break;
 case '=':
 addChar();
 nextToken = EQUAL;
 default:
 addChar();
 nextToken = EOF;
 break;
 }
 return nextToken;
}
/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar()
{

 if (lexLen <= 98) {
 lexeme[lexLen++] = nextChar;
 lexeme[lexLen] = '\0';
 } else
 printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
 input and determine its character class
 Two globals are set
 nextChar - the next character scanned from the input.
 charClass - the category of the character - LETTER, DiGIT, OPERATOR
*/
void getChar()
{
 //need to chnage to all io redirection
 if ((nextChar = getchar()) != 'q') {
    if (isalpha(nextChar))
       charClass = LETTER;
    else if (isdigit(nextChar))
       charClass = DIGIT;
    else
    charClass = OPERATOR;
 } else
 charClass = EOF;
}
/*****************************************************/
/* getNonBlank - remove white space characters.
 call getChar until it returns a non-whitespace
 character.
 nextChar will be set to the next non-whitespace char.
*/
void getNonBlank()
{
  //WILL NEED TO FIX TO NOT REMOVE NEWLINES
  //ALSO NEED THE NEWLINE TO BE THE END OF LINE SYMBOL
  if(nextChar == '\n'){
    cout << "newline" << endl;
    getChar();
  }
   else{ 
      while (isspace(nextChar))
        getChar();
  }
}
/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex()
{
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
    /* Parse identifiers - once you find the first
    letter, read and add char by char to lexeme. */
    case LETTER:
    addChar();
   // table.insert(lexeme);
    getChar();
    /* After first char, you may use either char or digits */
    while (charClass == LETTER || charClass == DIGIT) {
    addChar();
    getChar();
    }
    //NEED TO STORE THE IDENT IN THE SYMBOL TABLE
    //LOOKUP TO SEE IF IT IS THERE IF NOT THEN INSERT
    //IF IT IS THEN ADJUST VALUE

    nextToken = IDENT;
    break;
 /* Parse integer literals - once you find the first
 digit, read and add digits to lexeme. */
    case DIGIT:
    addChar();
    getChar();
    while (charClass == DIGIT) {
    addChar();
    getChar();
    }
    nextToken = INT_LIT;
    break;
    /* Parentheses and operators */
    case OPERATOR:
    /* Call lookup to identify the type of operator */
    lookup(nextChar);
    getChar();
    break;
    /* EOF */
    //EOF WILL NEED TO BE NEWLINE SINCE THAT IS OUR NEW LINE SEPERATOR
    case EOF:
    nextToken = EOF;
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = '\0';
    break;

 } /* End of switch */
 printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
 return nextToken;
}
