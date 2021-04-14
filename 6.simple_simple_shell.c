#include "shell.h"
/**
* main - entry point th the simple shell
*
* Return: 0 on suceess, exit code on error (with stderr output)
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
			if (errno == 0)
				break; /* this means EOF */
			else if (errno == 25)
			{
				break;
			}
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

/**
* tokenize - Use strtok to measure a string and create an array of pointers
*	to delimited sections within it
* @string: null-terminated array of characters to be tokenized
* @delim: delimiter by which to identify the end of one token
*	and beginning of the next
*
* Return: An array of pointers which each point to the first character
*	of subsequnt token segments of the input string.
*/
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

/**
  *fork_find_exec - function to preform the fork function
  *@lineptr: the the string being passed int the stream
  *@exec_str: the token of the stream being searched for
  *Return: status of wait
  */
int fork_find_exec(char *lineptr, char **exec_str)
{

	pid_t child;
	int status = 0;
	char *path_str = NULL;
	char word_path[5] = {'P', 'A', 'T', 'H', '\0'};

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
		if (execve(exec_str[0], exec_str, environ) == -1)
		{
			free(lineptr);
			free(exec_str);
			perror("execve");
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
	return (status);
}
