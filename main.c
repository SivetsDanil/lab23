#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "three.h"


Node* add(Node* root, char data) {
    if (root == NULL) {
        Node* nw = malloc(sizeof(Node));
        nw->data = data;
        nw->left = nw->right = NULL;
        return nw;
    }
    if (data < root->data)
        root->left = add(root->left, data);
    else if (data > root->data)
        root->right = add(root->right, data);
    return root;
}

void free_tree(Node* root) {
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
void print_three(Node* root, int depth) {
    if (root == NULL) {
        return;
    }
    for (int i=0; i <depth; i++) {
        printf("    ");
    }
    printf("%c\n", root->data);
    print_three(root->left, depth+1);
    print_three(root->right, depth+1);
}

Node* delete(Node* root, char c){
    if (root == NULL) {
        return NULL;
    }
    if (c > root->data) {
        root->right = delete(root->right, c);
    }
    else if (c < root->data) {
        root->left = delete(root->left, c);
    }
    else {
        if (root->left == NULL) {
            Node* r = root->right;
            free(root);
            return r;
        }
        if (root->right == NULL) {
            Node* l = root->left;
            free(root);
            return l;
        }
        Node* s = root->right;
        while (s->left != NULL)
            s = s->left;
        root->data = s->data;
        root->right = delete(root->right, s->data);
    }
    return root;
}

void count_widths(Node* t, int depth, int widths[]) {
    if (t == NULL) return;
    if (depth < MAX_H) widths[depth]++;
    count_widths(t->left,  depth + 1, widths);
    count_widths(t->right, depth + 1, widths);
}

int check(Node *t) {
    int widths[MAX_H] = {0};
    count_widths(t, 0, widths);
    if (widths[0] == 0) return 1;
    for (int i = 1; i < MAX_H; i++) {
        if (widths[i] == 0) {
            break;
        }
        if (widths[i] < widths[i-1]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int n;
    scanf("%d", &n);
    char s[13];
    snprintf(s, sizeof(s), "..\\test%d.txt", n);
    FILE* f = fopen(s, "r");
    Node* three = NULL;
    char com[15];
    char c;
    while (1) {
        if (fscanf(f, "%14s", com) != 1) {
            printf("\nEOF: freeing tree and exiting\n");
            free_tree(three);
            break;
        }
        if (!strcmp(com, "exit")) {
            free_tree(three);
            break;
        }
        if (!strcmp(com, "add")) {
            fscanf(f, " %c", &c);
            three = add(three, c);
            printf("Added %c\n", c);
        }
        if (!strcmp(com, "print")) {
            print_three(three, 0);
        }
        if (!strcmp(com, "delete")) {
            fscanf(f, " %c", &c);
            three = delete(three, c);
            printf("Deleted %c\n", c);

        }
        if (!strcmp(com, "check")) {
            if (check(three)) {
                printf("YES\n");
            } else printf("NO\n");
        }
    }
    return 0;
}