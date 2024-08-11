#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

/*
    Author: Kaushal Atul Sorte
    Email: sorte.k@northeastern.edu
    Compile with:
    g++ -std=c++17 -O2 -Wall -Wextra -o convolution_optimized /filepath/convolution_optimized.cpp

    Assumptions, Considerations and Design Decisions:
    1. Convolution mathematically results into a matrix larger than the original.
    Here, Dx and Dy are considered to be of the same size.
    Boundary pixels will not be convolved at all and our excluded.
    Potentially a wrapping can be done.

    2. Since this is a convolution, the filter is flipped around (as opposed to correlation).

    3. A Convolution Result struct is written to package all the deliverables into an object.

    4. Since the filter K is a constant, it is not taken as an input, rather the logic implicitly
    implements convolution by filter K = [-1, 0, 1].
    This implementation is not designed for expansion or modularity.

    5. Unsigned char is used for input matrix. To prevent the wrapping of values, int16_t is used for the output.

    6. std::mt19937(since C++11) is used for randomly populating a matrix.
    This is chosen for its speed and is based on the Mersenne twister algorithm.
    This article is taken as a reference:
    https://medium.com/@odarbelaeze/how-competitive-are-c-standard-random-number-generators-f3de98d973f0#:~:text=As%20described%20in%20the%20stack,this%20version%20of%20the%20standard

    7. C++ Chrono class is used for calculating compute times for row wise and column wise computations.

    8. Display of matrices is optional.

    9. Calculation of max and min for Dx Dy is moved out of the convolution function itself, making these function efficient.
*/

// Struct for packaging the convolution result.
struct ConvolutionResult {
    // Row wise convolution matrix.
    std::vector<int16_t> Dx;

    // Column wise convolution matrix.
    std::vector<int16_t> Dy;

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
    Dx(rows*columns, 0), Dy(rows*columns, 0) {};
};

class Convolution {
public:
    Convolution(int num_rows, int num_columns) :
        rows(num_rows), columns(num_columns),
        matrix_to_convolve(num_rows*num_columns, 0)
    {
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
        for (int i = 1; i < rows - 1; i ++) {
            for (int j = 1; j < columns - 1; j ++) {
                // Convolve row-wise with constant filter K = [-1, 0, 1].
                // Convolution with K handled implicitly in the logic.
                result.Dx[i*columns + j] =
                    matrix_to_convolve[i*columns + j - 1] - matrix_to_convolve[i*columns + j + 1];
            }
        }
    }

    /**
     * @brief Convolve matrix along columns using constant filter K [-1, 0, 1].
     */
    void convolve_columns_with_constant_filter_K() {
        for (int i = 1; i < rows - 1; i ++) {
            for (int j = 1; j < columns -1; j ++) {
                // Convolve column-wise with constant filter K = [-1, 0, 1].
                // Convolution with K handled implicitly in the logic.
                result.Dy[i*columns + j] =
                    matrix_to_convolve[(i+1)*columns + j] - matrix_to_convolve[(i-1)*columns + j];
            }
        }
    }

    // Convolution result object.
    ConvolutionResult result;

    // Matrix to convolve.
    std::vector<unsigned char> matrix_to_convolve;

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
        for (auto & element : matrix_to_convolve) {
            element = dist(engine);
        }
    }

    // Rows and colummns received from command line.
    int rows;
    int columns;
};

// Helper Functions.
// TODO (KSorte): These can be templatized.
void print_unsigned_char_matrix(const std::vector<unsigned char>& row_major_matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // Calculate the index for row-major order
            int index = i * columns + j;
            std::cout << static_cast<int>(row_major_matrix[index]) << " ";
        }
        std::cout << std::endl;
    }
}

void print_int16_t_matrix(const std::vector<int16_t>& row_major_matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // Calculate the index for row-major order
            int index = i * columns + j;
            std::cout << static_cast<int>(row_major_matrix[index]) << " ";
        }
        std::cout << std::endl;
    }
}

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
    auto Dx_max = std::max_element(convolve.result.Dx.begin(), convolve.result.Dx.end());
    auto Dx_min = std::min_element(convolve.result.Dx.begin(), convolve.result.Dx.end());
    auto Dy_max = std::max_element(convolve.result.Dy.begin(), convolve.result.Dy.end());
    auto Dy_min = std::min_element(convolve.result.Dy.begin(), convolve.result.Dy.end());
    std::cout<<"Dx matrix max = "<<*Dx_max<<'\n';
    std::cout<<"Dx matrix min = "<<*Dx_min<<'\n';
    std::cout<<"Dy matrix max = "<<*Dy_max<<'\n';
    std::cout<<"Dy matrix min = "<<*Dy_min<<'\n';

    std::cout<<'\n';
    std::cout<<"Diplay matrices? (y/n)"<<'\n';

    std::string display_matrices;
    std::cin>>display_matrices;

    if (display_matrices == "y") {
        // Print all three matrices.
        std::cout<<'\n';
        std::cout<<"original matrix "<<'\n';
        print_unsigned_char_matrix(convolve.matrix_to_convolve, number_of_rows, number_of_cols);

        std::cout<<'\n';
        std::cout<<"Dx matrix "<<'\n';
        print_int16_t_matrix(convolve.result.Dx, number_of_rows, number_of_cols);

        std::cout<<'\n';
        std::cout<<"Dy matrix "<<'\n';
        print_int16_t_matrix(convolve.result.Dy, number_of_rows, number_of_cols);
    }
}