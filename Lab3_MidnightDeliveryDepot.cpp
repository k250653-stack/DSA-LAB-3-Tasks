#include <iostream>
#include <iomanip>
using namespace std;

void printArray(const int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]";
}

int* copyArray(const int arr[], int size) {
    int* copy = new int[size];
    for (int i = 0; i < size; i++) {
        copy[i] = arr[i];
    }
    return copy;
}

void adjacentSwapper(int arr[], int size) {
    int swaps = 0;
    int comparisons = 0;
    int passes = 0;

    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        passes++;
        for (int j = 0; j < size - 1 - i; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    int worstPasses = size > 0 ? size - 1 : 0;
    int worstComparisons = size * (size - 1) / 2;

    cout << "Sorted: ";
    printArray(arr, size);
    cout << endl;
    cout << "Total swaps made: " << swaps << endl;
    cout << "Total comparisons made: " << comparisons << endl;
    cout << "Passes performed: " << passes << " (worst case " << worstPasses << ")" << endl;
    cout << "Passes saved: " << (worstPasses - passes) << endl;
    cout << "Actual comparisons: " << comparisons << " | Theoretical worst case N(N-1)/2: " << worstComparisons << endl;
}

void insertionArmSorter(int arr[], int size) {
    int totalShift = 0;

    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        int shifts = 0;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            shifts++;
        }
        arr[j + 1] = key;
        totalShift += shifts;

        cout << "Key " << key << " placed: ";
        printArray(arr, size);
        cout << endl;
        if (shifts == 0) {
            cout << "  No shift required" << endl;
        } else {
            cout << "  Shifted " << shifts << " position(s)" << endl;
        }
    }

    cout << "Sorted: ";
    printArray(arr, size);
    cout << endl;
    cout << "Total shift distance: " << totalShift << endl;
}

void minimalSwapCrane(int arr[], int size) {
    int swaps = 0;
    int skipped = 0;
    int comparisons = 0;

    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            comparisons++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex == i) {
            skipped++;
        } else {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            swaps++;
        }
    }

    cout << "Sorted: ";
    printArray(arr, size);
    cout << endl;
    cout << "Total actual swaps: " << swaps << endl;
    cout << "Number of skipped swaps: " << skipped << endl;
    cout << "Total comparisons: " << comparisons << " (N(N-1)/2 = " << size * (size - 1) / 2 << ")" << endl;
    if (comparisons > 0) {
        double ratio = (static_cast<double>(swaps) / comparisons) * 100.0;
        cout << "Swap-to-Comparison Ratio: " << fixed << setprecision(2) << ratio << "%" << endl;
    } else {
        cout << "Swap-to-Comparison Ratio: N/A (no comparisons)" << endl;
    }
}

void diminishingDistanceScanner(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        int comparisons = 0;
        int swaps = 0;

        for (int i = gap; i < size; i++) {
            for (int j = i; j >= gap; j -= gap) {
                comparisons++;
                if (arr[j - gap] > arr[j]) {
                    int temp = arr[j];
                    arr[j] = arr[j - gap];
                    arr[j - gap] = temp;
                    swaps++;
                } else {
                    break;
                }
            }
        }

        double percent = (static_cast<double>(gap) / size) * 100.0;
        cout << "Gap: " << gap << " | Gap as % of N: " << fixed << setprecision(2) << percent
             << "% | Comparisons: " << comparisons << " | Swaps: " << swaps << endl;
        cout << "  Array: ";
        printArray(arr, size);
        cout << endl;
    }

    cout << "Sorted: ";
    printArray(arr, size);
    cout << endl;
}

bool isSorted(const int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

int midpointSplitSearch(int arr[], int size, int targetID) {
    if (!isSorted(arr, size)) {
        cout << "Error: Conveyor is unsorted. Search aborted." << endl;
        return -1;
    }

    int maxSteps = 0;
    for (int t = size; t > 0; t >>= 1) {
        maxSteps++;
    }

    int low = 0;
    int high = size - 1;
    int steps = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        steps++;
        double remaining = (static_cast<double>(high - low + 1) / size) * 100.0;

        cout << "Step " << steps << ": low=" << low << ", mid=" << mid << ", high=" << high
             << " | Remaining search space: " << fixed << setprecision(2) << remaining << "%"
             << " | Steps: " << steps << "/" << maxSteps << " (theoretical max)" << endl;

        if (arr[mid] == targetID) {
            cout << "Found " << targetID << " at index " << mid << endl;
            return mid;
        } else if (targetID < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << "Tracking ID " << targetID << " not found." << endl;
    return -1;
}

int main() {
    int n;
    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of items." << endl;
        return 1;
    }

    int* original = new int[n];
    cout << "Enter tracking IDs: ";
    for (int i = 0; i < n; i++) {
        cin >> original[i];
    }

    cout << "\nOriginal: ";
    printArray(original, n);
    cout << endl;

    int* work = copyArray(original, n);
    cout << "\nTask 1: Adjacent Swapper" << endl;
    adjacentSwapper(work, n);
    delete[] work;

    work = copyArray(original, n);
    cout << "\nTask 2: Insertion Arm Sorter" << endl;
    insertionArmSorter(work, n);
    delete[] work;

    work = copyArray(original, n);
    cout << "\nTask 3: Minimal Swap Crane" << endl;
    minimalSwapCrane(work, n);
    delete[] work;

    work = copyArray(original, n);
    cout << "\nTask 4: Diminishing Distance Scanner" << endl;
    diminishingDistanceScanner(work, n);

    int target;
    cout << "\nEnter tracking ID to search: ";
    cin >> target;

    cout << "\nTask 5: Midpoint Split Search (on unsorted input)" << endl;
    int unsortedResult = midpointSplitSearch(original, n, target);
    cout << "Returned: " << unsortedResult << endl;

    cout << "\nTask 5: Midpoint Split Search (on sorted array)" << endl;
    int sortedResult = midpointSplitSearch(work, n, target);
    cout << "Returned: " << sortedResult << endl;

    delete[] work;
    delete[] original;
    return 0;
}
