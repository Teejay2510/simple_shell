#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing the history file
 */
char *get_history_file(info_t *info)
{
    char *home_dir = _getenv(info, "HOME=");
    if (!home_dir)
        return NULL;

    char *history_file;
    if (asprintf(&history_file, "%s/%s", home_dir, HIST_FILE) == -1)
    {
        free(home_dir);
        return NULL;
    }

    free(home_dir);
    return history_file;
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return -1;

    FILE *file = fopen(filename, "w");
    free(filename);
    if (!file)
        return -1;

    list_t *node = info->history;
    while (node)
    {
        fprintf(file, "%s\n", node->str);
        node = node->next;
    }

    fclose(file);
    return 1;
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return 0;

    FILE *file = fopen(filename, "r");
    free(filename);
    if (!file)
        return 0;

    char *line = NULL;
    size_t line_length = 0;
    ssize_t read;

    while ((read = getline(&line, &line_length, file)) != -1)
    {
        if (read > 0 && line[read - 1] == '\n')
            line[read - 1] = '\0';
        build_history_list(info, line, info->histcount++);
    }

    free(line);
    fclose(file);

    while (info->histcount >= HIST_MAX)
    {
        delete_node_at_index(&(info->history), 0);
        info->histcount--;
    }

    renumber_history(info);
    return info->histcount;
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    add_node_end(&(info->history), buf, linecount);
    return 0;
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;
    while (node)
    {
        node->num = i++;
        node = node->next;
    }
    return (info->histcount = i);
}

