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
#include <signal.h>

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

/**
 * struct all - struct
 * @envs: pointer to env array
 * @args: pointer to array of pointers of args
 * @env: pointer to head of env list
 * @count: the number that the
 * @s: the string that stores input
 * @status: last exit stat
 * @seq: seq of comands
 * @ali: array of alias
 * @name: name of the file
 * @com: name of the comand
 * @fd: file descreptor if any
 */
typedef struct all
{
	char **envs;
	char ***args;
	node *env;
	int count;
	char *s;
	int status;
	char seq[10];
	char **ali;
	char *name;
	char *com;
	int fd;
} all_t;


extern char **environ;

void handle_terminal(all_t *a);
void handle_echo(all_t *a);
void handle_file(all_t *a);


int isempty(char *s);
char **get_arg(char *s, char *dil);
int count_w(char *s);
char *get_path(char *PATH, char *s);
int print_env(node *env);
int _getline(char **s, int *l, int stream);
int exit_with(char *code, all_t *a);


void args_loop(all_t *a);



int _setenv(node **env, char *name, char *value);
int _unsetenv(char *env_name, node **env);
void free_env(node *env_head);
node *build_env(char **env);
int envcmp(char *env, char *s);
int is_env(char *var);
int add_node(node **head, char *env_value);




int cd(char *dir, all_t *a);
void cd_error(char *dir, all_t *a);
char *_strtok1(char *s, int *k);



char *env_val(node *env, char *name);
node *get_node(node *env, char *name);
void set_env(node *env, char *value, char *name);
int alias(node **env, char **arg, char ***ali);
int put_alias(char *new_ali, char ***ali);
char *get_alias(char *name, char **ali);
int free_arr(char **ar);

int *arg_num(char *s, char seq[10]);
char ***_strtok(char *s, char seq[10]);
char *get_next_arg(char *s, int *k);
int free_arg(char ***ar);
int list_arr(node *env, char ***envs);
char *ali_val(char **ali, char *name);
char *build_ali(char *ali, char *val);
void print_alias(char *ali);

void free_all(all_t *a);

int built_in(char **arg, all_t *a);
void print_err(char *name, int n, char *com);
void nto_string(int n, char *s);




void var(char **arg, node *env, char **ali, int n);
int handle_pid_rep(char **arg, int index);
int handle_exit_rep(char **arg, int n, int index);
int handle_env_rep(char **arg, node *env, int index);



char *str_concat(char *s1, char *s2);
char *_strdup(char *str);
int len(char *s);
int _strcmp(char *s1, char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
#endif
