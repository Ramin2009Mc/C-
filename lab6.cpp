#include <iostream>
#include <algorithm>
#include <utility>

//const size_t ROWS = 3;
//const size_t COLUMNS = 4;
const unsigned int SEED = 777;
std::pair<int, int> processSort(int *matrix, size_t rows, size_t cols, void (*sortFunction)(int *, size_t, int &, int &, bool));

void bubbleSort(int *arr, size_t n, int &swaps, int &comparisons, bool desc);
void selectionSort(int *arr, size_t n, int &swaps, int &comparisons, bool desc);
void insertionSort(int *arr, size_t n, int &swaps, int &comparisons, bool desc);
void shellSort(int *arr, size_t n, int &swaps, int &comparisons, bool desc);
void fastSort(int *arr, size_t n, int &swaps, int &comparisons, bool desc);

void transposeMatrix(int *matrix, size_t rows, size_t cols);
void fillMatrixWithRandom(int *matrix, size_t rows, size_t cols);
void copyMatrix(int *matrix, int *source, size_t rows, size_t cols);
void outputMatrix(int *matrix, size_t rows, size_t cols, std::ostream &out);

int main()
{
  size_t ROWS, COLUMNS;
  std::cout << "Enter the number of rows: ";
  std::cin >> ROWS;
  std::cout << "Enter the number of columns: ";
  std::cin >> COLUMNS;

  int* sourceMatrix = new int[ROWS * COLUMNS];
  fillMatrixWithRandom(sourceMatrix, ROWS, COLUMNS);
  std::cout << "\x1b[35msourceMatrix:\x1b[0m\n";
  outputMatrix(sourceMatrix, ROWS, COLUMNS, std::cout);
  std::cout << "\n\n";

  fillMatrixWithRandom(sourceMatrix, ROWS, COLUMNS);

  std::cout << "\x1b[35mbubbleSort:\x1b[0m\n";
  std::pair<int, int> bubble = processSort(sourceMatrix, ROWS, COLUMNS, bubbleSort);
  std::cout << "\x1b[35mselectionSort:\x1b[0m\n";
  std::pair<int, int> selection = processSort(sourceMatrix, ROWS, COLUMNS, selectionSort);
  std::cout << "\x1b[35minsertionSort:\x1b[0m\n";
  std::pair<int, int> insertion = processSort(sourceMatrix, ROWS, COLUMNS, insertionSort);
  std::cout << "\x1b[35mshellSort:\x1b[0m\n";
  std::pair<int, int> shell = processSort(sourceMatrix, ROWS, COLUMNS, shellSort);
  std::cout << "\x1b[35mfastSort:\x1b[0m\n";
  std::pair<int, int> fast = processSort(sourceMatrix, ROWS, COLUMNS, fastSort);

  std::cout << "\x1b[35m\n\n\tComparison table\x1b[0m\nSort\t\tswaps\tcomparisons\n";
  std::cout << "bubbleSort\t" << bubble.first << '\t' << bubble.second << '\n';
  std::cout << "selectionSort\t" << selection.first << '\t' << selection.second << '\n';
  std::cout << "insertionSort\t" << insertion.first << '\t' << insertion.second << '\n';
  std::cout << "shellSort\t" << shell.first << '\t' << shell.second << '\n';
  std::cout << "fastSort\t" << fast.first << '\t' << fast.second << '\n';
}

std::pair<int, int> processSort(int* matrix, size_t rows, size_t cols, void (*sortFunction)(int*, size_t, int&, int&, bool)) {
    int* matrixCopy = new int[rows * cols];
    copyMatrix(matrixCopy, matrix, rows, cols);
    int swaps = 0, comparisons = 0;

    // Сортировка по строкам по возрастанию
    for (size_t row = 0; row < rows; ++row) {
        sortFunction(matrixCopy + row * cols, cols, swaps, comparisons, false);
    }
    std::cout << "Sorted by rows in ascending order:\n";
    outputMatrix(matrixCopy, rows, cols, std::cout);
    std::cout << '\n';

    // Сортировка по строкам по возрастанию и по столбцам по убыванию
    int* columnTemp = new int[rows];
    for (size_t col = 0; col < cols; ++col) {
        for (size_t row = 0; row < rows; ++row) {
            columnTemp[row] = matrixCopy[row * cols + col];
        }
        sortFunction(columnTemp, rows, swaps, comparisons, true);
        for (size_t row = 0; row < rows; ++row) {
            matrixCopy[row * cols + col] = columnTemp[row];
        }
    }
    delete[] columnTemp;
    std::cout << "Sorted by rows in ascending order and by columns in descending order:\n";
    outputMatrix(matrixCopy, rows, cols, std::cout);
    std::cout << '\n';

    delete[] matrixCopy;
    return std::make_pair(swaps, comparisons);
}


void insertionSort(int* a, size_t n, int& swaps, int& comparisons, bool desc) {
    for (int i = 1; i < n; i++) {
        int x = a[i];

        comparisons++;
        for (int j = i - 1; j >= 0 && (desc ? a[j] < x : a[j] > x); j--) {
            std::swap(a[j + 1], a[j]);
            swaps++;
            comparisons++;
        }
    }
}


void shellSort(int *arr, size_t n, int &swaps, int &comparisons, bool desc) {
  if (n <= 1) {
    return;
  }

  int gap = n / 2;
  while (gap > 0) {
    for (size_t i = gap; i < n; i++) {
      size_t j = i;
      int temp = arr[i];
      comparisons++;
      while (j >= gap && (desc ? (arr[j - gap] < temp) : (arr[j - gap] > temp))) {
        comparisons++;
        std::swap(arr[j], arr[j - gap]);
        swaps++;
        j -= gap;
      }
      arr[j] = temp;
    }
    gap = gap / 2;  // classic shellSort
  }
}


void bubbleSort(int *arr, size_t n, int &swaps, int &comparisons, bool desc) {
  if (n <= 1) {
    return;
  }

  bool swapped;
  do {
    swapped = false;
    for (size_t i = 1; i < n; i++) {
      comparisons++;
      if (desc ? arr[i - 1] < arr[i] : arr[i - 1] > arr[i]) {
        std::swap(arr[i - 1], arr[i]);
        swaps++;
        swapped = true;
      }
    }

  } while (swapped);
}


void selectionSort(int* arr, size_t n, int& swaps, int& comparisons, bool desc)
{
    if (n <= 1)
    {
        return;
    }

    for (size_t i = 0; i < n - 1; i++)
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < n; j++)
        {
            comparisons++;
            if ((desc ? (arr[j] > arr[minIndex]) : (arr[j] < arr[minIndex])))
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            std::swap(arr[i], arr[minIndex]);
            swaps++;
        }
    }
}



void fastSort(int* arr, size_t n, int& swaps, int& comparisons, bool desc)
{
    if (n <= 1)
    {
        return;
    }

    size_t pivotIndex = n / 2;
    int pivotValue = arr[pivotIndex];

    // Если массив уже отсортирован, просто рекурсивно вызываем функцию для оставшихся частей
    if ((desc && arr[0] >= arr[n - 1]) || (!desc && arr[0] <= arr[n - 1]))
    {
        comparisons += n - 1;
        if (pivotIndex > 0)
        {
            fastSort(arr, pivotIndex, swaps, comparisons, desc);
        }
        if (n - pivotIndex - 1 > 0)
        {
            fastSort(arr + pivotIndex + 1, n - pivotIndex - 1, swaps, comparisons, desc);
        }
        return;
    }

    // Перемещаем пивот в конец массива
    if (pivotIndex != n - 1)
    {
        std::swap(arr[pivotIndex], arr[n - 1]);
        swaps++;
    }

    size_t storeIndex = 0;
    for (size_t i = 0; i < n - 1; i++)
    {
        comparisons++;
        if (desc ? arr[i] > pivotValue : arr[i] < pivotValue)
        {
            if (i != storeIndex)
            {
                std::swap(arr[i], arr[storeIndex]);
                swaps++;
            }
            storeIndex++;
        }
    }

    // Возвращаем пивот на его место
    std::swap(arr[storeIndex], arr[n - 1]);
    swaps++;

    if (storeIndex > 0)
    {
        fastSort(arr, storeIndex, swaps, comparisons, desc);
    }
    if (n - storeIndex - 1 > 0)
    {
        fastSort(arr + storeIndex + 1, n - storeIndex - 1, swaps, comparisons, desc);
    }
}


void transposeMatrix(int *matrix, size_t rows, size_t columns)
{
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = i + 1; j < columns; ++j)
    {
      std::swap(matrix[i * columns + j], matrix[j * rows + i]);
    }
  }
}

void fillMatrixWithRandom(int *matrix, size_t rows, size_t columns)
{
   srand(time(NULL));
  for (size_t i = 0; i < rows * columns; ++i)
  {
   
      matrix[i] = columns*rows-i;//rand() % 100; // 100 + std::rand() % 900;
  }
}
void copyMatrix(int *matrix, int *source, size_t rows, size_t columns)
{
  for (size_t i = 0; i < rows * columns; ++i)
  {
    matrix[i] = source[i];
  }
}
void outputMatrix(int *matrix, size_t rows, size_t columns, std::ostream &out)
{
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < columns; ++j)
    {
      out << matrix[i * columns + j] << " ";
    }
    out << std::endl;
  }
}
//взять 1 значение, посмотреть таблицу; взять 2 упорядоченных значения (0 sw, 1 com), посмотреть таблицу; взять 3 упорядоченных значения, посмотреть таблицу; взять j, взять i