#include "shell.h"

/**
* get_env - prints the environment
* @name: string sought within the environment array of strings
*
* Return: found string, name, at its location within ennviron
*/
char *_getenv(const char *name)
{
	int i;
	char *found;

	if (!name)
		exit(0);

	for (i = 0; environ[i] != 00; i++)
	{
		found = strstr(environ[i], name);
		if (found)
			break;
	}

	printf("%s\n", environ[i]);
	return (environ[i]);
}


int main (void)
{
	char *env = _getenv("PWD");

	(void)env;
	return (0);
}
