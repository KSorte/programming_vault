import time

'''
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
'''

'''
This file hosts the SeriesComputer and NegativeSeriesComputer(derived) to compute the sum for k = 1 to n for a function
f(k). Additionally, tests are included for both classes inside main.
'''
class SeriesComputer():
    def __init__(self, f) -> None:
        """
        Initialize SeriesComputer with a function to compute cumulative sums.

        Parameters:
        ----------
        f : callable
            Function to be summed. Must be callable.
        """
        if not callable(f):
            raise TypeError(f"Constructor argument to {SeriesComputer.__name__} is not a function")

        self.function = f

        # Initialize dictionary to store past calls.
        self.cache = {0:0}

        self.max_cached = 0

    def compute(self, n:int) -> float:
        """
        Compute the cumulative sum of `self.function(k)` up to `n`.

        Parameters:
        ----------
        n : int
            Target index for cumulative sum (must be >= 1).

        Returns:
        -------
        float
            Cumulative sum of `self.function(k)` up to `n`.
        """
        if n < 1:
            raise ValueError("argument to compute should be >= 1")

        cached_sum = self.cache.get(n)
        if cached_sum is not None:
            return cached_sum

        # Get the max cached call till now.
        sum = self.cache.get(self.max_cached)

        # Get result.
        for k in range(self.max_cached + 1, n + 1):
            sum += self.function(k)
            self.cache[k] = sum

        # Update max.
        self.max_cached = n

        return sum

class NegativeSeriesComputer(SeriesComputer):
    def __init__(self, f) -> None:
        super().__init__(f)
        self.function = lambda k: f(-k)

if __name__ == "__main__":
    # I have chosen a function for which f(-x) != f(x)
    f = lambda k: float(1/k**2 - 1/k)

    print("Series Computer Test")
    print("------------------------------------------------")
    try:

        series_com = SeriesComputer(f)

        # Test close values to see the efficacy of caching.
        test_val_1 = 10000
        test_val_2 = 10010


        start_t = time.perf_counter()
        sum = series_com.compute(test_val_1)
        end_t = time.perf_counter()

        print(f"n: {test_val_1}\tsum: {sum:.2f}\ttime: {(end_t - start_t)*1e3:.5f} ms")

        start_t = time.perf_counter()
        sum = series_com.compute(test_val_2)
        end_t = time.perf_counter()

        print(f"n: {test_val_2}\tsum: {sum:.2f}\ttime: {(end_t - start_t)*1e3:.5f} ms")

        print("\nTesting constraints")
        print("------------------------------------------------")
        print("n = -5")
        series_com.compute(-5)
    except ValueError as e:
        print(f"Error caught: {e}")

    print("\nNegative Series Computer Test")
    print("------------------------------------------------")
    try:
        n_series_com = NegativeSeriesComputer(f)
        start_t = time.perf_counter()
        sum = n_series_com.compute(test_val_1)
        end_t = time.perf_counter()

        print(f"n: {test_val_1}\tsum: {sum:.2f}\ttime: {(end_t - start_t)*1e3:.5f} ms")

        start_t = time.perf_counter()
        sum = n_series_com.compute(test_val_2)
        end_t = time.perf_counter()

        print(f"n: {test_val_2}\tsum: {sum:.2f}\ttime: {(end_t - start_t)*1e3:.5f} ms")

        print("\nTesting constraints")
        print("------------------------------------------------")
        print("n = -5")
        n_series_com.compute(-5)

    except ValueError as e:
        print(f"Error caught: {e}")