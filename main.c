#include "redirect.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <inp> <cmd> <out>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    execute_redir(argv[1], argv[2], argv[3]);
    return 0;
}
