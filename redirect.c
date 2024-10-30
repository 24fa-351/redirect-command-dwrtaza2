#include "redirect.h"

// Split cmd into arguments
char **split_command(const char *cmd) {
    char **args = malloc(MAX_ARGS * sizeof(char *));
    char *cmd_copy = strdup(cmd);  
    char *token;
    int i = 0;

    token = strtok(cmd_copy, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = strdup(token);  // Store each argument
        token = strtok(NULL, " ");
    }
    args[i] = NULL; 
    free(cmd_copy);
    return args;
}


void execute_redir(const char *inp, const char *cmd, const char *out) {
    char **args = split_command(cmd);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {  // Child process
        if (strcmp(inp, "-") != 0) {  // Redirect input if specified
            int in_fd = open(inp, O_RDONLY);
            if (in_fd < 0) { perror("Input file open failed"); exit(EXIT_FAILURE); }
            if (dup2(in_fd, STDIN_FILENO) < 0) { perror("dup2 failed for input"); close(in_fd); exit(EXIT_FAILURE); }
            close(in_fd);
        }

        if (strcmp(out, "-") != 0) {  // Redirect output if specified
            int out_fd = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_fd < 0) { perror("Output file open failed"); exit(EXIT_FAILURE); }
            if (dup2(out_fd, STDOUT_FILENO) < 0) { perror("dup2 failed for output"); close(out_fd); exit(EXIT_FAILURE); }
            close(out_fd);
        }

        execvp(args[0], args);  
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0); 
    }

    for (int i = 0; args[i] != NULL; i++) free(args[i]);  // Clean up args
    free(args);
}
