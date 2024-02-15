#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

// Function to generate a random integer array of size n
std::vector<int> generateRandomArray(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100;  // Generating random integers between 0 and 99
    }
    return arr;
}

// Sequential function to find the sum of elements in the array
int sequentialSum(const std::vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}

// Sequential function to search for a key element in the array
bool sequentialSearch(const std::vector<int>& arr, int key) {
    for (int num : arr) {
        if (num == key) {
            return true;
        }
    }
    return false;
}

// Function to find the sum of elements in a partition of the array
int sumPartition(const std::vector<int>& arr, int start, int end) {
    int sum = 0;
    for (int i = start; i < end; ++i) {
        sum += arr[i];
    }
    return sum;
}

// Function to search for a key element in a partition of the array
bool searchPartition(const std::vector<int>& arr, int start, int end, int key) {
    for (int i = start; i < end; ++i) {
        if (arr[i] == key) {
            return true;
        }
    }
    return false;
}

// Threaded function to perform sum computation in each thread
void threadedSum(const std::vector<int>& arr, int numThreads) {
    int n = arr.size();
    int numbersPerThread = n / numThreads;
    int remainder = n % numThreads;

    std::vector<std::thread> threads;
    std::vector<int> threadSums(numThreads, 0);

    // Create threads
    for (int i = 0; i < numThreads; ++i) {
        int start = i * numbersPerThread;
        int end = (i + 1) * numbersPerThread;
        if (i == numThreads - 1) {
            // Add the remainder to the last thread
            end += remainder;
        }

        // Create a thread and pass the sumPartition function along with the range of numbers
        threads.emplace_back([&, start, end, i]() {
            threadSums[i] = sumPartition(arr, start, end);
        });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Calculate the final sum
    int finalSum = 0;
    for (int sum : threadSums) {
        finalSum += sum;
    }

    std::cout << "Threaded Sum: " << finalSum << std::endl;
}

// Threaded function to perform search computation in each thread
void threadedSearch(const std::vector<int>& arr, int numThreads, int key) {
    int n = arr.size();
    int numbersPerThread = n / numThreads;
    int remainder = n % numThreads;

    std::vector<std::thread> threads;
    std::vector<bool> threadResults(numThreads, false);

    // Create threads
    for (int i = 0; i < numThreads; ++i) {
        int start = i * numbersPerThread;
        int end = (i + 1) * numbersPerThread;
        if (i == numThreads - 1) {
            // Add the remainder to the last thread
            end += remainder;
        }

        // Create a thread and pass the searchPartition function along with the range of numbers
        threads.emplace_back([&, start, end, i]() {
            threadResults[i] = searchPartition(arr, start, end, key);
        });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Check if the key is found in any partition
    bool keyFound = false;
    for (bool result : threadResults) {
        if (result) {
            keyFound = true;
            break;
        }
    }

    if (keyFound) {
        std::cout << "Key found in the array." << std::endl;
    } else {
        std::cout << "Key not found in the array." << std::endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int size, numThreads, key;

    std::cout << "Enter the array size: ";
    std::cin >> size;

    std::cout << "Enter the number of threads: ";
    std::cin >> numThreads;

    // Generate a random array
    std::vector<int> arr = generateRandomArray(size);

    // Measure execution time for sequential sum
    auto startSeqSum = std::chrono::high_resolution_clock::now();
    int seqSum = sequentialSum(arr);
    auto endSeqSum = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seqSumDuration = endSeqSum - startSeqSum;
    std::cout << "Sequential Sum: " << seqSum << " | Execution Time: " << seqSumDuration.count() << " seconds\n";

    // User input for the key
    std::cout << "Enter the key for search: ";
    std::cin >> key;

    // Measure execution time for sequential search
    auto startSeqSearch = std::chrono::high_resolution_clock::now();
    bool seqSearchResult = sequentialSearch(arr, key);
    auto endSeqSearch = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seqSearchDuration = endSeqSearch - startSeqSearch;
    std::cout << "Sequential Search for key " << key << ": " << (seqSearchResult ? "Found" : "Not Found")
              << " | Execution Time: " << seqSearchDuration.count() << " seconds\n";

    // Measure execution time for threaded sum and search
    std::cout << "\nNumber of Threads: " << numThreads << std::endl;

    // Measure execution time for threaded sum
    auto startThreadedSum = std::chrono::high_resolution_clock::now();
    threadedSum(arr, numThreads);
    auto endThreadedSum = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> threadedSumDuration = endThreadedSum - startThreadedSum;
    std::cout << "Threaded Sum | Execution Time: " << threadedSumDuration.count() << " seconds\n";

    // Measure execution time for threaded search
    auto startThreadedSearch = std::chrono::high_resolution_clock::now();
    threadedSearch(arr, numThreads, key);
    auto endThreadedSearch = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> threadedSearchDuration = endThreadedSearch - startThreadedSearch;
    std::cout << "Threaded Search for key " << key << " | Execution Time: " << threadedSearchDuration.count() << " seconds\n";

    return 0;
}
