#include "main.h"

/**
 * build_env - build linked list env
 * @env: env list
 *
 * Return: poniter to head of the linked list
 */
node *build_env(char **env)
{
	int i = 0;
	node *env_head = NULL;

	while (env[i])
	{
		add_node(&env_head, env[i++]);
	}

	return (env_head);
}

/**
 * free_env - free env linked list
 * @env_head: head of struct
 */
void free_env(node *env_head)
{
	node *head;
	int i;

	for (i = 0; env_head; i++)
	{
		head = env_head;
		env_head = env_head->next;
		free(head->env);
		free(head);
	}
}

/**
 * print_env - prints linked list
 * @head: pointer to linked list
 * Return: 1 allways
 */
int print_env(node *head)
{
	node *tmp = head;

	if (!tmp)
		return (0);
	print_env(tmp->next);
	write(STDOUT_FILENO, tmp->env, len(tmp->env) - 1);
	write(STDOUT_FILENO, "\n", 1);
	return (1);
}


/**
 * envcmp - fucntion
 * @env: a pointer to env value
 * @s: a pointer to a string
 *
 * Description: compares two strings env and s2
 *
 * Return: 1 if they r the same 0 otehr wise
 */

int envcmp(char *env, char *s)
{
	int i = 0;

	while (1)
	{
		if (env[i] == '=' && s[i] == '\0')
			return (1);
		else if (env[i] == '\0')
			return (0);
		else if (env[i] != s[i])
			return (0);
		i++;
	}
	return (0);
}

/**
 * is_env - cheks if env contains =
 * @var: value of env
 * Return: 1 if it dose 0 if not
 */
int is_env(char *var)
{

	int i = 0;

	for (i = 0; var[i]; i++)
	{
		if (var[i] == '=')
			return (1);
	}
	return (0);

}
