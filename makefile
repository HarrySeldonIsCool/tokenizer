GLOBAL_HEADERS = src/tokenizer.h src/grammar.h src/tokens.h

bin/libtokenizer.a : bin/tokenizer.o bin/grammar.o
	ar rcs bin/libtokenizer.a bin/tokenizer.o bin/grammar.o

bin/tokenizer.o : src/tokenizer.c $(GLOBAL_HEADERS)
	gcc src/tokenizer.c -Wall -O3 -c -o bin/tokenizer.o

bin/grammar.o : src/grammar.c $(GLOBAL_HEADERS)
	gcc src/grammar.c -Wall -O3 -c -o bin/grammar.o
