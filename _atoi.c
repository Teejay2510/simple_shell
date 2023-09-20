#include "shell.h"

/**
 * Checks if the shell is running in interactive mode.
 * @param info: A pointer to the info_t struct.
 * @return 1 if interactive mode, 0 otherwise.
 */
int is_interactive(info_t *info) {
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * Checks if a character is a delimiter.
 * @param c: The character to check.
 * @param delim: The delimiter string.
 * @return 1 if true, 0 if false.
 */
int is_delimiter(char c, const char *delim) {
    while (*delim) {
        if (*delim == c) {
            return 1;
        }
        delim++;
    }
    return 0;
}

/**
 * Checks if a character is alphabetic.
 * @param c: The character to check.
 * @return 1 if c is alphabetic, 0 otherwise.
 */
int is_alpha(int c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * Converts a string to an integer.
 * @param s: The string to be converted.
 * @return 0 if no numbers in string, converted number otherwise.
 */
int string_to_int(const char *s) {
    int i = 0;
    int sign = 1;
    int flag = 0;
    unsigned int result = 0;

    while (s[i] != '\0' && flag != 2) {
        if (s[i] == '-') {
            sign *= -1;
        }

        if (s[i] >= '0' && s[i] <= '9') {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
        i++;
    }

    return (sign == -1) ? -result : result;
}

