#ifndef LEXER_H
#define LEXER_H

#include "token.h"

int lexer_tokenize(const char* source_code, TokenList *token_list);

#endif