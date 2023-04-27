#include "temp.h"

/**
 * get_history_file - Function that gets the history file
 * @info: Pointer to the parameter structure
 *
 * Return: Allocated string containing the  history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *f;

	f = _getenv(info, "HOME=");
	if (!f)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(f) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, f);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Function that creates a file
 * @info: Pointer to the parameter structure
 *
 * Return: 1 on success, -1 otherwise
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Function that reads history from file
 * @info: Pointer to the parameter structure
 *
 * Return: Histcount on success, else 0
 */
int read_history(info_t *info)
{
	int n, fame = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (n = 0; n < fsize; n++)
		if (buf[n] == '\n')
		{
			buf[n] = 0;
			build_history_list(info, buf + fame, linecount++);
			fame = n + 1;
		}
	if (fame != n)
		build_history_list(info, buf + fame, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Function that adds entry to a history linked list
 * @info: Structure containing potential arguments
 * @buf: Pointer to the buffer
 * @linecount: The history linecount, histcount
 *
 * Return: 0 on success
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Function that renumbers the history linked list
 *		after changes are made
 * @info: Pointer to the structure containing potential arguments
 *
 * Return: New histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (info->histcount = n);
}
