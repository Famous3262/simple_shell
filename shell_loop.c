#include "temp.h"

/**
 * hsh - Main shell loop
 * @info: Pointer to the parameter and return info structure
 * @av: Argument vector from main()
 *
 * Return: 0 on success, 1 on error
 */
int hsh(info_t *info, char **av)
{
	ssize_t i = 0;
	int builtin_ret = 0;

	while (i != -1 && builtin_ret != -2)
	{
		clear_info(info);

		if (inter_mode(info))
			_puts("$ ");
		eput_char(BUFFER_FLUSH);

		i = get_input(info);

		if (i != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (inter_mode(info))
			_putchar('\n');

		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);

	if (!inter_mode(info) && info->status)
		exit(info->status);

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info structure
 *
 * Return: -1 if builtin not found,
 *	0 if builtin executed successfully,
 *	1 if builtin found but not successful,
 *	2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int s, built_in_ret = -1;

	 builtin_t builtin[] = {
		 {"exit", shell_exit},
		 {"env", print_env},
		 {"help", help},
		 {"history", hist_list},
		 {"setenv", set_env},
		 {"unsetenv", unset_env},
		 {"cd", change_dir},
		 {"alias", alias},
		 {NULL, NULL}
	};

	for (s = 0; builtin[s].type; s++)
	{
		if (_strcmp(info->argv[0], builtin[s].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtin[s].func(info);
			break;
		}
	}

	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: nothing
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int d, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (d = 0, j = 0; info->arg[d]; d++)
		if (!check_delim(info->arg[d], " \t\n"))
		j++;
	if (!j)
		return;

	path = find_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((inter_mode(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a process to execute command
 * @info: pointer to parameter & return info structure
 *
 * Return: none
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
 * is_cmd - determines if a file is executable
 * @info: pointer to the info structure
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;

	if (!path || stat(path, &st) == -1)
		return (0);

	return ((st.st_mode & S_IFREG) && (st.st_mode & S_IXUSR));
}

/**
 * dup_chars - duplicates characters
 * @pathstr: pointer to the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	char *buf = malloc(stop - start + 1);
	int j = 0;

	for (int s = start; s < stop; s++)
	{
		if (pathstr[s] != ':')
		{
			buf[j++] = pathstr[s];
		}
	}
	buf[j] = 0;
	return (buf);
}

/**
 * find_path - finds this command in the PATH string
 * @info: pointer to the info structure
 * @pathstr: pointer to the PATH string
 * @cmd: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	char *path = NULL;
	int j = 0;
	int curr_pos = 0;

	while (pathstr[j])
	{
		if (!pathstr[j] == ':')
		{
			path = dup_chars(pathstr, curr_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			curr_pos = j + 1;
		}
		j++;
	}

	/* Handle the last path in the PATH string */
	if (curr_pos < j)
	{
		path = dup_chars(pathstr, curr_pos, j);
		if (!*path)
			_strcat(path, cmd);
		else
		{
			_strcat(path, "/");
			_strcat(path, cmd);
		}
		if (is_cmd(info, path))
			return (path);
	}

	return (NULL);
}
