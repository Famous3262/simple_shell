#include "temp.h"

/**
 * print_env - prints the current environment
 * @info: Structure containing potential arguments
 *
 * Return: 0 on success
 */
int print_env(info_t *info)
{
	/* Print the list of strings in the info structure's environment */
	print_list_str(info->env);

	/* Return 0 to indicate successful execution */
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @name: env var name
 *
 * Return: the value
 */
char *get_env(info_t *info, const char *name)
{
	char **envp;

	for (envp = info->env; *envp; envp++)
	{
		char *p = starts_with(*envp, name);

		if (p && *p)
			return (p);
	}

	return (NULL);
}

/**
 * new_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int new_env(info_t *info)
{
	int success = 0;

	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		success = 1;
	}
	else
	{
		if (set_env(info, info->argv[1], info->argv[2]))
			success = 0;
		else
			success = 1;
	}

	return (success);
}

/**
 * rem_env - Removes environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int rem_env(info_t *info)
{
	int d, success = 0;

	if (info->argc < 2)
	{
		_eputs("Too few arguments.\n");
		success = 1;
	}
	else
	{
		for (d = 1; d < info->argc; d++)
		{
			if (!unset_env(info, info->argv[d]))
			{
				success = 1;
			}
		}
	}

	return (success);
}

/**
 * populate_env_list - populates environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a = 0;

	while (environ[a] != NULL)
	{
		add_node_end(&node, environ[a], 0);
		a++;
	}

	info->env = node;
	return (0);
}

/**
 * get_environ - returns the string array
 * @info: Structure containing potential arguments
 *
 * Return: pointer to the string array of the environment
 */
char **get_environ(info_t *info)
{
	if (info->environ == NULL || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string environment variable property
 * Return: 1 on delete, 0 otherwise
 */
int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t s = 0;
	char *p;

	if (node == NULL || var == NULL)
		return (0);

	while (node != NULL)
	{
		p = starts_with(node->str, var);
		if (p != NULL && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), s);
			s = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		s++;
	}

	return (info->env_changed);
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *
 * Return: Always 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buf;
	list_t *node;
	char *p;

	if (var == NULL || value == NULL)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (buf == NULL)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (node != NULL)
	{
		p = starts_with(node->str, var);
		if (p != NULL && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	info->env_changed = 1;
	return (0);
}
