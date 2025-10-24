#include "tokenizer.h"
#include <iso646.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void appendToken(char *token, tokens_t **tokens);
void tokenize(char *string, tokens_t **tokens);

void appendToken(char *token, tokens_t **tokens) {
  int n = (*tokens)->n;
  if ((*tokens)->capacity < (*tokens)->n) {
    (*tokens)->capacity *= 2;
    (*tokens)->array =
        realloc((*tokens)->array, sizeof(char **) * (*tokens)->capacity);
  }
  (*tokens)->array[n] = (char *)malloc(sizeof(char) * (strlen(token) + 1));
  strcpy((*tokens)->array[n], token);
  (*tokens)->n++;
}

void tokenize(char *string, tokens_t **tokens) {
  char *token;
  char *dstring = strdup(string);
  char *delimiter = " ";
  token = strtok(dstring, delimiter);
  *tokens = (tokens_t *)malloc(sizeof(tokens_t));
  (*tokens)->capacity = 8;
  (*tokens)->array = (char **)malloc(sizeof(char *) * (*tokens)->capacity);

  // Malloc for a single element of the array
  (*tokens)->array[0] = (char *)malloc(sizeof(char) * (strlen(token) + 1));
  strcpy((*tokens)->array[0], token);
  (*tokens)->n = 1;

  while (1) {
    token = strtok(NULL, delimiter);
    if (token == NULL)
      break;
    appendToken(token, tokens);
  }
  free(dstring);
}
