#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(const char *path)
{
    struct stat st;

    if (!path || stat(path, &st) != 0)
        return 0;

    return S_ISREG(st.st_mode);
}

/**
 * find_path - finds the cmd in the PATH string
 * @info: the info struct
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, const char *cmd)
{
    char *pathstr = _getenv(info, "PATH=");
    if (!pathstr || !cmd)
        return NULL;

    char *path = NULL;
    char *token = strtok(pathstr, ":");
    while (token != NULL)
    {
        path = malloc(strlen(token) + strlen(cmd) + 2); // +2 for '/' and null terminator
        if (path == NULL)
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        strcpy(path, token);
        strcat(path, "/");
        strcat(path, cmd);

        if (is_cmd(path))
            return path;

        free(path);
        token = strtok(NULL, ":");
    }

    return NULL;
}

