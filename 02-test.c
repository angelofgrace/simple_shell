#include "shell.h"

extern char **environ;
/**
  *get_env - prints the environment
  *
  */
void *get_env(char **name)
{
	int i;
	char *str;
	if (!name)
		return;
	for (i = 0; name[i] != 00; i++)
	{
		*str = name[i];
		printf("%s\n", str);
	}
}

int main(int ac, char **av, char *envp[])
{
	int i;
	size_t n;
	char *buf = *envp;
	char *token = NULL;
	/* char *pth = "PATH";*/

	/* getline(&pth, &n, "PATH");
	token = strtok(PATH, ":");
	while (token != NULL)
	{
		printf("PATH: %s\n", token);
		token = strtok(NULL, ":");
		printf("end test\n");
	}
	*/
	printf("%s\n", buf);
	for (i = 0; envp[i] != NULL; i++)
	        printf("\n%s", envp[i]);
	return (0);
}
