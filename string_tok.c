#include "temp.h"

/**
 * **strtow - Function splits a string into words
 *		Repeat delimiters are ignored
 * @str: Input string
 * @d: Pointer to the delimeter string
 *
 * Return: A pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, r, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!chain_delim(info_t, &str[i], NULL) &&
				(chain_delim(info, &str[i + 1], NULL) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (chain_delim(info, &str[i], NULL))
			i++;
		k = 0;
		while (!chain_delim(info, &str[i + k], NULL) && str[i + k])
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
