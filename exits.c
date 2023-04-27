#include "temp.h"

/**
 **_strncpy - Function that copies a string
 *@dest: Destination string to be copied to
 *@src: Source string
 *@n: Amount of characters to be copied
 *
 *Return: The concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j, k;
	char *d = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		k = j;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (d);
}

/**
 **_strncat - Concatenates two strings
 *@dest: Pointer to the first string
 *@src: Points to the second string
 *@n: Number of bytes to be used
 *Return: The concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	char *s = dest;
	int i = 0;
	int k = 0;

	while (dest[i] != '\0')
		i++;
	while (src[k] != '\0' && k < n)
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	if (k < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - Locates a character in a string
 *@s: Pointer to the string to be parsed
 *@c: Character to look for
 *Return: A pointer to the memory area s,
 *	or NULL if the character is not found
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}

	return (NULL);
}
