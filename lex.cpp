#include "general.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include "symbolTable.h"
#include <string.h>

Symbol_table table;
Symbol_ptr symbol_ptr;

using namespace std;


int main ()
{

   program = "";
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
 and return the token */
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
     cout << "In look up < " << endl;
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

//Ge string
char getString(){
cout<<"                     GET IT\n";
   if(inwhile == true){
      char temp = program[string_index];
      string_index++;
      cout << "inwhile " << string_index<<endl;
      return temp;
   } else {
     cout << "out while" << endl;
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
cout<<"                             getChar POW\n";
 //need to chnage to all io redirection
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
cout<<"                             gnb POW\n";
  //WILL NEED TO FIX TO NOT REMOVE NEWLINES
  //ALSO NEED THE NEWLINE TO BE THE END OF LINE SYMBOL
      while (isspace(nextChar) && nextChar != '\n')
        getChar();

}
/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex()
{
cout<<"                              POW\n";
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

      //put in table

    if(strcmp(lexeme,"dump") == 0){
       nextToken = DUMP;
    }
    else if (strcmp(lexeme,"quit") == 0){
       nextToken = QUIT;
    } else if (strcmp(lexeme, "if") == 0) {
        nextToken = IF;
    } else if (strcmp(lexeme, "then") == 0) {
      nextToken = THEN;
    } else if (strcmp(lexeme, "else") == 0) {
      nextToken = ELSE;
    } else if (strcmp(lexeme, "fi") == 0) {
      nextToken = FI;
    } else if (strcmp(lexeme, "while") == 0) {
      nextToken = WHILE;
    } else if (strcmp(lexeme, "do") == 0) {
      nextToken = DO;
    } else if (strcmp(lexeme, "done") == 0) {
      nextToken = DONE;
    } else if (strcmp(lexeme, "print") == 0) {
      nextToken = PRINT;
    }
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
    //EOF WILL NEED TO BE NEWLINE SINCE THAT IS OUR NEW LINE SEPERATOR
    case EOF:
    nextToken = EOF;
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = '\0';
    break;

    //comment
    case COMMENT:
      do{
         getChar();
      } while (charClass != NEWLINE);
    break;


 } /* End of switch */
 //printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
 return nextToken;
}
