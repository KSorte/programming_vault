#include <chrono>
#include <iostream>
#include <random>
#include <vector>

/*
Author: Kaushal Atul Sorte
Email: sorte.k@northeastern.edu
Compile with:
g++ -std=c++17 -O2 -Wall -Wextra -o convolution /filepath/convolution.cpp

Assumptions, Considerations and Design Decisions:
1. Convolution mathematically results into a matrix larger than the original.
Here, Dx and Dy are considered to be of the same size.
Thus, while computation on the boundaries, when the algorithm encounters invalid indices, those values are simply not
considered in the computation.

Since this is a convolution, the filter is flipped around (as opposed to correlation).

2. A Convolution Result struct is written to package all the deliverables into an object.

3. Since the filter K is a constant, it is not taken as an input, rather the logic implicitly
implements convolution by filter K = [-1, 0, 1].
This implementation is not designed for expansion or modularity.

4. Unsigned integer is used everywhere as per the question requirement.
This means that negative values wrap around to 255 and downwards from there.

5. std::mt19937(since C++11) is used for randomly populating a matrix.
This is chosen for its speed and is based on the Mersenne twister algorithm.
This article is taken as a reference:
https://medium.com/@odarbelaeze/how-competitive-are-c-standard-random-number-generators-f3de98d973f0#:~:text=As%20described%20in%20the%20stack,this%20version%20of%20the%20standard

6. C++ Chrono class is used for calculating compute times for row wise and column wise computations.

7. Display of matrices is optional.
*/

// Struct for packaging the convolution result.
struct ConvolutionResult {
    // Row wise convolution matrix.
    std::vector<std::vector<unsigned char>> Dx;

    // Column wise convolution matrix.
    std::vector<std::vector<unsigned char>> Dy;

    // Maimum and minimum values in convolution matrices.
    int max_Dx;
    int min_Dx;
    int max_Dy;
    int min_Dy;

    /**
     * @brief  Implicit default constructor.
     */
    ConvolutionResult () {}

    /**
     * @brief Constructor to resize Dx and Dy and initializing max-min values in
     * Dx and Dy.
     * @param rows Int number of rows.
     * @param columns Int number of columns.
     */
    ConvolutionResult(int rows, int columns) :
    Dx(rows, std::vector<unsigned char>(columns, 0)),
    Dy(rows, std::vector<unsigned char>(columns, 0)) {

        // Set default maximum and minimum values.
        max_Dx = std::numeric_limits<unsigned char>::min();
        max_Dy = std::numeric_limits<unsigned char>::min();
        min_Dx = std::numeric_limits<unsigned char>::max();
        min_Dy = std::numeric_limits<unsigned char>::max();
    };
};

class Convolution {
public:
    Convolution(int num_rows, int num_columns) :
        rows(num_rows),
        columns(num_columns)
    {
        // Resize matrix to convolve.
        matrix_to_convolve.resize(rows);
        for (auto & row: matrix_to_convolve) {
            row.resize(columns, 0);
        }

        randomly_populate_matrix();

        // Initialize result object.
        result = ConvolutionResult(rows, columns);
    }

    /**
     * @brief Destructor.
     */
    ~Convolution() {}

    /**
     * @brief Convolve matrix along rows using constant filter K [-1, 0, 1].
     */
    void convolve_rows_with_constant_filter_K() {
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < columns; j ++) {
                // Convolve row-wise with constant filter K = [-1, 0, 1].
                // Convolution with K handled implicitly in the logic.
                if (j - 1 >= 0) {
                    // if the pixel in previous column within matrix limits.
                    // Ignore if not within bounds.
                    result.Dx[i][j] += matrix_to_convolve[i][j-1];
                }

                if (j + 1 < columns) {
                // if the pixel in next column within matrix limits.
                // Ignore if not within bounds.
                    result.Dx[i][j] -= matrix_to_convolve[i][j+1];
                }

                // Update maximum in Dx.
                if (result.Dx[i][j] > result.max_Dx) {
                    result.max_Dx = result.Dx[i][j];
                }

                // Update minimum in Dy.
                if (result.Dx[i][j] < result.min_Dx) {
                    result.min_Dx = result.Dx[i][j];
                }
            }
        }
    }

    /**
     * @brief Convolve matrix along columns using constant filter K [-1, 0, 1].
     */
    void convolve_columns_with_constant_filter_K() {
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < columns; j ++) {
                // Convolve column-wise with constant filter K = [-1, 0, 1].
                // Convolution with K handled implicitly in the logic.
                if (i - 1 >= 0) {
                // if the pixel in previous row within matrix limits.
                // Ignore if not within bounds.
                    result.Dy[i][j] += matrix_to_convolve[i - 1][j];
                }

                if (i + 1 < rows) {
                // if the pixel in next row within matrix limits.
                // Ignore if not within bounds.
                    result.Dy[i][j] -= matrix_to_convolve[i + 1][j];
                }

                // Update maximum in Dy.
                if (result.Dy[i][j] > result.max_Dy) {
                    result.max_Dy = result.Dy[i][j];
                }

                // Update minimum in Dy.
                if (result.Dy[i][j] < result.min_Dy) {
                    result.min_Dy = result.Dy[i][j];
                }
            }
        }
    }

    // Convolution result object.
    ConvolutionResult result;

    // Matrix to convolve.
    std::vector<std::vector<int>> matrix_to_convolve;

private:
    /**
     * @brief Randomly populate matrix.
     */
    void randomly_populate_matrix() {
        // Obtain a random number from hardware
        std::random_device rd;

        // Seed the 64-bit Mersenne Twister engine
        std::mt19937_64 engine(rd());

        // Set limits of unsigned char datatype as distribution limits.
        std::uniform_int_distribution<unsigned char> dist(
            std::numeric_limits<unsigned char>::min(),
            std::numeric_limits<unsigned char>::max());

        // Randomly populate matrix.
        for (auto & row : matrix_to_convolve) {
            for (auto & element : row) {
                element = dist(engine);
            }
        }
    }

    // Rows and colummns received from command line.
    int rows;
    int columns;
};

int main() {

    // Get rows and columns from the command line.
    std::cout<<"Enter rows."<<'\n';
    int number_of_rows;
    std::cin>>number_of_rows;

    std::cout<<"Enter columns."<<'\n';
    int number_of_cols;
    std::cin>>number_of_cols;

    // Initialize convolution object.
    Convolution convolve = Convolution(number_of_rows, number_of_cols);

    // Row convolution and its computation time.
    auto start_row_convolve = std::chrono::high_resolution_clock::now();
    convolve.convolve_rows_with_constant_filter_K();
    auto end_row_convolve = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_x = end_row_convolve - start_row_convolve;
    std::cout << "Row-wise convolution time: " << duration_x.count() << " seconds" << '\n';

    // Column convolutio and its computation time.
    auto start_col_convolve = std::chrono::high_resolution_clock::now();
    convolve.convolve_columns_with_constant_filter_K();
    auto end_col_convolve = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_y = end_col_convolve - start_col_convolve;
    std::cout << "Column-wise convolution time: " << duration_y.count() << " seconds" << std::endl;

    // Print maximum and minimum in Dx and Dy.
    std::cout<<'\n';
    std::cout<<"Dx matrix max = "<<convolve.result.max_Dx<<'\n';
    std::cout<<"Dx matrix min = "<<convolve.result.min_Dx<<'\n';
    std::cout<<"Dy matrix max = "<<convolve.result.max_Dy<<'\n';
    std::cout<<"Dy matrix min = "<<convolve.result.min_Dy<<'\n';

    std::cout<<"Diplay matrices? (y/n)"<<'\n';

    std::string display_matrices;
    std::cin>>display_matrices;

    if (display_matrices == "y") {
        // Print all three matrices.
        std::cout<<'\n';
        std::cout<<"original matrix "<<'\n';
        for (const auto& row : convolve.matrix_to_convolve) {
            for (int element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }

        std::cout<<'\n';
        std::cout<<"Dx matrix "<<'\n';
        for (const auto& row : convolve.result.Dx) {
            for (int element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }

        std::cout<<'\n';
        std::cout<<"Dy matrix "<<'\n';
        for (const auto& row : convolve.result.Dy) {
            for (int element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }
}

/*
 If conditions in for loops are very bad in this case as they break CPU cache pipelines. It doesn’t matter in typical general software, however with numerical repeated computes, how fast you can crunch data, is a function of how filled your CPU cache lines are. An ideal way would have been to unroll these boundary conditions explicitly before the main [1,rows-1]x[1, cols-1] for loop.
- Vector of vector allocates each row in a different memory location, this breaks CPU cache lines for every row access. A much faster way (esp for bigger rows and cols values) is to allocate one vector but then view it as [i*cols + j] indices.
- Somewhat surprisingly, your input matrix is int typed but Dx/Dy are unsigned char. Please note that if input data is initialized to numbers in range [0, 255], the difference would be the range [-255, 255] and it can not fit in unsigned char. You should have used int16 for Dx/Dy.
*/