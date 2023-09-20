#include "shell.h"

/**
 * Write a string to the specified file descriptor.
 * @param fd: The file descriptor to write to.
 * @param str: The string to be printed.
 * @return: The number of characters written, or -1 on error.
 */
int write_to_fd(int fd, char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    while (*str) {
        int result = write(fd, str, 1);
        if (result == -1) {
            return -1;  // Error occurred
        }
        count++;
        str++;
    }
    return count;
}

/**
 * Write a string to stderr.
 * @param str: The string to be printed.
 */
void _eputs(char *str) {
    int count = write_to_fd(STDERR_FILENO, str);
    if (count == -1) {
        perror("Error writing to stderr");
    }
}

/**
 * Write a character to stderr.
 * @param c: The character to print.
 * @return: On success, 1; on error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c) {
    int result = write(STDERR_FILENO, &c, 1);
    if (result == -1) {
        perror("Error writing to stderr");
        return -1;
    }
    return 1;
}

/**
 * Write a character to the specified file descriptor.
 * @param c: The character to print.
 * @param fd: The file descriptor to write to.
 * @return: On success, 1; on error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd) {
    int result = write(fd, &c, 1);
    if (result == -1) {
        perror("Error writing to file descriptor");
        return -1;
    }
    return 1;
}

/**
 * Write a string to the specified file descriptor.
 * @param str: The string to be printed.
 * @param fd: The file descriptor to write to.
 * @return: The number of characters written, or -1 on error.
 */
int _putsfd(char *str, int fd) {
    return write_to_fd(fd, str);
}

