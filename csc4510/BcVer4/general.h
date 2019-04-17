#include<string>
using namespace std;
/* Global declarations */
/* Variables */
char lexeme [100];
char nextChar;
int lexLen;
string program;
int curr_index;
//FILE *in_fp, *fopen();
/* Function declarations */
extern void addChar();
extern char getString();
extern void getChar();
extern void getNonBlank();
extern int lex();
extern int stmt();
extern int expr();
extern int term();
extern int factor();
extern int negatives();
extern int powers();
extern bool cond();
extern void optionalElse();
extern void error(const char *);
/* Character classes */
int charClass;
#define LETTER 0
#define DIGIT 1
#define OPERATOR 99
#define END 55
/* Token codes */
int token;
int nextToken;
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
#define IF 33
#define THEN 34
#define ELSE 35
#define FI 36
#define WHILE 37
#define DO 38
#define DONE 39
#define PRINT 40
#define POUND 41
#define EE 42
#define NE 43
#define LESSTHEN 44
#define GREATERTHEN 45
#define LE 46
#define GE 47
#define COMMENT 48

#define SYM_DEBUG 0 //used to turn on/off debug messages in
 //symbol table methods
#define TABLE_SIZE 211 //Studies show it should be a prime number
#define MAX_ID_LENGTH 1 //Indicates the maximum number of characters
 //to make the id's unique
#ifndef V_TYPE
#define V_TYPE
typedef union {
 int ivalue;
 char cvalue;
 double dvalue;
} VALUE;
#endif
