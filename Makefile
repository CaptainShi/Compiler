CC=g++
bc:	topdown.o lex.o
		$(CC) -o bc topdown.o lex.o -lfl -lm

topdown.o:		topdown.cpp  
						$(CC) -c topdown.cpp 

lex.o:		lex.cpp
						$(CC) -c lex.cpp
clean:
	rm bc lex.yy.* calc.tab.*
