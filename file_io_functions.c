#include "shell.h"

/**
 * get_history_file - Get the path to the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file path or NULL on failure.
 */
char *get_history_file(info_t *info)
{
    char *home_dir = _getenv(info, "HOME=");
    if (!home_dir)
        return NULL;

    char *filename = malloc(strlen(home_dir) + strlen(HIST_FILE) + 2);
    if (!filename)
        return NULL;

    snprintf(filename, strlen(home_dir) + strlen(HIST_FILE) + 2, "%s/%s", home_dir, HIST_FILE);
    return filename;
}

/**
 * write_history - Write the shell history to a file.
 * @info: Parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return -1;

    int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return -1;

    list_t *node;
    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }

    _putfd(BUF_FLUSH, fd);
    close(fd);
    return 1;
}

/**
 * read_history - Read shell history from a file.
 * @info: Parameter struct.
 *
 * Return: The history count on success, 0 on failure.
 */
int read_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return 0;

    int fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    struct stat st;
    if (fstat(fd, &st) == -1 || st.st_size < 2)
    {
        close(fd);
        return 0;
    }

    char *buf = malloc(st.st_size + 1);
    if (!buf)
    {
        close(fd);
        return 0;
    }

    ssize_t rdlen = read(fd, buf, st.st_size);
    close(fd);

    if (rdlen <= 0)
    {
        free(buf);
        return 0;
    }

    buf[st.st_size] = '\0';

    int linecount = 0;
    int last = 0;
    int i;

    for (i = 0; i < st.st_size; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        build_history_list(info, buf + last, linecount++);

    free(buf);

    info->histcount = linecount;

    while (info->histcount >= HIST_MAX)
    {
        delete_node_at_index(&(info->history), 0);
        info->histcount--;
    }

    renumber_history(info);

    return info->histcount;
}

/**
 * build_history_list - Add an entry to the history linked list.
 * @info: Parameter struct.
 * @buf: Buffer containing the history entry.
 * @linecount: Line count, histcount.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    add_node_end(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumber_history - Renumber the history linked list after changes.
 * @info: Parameter struct.
 *
 * Return: The new histcount.
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

