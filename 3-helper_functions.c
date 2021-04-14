#include "shell.h"

/**
* _strstr - locate a substring
* @haystack: string to be searched
* @needle: substring sought
*
* Return: pointer to beginning of found substring, or NULL
*/

char *_strstr(char *haystack, char *needle)
{
	int i, j, y;
	char *p = NULL;

	i = y = 0;
	p = &haystack[0];

	while (haystack[i] != 00)
	{
		j = 0;

		if (needle[0] == 00)
			return (p);

		while (needle[j] == haystack[i])
		{
			j++;
			i++;
			if (needle[j] == 00)
			{
				y = 1;
				break;
			}
		}
		i++;
	}
	if (y == 0)
	{
		return (NULL);
	}
	else
		return (p);
}

/**
  **_strdup - returns a pointer to a newly allocated space in memory
  *@str: the string to duplicate
  *
  *Return: pointer to dup string or NULL if str is NULL or insufficient memory
  */
char *_strdup(char *str)
{
	char *p;
	int n, len;

	if (str == NULL)
		return (NULL);
	for (len = 0; str[len] != 00; len++)
		continue;
	p = malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	for (n = 0; n <= len; n++)
		p[n] = str[n];
	return (p);
}

/**
* _strncpy - copy n characters from string src to dest
* @dest: location to be written as src
* @src: string literal of any length
* @n: number of characters to write from src to dest
*	(excess written as null bytes)
*
* Return: pointer to the newly copied string (dest)
*/
char *_strncpy(char *dest, char *src, int n)
{
	int k;

	for (k = 0; k < n; k++)
	{
		if (k < _strlen(src))
			dest[k] = src[k];
	}
	dest[k] = '\0';
	return (dest);
}

/**
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
		return (x);
	}

	while (s[x] != '\0')
	{
		x++;
	}

return (x);
}

/**
* _strncat - concatenate up to n characters from source to dest
* @dest: first part of string, target for concatenation
* @src: second part of string, some amount of it will be added to dest
* @n: a number, of letters from src to be concatenated to dest
*
* Return: pointer at dest
*/

char *_strncat(char *dest, char *src, int n)
{
	int i, k;

	for (i = _strlen(dest), k = 0; k < n; i++, k++)
	{
		dest[i] = src[k];

		if (k == _strlen(src))
			break;
	}

	return (dest);
}

