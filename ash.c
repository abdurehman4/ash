#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void getCommand(char **string);
void prompt(int *isFirst, char *path);

int main() {
  char path[PATH_MAX];
  char *command;
  int isFirst = 1;

  getcwd(path, sizeof(path));
  while (1) {
    prompt(&isFirst, path);
    getCommand(&command);
    printf("The given cmd is :\n%s", command);
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
