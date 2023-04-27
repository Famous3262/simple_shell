#include "temp.h"

/**
 * _memset - Function that fills memory with a constant byte
 * @s: Pointer to the memory area
 * @b: The byte to fill *s with
 * @n: Amount of bytes to be filled
 *
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	char *start = s;

	while (n-- > 0)
		*s++ = b;

	return (start);
}

/**
 * ffree - Function that frees a string of strings
 * @pp: The string of strings
 */
void ffree(char **pp)
{
	if (pp == NULL)
		return;

	char **start = pp;

	while (*pp != NULL)
	{
		free(*pp);
		pp++;
	}

	free(start);
}

/**
 * _realloc - Function that reallocates a block of memory
 * @ptr: Pointer to previous malloc'ated block
 * @old_size: Byte size of previous block
 * @new_size: Byte size of new block
 *
 * Return: Pointer to the reallocated memory block,
 *	or NULL on failure
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size <= old_size)
		return (ptr);

	char *new_ptr = malloc(new_size);

	if (!new_ptr)
		return (NULL);


	for (unsigned int s = 0; s < old_size; s++)
		new_ptr[s] = ((char *)ptr)[s];
	free(ptr);

	return (new_ptr);
}
