#include "posh.h"

/**
 * starts_with - check if needle starts with haystack       * @haystack: string to search                              * @needle: the substring to find                           *                                                          * Return: address of next char of haystack or NULL         */
char *starts_with(const char *haystack, const char *needle){                                                                  while (*needle)
                if (*needle++ != *haystack++)                                      return (NULL);                             return ((char *)haystack);                         }

/**
 * _putchar - write the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

