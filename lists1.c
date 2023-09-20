#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * list_len - determines the length of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t list_len(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }

    return i;
}

/**
 * list_to_strings - returns an array of strings from the list
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
    size_t list_size = list_len(head);
    char **strs = malloc(sizeof(char *) * (list_size + 1));

    if (!strs)
        return NULL;

    size_t i = 0;
    while (head)
    {
        strs[i] = strdup(head->str ? head->str : "");
        if (!strs[i])
        {
            for (size_t j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return NULL;
        }

        head = head->next;
        i++;
    }

    strs[i] = NULL;
    return strs;
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        printf("%zu: %s\n", h->num, h->str ? h->str : "(nil)");
        h = h->next;
        i++;
    }

    return i;
}

/**
 * node_starts_with - returns the node whose string starts with a prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *node_starts_with(list_t *node, const char *prefix, char c)
{
    while (node)
    {
        if (starts_with(node->str, prefix) && (c == -1 || *(node->str + strlen(prefix)) == c))
            return node;

        node = node->next;
    }

    return NULL;
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1 if not found
 */
ssize_t get_node_index(const list_t *head, const list_t *node)
{
    size_t i = 0;

    while (head)
    {
        if (head == node)
            return i;
        head = head->next;
        i++;
    }

    return -1;
}

