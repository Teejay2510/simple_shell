#include "shell.h"

/**
 * Print the current environment variables.
 * @param info: Structure containing potential arguments.
 * @return Always 0.
 */
int shell_env(info_t *info) {
    print_env_list(info->env);
    return 0;
}

/**
 * Get the value of an environment variable.
 * @param info: Structure containing potential arguments.
 * @param name: Environment variable name.
 * @return The value of the environment variable or NULL if not found.
 */
char *_getenv(info_t *info, const char *name) {
    list_t *node = info->env;
    char *value;

    while (node) {
        value = starts_with(node->str, name);
        if (value && *value == '=') {
            return value + 1; // Move past the '=' character
        }
        node = node->next;
    }

    return NULL;
}

/**
 * Set or update an environment variable.
 * @param info: Structure containing potential arguments.
 * @return 0 on success, 1 on error.
 */
int shell_setenv(info_t *info) {
    if (info->argc != 3) {
        _eputs("Usage: setenv VARIABLE VALUE\n");
        return 1;
    }

    int result = set_env_variable(&(info->env), info->argv[1], info->argv[2]);
    if (result != 0) {
        _eputs("Failed to set environment variable.\n");
    }
    
    return result;
}

/**
 * Unset one or more environment variables.
 * @param info: Structure containing potential arguments.
 * @return 0 on success, 1 on error.
 */
int shell_unsetenv(info_t *info) {
    if (info->argc == 1) {
        _eputs("Usage: unsetenv VARIABLE [VARIABLE ...]\n");
        return 1;
    }

    int result = 0;
    for (int i = 1; i < info->argc; i++) {
        if (unset_env_variable(&(info->env), info->argv[i]) != 0) {
            _eputs("Failed to unset environment variable: ");
            _eputs(info->argv[i]);
            _eputs("\n");
            result = 1;
        }
    }

    return result;
}

/**
 * Populate the environment variables linked list from the global environ variable.
 * @param info: Structure containing potential arguments.
 * @return Always 0.
 */
int populate_env_list(info_t *info) {
    for (char **env = environ; *env != NULL; env++) {
        add_env_node(&(info->env), *env);
    }
    return 0;
}

