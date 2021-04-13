#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include "shell.h"

#define BUF_SIZE 1024

int main(void)
{
	int  status, x, chars_read;
	char *lineptr = NULL, *path_str = NULL;
	char word_path[5] = {'P', 'A', 'T', 'H', '\0'};
	char **exec_str = NULL; 
	size_t n = 0;
	pid_t child;

	while (1)
	{
		if (isatty(fileno(stdin)))
		       	write(2, "$ ", 2); /* prompt user for input */
		
		if (getline(&lineptr, &n, stdin) == -1)
		{
			chars_read = read(STDIN_FILENO, lineptr, BUF_SIZE);
			if (chars_read == 0)
				break; /* this means EOF */
			else if (chars_read == -1)
			{
				perror("read"); /* read error */
				break;
			}	
			else
			{
				perror("getline"); /* getline error */
				break;
			}
		}
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
			path_str = _getenv(word_path);
			exec_str[0] = search_PATH(path_str, exec_str[0]);
			for (x = 0; exec_str[x] != NULL; x++)
				printf("Element %d of exec_str: %s\n", x, exec_str[x]);
			/* execute shell script, overwriting child process */
                	if (execve(exec_str[0], exec_str, environ) == -1)
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
	token_count--;
	while (i < token_count)
	{
		parsed_str[i] = (token);
		token = strtok(NULL, delim);
		i++;
	}
	return (parsed_str);
}

