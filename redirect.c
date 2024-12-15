#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void add_char_to_string(char *str, char ch) {
    int ln = strlen(str);
    str[ln] = ch;
    str[ln + 1] = '\0';
}

void split(char *cmd, char *words[], char dl) {
    int wc = 0;
    char *nc = cmd;
    char cw[1004];
    strcpy(cw, "");

    while (*nc != '\0') {
        if (*nc == dl) {
            words[wc++] = strdup(cw);
            strcpy(cw, "");
        } else {
            add_char_to_string(cw, *nc);
        }
        ++nc;
    }
    words[wc++] = strdup(cw);
    words[wc] = NULL;
}

// true == found
bool get_abs_path(char *cmd, char abs_path[]) {

  char *directory[1000];
  split(getenv("PATH"), directory, ':');

  for (int i = 0; directory[i] != NULL; i++) {
    char path[1004];
    strcpy(path, directory[i]);
    add_char_to_string(path, '/');
    strcat(path, cmd);
    if (access(path, X_OK) == 0) {
      strcpy(abs_path, path);
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  char abs_path[1024];
  char *words[1024];

  split(argv[2], words, ' ');

  if (words[0] == NULL) {
    printf("No command provided\n");
    return 1;
  }
  if (!get_abs_path(words[0], abs_path)) {
    printf("Command not found: %s\n", words[0]);
    return 1;
  }

  for (int i = 0; words[i] != NULL; i++) {
    printf("words[%d] = %s\n", i, words[i]);
  }
  printf("abs_path = %s\n", abs_path);

  execve(abs_path, words, NULL);
  printf("Failed to execute \n");
  return 1;
}