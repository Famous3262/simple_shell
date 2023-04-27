#include "temp.h"

/**
 * input_buf - Buffer chained commands
 * @info: Pointer to the parameter structure
 * @buf: Address of the buffer
 * @len: Address of the length variable
 *
 * Return: Bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t len_p = 0;

	if (!*len)
	{
		/* if nothing left in the buffer, fill it */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

		#if USE_GETLINE
		a = getline(buf, &len_p, stdin);
		#else
		a = _getline(info, buf, &len_p);
		#endif

		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0'; /* remove trailing newline */
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * get_input - Function that gets a line minus the newline
 * @info: Pointer to the parameter structure
 *
 * Return: Bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, s, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
	{
		/* EOF */
		return (-1);
	}


	if (len)
	{
		/* we have commands left in the chain buffer */
		s = i; /* init new iterator to current buffer position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &s, i, len);

		while (s < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &s))
				break;
		}
		s++;
	}

		i = s + 1; /* increment past nulled ';'' */

		if (i >= len)
		{
			/* reached end of buffer? */
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */

		/* else not a chain, pass back buffer from _getline() */
		*buf_p = buf;
		return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - Function that reads a buffer
 * @info: Pointer to the parameter structure
 * @buf: Points to buffer
 * @s: The Size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *s)
{
	ssize_t r = 0;

	if (*s)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);

	if (r >= 0)
		*s = r;
	return (r);
}

/**
 * _getline - Function that gets the next line of input from STDIN
 * @info: Pointer to the parameter structure
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated pointer to buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t n;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (j == len)
		j = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	n = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + n : n + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + j, n - j);
	else
		_strncpy(new_p, buf + j, n - j + 1);

	s += n - j;
	j = n;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Function that blocks ctrl-C
 * @sig_num: Signal number
 *
 * Return: Nothing
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n$ ");
	_putchar(BUF_FLUSH);
}
