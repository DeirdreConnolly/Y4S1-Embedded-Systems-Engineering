#include <ctype.h>
#include <stdio.h>
#include <stdio.h>
#include <malloc.h>
#include <mem.h>

struct Node {
    char *data;
    struct Node *ltree;
    struct Node *rtree;
};

struct Node *head;

struct Node *newTree(char *p) {
    struct Node *n = malloc(sizeof(struct Node));
    n->data = malloc(strlen(p) + 1);
    strcpy(n->data, p);
    n->ltree = n->rtree = NULL;
    return n;
}

struct Node *insert(struct Node *tree, char *p) {
    if (tree == NULL)
        return newTree(p);
    int cmp = strcmp(p, tree->data);
    if (cmp <= 0)
        tree->ltree = insert(tree->ltree, p);
    else
        tree->rtree = insert(tree->rtree, p);
    return tree;
}

void inorder(struct Node *tree) {
    if (tree == NULL)
        return;
    inorder(tree->ltree);
    printf("%s\n", tree->data);
    inorder(tree->rtree);
}

main() {
    char buf[200];
    FILE *fp;
    fp = fopen("C:\\Users\\Deirdre\\College\\CIT\\Year 4\\Semester 1\\Embedded Systems Engineering\\Lab01\\test.txt", "r");

    char id[100];
    int j;
    while (fgets(buf, 100, fp)) {
        int i = 0;
        int len = strlen(buf);
        for (j = 0, i = 0; i < len; i++) {
            if (isalpha(buf[i]) || buf[i] == '_') {
                while (buf[i] && (isalnum(buf[i]) || buf[i] == '_'))
                    id[j++] = buf[i++];
                // have id
                id[j] = 0;  // Currently on, 0 is NULL terminator

                // At this point, we have a completed word
                head = insert(head, id);

                printf("id = %s\n", id);
                j = 0;  // Reset to start of array
            }
        }
    }

    inorder(head);
}