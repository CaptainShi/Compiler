
//using namespace std;

/* Global declarations */
/* Variables */
extern char lexeme [100];
extern char nextChar;
extern int lexLen;
//FILE *in_fp, *fopen();
/* Function declarations */
extern void addChar();
extern void getChar();
extern void getNonBlank();
extern int lex();
extern int stmt();
extern int expr();
extern int term();
extern int factor();
extern int powers();
extern int negatives();
extern void error(const char *);
/* Character classes */
extern int charClass;
#define LETTER 0
#define DIGIT 1
#define OPERATOR 99
/* Token codes */
extern int token;
extern int nextToken;
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define EQUAL 27
#define NEWLINE 28
#define DUMP 29
#define QUIT 30
#define EXPO 31
#define MOD 32

#define SYM_DEBUG 0 //used to turn on/off debug messages in
 //symbol table methods
#define TABLE_SIZE 211 //Studies show it should be a prime number
#define MAX_ID_LENGTH 6 //Indicates the maximum number of characters
 //to make the id's unique
#ifndef V_TYPE
#define V_TYPE
typedef union {
 int ivalue;
 char cvalue;
 double dvalue;
} VALUE;
#endif
