#ifndef TOKENS_
#define TOKENS_
#include <stddef.h>
#include <stdint.h>

typedef struct {
	int16_t t;
	char* start;
	size_t len;
} token;

typedef struct {
	token* bf;
	size_t len;
	size_t cap;
} tokens;

typedef char** sbf;

void push_token(tokens*, token);
tokens new_tokens();
token token_concat(token, token);
#endif
