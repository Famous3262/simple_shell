#include "temp.h"

/**
 * **strtow - Function splits a string into words
 *		Repeated delimiters are ignored
 * @str: Input string
 * @d: Pointer to the delimeter string
 *
 * Return: A pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, n, k, r, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, n = 0; n < numwords; n++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[n] = malloc((k + 1) * sizeof(char));
		if (!s[n])
		{
			for (k = 0; k < n; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (r = 0; r < k; r++)
			s[n][r] = str[i++];
		s[n][r] = 0;
	}
	s[n] = NULL;
	return (s);
}

/**
 * **strtow2 - Function that splits a string into words
 * @str: Pointer to the input string
 * @d: The delimeter string
 *
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, r, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (r = 0; r < k; r++)
			s[j][r] = str[i++];
		s[j][r] = 0;
	}
	s[j] = NULL;
	return (s);
}
