#include "main.h"
/**
 * add_end_node - Add a new node at the end of the list.
 * @head: Pointer to the head of the list.
 * @dir: Directory value for the new node.
 *
 * Return: Pointer to the newly added node or NULL on failure.
 */
node_t *add_end_node(node_t **head, char *dir)
{
	node_t *n_node = malloc(sizeof(node_t));
	node_t *last_node;

	if (!n_node)
		return (NULL);

	n_node->directory = dir;
	n_node->next = NULL;

	if (*head)
	{
		last_node = *head;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = n_node;
	}
	else
		*head = n_node;

	return (n_node);
}
/**
 * alias_end_add - Add a new alias node at the end of the list.
 * @head: Pointer to the head of the alias list.
 * @name: Name of the alias.
 * @value: Value of the alias.
 *
 * Return: Pointer to the newly added alias node or NULL on failure.
 */
struct_alias_t *alias_end_add(struct_alias_t **head, char *name, char *value)
{
	struct_alias_t *n_node = malloc(sizeof(struct_alias_t));
	struct_alias_t *last_node;

	if (!n_node)
		return (NULL);

	n_node->next = NULL;
	n_node->a_name = malloc(sizeof(char) * (str_len(name) + 1));
	if (!n_node->a_name)
	{
		free(n_node);
		return (NULL);
	}
	n_node->a_name = value;
	str_cpy(n_node->a_name, name);

	if (*head)
	{
		last_node = *head;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = n_node;
	}
	else
		*head = n_node;

	return (n_node);
}

/**
 * free_list_alias - Frees the memory allocated for a linked list of aliases.
 * @head: Pointer to the head of the alias list.
 *
 * Return: void
 */
void free_list_alias(struct_alias_t *head)
{
	struct_alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->a_name);
		free(head->a_name);
		free(head);
		head = next;
	}
}
/**
 * list_free - Frees the memory allocated for a linked list.
 * @head: Pointer to the head of the list.
 *
 * Return: void
 */
void list_free(node_t *head)
{
	node_t *next;

	while (head)
	{
		next = head->next;
		free(head->directory);
		free(head);
		head = next;
	}
}