#include "temp.h"

/**
 * clear_info - Function that initializes info_t structure
 * @info: The structure address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Function that initializes info_t structure
 * @info: Address of the structure
 * @av: Argument vector
 */
void set_info(info_t *info, char **av)
{
	int j = 0;

	info->fname = av[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");

		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);

			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		for (j = 0; info->argv && info->argv[j]; j++)
			;

		info->argc = j;

		rep_alias(info);
		rep_vars(info);
	}
}

/**
 * free_info - Function that frees info_t structure fields
 * @info: Pointer to structure address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFER_FLUSH);
	}
}
