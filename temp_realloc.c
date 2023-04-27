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
	char **s = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(s);

}

/**
 * _realloc - Function that reallocates a memory block
 * @ptr: Pointer to previous malloc'ated block
 * @old_size: Byte size of previous block
 * @new_size: Byte size of new block
 *
 * Return: Pointer to the reallocated memory block,
 *	or NULL on failure
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *m;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	m = malloc(new_size);
	if (!m)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		m[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (m);
}
