/*
Authors: Cole Burkhart, Jacky Shi, Justin Weiss 
Date: 4/23/2019
Class: CSC 4510-01
BC Version 4 - Recursive descent parser
Uses grammar rules to parser statement that are entered in from the keyboard or input redirection

*/
#include "symbolNode.h"
#include "symbolTable.h"
#include<cstddef>
#include<cstring>

using namespace std;

//default constructor
Symbol_node::Symbol_node() {
    next = NULL;
}

Symbol_node::Symbol_node(char* identifier) {
     this->id = new char[strlen(identifier)+1];
     strcpy(this->id,identifier);
}
//constructor
Symbol_node::Symbol_node(char* identifier,int Token, int Val) {
     this->id = identifier;
     this->token = Token;    
     this->value = Val;    
     next = NULL;

}

Symbol_node::~Symbol_node() {

  //destructor

}

//Puts a new value in the node
void Symbol_node::putval(int val) {
    
    //Puts the value in the symbol table 
    value = val;


    
}

//Gets the value in the node
int Symbol_node::getval() {
   
    //returns the value 
    return value;

}

//Gets the id of the node
char * Symbol_node::getid() {

    //returns the id    
    return id;
    
}
   
