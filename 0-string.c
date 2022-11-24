#include "posh.h"

/**
 * _strlen - return the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - perform lexicogarphic comparison of two strings
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**                                                         * _strcpy - copy a string
 * @dest: the destination                                   * @src: the source                                         *                                                          * Return: pointer to destination                           */                                                        char *_strcpy(char *dest, char *src)
{                                                                  int i = 0;
                                                                   if (dest == src || src == 0)                                       return (dest);
        while (src[i])
        {                                                                  dest[i] = src[i];
                i++;                                               }
        dest[i] = 0;                                               return (dest);                                     }
                                                           /**
 * _strdup - duplicate a string
 * @str: the string to duplicate                            *                                                          * Return: pointer to the duplicated string                 */
char *_strdup(const char *str)                             {
        int length = 0;
        char *ret;

        if (str == NULL)
                return (NULL);
        while (*str++)
                length++;
        ret = malloc(sizeof(char) * (length + 1));
        if (!ret)
                return (NULL);
        for (length++; length--;)
                ret[length] = *--str;
        return (ret);
}

/**
 * _strcat - concatenate two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

