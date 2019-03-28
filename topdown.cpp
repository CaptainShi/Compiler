#include "general_ex.h"
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include "symbolTable.h"

extern Symbol_table table;
extern Symbol_ptr symbol_ptr;

using namespace std;


/*stmt
Parses strings inthe langauge generated by the rule:
<stmt> -> ID = <expr>
       | QUIT
       | DUMP
*/
int stmt()
{
   int value = 0;

  // cout << "START STMT" << endl;
  // cout << "NEXT TOKEN IS "<< nextToken << endl;
  // cout << "LEXEME IS "<< lexeme << endl;
   
   lex(); 

  // cout << "NEXT TOKEN IS "<< nextToken << endl;
  // cout << "LEXEME IS "<< lexeme << endl;


  // cout << "Next token is " << nextToken << endl;
   //int number = factor();
//   lex();
   //Case ID = expr
   if(nextToken == EQUAL){
    // cout << "in id = expr" << endl; 

      lex();
      //cout << "NEXT TOKEN IS "<< nextToken << endl;
      //cout << "LEXEME IS "<< lexeme << endl;
      //gets the value
      value = expr();
      //cout << "VALUE IS " << value << endl; 
      //cout << "POINTER IS " << symbol_ptr << endl; 
      //loads into symbol table
      //symbol_ptr = table.lookup(symbol_ptr); 
      symbol_ptr->putval(value);

      //cout << symbol_ptr->getid();

      //return value;
   }


   //case QUIT
   //add quit
   //if(nextToken == QUIT){
   //   return -1;
   //}
 
   //case Dump
   //if(nextToken == DUMP)
      table.dump_table();

    return value;

}
/* expr
 Parses strings in the language generated by the rule:
 <expr> -> <term> {(+ | -) <term>}
 */
int expr()
{
    int value1 = 0;
    int value2 = 0;
   
 /* Parse the first factor */
     value1 = term();
     //cout << value1 << endl;
     //cout << "NEXT TOKEN " << nextToken << endl;
   //  lex();
    /* As long as the next token is + or -, get the
     next token and parse the next factor */
     while (nextToken == ADD_OP || nextToken == SUB_OP) {
       if(nextToken == ADD_OP){
          lex();
         // cout << "BEFORE" << endl; 
          value2 = term();
         // cout << "AFTER" << endl;
         // cout << "value 1 = " << value1 << endl;
         // cout << "value 2 = " << value2 << endl;
          value1 = value1 + value2;
          //cout << value1 << endl;
       }else if(nextToken == SUB_OP){
          lex();
          //cout << "SUB" << endl;
          value2 = term();
          //cout << "value 2 = " << value2 << endl;
          value1 = value1 - value2;
          //cout << value1 << endl;
      }
      lex();
      //cout << "EXPR" << endl;
     }
     //cout << value1<< endl; 
     //cout << "Ending expr" << endl;
     return value1;


} /* End of function expr */
/* term
 * Parses strings in the language generated by the rule:
 * <term> -> <factor> {(* | /) <factor>)
 */
int term()
{
    int value1 = 0;
    int value2 = 0;
    //cout << "term" << endl;
    //cout << "value 1 = " << value1 << endl;
    //cout << "value 2 = " << value2 << endl;

 /* Parse the first factor */
     value1 = factor();
     lex();

    /* As long as the next token is * or /, get the
     next token and parse the next factor */
     while (nextToken == MULT_OP || nextToken == DIV_OP) {
        if(nextToken == MULT_OP){
        //  cout << "In MULT" << endl;
          lex();
          value2 = factor();
         // cout << value2 << endl;
          value1 = value1 * value2;
          //cout << value1 << endl;
       }else if(nextToken == DIV_OP){
          lex();
          value2 = factor();
          value1 = value1 / value2;
          //cout << value1 << endl;
      }
      lex();
      //cout << "TERM" << endl;
     }
   
    //cout << "out of term" << endl; 
     return value1;

} /* End of function term */
/* factor
 * Parses strings in the language generated by the rule:
 *
 * <factor> -> id | int_constant | ( <expr )
 *
 */
int factor()
{
 //printf("Enter <factor>\n");
    /* Determine which RHS */
    
    //NEED TO SPILT THIS IF UP
    //IF IT IS A NUMBER RETURN IT
    //IF IT IS A IDENT THEN LOOK UP VALUE IN TABLE AND RETURN THAT

    //If it is a number 
    //return it 
    if(nextToken == INT_LIT){
      // cout << "out of factor" << endl;
       return atoi(lexeme);
    }
    
    //if is ident
    else if (nextToken == IDENT){
        cout << "in IDENT" << endl;
       /* Get the next token */
        //get value from the table
        symbol_ptr = table.lookup(lexeme);
       // cout << "symbol_ptr is " << symbol_ptr << endl;
       // if(symbol_ptr == NULL){
        //   cout << "ABOUT TO INSERT" << endl;
        //   table.insert(lexeme);
        //   cout << "INSERTED" << endl;
        //}            
 
        //if there is a value
        int result;
        result = symbol_ptr->getval();
        cout << "RESULT " << result << endl;
        //then return
        return result;
    }
 
    /* If the RHS is ( <expr> ), call lex to pass over the left
    parenthesis, call expr and check for the right parenthesis */
    else if (nextToken == LEFT_PAREN) {
       lex();
       //WILL RERECURSE
      // cout << "inleft paren" << endl;
       int value = expr();
       if (nextToken == RIGHT_PAREN){
          //lex();
        //  cout << "(expr) " << value << endl;
          return value;    
          }
    
       else
          error("Right without left paren");
    } 
    else {
    /* It was not an id, an integer literal, or a left
    parenthesis */
    error("expected an id, integer, or a left paren");
    } /* End of else */

    //cout << "out of factor" << endl;
  
 // printf("Exit <factor>\n");;
}/* End of function factor */

int negatives()
{
 //will return a negative number



}

int powers()
{
//will return a number that has been raised to a power
}


void error(const char *message)
{
 printf("Error: %s\n",message);
}
