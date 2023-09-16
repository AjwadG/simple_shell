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
