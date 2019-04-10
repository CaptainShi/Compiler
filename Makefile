CC=g++
bc:	topdown.o lex.o symbolTable.o symbolNode.o
		$(CC) -o bc topdown.o lex.o symbolTable.o symbolNode.o -lfl -lm

topdown.o:		topdown.cpp general.h 
						$(CC) -c topdown.cpp  


lex.o:		lex.cpp general.h
						$(CC) -c lex.cpp

symbolTable.o:		symbolTable.cpp symbolTable.h 
						$(CC) -c symbolTable.cpp 

symbolNode.o:		symbolNode.cpp symbolNode.h
						$(CC) -c symbolNode.cpp

clean:
	rm bc lex.o topdown.o symbolTable.o symbolNode.o
