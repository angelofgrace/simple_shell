#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
extern char **environ; /* enviornmental array */
int _strlen(char *s); /* string length helper function */
void free_token(char *array[], int size); /* data free-ing helper function */
char **tokenize(char *line, int *token_count);

int main(void)
{
        int  token_count = 0, status;
        char *lineptr = NULL;
	char **exec_str = NULL; 
        size_t n = 0;
        ssize_t character;
        pid_t child;

        printf("$ "); /* prompt user for input */
        getline(&lineptr, &n, stdin);
	exec_str = tokenize(lineptr, &token_count);
        child = fork();
        if (child == -1) /* fork fail */
        {
                free(lineptr);
                free_token(exec_str, token_count);
                exit(0);
        }
	if (child == 0)
        {
		/* execute bash script, overwriting child process */
                character = execve(exec_str[0], exec_str, environ);
		if (character == EOF) /* execve fail */
		{
			free(lineptr);
			free_token(exec_str, token_count);
			exit(0);
		}
        }
        else
        {
		wait(&status);
        }
        free(lineptr);
        free_token(exec_str, token_count);
        return (0);
}

char **tokenize(char *line, int *token_count)
{
	char *token = NULL;
	char **exec_str = malloc(50 * sizeof(char *));

	*token_count = 0;
	token = strtok(line, " ");
	while (token != NULL)
	{
		exec_str[*token_count] = malloc(sizeof(token));
		if (exec_str[*token_count] == NULL)
		{
			free(line);
			free_token(exec_str, *token_count);
			exit (0);
		}
		strcpy(exec_str[*token_count], token);
		token = strtok(NULL, " ");
		*token_count = *token_count + 1;
	}
	exec_str[*token_count - 1][_strlen(exec_str[*token_count - 1]) - 1] = '\0';

	return(exec_str);
}

/**
* free_token - frees tokens upon error
*/
void free_token(char **exec_str, int i)
{
        while (i >= 0)
        {
                free(exec_str[i]);
                i--;
        }
        free(exec_str);
}


int _strlen(char *s)
{
        int x;

        x = 0;
        while (s[x] != '\0')
        {
                x++;
        }

return (x);
}
