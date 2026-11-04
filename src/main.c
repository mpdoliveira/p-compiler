#include "file_utils.h"
#include "token.h"
#include "lexer.h"

int main() {
    char *source_file = read_file("tests/test.txt");
    TokenList token_list = create_token_list();
    lexer_tokenize(source_file, &token_list);
    print_token_list(&token_list);
}