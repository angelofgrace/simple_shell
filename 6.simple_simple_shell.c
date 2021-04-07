#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
extern char **environ; /* enviornmental array */
int _strlen(char *s); /* string length helper function */
void free_token(char *array[], int size); /* data free-ing helper function */


int main(void)
{
        int i = 0, status;
        char *lineptr = NULL;
        char *token = NULL;
	char **exec_str = calloc(50, sizeof(char *));
        size_t n = 0;
        ssize_t character;
        pid_t child;

        printf("$ "); /* prompt user for input */
        getline(&lineptr, &n, stdin);
        token = strtok(lineptr, " ");
        while (token != NULL)
        {
        /*fill tokens into array of strings: exec_str*/
                exec_str[i] = malloc(sizeof(token));
                if (exec_str[i] == NULL) /* malloc fail */
                {
                        free(lineptr);
                        free_token(exec_str, i);
			exit(-1);
            	}
                strcpy(exec_str[i], token);
                token = strtok(NULL, " ");
                i++;
        }
	/* replace newline character with null byte */
	exec_str[i - 1][_strlen(exec_str[i - 1]) - 1] = '\0'; 
        child = fork();
        if (child == -1) /* fork fail */
        {
                free(lineptr);
                free_token(exec_str, i);
                exit(0);
        }
	if (child == 0)
        {
		/* execute bash script, overwriting child process */
                character = execve(exec_str[0], exec_str, environ);
		if (character == EOF) /* execve fail */
		{
			free(lineptr);
			free_token(exec_str, i);
			exit(0);
		}
        }
        else
        {
		wait(&status);
        }
        free(lineptr);
        free_token(exec_str, i);
        return (0);
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

        while (*s != '\0')
        {
                s++;
                x++;
        }

return (x);
}
