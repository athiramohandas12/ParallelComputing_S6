#include <iostream>
#include <thread>

// Function to print first n natural numbers
void printNumbers(int n) {
    for (int i = 1; i <= n; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Get the value of n from the user
    int n;
    std::cout << "Enter the value of n: ";
    std::cin >> n;

    // Create a thread and pass the printNumbers function along with the value of n
    std::thread t(printNumbers, n);

    // Wait for the thread to finish
    t.join();

    return 0;
}
