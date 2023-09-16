#include "shell.h"

/**
 * get_environ - Returns a copy of the environment variables as a string array.
 * @info: Structure containing potential arguments.
 *
 * Return: A copy of the environment variables (char **) or NULL on error.
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: Name of the environment variable to remove.
 *
 * Return: 1 if a variable is deleted, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t index = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), index);
            index = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        index++;
    }

    return info->env_changed;
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: Name of the environment variable.
 * @value: Value of the environment variable.
 *
 * Return: 0 on success, 1 on error.
 */
int _setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return 1;

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return 1;

    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);

    node = info->env;
    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }

    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return 0;
}

