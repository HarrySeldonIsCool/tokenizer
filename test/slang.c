#include "../src/tokenizer.h"
#include <stdio.h>

typedef enum {
	NUM = 1,
} TOKS;

int main(){
	char* s = "return 69;";
	char* s2 = s;
	tokens ts = new_tokens();

	CHAR_CLASS(numchars, "0123456789");
	REPEAT1(numstri, numchars);
	GROUP(numstr, numstri);
	CAST(number, numstr, NUM);
	LITERAL(semi, ";");
	CHAR_CLASS(whitespacec, " \n");
	REPEAT0(whitespace, whitespacec);
	IGNORE(ws, whitespace);
	LITERAL(_return, "return");
	OR(keyword, _return);
	OR(g1, keyword, number, semi);
	CHAIN(g2, g1, whitespace);
	REPEAT0(g, g2);
	tokenize(&s, g, &ts);
	for (int i = 0; i < ts.len; i++) {
		printf("{t: %i, start: _, len: %li}\n", ts.bf[i].t, ts.bf[i].len);
	}
	tok_dealloc(g);
}
