#include "grammar.h"

BASE_RULE(tok_or, (grammar* g, size_t len), g, len) {
	for (int i = 0; i < g.len; i++) {
		if (tokenize(s, ((grammar*)g.g)[i], ts)) return 1;
	}
	return 0;
}

BASE_RULE(tok_chain, (grammar* g, size_t len), g, len) {
	for (int i = 0; i < g.len; i++) {
		if (!tokenize(s, ((grammar*)g.g)[i], ts)) return 0;
	}
	return 1;
}

BASE_RULE(tok_repeat0, (grammar* g), g, 1) {
	while (tokenize(s, *(grammar*)g.g, ts));
	return 1;
}

grammar tok_repeat1(grammar* g) {
	CHAINH(g2, *g, tok_repeat0(g));
	return g2;
}

BASE_RULE(tok_lit, (char* a, size_t _len), a, strlen(a)) {
	char* a = (char*)g.g;
	if (strlen(*s) < g.len) return 0;
	for (int i = 0; a[i] && (*s)[i]; i++){
		if (a[i] != (*s)[i]) return 0;
	}
	push_token(ts, (token){0, *s, g.len});
	*s += g.len;
	return 1;
}

BASE_RULE(tok_group, (grammar* g), g, 1) {
	size_t base = ts->len;
	if (!tokenize(s, *(grammar*)g.g, ts)) return 0;
	if (ts->len <= base + 1) return 1;
	for (size_t i = base + 1; i < ts->len; i++) {
		ts->bf[base] = token_concat(ts->bf[base], ts->bf[i]);
	}
	ts->len = base + 1;
	return 1;
}

//a bit of a hack, using the len field to store the token type
//luckily, len is also just metadata for f, which should NOT be depended on BY ANYONE, EVER
BASE_RULE(tok_cast, (grammar* g, int16_t i), g, i) {
	if (!tokenize(s, *(grammar*)g.g, ts)) return 0;
	ts->bf[ts->len - 1].t = g.len;
	return 1;
}

BASE_RULE(tok_char_class, (char* a, size_t _len), a, strlen(a)) {
	char* a = (char*)g.g-1;
	while (*++a) {
		if (**s != *a) continue;
		(*s)++;
		push_token(ts, (token){0, *s, 1});
		return 1;
	}
	return 0;
}
