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
        int hash(char* id);
   private:
    //  Symbol_ptr *table;
    Symbol_node* head;//[TABLE_SIZE];
}; 
#endif
