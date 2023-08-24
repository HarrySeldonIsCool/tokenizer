#ifndef GRAMMAR_
#define GRAMMAR_
#include "tokens.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#define _CONCC(A, B) A ## B
#define _CONCAT(A, B) _CONCC(A, B)
#define _LOCAL_VAR _CONCAT(__grmr_chn2, __LINE__)

//puts ... (of type TP) onto heap and calls tok_OP on it (mainly for chain and or)
#define _HEAP_OP(TGT, TP, OP, ...) TP* _LOCAL_VAR; grammar TGT;\
			{TP __grmr_chn[] = __VA_ARGS__; \
			_LOCAL_VAR = malloc(sizeof(__grmr_chn)); \
			memcpy(_LOCAL_VAR, __grmr_chn, sizeof(__grmr_chn)); \
			TGT = tok_##OP(_LOCAL_VAR, sizeof(__grmr_chn) / sizeof(TP));}
#define _STACK_OP(TGT, TP, OP, ...) TP _CONCAT(__grmr_, __LINE__)[] = __VA_ARGS__; \
				grammar TGT = tok_##OP(_CONCAT(__grmr_, __LINE__), sizeof(_CONCAT(__grmr_, __LINE__)) / sizeof(TP))

#define CHAINH(TGT, ...) _HEAP_OP(TGT, grammar, chain, {__VA_ARGS__})
#define CHAIN(TGT, ...) _STACK_OP(TGT, grammar, chain, {__VA_ARGS__})
#define ORH(TGT, ...) _HEAP_OP(TGT, grammar, or, {__VA_ARGS__})
#define OR(TGT, ...) _STACK_OP(TGT, grammar, or, {__VA_ARGS__})

#ifndef CUSTOM_LITERAL 
//presumes literal has code 0, if yours does not, define CUSTOM_LITERAL
#define LITERALH(TGT, SRC) _HEAP_OP(TGT, char, lit, SRC)
#define LITERAL(TGT, SRC) _STACK_OP(TGT, char, lit, SRC)
#define CHAR_CLASSH(TGT, SRC) _HEAP_OP(TGT, char, char_class, SRC)
#define CHAR_CLASS(TGT, SRC) _STACK_OP(TGT, char, char_class, SRC)
#endif

#define _SHEAP_OP(TGT, TP, OP, SRC) TP* _LOCAL_VAR = malloc(sizeof(TP)); \
				*_LOCAL_VAR = SRC; \
				grammar TGT = tok_##OP(_LOCAL_VAR)
#define _SSTACK_OP(TGT, TP, OP, SRC) grammar TGT = tok_##OP(&SRC)

#define REPEAT1H(TGT, SRC) _SHEAP_OP(TGT, grammar, repeat1, SRC)
#define REPEAT1(TGT, SRC) _SSTACK_OP(TGT, grammar, repeat1, SRC)
#define REPEAT0H(TGT, SRC) _SHEAP_OP(TGT, grammar, repeat0, SRC)
#define REPEAT0(TGT, SRC) _SSTACK_OP(TGT, grammar, repeat0, SRC)

#define GROUPH(TGT, SRC) _SHEAP_OP(TGT, grammar, group, SRC)
#define GROUP(TGT, SRC) _SSTACK_OP(TGT, grammar, group, SRC)

#define CASTH(TGT, SRC, TYPE) grammar* _LOCAL_VAR = malloc(sizeof(grammar)); \
			*_LOCAL_VAR = SRC; \
			grammar TGT = tok_cast(_LOCAL_VAR, TYPE)
#define CAST(TGT, SRC, TYPE) grammar TGT = tok_cast(&SRC, TYPE);

#define BASE_RULE(NAME, PARAMS, G, LEN) ATOM_DEF(NAME); BASE_RULE2(NAME, PARAMS, G, LEN) ATOM_DEF(NAME)

#define BASE_RULE2(NAME, PARAMS, G, LEN) grammar NAME PARAMS { grammar g2; g2.f = _##NAME; g2.g = G; g2.len = LEN; return g2;}
#define ATOM_DEF(NAME) int _##NAME (sbf s, tokens* ts, grammar g)

//g acts like metadata and the entire grammar is passed into f, since C has no closures
//and no, I still don't wanna use c++
typedef struct grammr_t{
	int (*f)(sbf, tokens*, struct grammr_t);
	void* g;
	size_t len;
} grammar;

#include "tokenizer.h"

typedef int (*atom_fn)(sbf, tokens*, grammar);

grammar tok_or(grammar* g, size_t len);
grammar tok_repeat0(grammar* g);
grammar tok_repeat1(grammar* g);
grammar tok_chain(grammar* g, size_t len);
grammar tok_lit(char* s, size_t _len);
grammar tok_group(grammar* g);
grammar tok_cast(grammar* g, int16_t i);
grammar tok_char_class(char* a, size_t _len);
#endif
