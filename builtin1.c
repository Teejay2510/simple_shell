#include "shell.h"

/**
 * Display command history with line numbers.
 * @param info: Structure containing potential arguments.
 * @return Always 0.
 */
int shell_history(info_t *info) {
    print_command_history(info->history);
    return 0;
}

/**
 * Unset an alias.
 * @param info: Parameter struct.
 * @param str: The alias string.
 * @return 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str) {
    char *equals_sign, tmp;
    int result;

    equals_sign = _strchr(str, '=');
    if (!equals_sign)
        return 1;

    tmp = *equals_sign;
    *equals_sign = '\0';

    result = delete_alias(&(info->alias), str);

    *equals_sign = tmp;

    return result;
}

/**
 * Set or update an alias.
 * @param info: Parameter struct.
 * @param str: The alias string.
 * @return 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str) {
    char *equals_sign;

    equals_sign = _strchr(str, '=');
    if (!equals_sign)
        return 1;

    if (*(equals_sign + 1) == '\0')
        return unset_alias(info, str);

    unset_alias(info, str);
    return add_alias(&(info->alias), str);
}

/**
 * Print an alias.
 * @param node: The alias node.
 * @return 0 on success, 1 on error.
 */
int print_alias(list_t *node) {
    char *equals_sign, *alias_name;

    if (node) {
        equals_sign = _strchr(node->str, '=');
        if (equals_sign) {
            alias_name = node->str;
            while (alias_name <= equals_sign)
                _putchar(*alias_name++);

            _puts("'");
            _puts(equals_sign + 1);
            _puts("'\n");
            return 0;
        }
    }
    return 1;
}

/**
 * Manage aliases, mimicking the alias builtin.
 * @param info: Structure containing potential arguments.
 * @return Always 0.
 */
int shell_alias(info_t *info) {
    int i;
    char *equals_sign;
    list_t *node;

    if (info->argc == 1) {
        node = info->alias;
        while (node) {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++) {
        equals_sign = _strchr(info->argv[i], '=');
        if (equals_sign)
            set_alias(info, info->argv[i]);
        else
            print_alias(find_alias(info->alias, info->argv[i]));
    }

    return 0;
}

