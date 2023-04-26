#include "temp.h"

/**
 * inter_mode - returns true if shell is interactive mode
 * @info: points to struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int inter_mode(info_t *info)
{
	int result = 0;

	if (isatty(STDIN_FILENO) && info->readfd <= 2)
	{
		result = 1;
	}
	return (result);
}

/**
 * check_delim - checks if character is a delimiter
 * @c: the char to check
 * @delimiter: the delimiter string
 * Return: 1 if true, 0 if false
 */
int check_delim(char c, char *delimiter)
{
	while (*delimiter != '\0')
	{
		if (*delimiter == c)
			return (1);
		delimiter++;
	}
	return (0);
}

/**
 * check_alphabet - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int check_alphabet(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * s_atoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int s_atoi(char *str)
{
	int r = 0;
	int sign = 1;
	int flag = 0;
	int output = 0;

	while (*str != '\0' && flag != 2)
	{
		if (*str == '-')
			sign *= -1;
		if (*str >= '0' && *str <= '9')
		{
			flag = 1;
			output *= 10;
			output += (*str - '0');
		}
		else if (flag == 1)
			flag = 2;
		str++;
	}

	return (sign * output);
}
