#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr,
                "[ERROR] Container to run not specified.\n");
        return 1;
    }

    char *program = argv[1];

    pid_t process = fork();

    if (process < 0) {
        perror("fork");
        return 1;
    }

    if (process == 0) {
        // Execvup doesnt return on success case. 
        execvp(program, &argv[1]);

        // We only get here if execvup failed.
        perror("execvp");
        return 127;
    }

    // father
    int status;

    if (waitpid(process, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    return 1;
}