#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* insert(struct Node* node, int value) {
    if (node == NULL) {
        return newNode(value);
    }
    if (value < node->data) {
        node->left = insert(node->left, value);
    } else {
        node->right = insert(node->right, value);
    }
    return node;
}

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

void freeTree(struct Node* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

int sequentialSearch(int array[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int array[], int size, int key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid] == key) {
            return mid;
        }
        if (array[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pivot = array[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (array[j] <= pivot) {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }

        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;

        int pi = i + 1;

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int diagonalSearch(int** matrix, int n, int target) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        count++;
        if (matrix[i][i] == target) {
            return count;
        }
    }

    for (int i = 0; i < n; i++) {
        count++;
        if (matrix[i][n - 1 - i] == target) {
            return count;
        }
    }

    return -1;
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    while (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer: ");
        while (getchar() != '\n'); // Clearing buffer
    }

    int** matrix = (int**)malloc(n * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            while (scanf("%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Invalid input. Please enter an integer: ");
                while (getchar() != '\n'); // Clearing buffer
            }
        }
    }

    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, matrix[i][i]);
    }

    printf("In-order traversal: ");
    inOrderTraversal(root);
    printf("\nPre-order traversal: ");
    preOrderTraversal(root);
    printf("\nPost-order traversal: ");
    postOrderTraversal(root);
    printf("\n");

    int target;
    printf("Enter the target value to search in the matrix: ");
    while (scanf("%d", &target) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer: ");
        while (getchar() != '\n'); // Clearing buffer
    }

    int* arr = (int*)malloc(n * n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

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
    } else {
        printf("Element not found (sequential search)\n");
    }

    // Сортировка массива по возрастанию
    quickSort(arr, 0, n * n - 1);

    // Бинарный поиск
    int binIndex = binarySearch(arr, n * n, target);
    if (binIndex != -1) {
        printf("Element found at index %d (binary search)\n", binIndex);
    } else {
        printf("Element not found (binary search)\n");
    }

    // Поиск элемента по диагональным элементам матрицы
    int diagSteps = diagonalSearch(matrix, n, target);
    if (diagSteps != -1) {
        printf("Element found after %d steps (diagonal search)\n", diagSteps);
    } else {
        printf("Element not found (diagonal search)\n");
    }

    // Освобождение памяти
    free(arr);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    freeTree(root);

    return 0;
}
