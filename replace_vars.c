#include "temp.h"

/**
 * is_chain - test if current character in the buffer is a chain delimeter
 * @info: parameter struct
 * @buf: the char buffer
 * @p: the current position address in the buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t a = *p;
	int result = 0;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
		result = 1;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
		result = 1;
	}
	else if (buf[a] == ';')
	{
		buf[a] = 0;
		info->cmd_buf_type = CMD_CHAIN;
		result = 1;
	}

	*p = a;
	return (result);
}

/**
 * check_chain - checks if we should continue chaining based on the last status
 * @info: pointer to the parameter structure
 * @buf: the char buffer
 * @p: points to address of the current position in the buffer
 * @s: starting position in the buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t s, size_t len)
{
	size_t a = *p;

	if (info->cmd_buf_type == CMD_AND && info->status)
	{
		buf[s] = 0;
		a = len;
	}
	else if (info->cmd_buf_type == CMD_OR && !info->status)
	{
		buf[s] = 0;
		a = len;
	}

	*p = a;
}

/**
 * replace_vars - function replaces variables in the tokenized string
 * @info: pointer to the parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int m = 0;
	list_t *node;

	for (m = 0; info->argv[m]; m++)
	{
		if (info->argv[m][0] != '$' || !info->argv[m][1])
			continue;

		if (!_strcmp(info->argv[m], "$?"))
		{
			replace_string(&(info->argv[m]),
					_strdup(convert_number(info->status, 10, 0)));
		}
		else if (!_strcmp(info->argv[m], "$$"))
		{
			replace_string(&(info->argv[m]),
					_strdup(convert_number(getpid(), 10, 0)));
		}
		else
		{
			node = node_starts_with(info->env, &info->argv[m][1], '=');
			if (node)
			{
				replace_string(&(info->argv[m]),
					_strdup(_strchr(node->str, '=') + 1));
			}
		}

		if (!info->argv[m])
			replace_string(&info->argv[m], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - function replaces string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	int result = 0; /* Initialize result to 0 */

	free(*old);
	*old = new;
	return (1); /* Update result to 1 indicating string replaced */
	return (result); /* Return the result */
}

/**
 * replace_alias - function replaces an alias in the tokenized string
 * @info: the parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int n;
	list_t *node;
	char *p;

	for (n = 0; n < 10; n++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (node)
		{
			free(info->argv[0]);
			p = _strchr(node->str, '=');
			if (p)
			{
				p = _strdup(p + 1);
				if (p)
				{
					info->argv[0] = p;
					return (1); /* Return 1 if alias is replaced */
				}
			}
		}
	}

	return (0); /* Return 0 if alias is not replaced */
}
