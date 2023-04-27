#include "temp.h"

/**
 * list_len - Function that defines length of linked list
 * @h: Pointer to the first node
 *
 * Return: size of the list
 */
size_t list_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - Function that returns an array of strings of the list->str
 * @head: Pointer to that first node
 *
 * Return: Array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t j = list_len(head), i;
	char **strs;
	char *str;

	if (!head || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);
	for (j = 0; node; node = node->next, j++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (i = 0; i < j; i++)
				free(strs[i]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}


/**
 * print_list -Function that  prints all elements of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * node_starts_with - Function returns node whose string starts with prefix
 * @node: Pointer to list head
 * @prefix: Pointer to string to match
 * @c: Next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *s = NULL;

	while (node)
	{
		s = starts_with(node->str, prefix);
		if (s && ((c == -1) || (*s == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Function that gets the index of a node
 * @head: Pointer to list head
 * @node: Pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
