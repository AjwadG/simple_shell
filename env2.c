#include "main.h"


/**
 * add_node - add node
 * @head: head of nude
 * @env_value: string
 * Return: 1 success 0 otehr wise
 */
int add_node(node **head, char *env_value)
{
	node *tmp;

	tmp = malloc(sizeof(node));
	if (tmp == NULL)
	{
		write(STDOUT_FILENO, "filed add_node\n", 15);
		return (0);
	}
	tmp->next = *head;
	tmp->env = strdup(env_value);
	*head = tmp;
	return (1);
}
/**
 * env_val - gets the value of env
 * @env: env list head
 * @name: name of the env
 * Return: pointer to the value
 */
char *env_val(node *env, char *name)
{
	node *tmp = env;
	int i;

	while (tmp)
	{
		if (envcmp(tmp->env, name))
		{
			for (i = 0; tmp->env[i]; i++)
			{
				if (tmp->env[i] == '=')
					return (&(tmp->env[i + 1]));
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}


/**
 * get_node - pointer to node
 * @env: env list head
 * @name: name of the env
 * Return: pointer to the value
 */
node *get_node(node *env, char *name)
{
	node *tmp = env;

	while (tmp)
	{
		if (envcmp(tmp->env, name))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * set_env - sets the value of env
 * @env: env pointer
 * @name: name of the env
 * @value: value of the env
 * Return: pointer to the value
 */
void set_env(node *env, char *value, char *name)
{
	free(env->env);
	env->env = str_concat(name, value);
}
