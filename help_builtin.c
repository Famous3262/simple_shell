#include "temp.h"

/**
 * _myexit - fumction exits the shell
 * @info: potential arguments used to maintain
 * constant function prototype.
 *
 * Return: exits with a given exit status
 *	 (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
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
 * _mycd - function changes current directory of the process
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int _mycd(info_t *info)
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
 *_ myhelp - function changes the current directory of the process
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array = info->argv;

	_puts("help call works. Function not yet implemented \n");
	/* Temporarily unused variable workaround */
	(void)arg_array;

	return (0);
}

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - function sets alias to string
 * @info: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, cee;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	cee = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = cee;
	return (ret);

}

/**
 * print_alias - function prints alias string
 * @node: pointer to the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *c = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (c = node->str; c <= p; c++)
		_putchar(*c);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * set_alias - function that sets alias to string
 * @info: pointer to the parameter structure
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 *_myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
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
