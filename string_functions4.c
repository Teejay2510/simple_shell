/**
 * _strncpy - Copies a string up to 'n' characters.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }
    
    if (i < n)
    {
        j = i;
        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }
    
    return s;
}

/**
 * _strncat - Concatenates two strings, up to 'n' characters from src.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of characters from src to concatenate.
 * Return: A pointer to the concatenated string (dest).
 */
char *_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    while (dest[i] != '\0')
        i++;

    j = 0;
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    if (j < n)
        dest[i] = '\0';

    return s;
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to look for.
 * Return: A pointer to the first occurrence of 'c' in 's', or NULL if not found.
 */
char *_strchr(char *s, char c)
{
    do
    {
        if (*s == c)
            return s;
    }
    while (*s++ != '\0');

    return NULL;
}

