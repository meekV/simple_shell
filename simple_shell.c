#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main(void) {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("($) ");
        fflush(stdout);

        // Read command from the user
        if (fgets(command, sizeof(command), stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid == -1) {
            // Forking error
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process

            // Execute the command
            if (execlp(command, command, (char *)NULL) == -1) {
                // Handle command not found
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process

            // Wait for the child to finish
            int status;
            waitpid(pid, &status, 0);

            // Check for errors
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                printf("Error: Command not found\n");
            }
        }
    }

    return (0);
}
