#Batch Number - 37
#AKSHAY R 2013B3A7543P
#GAURANG BANSAL 2014A7PS128P

output: driver.o 
	gcc -w -O3 driver.o -o compiler

lexer.o: lexer.h lexer.c 
	gcc -w -c -g lexer.c

parser.o: parser.h parser.c 
	gcc -w -c -g parser.c

symboltable.o: tokensymboltable.h symboltable.c
	gcc -w -c -g symboltable.c

driver.o: driver.c
	gcc -w -c -g driver.c
clean:
	rm *.o