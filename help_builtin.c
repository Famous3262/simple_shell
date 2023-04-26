#include "temp.h"

/**
 * shell_exit - exits the shell
 * @info: potential arguments used to maintain
 * constant function prototype.
 *
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int shell_exit(info_t *info)
{
	int exit = 0;
	int result = -2;

	if (info->argv[1] != NULL) /* If there is an exit arguement */
	{
		exit = _erratoi(info->argv[1]);
		if (exit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		else
		{
			info->err_num = _erratoi(info->argv[1]);
		}
	}
	else
	{
		info->err_num = -1;
	}

	return (result);
}

/**
 * change_dir - changes current directory of the process
 * @info: Structure containing potential arguments used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int change_dir(info_t *info)
{
	char *dir;
	int cd = 0;

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
		{
			/* TODO: handle error */
			return (0);
		}
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			/* TODO: handle error */
			return (0);
		}
	}
	else
	{
		dir = info->argv[1];
	}

	cd = chdir(dir);
	if (cd == -1)
	{
		print_error(info, "can't change directory to ");
		_eputs(dir);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(NULL, 0));
	}

	return (0);
}

/**
 * help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int help(info_t *info)
{
	char **arg_array = info->argv;

	_puts("help call works. Function not yet implemented \n");
	/* Temporarily unused variable workaround */
	(void)arg_array;

	return (0);
}

/**
 * hist_list - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int hist_list(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * onset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int onset_alias(info_t *info, char *str)
{
	char *r = strchr(str, '=');
	int d;

	if (!r)
		return (1);
	char j = *r;
	*r = 0;
	d = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*r = j;
	return (d);
}

/**
 * print_alias - prints alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	if (node == NULL)
		return (1);

	char *equals_pos = strchr(node->str, '=');

	if (equals_pos == NULL)
		return (1);

	size_t key_len = equals_pos - node->str;

	printf("%.*s'", (int) key_len, node->str);
	puts(equals_pos + 1);
	puts("'");

	return (0);
}

/**
 * set_alias - set alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *equals_pos = strchr(str, '=');

	if (equals_pos == NULL)
		return (1);

	char *value_str = equals_pos + 1;

	if (*value_str == '\0')
		return (onset_alias(info, str));

	onset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) != NULL ? 0 : 1);
}

/**
 * alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int alias(info_t *info)
{
	int a;
	char *p;
	list_t *node;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		p = _strchr(info->argv[a], '=');
		if (p)
		{
			set_alias(info, info->argv[a]);
		}
		else
		{
			node = node_starts_with(info->alias, info->argv[a], '=');
			if (node)
			{
				print_alias(node);
			}
		}
	}

	return (0);
}
