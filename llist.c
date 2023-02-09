#include "llist.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void llist_insert_head(struct node **head, struct node *n) {
    n->next = *head;
    *head = n;
}

struct node *llist_delete_head(struct node **head) {
    if (*head == NULL) {
        return NULL;
    } else {
        struct node *return_node = *head;
        *head = (*head)->next;
        return return_node;
    }
};

void llist_insert_tail(struct node **head, struct node *n) {
    struct node *current_node = *head;

    if (current_node == NULL) {
        *head = n;
        return;
    }
    
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }
    current_node->next = n;
};

void llist_print(struct node *head) {
    if (head == NULL) { 
        printf("[empty]");
    }

    struct node *current_node = head;
    while (current_node != NULL) {
        printf("%d", current_node->value);
        if (current_node->next != NULL) {
            printf(" -> ");
        }
        current_node = current_node->next;
    }

    printf("\n");
};

void llist_free(struct node **head) {
    struct node *current_node = *head;
    struct node *next_node = current_node;
    if (current_node == NULL) {
        return;
    }

    while (next_node != NULL) {
        next_node = current_node->next;
        node_free(current_node);        // current node doesnt change, need to access after freeing
        current_node = next_node;
    }
    *head = NULL;
};

struct node *node_alloc(int value) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
};

void node_free(struct node *n) {
    free(n);
};

int main(int argc, char **argv) {
    struct node *head = NULL;

    for (int i=1; i < argc;) {
        if ((strcmp(argv[i], "ih")) == 0) {
            struct node *new_node = node_alloc(atoi(argv[i+1]));
            llist_insert_head(&head, new_node);
            i += 2;
        }
        else if ((strcmp(argv[i], "it")) == 0) {
            struct node *new_node = node_alloc(atoi(argv[i+1]));
            llist_insert_tail(&head, new_node);
            i += 2;
        }
        else if ((strcmp(argv[i], "dh")) == 0) {
            llist_delete_head(&head);
            i++;
        }
        else if ((strcmp(argv[i], "f")) == 0) {
            llist_free(&head);
            i++;
        }
        else if ((strcmp(argv[i], "p")) == 0) {
            llist_print(head);
            i++;
        }
        else {
            printf("Error");
        }
    }
}
