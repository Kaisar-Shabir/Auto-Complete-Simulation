#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*
other efficient data structure like this can be used instead. This will make searching even faster.
struct node {
    char ch;
    struct node *arr[26];
}
*/

struct node {
    struct node *arr[26];
};

typedef struct node* Node;

Node fnAdd(Node root, char *str) {
    Node cur = root;
    int i;
    for(i = 0; str[i] != '\0'; i++) {
        if(cur->arr[tolower(str[i]) - 'a'] == NULL) {
            Node temp = (Node) malloc(sizeof(struct node));
            int j;
            for(j = 0; j < 26; j++) {
                temp->arr[j] = NULL;
            }
            cur->arr[tolower(str[i]) - 'a'] = temp;
            cur = temp;
        }
        else {
            cur = cur->arr[tolower(str[i]) - 'a'];
        }
    }
    return root;
}

void dispAll(char str[], Node cur) {
    int i;
    bool flag = true;
    for(i = 0; i < 26; i++) {
        if(cur->arr[i] != NULL) {
            char ch = i + 'a';
            strncat(str, &ch, 1);
            dispAll(str, cur->arr[i]);
            str[strlen(str) - 1] = '\0';
            flag = false;
        }
    }
    if(flag) {
        printf("%s\n", str);
    }
}

void fnSearch(Node cur, char *str) {
    int i;
    for(i = 0; str[i] != '\0'; i++) {
        if(cur->arr[tolower(str[i]) - 'a'] != NULL) {
            cur = cur->arr[tolower(str[i]) - 'a'];
        }
        else {
            printf("%s was not found. Do you want to add it?(y/n)\t", str);
            char decision;
            scanf("%c", &decision);
            if(tolower(decision) == 'y') {
                fnAdd(str);
            }
            return;
        }
    }
    dispAll(str, cur);
}

int main()
{
    Node root = (Node) malloc(sizeof(struct node));
    int i;
    for(i = 0; i < 26; i++) {
        root->arr[i] = NULL;
    }
    char string[20];
    
    while(1) {
        int choice;
        printf("1. Add word.\n");
        printf("2. Search word.\n");
        printf("3. Exit word.\n");
        printf("Enter your choice:\t");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter the word to be added:\t");
                scanf("%s", string);
                root = fnAdd(root, string);
                break;
            case 2:
                printf("Enter the intial letters of the word to be searched:\t");
                scanf("%s", string);
                fnSearch(root, string);
                break;
            case 3: 
                exit(0);
            default:
                printf("Invalid option. Try again.\n");
        }
    }
    
    return 0;
}
