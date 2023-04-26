#include "temp.h"

/**
 * put_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void put_string(char *str)
{
	if (str == NULL)
		return;

	for (; *str != '\0'; str++)
	{
		eput_char(*str);
	}
}

/**
 * eput_char - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int eput_char(char c)
{
	static int r;
	static char buf[WRITE_BUFFER_SIZE];

	/* Check if r is uninitialized */
	if (r == 0)
	{
		/* Initialize static variables here if needed */
		/* e.g., r = 0; buf[0] = '\0'; */
	}

	if (c == BUFFER_FLUSH || r >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, r);
		r = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[r++] = c;

	return (1);
}

/**
 * put_file_desc - writes the character c to a given file descriptor
 * @c: character to print
 * @fd: file descriptor to write to
 *
 * Return: On success 1.
 *	   On error, -1 is returned, and errno is set appropriately.
 */
int put_file_desc(char c, int fd)
{
	static int r;
	static char buf[WRITE_BUFFER_SIZE];

	/* Check if r is uninitialized */
	if (r == 0)
	{
		/* Initialize static variables here if needed */
		/* e.g., r = 0; buf[0] = '\0'; */
	}

	if (c == BUFFER_FLUSH || r >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, r);
		r = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[r++] = c;

	return (1);
}

/**
 * str_fd - prints an input string
 * @str: string to be printed
 * @fd: file descriptor to write to
 *
 * Return: number of chars input
 */
int str_fd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);

	while (*str)
	{
		a += put_file_desc(*str++, fd);
	}
	return (a);
}

/**
 * erratoi - converts a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *	  -1 on error
 */
int erratoi(char *s)
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
	put_string(info->fname);
	put_string(": ");
	print_dec(info->line_count, STDERR_FILENO);
	put_string(": ");
	put_string(info->argv[0]);
	put_string(": ");
	put_string(estr);
}

/**
 * print_dec - prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int n, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = eput_char;

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
 * convert_num - converter function, similar to itoa
 * @num: number to convert
 * @base: base for the conversion
 * @flags: argument flags controlling the conversion
 *
 * Return: pointer to a string containing the number
 */
char *convert_num(long int num, int base, int flags)
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
 * rem_comments - replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: nothing
 */
void rem_comments(char *buf)
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
