#ifndef header
#define header 

using namespace std;

/* Global declarations */
/* Variables */
char lexeme [100];
char nextChar;
int lexLen;
//FILE *in_fp, *fopen();
/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
void expr();
void term();
void factor();
void error(const char *);
/* Character classes */
int charClass;
#define LETTER 0
#define DIGIT 1
#define OPERATOR 99
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

#endif
