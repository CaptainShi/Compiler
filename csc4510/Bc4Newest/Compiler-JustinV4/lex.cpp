/*
Authors: Cole Burkhart, Jacky Shi, Justin Weiss 
Date: 4/23/2019
Class: CSC 4510-01
BC Version 4 - Recursive descent parser
Uses grammar rules to parser statement that are entered in from the keyboard or input redirection

*/
#include "general.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include "symbolTable.h"
#include <string.h>

//Global symbol tables
Symbol_table table;
Symbol_ptr symbol_ptr;

using namespace std;


int main ()
{

   //sets the inital program string to nothing
   program = "";
   //index is -1
   curr_index = -1;
   inwhile = false;

   getChar();
   do {
        lex();
        int value = stmt();
        getChar();
   }
   while(nextToken != EOF);


   return 0;


}


/*****************************************************/
/* lookup - a function to lookup operators and parentheses
 and return the token.
Sets the nextToken and returns it */
int lookup(char ch) {
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
    break;

   case '^':
      addChar();
      nextToken = EXPO;
   break;

   case '\n':
      addChar();
      nextToken = NEWLINE;
   break;

   case '%':
      addChar();
      nextToken = MOD;
   break;

   case '<':
     addChar();
     nextToken = LESSTHEN;
     break;

   case '>':
     addChar();
     nextToken = GREATERTHEN;
     break;

   case '#':
     addChar();
     nextToken = COMMENT;
     break;

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

//Get string
//Buffers the input and resets the input to all for the while statement
//to recheck the condition
//returns a character
char getString(){
   
   //checks if it is in a while statement
   if(inwhile == true){
      char temp = program[string_index];
      string_index++;
      return temp;
   } else {
      char temp = getchar();
      program = program + temp;
      return temp;
   }

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

 //calls the get string function that we created to buffer the input
 if ((nextChar = getString()) != EOF) {
    if (isalpha(nextChar))
       charClass = LETTER;
    else if (isdigit(nextChar))
       charClass = DIGIT;
    else if(nextChar == '\n')
       charClass = NEWLINE;
    else if(nextChar == '#')
       charClass = COMMENT;
    else
       charClass = OPERATOR;
 }  else
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
    //Gets the nextChar if it is not a space
    while (isspace(nextChar) && nextChar != '\n')
       getChar();

}
/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions 
 Gets the next lexeme and token
 Calls the other functions above to do this
 Returns an integer*/
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

    //Checks if the lexeme is dump 
    //if it is then it sets nextToken as DUMP
    if(strcmp(lexeme,"dump") == 0){
       nextToken = DUMP;
    }

    //Checks if the lexeme is quit 
    //if it is then it sets nextToken as QUIT
    else if (strcmp(lexeme,"quit") == 0){
       nextToken = QUIT;

    //Checks if the lexeme is If 
    //if it is then it sets nextToken as IF
    } else if (strcmp(lexeme, "if") == 0) {
        nextToken = IF;

    //Checks if the lexeme is then 
    //if it is then it sets nextToken as THEN
    } else if (strcmp(lexeme, "then") == 0) {
      nextToken = THEN;

    //Checks if the lexeme is else 
    //if it is then it sets nextToken as ELSE
    } else if (strcmp(lexeme, "else") == 0) {
      nextToken = ELSE;

    //Checks if the lexeme is fi
    //if it is then it sets nextToken as FI
    } else if (strcmp(lexeme, "fi") == 0) {
      nextToken = FI;

    //Checks if the lexeme is while 
    //if it is then it sets nextToken as WHILE
    } else if (strcmp(lexeme, "while") == 0) {
      nextToken = WHILE;

    //Checks if the lexeme is do 
    //if it is then it sets nextToken as D)
    } else if (strcmp(lexeme, "do") == 0) {
      nextToken = DO;

    //Checks if the lexeme is done 
    //if it is then it sets nextToken as DONE
    } else if (strcmp(lexeme, "done") == 0) {
      nextToken = DONE;

    //Checks if the lexeme is print 
    //if it is then it sets nextToken as print
    } else if (strcmp(lexeme, "print") == 0) {
      nextToken = PRINT;
    }
  
    //Else the lexeme is an identifier and it is put in the symbol table
    else
    {
       nextToken = IDENT;
       symbol_ptr = table.insert(lexeme);
    }

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
    case EOF:
       nextToken = EOF;
       lexeme[0] = 'E';
       lexeme[1] = 'O';
       lexeme[2] = 'F';
       lexeme[3] = '\0';
    break;

    //comment case
    //process the entire line as a comment
    case COMMENT:
       do{
          getChar();
       } while (charClass != NEWLINE);
    break;


 } /* End of switch */
 //printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
 return nextToken;
}
