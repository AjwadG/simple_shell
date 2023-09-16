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

/**
 * struct list - struct
 * @env: evirument value
 * @next: pointer to next node
 */
typedef struct list
{
	char *env;
	struct list *next;
} node;

extern char **environ;

void handle_terminal(char *name, node **env);
void handle_echo(char *name, node **env);
void handle_file(char **arg, node **env);


int isempty(char *s);
char **get_arg(char *s, char *dil);
int count_w(char *s);
char *get_path(char *s);
int print_env(node *env);
int _getline(char **s, int *l, int stream);
void exit_with(char *code);

char *_strtok1(char *str, char *dilm);

int _setenv(node **env, char *name, char *value);
int _unsetenv(char *env_name, node **env);
void free_env(node *env_head);
node *build_env(char **env);
int envcmp(char *env, char *s);
int is_env(char *var);
int add_node(node **head, char *env_value);
int cd(node **env, char *dir);
char *env_val(node *env, char *name);
node *get_node(node *env, char *name);
void set_env(node *env, char *value, char *name);
int alias(node **env, char **arg, char ***ali);
int put_alias(char *new_ali, char ***ali);
char *get_alias(char *name, char **ali);
int free_arr(char **ar);

int *arg_num(char *s, char seq[]);
char ***_strtok(char *s, char seq[]);
char *get_next_arg(char *s, int *k);
int free_arg(char ***ar);

int built_in(node **env, char **arg, char ***ali);


char *str_concat(char *s1, char *s2);
char *_strdup(char *str);
int len(char *s);
int _strcmp(char *s1, char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
#endif
