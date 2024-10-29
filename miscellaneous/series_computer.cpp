#include <cmath>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include <chrono>

/*
    ---------------------------------Series Computer Problem Description ----------------------------------

    Write a class called “SeriesComputer” with:
    ● A constructor that accepts a function argument “f” that accepts a positive integer
    argument “k” and returns a float

    ● A method “compute” that accepts a positive integer argument “n” and returns the sum for
    k=1..n of f(k)

    ● If compute() is called multiple times on the same SeriesComputer object, it should reuse
    results from previous calls to compute() to speed up the computation

    ● compute() should raise/throw an exception if an invalid argument is entered
    Next, write a class called “NegativeSeriesComputer” that inherits from SeriesComputer but
    instead computes the sum for k from -1 to -n of f(k).
*/

/*
    ------------------------------Approach -----------------------------------------------------------------
    SeriesComputer constructor class accepts function as an argument,
    which accepts a positive integer with validation checks.

    In order to speed up computation, I have used unordered_map which caches the results from previous calls in O(1).
    I am also tracking the maximum value (max_call) for which the result has been cached.
    For any integer n <= max_call, the result is retrieved within O(1)
    For any integer n > max_call, we need to compute results in range (n-max_call) to n

    The working of cache is demonstrated by the retrival times printed alongside the large values of n
*/

class SeriesComputer {
protected:
    // Function.
    std::function<double(int)> f;

    // Store cache as a dictionary.
    std::unordered_map<int, double> cached_sums;

    // Track max call.
    int max_call = 0;

public:
    SeriesComputer(std::function<double(int)> func) : f(func) {}

    /**
     * @brief Compute the series value upto n.
     * @param int n Integer value to compute upto.
     * @returns Double value of the sum of the series.
     */
    double compute(int n) {
        if (n <= 0) {
            throw std::invalid_argument("n must be a positive integer");
        }

        // If we've computed this before, return cached result
        auto it = cached_sums.find(n);
        if (it != cached_sums.end()) {
            return it->second;
        }

        double result = 0.0;

        // Use previous result and add new terms
        result = cached_sums[max_call];
        for (int k = max_call + 1; k <= n; ++k) {
            result += f(k);
            // Cache intermediate results.
            cached_sums[k] = result;
        }

        // Update max_call and cache the result
        max_call = n;
        return result;
    }
};

class NegativeSeriesComputer : public SeriesComputer {
public:
    NegativeSeriesComputer(std::function<double(int)> func)
        : SeriesComputer([func](int k) { return func(-k); }) {}
};

int main() {
   auto reciprocal = [](int k) -> double { return 1.0/k; };

   // Test SeriesComputer
   std::cout << "\nTesting SeriesComputer..\n";
   try {
       SeriesComputer sc(reciprocal);

       // Define test values
       int val1 = 20000000;
       int val2 = val1 + 1;
       int val3 = val1 + 2;

       // First computation
       auto start = std::chrono::high_resolution_clock::now();
       double result1 = sc.compute(val1);
       auto end = std::chrono::high_resolution_clock::now();
       std::chrono::duration<double, std::milli> duration1 = end - start;
       std::cout << "SeriesComputer compute " << val1 << " " << result1
                 << " Time: " << duration1.count() << " ms" << std::endl;

       // Second computation
       start = std::chrono::high_resolution_clock::now();
       double result2 = sc.compute(val2);
       end = std::chrono::high_resolution_clock::now();
       std::chrono::duration<double, std::milli> duration2 = end - start;
       std::cout << "SeriesComputer compute " << val2 << " " << result2
                 << " Time: " << duration2.count() << " ms" << std::endl;

       std::cout << "Attempting compute(-10)..." << std::endl;
       start = std::chrono::high_resolution_clock::now();
       sc.compute(-10);
       end = std::chrono::high_resolution_clock::now();
       std::chrono::duration<double, std::milli> duration4 = end - start;
       std::cout << "Time: " << duration4.count() << " ms" << std::endl;
   }
   catch (const std::invalid_argument& e) {
       std::cout << "Error caught: " << e.what() << std::endl;
   }

   // Test NegativeSeriesComputer
   std::cout << "\nTesting NegativeSeriesComputer...\n";
   try {
       NegativeSeriesComputer nsc(reciprocal);

       // Define test values
       int val1 = 200;
       int val2 = 300;
       int val3 = 400;

       // First computation
       auto start = std::chrono::high_resolution_clock::now();
       double result1 = nsc.compute(val1);
       auto end = std::chrono::high_resolution_clock::now();
       std::chrono::duration<double, std::milli> duration1 = end - start;
       std::cout << "NegativeSeriesComputer compute " << val1 << " " << result1
                 << " Time: " << duration1.count() << " ms" << std::endl;

       // Second computation
       start = std::chrono::high_resolution_clock::now();
       double result2 = nsc.compute(val2);
       end = std::chrono::high_resolution_clock::now();
       std::chrono::duration<double, std::milli> duration2 = end - start;
       std::cout << "NegativeSeriesComputer compute " << val2 << " " << result2
                 << " Time: " << duration2.count() << " ms" << std::endl;

       std::cout << "Attempting compute(-1)..." << std::endl;
       start = std::chrono::high_resolution_clock::now();
       nsc.compute(-1);
       end = std::chrono::high_resolution_clock::now();
       std::chrono::duration<double, std::milli> duration4 = end - start;
       std::cout << "Time: " << duration4.count() << " ms" << std::endl;
   }
   catch (const std::invalid_argument& e) {
       std::cout << "Error caught: " << e.what() << std::endl;
   }

   return 0;
}