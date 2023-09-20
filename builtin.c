#include "shell.h"

/**
 * Exit the shell with a given exit status.
 * @param info: Structure containing potential arguments.
 * @return -2 if an exit status is provided, 0 otherwise.
 */
int shell_exit(info_t *info) {
    if (info->argv[1]) {
        int exit_status = _strtoi(info->argv[1]);
        if (exit_status == -1) {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = exit_status;
        return -2;
    }
    info->err_num = -1;
    return -2;
}

/**
 * Change the current directory of the process.
 * @param info: Structure containing potential arguments.
 * @return 0 on success, 1 on failure.
 */
int shell_cd(info_t *info) {
    char *dir;
    char buffer[1024];

    char *current_dir = getcwd(buffer, 1024);
    if (!current_dir) {
        _puts("Error: Unable to get current working directory.\n");
        return 1;
    }

    if (!info->argv[1]) {
        dir = _getenv(info, "HOME=");
        if (!dir)
            dir = _getenv(info, "PWD=");
    } else if (_strcmp(info->argv[1], "-") == 0) {
        dir = _getenv(info, "OLDPWD=");
        if (!dir) {
            _puts(current_dir);
            _putchar('\n');
            return 1;
        }
    } else {
        dir = info->argv[1];
    }

    if (chdir(dir) == -1) {
        print_error(info, "can't cd to ");
        _eputs(dir);
        _eputchar('\n');
        return 1;
    }

    _setenv(info, "OLDPWD", _getenv(info, "PWD="));
    _setenv(info, "PWD", getcwd(buffer, 1024));
    return 0;
}

/**
 * Display help message.
 * @param info: Structure containing potential arguments.
 * @return 0 always.
 */
int shell_help(info_t *info) {
    _puts("Help: This is a basic shell. Commands available: exit, cd, help\n");
    return 0;
}

