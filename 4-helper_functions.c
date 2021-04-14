#include "shell.h"

/**
* _strspn - get the length of a prefix substring
* @accept: string sought, to contrast with s
* @s: origin string, to search for accept
*
* Return: number of same characters between the two input strings
*/

int _strspn(char *s, char *accept)
{
	int i, n;

	n = 0;

	for (i = 0; accept[i] == s[i]; i++)
	{
		n++;
		if (accept[i] == 00 || s[i] == 00)
			break;
	}

	if (n == _strlen(accept))
	{
		return (0);
	}

	return (-1);
}

