GLOBAL_HEADERS = tokenizer.h grammar.h tokens.h

libtokenizer.a : tokenizer.o grammar.o
	ar rcs libtokenizer.a tokenizer.o grammar.o

tokenizer.o : tokenizer.c $(GLOBAL_HEADERS)
	gcc tokenizer.c -ggdb -Wall -O3 -c -o tokenizer.o

grammar.o : grammar.c $(GLOBAL_HEADERS)
	gcc grammar.c -ggdb -Wall -O3 -c -o grammar.o
