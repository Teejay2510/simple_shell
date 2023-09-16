#include "shell.h"

/**
 * _myhistory - Display the command history.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return 0; // Success
}

/**
 * unset_alias - Unset an alias.
 * @info: Parameter struct.
 * @str: The alias string.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *equal_sign, saved_char;
    int ret;

    equal_sign = _strchr(str, '=');
    if (!equal_sign)
        return 1; // Error

    saved_char = *equal_sign;
    *equal_sign = '\0';

    ret = delete_node_at_index(&(info->alias), get_node_index(info->alias, str));

    *equal_sign = saved_char;
    return ret;
}

/**
 * set_alias - Set an alias.
 * @info: Parameter struct.
 * @str: The alias string.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *equal_sign;

    equal_sign = _strchr(str, '=');
    if (!equal_sign)
        return 1; // Error

    *equal_sign = '\0';
    unset_alias(info, str);

    return (add_node_end(&(info->alias), str, 0) == NULL) ? 0 : 1;
}

/**
 * print_alias - Print an alias.
 * @node: The alias node.
 *
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    if (node) {
        char *equal_sign = _strchr(node->str, '=');

        if (equal_sign) {
            *equal_sign = '\0';
            _printf("%s='%s'\n", node->str, equal_sign + 1);
            *equal_sign = '=';
            return 0; // Success
        }
    }
    return 1; // Error
}

/**
 * _myalias - Display or set aliases.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
    int i;
    char *equal_sign, *alias_name;

    if (info->argc == 1) {
        // Print all defined aliases
        list_t *node = info->alias;
        while (node) {
            print_alias(node);
            node = node->next;
        }
    } else {
        for (i = 1; info->argv[i]; i++) {
            equal_sign = _strchr(info->argv[i], '=');
            if (equal_sign) {
                // Set or update alias
                set_alias(info, info->argv[i]);
            } else {
                // Print alias
                alias_name = info->argv[i];
                print_alias(node_starts_with(info->alias, alias_name, '='));
            }
        }
    }

    return 0; // Success
}

