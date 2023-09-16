#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;

void handle_terminal(char *name);
void handle_echo(char *name);
int isempty(char *s);
char **get_arg(char *s, char *dil);
int count_w(char *s);
char *get_path(char *s);
int print_env(void);
int _getline(char **s, int *l, int stream);
void exit_with(char *code);
char *_strtok(char *str, char *dilm);
int _setenv(char *name, char *value);
int _unsetenv(char *env_name);




char *str_concat(char *s1, char *s2);
char *_strdup(char *str);
int len(char *s);
int _strcmp(char *s1, char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
#endif
