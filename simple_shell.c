#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt(void)
{
    printf("($) ");
}

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;

    while (1)
    {
        display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        pid = fork();

        if (pid == -1)
        {
            perror("Fork error");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (execlp(command, command, (char *)NULL) == -1)
            {
                perror("Command not found");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
        }
    }

    return 0;
}

