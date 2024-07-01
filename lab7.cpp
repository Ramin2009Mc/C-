#include <stdio.h>
#include <stdlib.h>

// ��������� ��� ���� ������
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// ������� ��� �������� ������ ���� ������
struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ������� ��� ������� �������� � ������
struct Node* insert(struct Node* node, int value) {
    if (node == NULL) {
        return newNode(value);
    }
    if (value < node->data) {
        node->left = insert(node->left, value);
    }
    else {
        node->right = insert(node->right, value);
    }
    return node;
}

// ������� ��� ������ ������
void inOrderTraversal(struct Node* node) {
    if (node != NULL) {
        inOrderTraversal(node->left);
        printf("%d ", node->data);
        inOrderTraversal(node->right);
    }
}

// ������� ��� ������ �������� � ���������� ������� ���������������� �������
int sequentialSearch(int array[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

// ������� ��� ������ �������� � ���������� ������� �������� �������
int binarySearch(int array[], int size, int key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid] == key) {
            return mid;
        }
        if (array[mid] < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

// ����� �������� �� ������������ ��������� �������
int diagonalSearch(int** matrix, int n, int target) {
    int count = 0;

    // ����� �������� �� ������� ���������
    for (int i = 0; i < n; i++) {
        count++;
        if (matrix[i][i] == target) {
            return count;
        }
    }

    // ����� �������� �� �������� ���������
    for (int i = 0; i < n; i++) {
        count++;
        if (matrix[i][n - 1 - i] == target) {
            return count;
        }
    }

    return -1;
}

//����� �� ����� �������� ������ ������� ��������� (������, ��������, �����������)
void preOrderTraversal(struct Node* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

void postOrderTraversal(struct Node* node) {
    if (node != NULL) {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        printf("%d ", node->data);
    }
}

//������� ������� � �������, ���������� � �������� �������, ������� ������ �� ��������� (��������� � ��������� ������), � ������� ����� ��� ������ ������ � ���� ���, ������ ����. ���������� �����, ����������  (������� �����/����� ��� ���), ���������� �� �����������, ���� �������� �������, ������� �����, ����� ��� ���. ���� �� ������
int main() {
    // �������� ��������� ������ ������
    struct Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 12);
    root = insert(root, 20);

    // ����� �������� ������ ������� ���������
    printf("In-order traversal: ");
    inOrderTraversal(root);
    printf("\nPre-order traversal: ");
    preOrderTraversal(root);
    printf("\nPost-order traversal: ");
    postOrderTraversal(root);
    printf("\n");

    // ���������� ������ ������
    int arr[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
    int n = sizeof(arr) / sizeof(arr[0]);

    // ����� �������� � ������� � ������� ����������������� ������
    int target = 13;
    int index = sequentialSearch(arr, n, target);
    if (index != -1) {
        printf("Element found at index %d (sequential search)\n", index);
    }
    else {
        printf("Element not found (sequential search)\n");
    }

    // ����� �������� � ������� � ������� ��������� ������
    index = binarySearch(arr, n, target);
    if (index != -1) {
        printf("Element found at index %d (binary search)\n", index);
    }
    else {
        printf("Element not found (binary search)\n");
    }

    // �������� ���������� ������� (�������)
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }


    // ���������� ������� �������
    int count = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = count++;
        }
    }

    // ����� �������� � ������� �� ������������ ���������
    target = 15;
    index = diagonalSearch(matrix, n, target);
    if (index != -1) {
        printf("Element found at index %d (diagonal search)\n", index);
    }
    else {
        printf("Element not found (diagonal search)\n");
    }

    // ������������ ������
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}