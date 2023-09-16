#include "shell.h"

list_t *add_node(list_t **head, const char *str, int num) {
    if (!head)
        return NULL;

    list_t *new_head = malloc(sizeof(list_t));

    if (!new_head)
        return NULL;

    memset(new_head, 0, sizeof(list_t));
    new_head->num = num;

    if (str) {
        new_head->str = strdup(str);

        if (!new_head->str) {
            free(new_head);
            return NULL;
        }
    }

    new_head->next = *head;
    *head = new_head;
    return new_head;
}

list_t *add_node_end(list_t **head, const char *str, int num) {
    if (!head)
        return NULL;

    list_t *new_node = malloc(sizeof(list_t));

    if (!new_node)
        return NULL;

    memset(new_node, 0, sizeof(list_t));
    new_node->num = num;

    if (str) {
        new_node->str = strdup(str);

        if (!new_node->str) {
            free(new_node);
            return NULL;
        }
    }

    if (*head) {
        list_t *node = *head;

        while (node->next)
            node = node->next;

        node->next = new_node;
    } else {
        *head = new_node;
    }

    return new_node;
}

size_t print_list_str(const list_t *h) {
    size_t i = 0;

    while (h) {
        printf("%s\n", h->str ? h->str : "(nil)");
        h = h->next;
        i++;
    }

    return i;
}

int delete_node_at_index(list_t **head, unsigned int index) {
    if (!head || !*head)
        return 0;

    if (!index) {
        list_t *node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    list_t *node = *head;
    list_t *prev_node = NULL;
    unsigned int i = 0;

    while (node) {
        if (i == index) {
            if (prev_node)
                prev_node->next = node->next;
            else
                *head = node->next;

            free(node->str);
            free(node);
            return 1;
        }

        i++;
        prev_node = node;
        node = node->next;
    }

    return 0;
}

void free_list(list_t **head_ptr) {
    if (!head_ptr || !*head_ptr)
        return;

    list_t *node = *head_ptr;

    while (node) {
        list_t *next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }

    *head_ptr = NULL;
}

