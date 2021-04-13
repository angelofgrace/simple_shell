#include "shell.h"

/**
* get_env - prints the environment
* @name: string sought within the environment array of strings
*
* Return: found string, name, at its location within ennviron
*/
char *_getenv(char *name)
{
	int i;
	char *env_str = NULL;

	if (!name)
	{
		return NULL;
	}

	for (i = 0; environ[i] != '\0'; i++)
	{
		if (_strspn(environ[i], name) == 0)
			break;
	}
	env_str = _strdup(environ[i] + 5); /* preserve PATH integrity */
	printf("Environment String: %s\n", env_str);
	return (env_str);
}

/**
* search_PATH - tokenize the PATH environment and search for
* 	an existing executable file
* @pth: PATH environment value
* @command_file: desired executable command
*
* Return: pointer to the full path name of an executable script
*/
char *search_PATH(char *pth, char *command_file)
{
	int i = 0, cmd_len = 0, x;
	char **env_token = NULL;
	char *dir = NULL;
	struct stat structbuf;

	env_token = tokenize(pth, ":");
	for (x = 0; env_token[x] != NULL; x++)
	printf("Env_token %d: %s\n", x, env_token[x]);
	cmd_len = _strlen(command_file);
	while (env_token[i])
	{
		dir = malloc(sizeof(char) * (cmd_len + _strlen(env_token[i]) + 2));
		printf("DIR (envtok duplicate): %s\n", env_token[i]);
		dir = _strncpy(dir, env_token[i], _strlen(env_token[i]));
		printf("DIR is still: %s\n", dir);
		/* combine command with directory path */
		dir = _strncat(dir, "/", 2); /* slash before command sought */
		printf("DIR still is?: %s\n", dir);
		dir = _strncat(dir, command_file, cmd_len + 1); /* add command */
		printf("Full pathname %s\n", dir);
		if (stat(dir, &structbuf) == 0)
		{
			free(env_token);
			break;
		}
		free(dir);
		dir = NULL;
		i++;
	}
	free(pth);
	if (!dir)
	{
		return ("Error");
	}
	return (dir);
}
