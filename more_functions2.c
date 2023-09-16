#include "shell.h"

/**
 * interactive - Checks if the shell is in interactive mode.
 * @info: Pointer to the info_t structure.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int is_delim(char c, char *delim)
{
    while (*delim)
    {
        if (*delim == c)
            return 1;
        delim++;
    }
    return 0;
}

/**
 * _isalpha - Checks for an alphabetic character.
 * @c: The character to check.
 *
 * Return: 1 if 'c' is alphabetic, 0 otherwise.
 */
int _isalpha(int c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number or 0 if no numbers in the string.
 */
int _atoi(char *s)
{
    int i = 0;
    int sign = 1;
    int output = 0;

    while (s[i] == ' ')
    {
        i++;
    }

    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }

    while (s[i] >= '0' && s[i] <= '9')
    {
        output = output * 10 + (s[i] - '0');
        i++;
    }

    return (sign * output);
}

