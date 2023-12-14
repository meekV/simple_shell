#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void display_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

int main(void)

{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		display_prompt();

		if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		input[strcspn(input, "\n")] = '\0';

		pid_t pid = fork();

		if (pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			if (execlp(input, input, (char *)NULL) == -1)
			{
				perror("Command not found");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int status;
			waitpid(pid, &status, 0);

			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				printf("./shell: No such file or directory\n");
			}
		}
	}

	printf("\n");
	return (0);
}
