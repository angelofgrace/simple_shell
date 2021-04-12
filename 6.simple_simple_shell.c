#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include "shell.h"
int _strlen(char *s); /* string length helper function */
char **tokenize(char *string, char *delim);
void free_ptr_arr(char **dbl_ptr);

int main(void)
{
	int  status;
	char *lineptr = NULL;
	char **exec_str = NULL; 
	size_t n = 0;
	ssize_t character;
	pid_t child;

	while (getline(&lineptr, &n, stdin) != -1)
	{
        	printf("$ "); /* prompt user for input */
		lineptr[_strlen(lineptr) - 1] = '\0'; /* replace /n with null byte */
		exec_str = tokenize(lineptr, " "); /* tokenize commands */

		child = fork();
	        if (child == -1) /* fork fail */
        	{
                	free(lineptr);
	                free(exec_str);
        	        exit(0);
	        }
		if (child == 0)
	        {
			/* execute shell script, overwriting child process */
                	character = execve(exec_str[0], exec_str, environ);
			if (character == EOF) /* execve fail */
			{
				free(lineptr);
				free(exec_str);
				exit(0);
			}
        	}
	        else
        	{
			wait(&status);
	        }
	free(exec_str);
	}
	free(lineptr);
        return (0);
}


char **tokenize(char *string, char *delim)
{
	int token_count = 1, i = 0, x = 0, len = 0;
	char *token = NULL;
	char **parsed_str = NULL;

	len = _strlen(string);
	token = strtok(string, delim); /* init strtok with default delim */
	while (token != NULL)
	{
		token = strtok(NULL, delim); /* iterate strtok */
		token_count++; /* gauge number of required pointers */
	}
	for (x = 0; x < len; x++)
	{
		if (string[x] == '\0')
			string[x] = delim[0];
	}
	/* allocate space for pointers to the array of strings */
	parsed_str = malloc(sizeof(char *) * token_count);
	if (parsed_str == NULL)
	{
		free(string);
		exit(1);
	}
	token = strtok(string, delim); /* init strtok again */
	parsed_str[token_count - 1] = NULL; /* NULL terminate the array of strings */
	while (i <= token_count)
	{
		parsed_str[i] = (token);
		token = strtok(NULL, delim);
		token_count--;
		i++;
	}
	return (parsed_str);
}

/*
* _strlen - determine the length of an array of characters
* @s: input string literal
*
* Return: number of characters in the string
*/

int _strlen(char *s)
{
        int x;

	x = 0;

	if (s == NULL)
	{
		return(x);
 	}

        while (s[x] != '\0')
        {
                x++;
        }

return (x);
}
