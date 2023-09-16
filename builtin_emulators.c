#include "shell.h"

/**
 * _myexit - Exit the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0 unless there's an error.
 */
int _myexit(info_t *info)
{
    int exit_status = 0;

    if (info->argv[1]) {
        // Attempt to convert the exit argument to an integer
        exit_status = _erratoi(info->argv[1]);

        // Check if the conversion failed
        if (exit_status == -1) {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1; // Error
        }

        // Set the exit status
        info->err_num = exit_status;
    } else {
        info->err_num = -1;
    }

    return 0; // Success
}

/**
 * _mycd - Change the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0 unless there's an error.
 */
int _mycd(info_t *info)
{
    char *new_dir;
    char buffer[1024];

    // Get the current working directory
    char *current_dir = getcwd(buffer, sizeof(buffer));

    if (!current_dir) {
        _puts("Error: Unable to determine current directory.\n");
        return 1; // Error
    }

    if (!info->argv[1]) {
        // No argument provided, change to the home directory
        new_dir = _getenv(info, "HOME=");
        if (!new_dir) {
            new_dir = _getenv(info, "PWD=");
        }

        if (!new_dir) {
            new_dir = "/";
        }
    } else if (_strcmp(info->argv[1], "-") == 0) {
        // Change to the previous directory (OLDPWD)
        new_dir = _getenv(info, "OLDPWD=");
        if (!new_dir) {
            _puts(current_dir);
            _putchar('\n');
            return 0; // Success
        }
    } else {
        // Change to the specified directory
        new_dir = info->argv[1];
    }

    if (chdir(new_dir) == -1) {
        print_error(info, "Error: can't cd to ");
        _eputs(new_dir);
        _eputchar('\n');
        return 1; // Error
    }

    // Update environment variables
    _setenv(info, "OLDPWD", current_dir);
    _setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));

    return 0; // Success
}

/**
 * _myhelp - Display help message.
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int _myhelp(info_t *info)
{
    // Print a help message
    _puts("Shell Help: This shell supports the following built-in commands:\n");
    _puts("1. exit [status]: Exit the shell with an optional status code.\n");
    _puts("2. cd [directory]: Change the current working directory.\n");
    _puts("3. help: Display this help message.\n");

    return 0; // Success
}

