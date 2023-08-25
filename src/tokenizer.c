#include "tokenizer.h"

//tokenizes s with g and puts result in ts, returns success or fail
//on failiure, restores s and ts position
int tokenize(sbf s, grammar g, tokens* ts) {
	size_t base = ts->len;
	char* bck = *s;
	if (!g.f(s, ts, g)) {
		ts->len = base;
		*s = bck;
		return 0;
	}
	return 1;
}

void push_token(tokens* ts, token t) {
	if (++ts->len > ts->cap) {
		ts->cap = ts->cap * 2 + 1;
		ts->bf = realloc(ts->bf, sizeof(token) * ts->cap);
	}
	ts->bf[ts->len-1] = t;
	return;
}

tokens new_tokens(){
	return (tokens){NULL, 0, 0};
}

//a comes before b
token token_concat(token a, token b){
	token c = a;
	c.len = b.start - a.start + b.len;
	return c;
}
