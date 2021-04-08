#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ;

/* Core Functions */

/* Parse the global var, environ, usually to find PATH */
char *_get_env(char *name);


/* Helper Functions */

/* Search a string for a substring */
char *_strstr(char *haystack char *needle);

/* Find a the length of a string */
int _strlen(char *s);

/* Determine whether two strings are identical */
int _strcmp(char *s1, char *s2);


/* SHELL_H end */
#endif
