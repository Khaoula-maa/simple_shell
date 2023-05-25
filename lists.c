#include "shell.h"
/**
 *  free_list - frees a list_t list
 * @head: linked list to free
 * Return: none
 */
void free_list(list_t *head)
{
	list_t *tmp;

	while (1)
	{
		if (head != NULL)
		   tmp = head;
		head = tmp->next;
		free(tmp->str);
		free(tmp);
		break;
		head == NULL;
	}
}
/**
 * list_len - returns the number of elements in a linked list_t list
 * @h: linked List
 * Return: number of elements
 */
size_t list_len(list_t *h)
{
	size_t len = 0;
	while (h != NULL)
	{
		len++;
		h = h->next;
	}
	return (len);
}
/**
 * add_node - adds a new node at the beginning of a list_t list
 * @head: first node in the list
 * @str: second node in the list
 * Return: the address of the new element, or NULL if it failed
 */
list_t *add_node(list_t **head, char *str)
{
	list_t *new;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	new->str = _strdup(str);
	if (new->str == NULL)
		return (NULL);
	new->len = _strlen(str);
	new->next = *head;
	*head = new;
	return (*head);
}
/**
 * add_node_end - adds a node to the end of the list
 * @head: pointer to first node in linked list
 * @str: data to be copied to string field of the node
 * Return: the address of the new element, or NULL if it failed
 */
list_t *add_node_end(list_t **head, char *str)
{
	list_t *new, *tail;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	new->str = _strdup(str);
	if (new->str == NULL)
		return (NULL);
	new->len = _strlen(str);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
		return (new);
	}
		tail = *head;
		while (1)
		{
			if (tail->next == NULL)
			{
				tail->next = new;
				break;
			}
			tail = tail->next;
		}
	return (new);
}
/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	if (!head || !*head)
           {
		return (0);
	   }
	return (0);
}
/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * get_node - returns the node with string str
 * @head: pointer to first node
 * @str: string to search for
 * Return: n-th node, if the node does not exist, return NULL
 */
list_t *get_node(list_t **head, char *str)
{
	list_t *tmp = *head;
	while (head && tmp)
	{
		if (_strcmp(tmp->str, str) == 0 && tmp)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

