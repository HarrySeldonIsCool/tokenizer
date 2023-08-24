#include "../tokenizer.h"
#include <stdio.h>

typedef enum {
	NUM = 1,
} TOKS;

int main(){
	char* s = "return 69;";
	char* s2 = s;
	tokens ts = new_tokens();

	CHAR_CLASSH(numchars, "0123456789");
	REPEAT1H(numstri, numchars);
	GROUPH(numstr, numstri);
	CASTH(number, numstr, NUM);
	LITERALH(semi, ";");
	CHAR_CLASSH(whitespacec, " \n");
	REPEAT0H(whitespace, whitespacec);
	LITERALH(_return, "return");
	ORH(keyword, _return);
	ORH(g1, keyword, number, semi);
	CHAINH(g2, g1, whitespace);
	REPEAT0H(g, g2);
	tokenize(&s, g, &ts);
	for (int i = 0; i < ts.len; i++) {
		printf("{t: %i, start: _, len: %i}\n", ts.bf[i].t, ts.bf[i].len);
	}
	tok_dealloc(g);
}
