#include "shell.h"
#include <limits.h> // for INT_MAX and INT_MIN

/**
 * Convert a string to an integer with error handling.
 * @param s: The string to be converted.
 * @return: The converted number if successful, -1 on error.
 */
int _erratoi(char *s) {
    if (!s || (*s != '-' && *s != '+' && (*s < '0' || *s > '9')))
        return -1;

    char *endptr;
    long int result = strtol(s, &endptr, 10);

    if (*endptr != '\0' && *endptr != '\n')
        return -1; // Invalid characters in the string

    if (result > INT_MAX || result < INT_MIN)
        return -1; // Overflow or underflow

    return (int)result;
}

/**
 * Print an error message.
 * @param info: The parameter and return info struct.
 * @param estr: String containing the specified error type.
 */
void print_error(info_t *info, char *estr) {
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * Print a decimal (integer) number (base 10).
 * @param input: The input number.
 * @param fd: The file descriptor to write to.
 * @return: Number of characters printed.
 */
int print_d(int input, int fd) {
    int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
    int count = 0;
    long int _abs_ = (input < 0) ? -(long int)input : (long int)input;
    long int current = _abs_;

    if (input < 0) {
        __putchar('-');
        count++;
    }

    for (long int i = 1000000000; i > 1; i /= 10) {
        if (current / i) {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }

    __putchar('0' + current);
    count++;

    return count;
}

/**
 * Convert a number to a string with a given base and flags.
 * @param num: The number.
 * @param base: The base.
 * @param flags: Argument flags.
 * @return: The converted string.
 */
char *convert_number(long int num, int base, int flags) {
    static char buffer[50];
    char sign = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? '-' : 0;
    char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    char *ptr = &buffer[49];

    *ptr = '\0';

    unsigned long n = (num < 0) ? -num : num;
    do {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign) {
        *--ptr = sign;
    }

    return ptr;
}

/**
 * Replace the first instance of '#' with '\0'.
 * @param buf: Address of the string to modify.
 */
void remove_comments(char *buf) {
    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' ')) {
            buf[i] = '\0';
            break;
        }
    }
}

