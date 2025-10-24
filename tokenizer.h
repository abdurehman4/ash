#ifndef TOKENIZER_H
#define TOKENIZER_H

struct Tokens {
  int n;
  int capacity;
  char **array;
};

typedef struct Tokens tokens_t;
void appendToken(char *token, tokens_t **tokens);
void tokenize(char *string, tokens_t **tokens);

#endif // TOKENIZER_H
