/*
Authors: Cole Burkhart, Jacky Shi, Justin Weiss 
Date: 4/23/2019
Class: CSC 4510-01
BC Version 4 - Recursive descent parser
Uses grammar rules to parser statement that are entered in from the keyboard or input redirection

*/
#include "symbolTable.h"
#include "symbolNode.h"
#include "general_ex.h"
#include<cstddef>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>


using namespace std;

Symbol_table::Symbol_table(void) {

  head = new Symbol_node[TABLE_SIZE]; 


    for (int i = 0; i < TABLE_SIZE; i++) {
       head[i].next = NULL; 
    }


}

Symbol_table::~Symbol_table(void) {
	//destruct the table 
}

Symbol_ptr Symbol_table::insert(char * identifier) {

   Symbol_ptr node_ptr = lookup(identifier);

   if(!node_ptr){
      int pos = hash(identifier);
      Symbol_ptr newnode = new Symbol_node(identifier);
      newnode->next = head[pos].next;
      head[pos].next = newnode;
      return newnode;

   }

   return node_ptr;

}

void Symbol_table::remove(char * identifier) {

   //call lookup to find the location to remove
   int index = hash(identifier);
   Symbol_node* tmp = head[index].next;
   Symbol_node* par = head[index].next;


   //if empty do nothing
    if (tmp == NULL) {
        
    //else
    } else if (tmp->id == identifier && tmp->next == NULL) {
        tmp->next = NULL;
        delete tmp;
    } else {
        while (tmp->id != identifier && tmp->next != NULL) {
            par = tmp;
            tmp = tmp->next;
        }
        //set the pointer location to null
        if (tmp->id == identifier && tmp->next != NULL) {
            par->next = tmp->next;
            tmp->next = NULL;
            free(tmp);
        } else {
            par->next = NULL;
            tmp->next = NULL;
            free(tmp);
        }
    }
}

Symbol_ptr Symbol_table::lookup(char * identifier) {
  
   int pos = hash(identifier);
   Symbol_ptr curr_ptr = head[pos].next;

   while(curr_ptr && strcmp(curr_ptr->id,identifier))
      curr_ptr = curr_ptr->next;
 
   return curr_ptr;
}

void Symbol_table::dump_table(void) {
    
    for (int i=0; i<TABLE_SIZE; i++) {
        Symbol_node* start = head[i].next;
        //use pointer to get the value
        //return val
        while(start != NULL){
            cout << start->id << "=" << start->value << " "<< endl;
            start=start->next;
        }
    }


}

//Hash function determines where to put the nodes in the symbol table.
// It's based off of Brian Kernighan and Dennis Ritchie's hash function.
// Using the pattern 131..131..131
int Symbol_table::hash(const char* id) {
   unsigned int seed = 131;
   unsigned int hash = 0;
   unsigned int i = 0;

   for (i = 0; i < MAX_ID_LENGTH; ++id, ++i) {
      hash = (hash * seed) + (*id);
   }
   return (hash % (TABLE_SIZE-1));
}


