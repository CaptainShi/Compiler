#ifndef SYM_NODE
#define SYM_NODE
class Symbol_node {
   friend class Symbol_table;
   public:
      Symbol_node(void);
      Symbol_node(char*);
      Symbol_node(char*,int, int);
      ~Symbol_node(void);
      void putval(int);
      int getval(void);
      char * getid(void);
   private:
      char * id;
      int token;
      int value;   //VALUE is defined on next page.
      Symbol_node * next;
};
#endif
