#include "tokenizer.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void getCommand(char **string);
void prompt(int *isFirst, char *path);
int newProcess(tokens_t *tokens);

int main() {
  char path[PATH_MAX];
  tokens_t *tokens;
  char *command;
  int isFirst = 1;
  getcwd(path, sizeof(path));
  while (1) {
    prompt(&isFirst, path);
    getCommand(&command);
    if (strlen(command) == 0) {
      continue;
    }
    tokenize(command, &tokens);
    if (strcmp(tokens->array[0], "exit") == 0) {
      return 0;
    }
    newProcess(tokens);
  }
}

void prompt(int *isFirst, char *path) {
  *isFirst ? printf("«%s» ", path) : printf("\n«%s» ", path);
  if (*isFirst)
    *isFirst = 0;
}

void getCommand(char **string) {
  char buffer[1024];
  fgets(buffer, 1024, stdin);
  buffer[strcspn(buffer, "\n")] = '\0';
  *string = strdup(buffer);
}

int newProcess(tokens_t *tokens) {
  pid_t pid;
  pid = fork();
  int status;
  char **args = tokens->array;
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("Error occured while forking");
  } else {
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}
