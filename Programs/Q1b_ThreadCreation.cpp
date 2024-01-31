#include <iostream>
#include <thread>
#include <vector>

// Function to print first n natural numbers
void printNumbers(int start, int end) {
    for (int i = start; i <= end; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Get the value of n from the user
    int n;
    std::cout << "Enter the value of n: ";
    std::cin >> n;

    // Number of threads
    const int numThreads = 10;

    // Calculate the range of numbers each thread will handle
    int numbersPerThread = n / numThreads;
    int remainder = n % numThreads;

    // Vector to store thread objects
    std::vector<std::thread> threads;

    // Create threads
    for (int i = 0; i < numThreads; ++i) {
        int start = i * numbersPerThread + 1;
        int end = (i + 1) * numbersPerThread;
        if (i == numThreads - 1) {
            // Add the remainder to the last thread
            end += remainder;
        }

        // Create a thread and pass the printNumbers function along with the range of numbers
        threads.emplace_back(printNumbers, start, end);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
