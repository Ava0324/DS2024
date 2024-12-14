#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>

// （1）起泡排序
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// （2）插入排序
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// （3）选择排序
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex!= i) {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}

// （4）归并排序
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// （5）快速排序
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// （6）堆排序
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest!= i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 生成顺序序列
std::vector<int> generateAscendingSequence(int size) {
    std::vector<int> seq(size);
    for (int i = 0; i < size; ++i) {
        seq[i] = i;
    }
    return seq;
}

// 生成逆序序列
std::vector<int> generateDescendingSequence(int size) {
    std::vector<int> seq(size);
    for (int i = 0; i < size; ++i) {
        seq[i] = size - i - 1;
    }
    return seq;
}

// 生成随机序列
std::vector<int> generateRandomSequence(int size) {
    std::vector<int> seq(size);
    for (int i = 0; i < size; ++i) {
        seq[i] = rand() % 1000;  // 生成0到999之间的随机数，可根据需要调整范围
    }
    return seq;
}

// 输出表格形式的性能对比结果
void printPerformanceTable(int sequenceSize, const std::vector<double>& ascendingTimes, const std::vector<double>& descendingTimes, const std::vector<double>& randomTimes) {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "| Algorithm        | Ascending (s) | Descending (s) | Random (s) |\n";
    std::cout << "|------------------|---------------|----------------|------------|\n";
    std::vector<std::string> algorithmNames = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort", "Heap Sort"};
    for (size_t i = 0; i < algorithmNames.size(); ++i) {
        std::cout << "| " << std::left << std::setw(16) << algorithmNames[i] << " | " << std::setw(13) << ascendingTimes[i] << " | " << std::setw(14) << descendingTimes[i] << " | " << std::setw(10) << randomTimes[i] << " |\n";
    }
    std::cout << "=========================================\n";
}

// 测试排序算法性能
void testSortingAlgorithms() {
    int sequenceSizes[] = {100, 500, 1000};  // 可以调整测试的序列大小

    for (int size : sequenceSizes) {
        std::vector<double> ascendingTimes;
        std::vector<double> descendingTimes;
        std::vector<double> randomTimes;

        // 顺序序列测试
        std::vector<int> ascending = generateAscendingSequence(size);
        std::vector<int> ascendingCopy1 = ascending;
        std::vector<int> ascendingCopy2 = ascending;
        std::vector<int> ascendingCopy3 = ascending;
        std::vector<int> ascendingCopy4 = ascending;
        std::vector<int> ascendingCopy5 = ascending;
        std::vector<int> ascendingCopy6 = ascending;

        clock_t start, end;

        start = clock();
        bubbleSort(ascendingCopy1);
        end = clock();
        ascendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        insertionSort(ascendingCopy2);
        end = clock();
        ascendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        selectionSort(ascendingCopy3);
        end = clock();
        ascendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        mergeSort(ascendingCopy4, 0, size - 1);
        end = clock();
        ascendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        quickSort(ascendingCopy5, 0, size - 1);
        end = clock();
        ascendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        heapSort(ascendingCopy6);
        end = clock();
        ascendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        // 逆序序列测试
        std::vector<int> descending = generateDescendingSequence(size);
        std::vector<int> descendingCopy1 = descending;
        std::vector<int> descendingCopy2 = descending;
        std::vector<int> descendingCopy3 = descending;
        std::vector<int> descendingCopy4 = descending;
        std::vector<int> descendingCopy5 = descending;
        std::vector<int> descendingCopy6 = descending;

        start = clock();
        bubbleSort(descendingCopy1);
        end = clock();
        descendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        insertionSort(descendingCopy2);
        end = clock();
        descendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        selectionSort(descendingCopy3);
        end = clock();
        descendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        mergeSort(descendingCopy4, 0, size - 1);
        end = clock();
        descendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        quickSort(descendingCopy5, 0, size - 1);
        end = clock();
        descendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        heapSort(descendingCopy6);
        end = clock();
        descendingTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        // 随机序列测试
        std::vector<int> random = generateRandomSequence(size);
        std::vector<int> randomCopy1 = random;
        std::vector<int> randomCopy2 = random;
        std::vector<int> randomCopy3 = random;
        std::vector<int> randomCopy4 = random;
        std::vector<int> randomCopy5 = random;
        std::vector<int> randomCopy6 = random;

        start = clock();
        bubbleSort(randomCopy1);
        end = clock();
        randomTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        insertionSort(randomCopy2);
        end = clock();
        randomTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        selectionSort(randomCopy3);
        end = clock();
        randomTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        mergeSort(randomCopy4, 0, size - 1);
        end = clock();
        randomTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        quickSort(randomCopy5, 0, size - 1);
        end = clock();
        randomTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        heapSort(randomCopy6);
        end = clock();
        randomTimes.push_back((double)(end - start) / CLOCKS_PER_SEC);

        printPerformanceTable(size, ascendingTimes, descendingTimes, randomTimes);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    testSortingAlgorithms();
    return 0;
}