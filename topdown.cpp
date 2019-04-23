#include "general_ex.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "symbolTable.h"

extern Symbol_table table;
extern Symbol_ptr symbol_ptr;
Symbol_ptr symbol_ptr2;

using namespace std;


/*stmt
Parses strings inthe langauge generated by the rule:
<stmt> -> id = <expr>
       | if <cond> then <stmts> <optional_else>
       | while <cond> do <stmts> done
       | print id
       | #comment
       | QUIT
       | DUMP
*/
int stmt()
{
    int value = 0;
    Symbol_ptr s_ptr;
    Symbol_ptr p_ptr;

   //Print rule
   if(nextToken == PRINT){
     lex();
     p_ptr = table.lookup(lexeme);
     cout << "PRINT" << endl;
     cout << "        " << p_ptr->getid() << "=" << p_ptr->getval() << endl;
     p_ptr = NULL;

   }

    //Comment rule




    //if the next token is 'if'
    if (nextToken == IF) {
      //cout << "In If" << endl;
      lex();
      bool condition = cond();
      //cout << "Condition Status:" << condition << endl;
      if (condition == 1) {
         cout << "The condition is true" << endl;
         lex();
         if (nextToken == THEN) {
            lex();
            int value = stmt();
         }
      }
      cout << "Next token before going into optional else is " <<  nextToken << endl;
      while (nextToken != ELSE && nextToken != FI) {
         lex();
         cout << "Next token in the while loop is " <<  nextToken << endl;
      }
      optionalElse();

    }


    //While case
    if(nextToken == WHILE){
       string_index = 0;
       curr_index = program.length();
       cout << "string_index: " << string_index << endl;
       lex();
       cout << "before condition -1" << endl;
       bool condition = cond();
       cout << "before condition 1 | " << condition << endl;

       //if cond is true
       if(condition == 1){
          //lex();
          cout << "before do " << nextToken << lexeme << endl;
           if(nextToken == DO){
             cout << "after do " << nextToken << lexeme << endl;
             lex();
             do {
               cout << nextToken << lexeme << endl;
               int value = stmt();
               lex();
               if(nextToken == DONE){
                 inwhile = true;
                  cout << "Done" << endl;
                  string_index = curr_index;
                   cout << "curr_index: " << curr_index << endl;
                  cout << "before condition 2 " << string_index<<program[string_index]<<" "<<nextToken << lexeme << endl;
                  getChar();
                  lex();
                  cout << "after condition 2 " << string_index<<nextToken << lexeme << endl;
                  cout<<"my code\n"<<program<<endl<<"program end"<<endl;
                  condition = cond();
                  cout << "condition: " << condition << endl;
                  //value = stmt();
               }
               //condition = cond();
             } while(condition == 1);
             inwhile = false;

              //check condition again
              //while(condition == 1) {

                //cout << nextToken << lexeme << endl;
                //string_index = curr_index;
                //condition = cond();
                //value = stmt();
              //}
           }
       }

       getChar();

    }

    cout << "getChar **********************" << nextToken << endl;
    //getChar();
    ///lex();
    //getChar();
    lex();

    if (nextToken == EQUAL) {

      cout << "Next Token is " << nextToken << endl;
      //Case ID = expr
       s_ptr = symbol_ptr;
       lex();
       //gets the value
       value = expr();
       //loads into symbol table
       s_ptr->putval(value);

       //Prints the value
       cout << "        " << symbol_ptr->getid() << "=" << value << endl;
       symbol_ptr = NULL;
    }

    //if the nextoken is dump then dump the table
    if (nextToken == DUMP) {
       cout << "Dump" << endl;
       cout << "================" << endl;
       table.dump_table();
       cout << "================" << endl;
    }

    //if the next token is quit then quit the table
    if(nextToken == QUIT){
      nextToken = EOF;
      exit(1);
   }

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
    /* As long as the next token is + or -, get the
    next token and parse the next factor */

    while (nextToken == ADD_OP || nextToken == SUB_OP) {
       if (nextToken == ADD_OP) {
          //cout << "In ADD_OP" << endl;
          lex();
          value2 = term();
          value1 = value1 + value2;
       } else if(nextToken == SUB_OP){
          //cout << "In SUB_OP" << endl;
          lex();
          value2 = term();
          value1 = value1 - value2;
       } else {
          cout << "Token Error in expr()" << endl;
       }
       lex();
    }
    return value1;


} /* End of function expr */
/* term
 * Parses strings in the language generated by the rule:
 * <term> -> <factor> {(* | /) <factor>)
 */
int term()
{
    //cout << "In terms()" << endl;
    int value1 = 0;
    int value2 = 0;

    /* Parse the first factor */
    value1 = negatives();
     //lex();

    /* As long as the next token is * or / or %, get the
     next token and parse the next factor */
     while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MOD) {
        if (nextToken == MULT_OP){
           //cout << "In MULT_OP" << endl;
           lex();
           value2 = factor();
           value1 = value1 * value2;
        } else if(nextToken == DIV_OP){
           //cout << "In DIV_OP" << endl;
           lex();
           value2 = factor();
           value1 = value1 / value2;
        } else if(nextToken == MOD){
           //cout << "In MOD" << endl;
           lex();
           value2 = factor();
           value1 = value1 % value2;
        } else {
           cout << "Token error in term()" << endl;
        }
        lex();
     }

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

    //If it is a number
    //return it
    //cout << "Next Toke in factor is: " << nextToken << endl;
    if (nextToken == INT_LIT){
      // cout << "out of factor" << endl;
       return atoi(lexeme);
    }

    //if is ident
    else if (nextToken == IDENT){
       /* Get the next token */

        //if there is a value
        int result;
        result = symbol_ptr->getval();
        //then return
        return result;
    }

    /* If the RHS is ( <expr> ), call lex to pass over the left
    parenthesis, call expr and check for the right parenthesis */
    else if (nextToken == LEFT_PAREN) {
       lex();
       int value = expr();
       if (nextToken == RIGHT_PAREN){
          return value;
          }

       else
          error("Right without left paren");
    }
    else {
    /* It was not an id, an integer literal, or a left
    parenthesis */
    error("expected an id, integer, or a left paren");
    return 0;
    } /* End of else */


}/* End of function factor */

//Checks for unary minus
//if there is one then mult the value by -1
int negatives() {
   //cout << "In Negatives" << endl;
   int value = 0;

   //will return a negative number
   if (nextToken == SUB_OP){
      lex();
      value = powers();
      value *= -1;
   } else {
      value = powers();
   }
   return value;
}

//Calculate exponments
//returns the power
int powers()
{
//will return a number that has been raised to a power

   int value1 = factor();
   lex();

   //gets the exponents
   while(nextToken == EXPO){
      lex();
      int value2 = factor();
      value1 = pow(value1, value2);
      lex();
   }

   return value1;

}

bool cond() {
    char Oper;
    int value1 = 0;
    int value2 = 0;
    //cout << "In condition" << endl;

    value1 = expr();
    //cout << "LHS is" << value1 << endl;
    //lex();
    Oper = nextToken;
    //cout << "Operator is " << Oper << endl;
    lex();
    value2 = expr();
    //cout << "RHS is" << value2 << endl;
    if (Oper == EE) {
        cout << "EE" << endl;
        if (value1 == value2) {
            return true;
        } else return false;
    } else if (Oper == NE) {
        cout << "NE" << endl;
        if (value1 == value2) {
            return false;
        } else return true;
    } else if (Oper == LESSTHEN) {
        cout << "L" << endl;
        if (value1 < value2) {
            return true;
        } else return false;
    } else if (Oper == GREATERTHEN) {
        cout << "G" << endl;
        if (value1 > value2) {
          return true;
        } else return false;
    } else if (Oper == LE) {
        cout << "LE" << endl;
        if (value1 <= value2) {
          return true;
        } else return false;
    } else if (Oper == GE) {
        cout << "GE" << endl;
        if (value1 >= value2) {
          return true;
        } else return false;
    } else {
        cout << "Ooops, there is a problem" << endl;
        return false;
    }
}

void optionalElse() {
   cout << "In Optional Else" << endl;
   if (nextToken == FI) {
       cout << "Out of if" << endl;
   } else if (nextToken == ELSE) {
      cout << "In Else" << endl;
      lex();
      int value = stmt();
   } else {
      cout << "Whoops, we got a problem in optional else" << endl;
   }
}


void error(const char *message)
{
    printf("Error: %s\n",message);
}
