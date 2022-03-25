#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>



typedef struct node
{
    unsigned char* data;
    struct node* right_child;
    struct node* left_child;
    int count;
} TreeNode;


TreeNode* insert(TreeNode* p, unsigned char* word)
{
    if (p == NULL)
    {
        p = (TreeNode*)malloc(sizeof(TreeNode));
        p->data = _strdup(word);
        p->left_child = NULL;
        p->right_child = NULL;
        p->count = 1;
    }
    else if ((strcmp(word, p->data)) == 0)
        p->count++;
    else if ((strcmp(word, p->data)) < 0)
        p->left_child = insert(p->left_child, word);
    else
        p->right_child = insert(p->right_child, word);
    return p;
}


TreeNode* insertFrequency(TreeNode* p, TreeNode* p2)
{
    if (p == NULL)
    {
        p = (TreeNode*)malloc(sizeof(TreeNode));
        p->data = _strdup(p2->data);
        p->count = p2->count;
        p->left_child = NULL;
        p->right_child = NULL;

    }
    else if (p2->count > p->count)
        p->left_child = insertFrequency(p->left_child, p2);
    else if (p2->count <= p->count)
        p->right_child = insertFrequency(p->right_child, p2);
    return p;
}

TreeNode* readFromFile(TreeNode* p)
{
    FILE* file;
    unsigned char* fname = "1.txt";
    unsigned char c;
    unsigned char temp[255];
    int j = 0;
    file = fopen(fname, "r");

    if (file == 0) {
        printf("Cant open file '%s'", fname);
        return 0;
    }
    while (!feof(file)) {
        c = fgetc(file);
        if (c == '\0')
            break;

        if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)) || ((c >= 192) && (c <= 255))) 
        {
            temp[j] = c;
            temp[j + 1] = '\0';
            j++;
        }
        else if (strcmp(temp, "\0")) {
            p = insert(p, temp);
            temp[0] = '\0';
            j = 0;
        }
    }
    fclose(file);
    return p;
}

TreeNode* searchWord(TreeNode* p, unsigned char* word)
{
    if ((p == NULL) || (strcmp(p->data, word) == 0))
        return p;
    else if (strcmp(p->data, word) > 0)
        return searchWord(p->left_child, word);

    else if (strcmp(p->data, word) < 0)
        return searchWord(p->right_child, word);
}

void deleteTreeNode(TreeNode* tree) {
    if (tree != NULL) {
        deleteTreeNode(tree->left_child);
        deleteTreeNode(tree->right_child);
        free(tree->data);
        free(tree);
    }
}

void printInOrderLeft(TreeNode* p)
{
    if (p != NULL)
    {
        printInOrderLeft(p->left_child);
        printf("%s %d\n", p->data, p->count);
        printInOrderLeft(p->right_child);

    }
}

void printInOrderRight(TreeNode* p)
{
    if (p != NULL)
    {
        printInOrderRight(p->right_child);
        printf("%s %d\n", p->data, p->count);
        printInOrderRight(p->left_child);

    }
}

int sizeOfTree(TreeNode* p)
{
    if (p == NULL)
        return 0;
    int res = 1;
    res += sizeOfTree(p->left_child);
    res += sizeOfTree(p->right_child);
    return res;
}

TreeNode** inputArray(TreeNode* p, TreeNode** array)
{
    static int i1 = 0;
    if (p != NULL)
    {
        inputArray(p->right_child, array);
        array[i1] = p;
        i1++;
        inputArray(p->left_child, array);
    }
    return array;
}

TreeNode* deleteAllExcept(TreeNode* p, int wordSize)
{
    static TreeNode* tmp = NULL;
    if (p != NULL)
    {
        deleteAllExcept(p->left_child, wordSize);
        deleteAllExcept(p->right_child, wordSize);

        if (strlen(p->data) == wordSize)
            if (p->count > 1) {
                for (int i = 0; i < p->count; i++)
                    tmp = insert(tmp, p->data);
            }
            else if (p->count == 1) {
                tmp = insert(tmp, p->data);
            }

    }
    return tmp;

}

void shellSort(TreeNode** a, int size)
{
    int i, j, step;
    TreeNode* tmp;
    for (step = size / 2; step > 0; step /= 2)
        for (i = step; i < size; i++)
        {
            tmp = a[i];
            for (j = i; j >= step; j -= step)
                if (tmp->count < a[j - step]->count)
                    a[j] = a[j - step];
                else
                    break;
            a[j] = tmp;
        }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    TreeNode* rootTree1;
    rootTree1 = NULL;
    rootTree1 = readFromFile(rootTree1);
    int  counterWord = sizeOfTree(rootTree1);

    TreeNode** ptr = (TreeNode**)malloc(sizeof(TreeNode*) * 100000);
        ptr = inputArray(rootTree1, ptr);
    shellSort(ptr, counterWord);

    long int counterAll = 0;
    for (int j = 0; j < counterWord; j++)
    {
        printf("%s %d id: %d\n", ptr[j]->data, ptr[j]->count, j);
        counterAll = counterAll + ptr[j]->count;
    }

    printf("%d ", counterAll);
    //printInOrder(rootTree1);
    

    deleteTreeNode(rootTree1);
    return 0;

}


