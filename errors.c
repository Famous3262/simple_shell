#include "temp.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	if (str == NULL)
		return;

	for (; *str != '\0'; str++)
	{
		_eputchar(*str);
	}
}

/**
 * _eputchar - function that writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int r;
	static char buf[WRITE_BUF_SIZE];

	/* Check if r is uninitialized */
	if (r == 0)
	{
		/* Initialize static variables here if needed */
		/* e.g., r = 0; buf[0] = '\0'; */
	}

	if (c == BUF_FLUSH || r >= WRITE_BUF_SIZE)
	{
		write(2, buf, r);
		r = 0;
	}
	if (c != BUF_FLUSH)
		buf[r++] = c;

	return (1);
}

/**
 * _putfd - writes the character c to a given file descriptor
 * @c: character to print
 * @fd: file descriptor to write to
 *
 * Return: On success 1.
 *	   On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int r;
	static char buf[WRITE_BUF_SIZE];

	/* Check if r is uninitialized */
	if (r == 0)
	{
		/* Initialize static variables here if needed */
		/* e.g., r = 0; buf[0] = '\0'; */
	}

	if (c == BUF_FLUSH || r >= WRITE_BUF_SIZE)
	{
		write(fd, buf, r);
		r = 0;
	}
	if (c != BUF_FLUSH)
		buf[r++] = c;

	return (1);
}

/**
 * _putsfd - function that prints an input string
 * @str: string to be printed
 * @fd: file descriptor to write to
 *
 * Return: number of chars input
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);

	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}

/**
 * _erratoi - converts a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *	  -1 on error
 */
int _erratoi(char *s)
{
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (; *s != '\0'; s++)
	{
		if (*s >= '0' && *s <= '9')
		{
			result *= 10;
			result += (*s - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}

	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 *
 * Return: nothing
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int n, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
	{
		_abs_ = input;
	}

	current = _abs_;
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (_abs_ / n)
		{
			__putchar('0' + current / n);
			count++;
		}
		current %= n;
	}

	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, similar to itoa
 * @num: number to convert
 * @base: base for the conversion
 * @flags: argument flags controlling the conversion
 *
 * Return: pointer to a string containing the number
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments - replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: nothing
 */
void remove_comments(char *buf)
{
	int j = 0;

	while (buf[j] != '\0')
	{
		if (buf[j] == '#' && (j == 0 || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
		j++;
	}
}
