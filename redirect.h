#ifndef REDIR_H
#define REDIR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

char **split_command(const char *cmd);  // Splits cmd into arguments
void execute_redir(const char *inp, const char *cmd, const char *out);  // Redirects input/output, executes cmd

#endif // REDIR_H
