#include "shell.h"
#include <stddef.h> // for NULL
#include <string.h> // for strlen

/**
 * Copy a string with a maximum length.
 * @param dest: The destination string to be copied to.
 * @param src: The source string.
 * @param n: The maximum number of characters to be copied.
 * @return: The concatenated string.
 */
char *_strncpy(char *dest, const char *src, size_t n) {
    char *s = dest;
    size_t i = 0;

    while (i < n - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    while (i < n) {
        dest[i] = '\0';
        i++;
    }

    return s;
}

/**
 * Concatenate two strings with a maximum length.
 * @param dest: The destination string.
 * @param src: The source string.
 * @param n: The maximum number of characters to be used.
 * @return: The concatenated string.
 */
char *_strncat(char *dest, const char *src, size_t n) {
    char *s = dest;
    size_t i = 0;
    size_t dest_len = strlen(dest);

    while (i < n - 1 && src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }

    dest[dest_len + i] = '\0';

    return s;
}

/**
 * Locate a character in a string.
 * @param s: The string to be parsed.
 * @param c: The character to look for.
 * @return: A pointer to the first occurrence of the character in the string or NULL if not found.
 */
char *_strchr(const char *s, int c) {
    do {
        if (*s == (char)c) {
            return (char *)s;
        }
    } while (*s++ != '\0');

    return NULL;
}

