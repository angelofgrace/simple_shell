#include "shell.h"
/**
  *main - entry point th the simple shell
  *
  *Return 0 on suceess
  */
int main(void)
{
	char *lineptr = NULL;
	char **exec_str = NULL; 
	size_t n = 0;

	errno = 0;
	while (1)
	{
		if (isatty(fileno(stdin)))
		       	write(2, "$ ", 2); /* prompt user for input */
		
		if (getline(&lineptr, &n, stdin) == -1)
		{
			if (errno = 0)
				break; /* this means EOF */
			else
			{
				perror("getline"); /* getline error */
				break;
			}
		}
		lineptr[_strlen(lineptr) - 1] = '\0'; /* replace /n with null byte */
		exec_str = tokenize(lineptr, " "); /* tokenize commands */
		fork_find_exec(lineptr, exec_str);
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
