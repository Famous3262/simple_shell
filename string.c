#include "temp.h"

/**
 * _strlen - Function that returns the length of a string
 * @s: Pointer to the string length
 *
 * Return: Int length of the string
 */
int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strcmp - Function that performs
 *	lexicogarphic comparison of two strings.
 * @s1: Pointer to the first string
 * @s2: Pointer to the second string
 *
 * Return: negative if s1 < s2,
 *	positive if s1 > s2,
 *	zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else if (*s1 < *s2)
		return (-1);
	else
		return (1);
}

/**
 * starts_with -Function that checks if needle starts with haystack
 * @haystack: Pointer to string to search
 * @needle: Pointer to the substring to find
 *
 * Return: Address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle != '\0')
	{
		if (*needle != *haystack)
			return (NULL);
		needle++;
		haystack++;
	}
	return ((char *)haystack);
}

/**
 * _strcat - Function that concatenates two strings
 * @dest: Pointer to the destination buffer
 * @src: Pointer to the source buffer
 *
 * Return: Pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *d = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (d);
}

/**
 * _strcpy - Function that copies a string
 * @dest: Pointer to the destination string
 * @src: Pointer to the source string
 *
 * Return: Pointer to destination string
 */
char *_strcpy(char *dest, char *src)
{
	int d = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[d])
	{
		dest[d] = src[d];
		d++;
	}
	dest[d] = 0;
	return (dest);
}

/**
 * _strdup - Function that duplicates a string
 * @str: Pointer to the string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	for (len++; len--;)
		result[len] = *--str;
	return (result);
}

/**
 * _puts - Function that prints an input string
 * @str: Pointer to string to be printed
 *
 * Return: None
 */
void _puts(char *str)
{
	int k = 0;

	if (!str)
		return;
	while (str[k] != '\0')
	{
		_putchar(str[k]);
		k++;
	}
}

/**
 * _putchar - Function that writes the character c to stdout
 * @c: The character to be printed
 *
 * Return: 1 on success
 *	-1 On error, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
