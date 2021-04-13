#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

/* Core Functions */

/* Apply strtok to a string, create pointer array navigating the elements */
char **tokenize(char *string, char *delim);

/* Parse the global var, environ, usually to find PATH */
char *_getenv(const char *name);

/* Parse the PATH value string to identify requested executable file status */
char *search_PATH(char *pth, char *command_file);


/* Helper Functions */

/* Search a string for a substring */
char *_strstr(char *haystack, char *needle);

/* Find a the length of a string */
int _strlen(char *s);

/* Returns a pointer to a newly allocated memory with identical contents */
char *_strdup(char *str);

/* Concatenate up to n characters from source buffer to destination */
char *_strncat(char *dest, char *src, int n);

/* Copy n characters from source buffer to destination */
char *_strncpy(char *dest, char *src, int n);

/* Reallocate memory holding a string literal */
char *realloc_lite(char *og_str, size_t size);


/* SHELL_H end */
#endif
