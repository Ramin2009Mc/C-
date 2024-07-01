#include <stdio.h>
#include <stdlib.h>

// Структура для узла дерева
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Функция для создания нового узла дерева
struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для вставки значения в дерево
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

// Функции для обхода дерева
void inOrderTraversal(struct Node* node) {
    if (node != NULL) {
        inOrderTraversal(node->left);
        printf("%d ", node->data);
        inOrderTraversal(node->right);
    }
}

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

// Функция для поиска элемента в одномерном массиве последовательным методом
int sequentialSearch(int array[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

// Функция для поиска элемента в одномерном массиве бинарным методом
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

// Поиск элемента по диагональным элементам матрицы
int diagonalSearch(int** matrix, int n, int target) {
    int count = 0;

    // Поиск элемента на главной диагонали
    for (int i = 0; i < n; i++) {
        count++;
        if (matrix[i][i] == target) {
            return count;
        }
    }

    // Поиск элемента на побочной диагонали
    for (int i = 0; i < n; i++) {
        count++;
        if (matrix[i][n - 1 - i] == target) {
            return count;
        }
    }

    return -1;
}

// Основная функция
int main() {
    // Ввод размера массива
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    // Создание и заполнение двумерного массива (матрицы)
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Создание бинарного дерева поиска из диагонали матрицы
    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, matrix[i][i]);
    }

    // Вывод значений дерева разными способами
    printf("In-order traversal: ");
    inOrderTraversal(root);
    printf("\nPre-order traversal: ");
    preOrderTraversal(root);
    printf("\nPost-order traversal: ");
    postOrderTraversal(root);
    printf("\n");

    // Ввод числа для поиска
    int target;
    printf("Enter the target value to search in the matrix: ");
    scanf("%d", &target);

    // Поиск элемента в массиве
    int arr[n * n];
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[index++] = matrix[i][j];
        }
    }

    // Последовательный поиск
    int seqIndex = sequentialSearch(arr, n * n, target);
    if (seqIndex != -1) {
        printf("Element found at index %d (sequential search)\n", seqIndex);
    }
    else {
        printf("Element not found (sequential search)\n");
    }

    // Сортировка массива по возрастанию
    for (int i = 0; i < n * n - 1; i++) {
        for (int j = 0; j < n * n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Бинарный поиск
    int binIndex = binarySearch(arr, n * n, target);
    if (binIndex != -1) {
        printf("Element found at index %d (binary search)\n", binIndex);
    }
    else {
        printf("Element not found (binary search)\n");
    }

    // Поиск элемента по диагональным элементам матрицы
    int diagSteps = diagonalSearch(matrix, n, target);
    if (diagSteps != -1) {
        printf("Element found after %d steps (diagonal search)\n", diagSteps);
    }
    else {
        printf("Element not found (diagonal search)\n");
    }

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
