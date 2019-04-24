/*
Authors: Cole Burkhart, Jacky Shi, Justin Weiss 
Date: 4/23/2019
Class: CSC 4510-01
BC Version 4 - Recursive descent parser
Uses grammar rules to parser statement that are entered in from the keyboard or input redirection

*/
#include "symbolNode.h"

typedef Symbol_node * Symbol_ptr;
#ifndef SYM_TABLE
#define SYM_TABLE
class Symbol_table {
    public:
        Symbol_table(void);
        ~Symbol_table(void);
        Symbol_ptr insert(char *);
        void remove(char *);
        Symbol_ptr lookup(char *);
        void dump_table(void);
        int hash(const char* id);
   private:
    //  Symbol_ptr *table;
    Symbol_node* head;//[TABLE_SIZE];
}; 
#endif
