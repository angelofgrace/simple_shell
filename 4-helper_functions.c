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

/**
* handler - handles ^C signal
* @num: input null argument
*
* Return: void
*/
void handler(int num)
{
	(void)num;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
* _strcmp - compare two strings, letter by letter
* @s1: a string literal
* @s2: another string literal
*
* Return: Positive or Negative (based on ASCII value difference) if strings
*	do not match, Zero if strings match entirely
*/

int _strcmp(char *s1, char *s2)
{
	int c;

	for (c = 0; c < _strlen(s2); c++)
	{
		if (s1[c] != s2[c])
			break;
	}

	return (s1[c] - s2[c]);
}
