#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>

/*

Create character matrix. First let it be a constant. To help debug.
(Later turn it into a randomized matrix.)

Initialize filter K as a vector of ints. (You may not need this, we can leverage K in logic).

unsigned integer, negative value wrap around.
*/

struct ConvolutionResult {
    std::vector<std::vector<unsigned char>> Dx;
    std::vector<std::vector<unsigned char>> Dy;
    int max_Dx;
    int min_Dx;
    int max_Dy;
    int min_Dy;

    ConvolutionResult () {}

    ConvolutionResult(int rows, int columns) : Dx(rows, std::vector<unsigned char>(columns, 0)),
          Dy(rows, std::vector<unsigned char>(columns, 0)) {
            max_Dx = 0;
            max_Dy = 0;
            min_Dx = 255;
            min_Dy = 255;
    };
};

class Convolution {
public:
    Convolution(int num_rows, int num_columns) :
        rows(num_rows),
        columns(num_columns)
    {
        matrix_to_convolve.resize(rows);
        for (auto & row: matrix_to_convolve) {
            row.resize(columns, 0);
        }

        // Seed the random number generator with the current time
        std::srand(static_cast<unsigned int>(std::time(0)));
        for (auto & row : matrix_to_convolve) {
            for (auto & element : row) {
                element = static_cast<unsigned char>(std::rand() % 256);
            }
        }

        result = ConvolutionResult(rows, columns);
    }

    ~Convolution() {

    }

    void convolve_rows_with_constant_filter_K() {
        unsigned char max_Dx, min_Dx;
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < columns; j ++) {

                // Handling row boundaries.
                // Convolution with constant Filter K implicit in this implementation.
                if (j - 1 >= 0) {
                    result.Dx[i][j] += matrix_to_convolve[i][j-1];
                }

                if (j + 1 < columns) {
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

    void convolve_columns_with_constant_filter_K() {
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < columns; j ++) {

                // Handling column boundaries.
                // Convolution with constant Filter K implicit in this implementation.
                if (i - 1 >= 0) {
                    result.Dy[i][j] += matrix_to_convolve[i - 1][j];
                }

                if (i + 1 < rows) {
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

    ConvolutionResult result;
    std::vector<std::vector<int>> matrix_to_convolve;
private:
    int rows;
    int columns;
};

int main() {

    std::cout<<"Enter the number of rows for the matrix to convolve."<<'\n';
    int number_of_rows;
    std::cin>>number_of_rows;

    std::cout<<"Enter the number of columns for the matrix to convolve."<<'\n';
    int number_of_cols;
    std::cin>>number_of_cols;

    Convolution convolve = Convolution(number_of_rows, number_of_cols);

    auto start_row_convolve = std::chrono::high_resolution_clock::now();
    convolve.convolve_rows_with_constant_filter_K();
    auto end_row_convolve = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_x = end_row_convolve - start_row_convolve;
    std::cout << "Row-wise convolution time: " << duration_x.count() << " seconds" << '\n';

    auto start_col_convolve = std::chrono::high_resolution_clock::now();
    convolve.convolve_columns_with_constant_filter_K();
    auto end_col_convolve = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_y = end_col_convolve - start_col_convolve;
    std::cout << "Column-wise convolution time: " << duration_y.count() << " seconds" << std::endl;

    std::cout<<"original matrix "<<'\n';
    for (const auto& row : convolve.matrix_to_convolve) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    std::cout<<"Dx matrix "<<'\n';
    for (const auto& row : convolve.result.Dx) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    std::cout<<"Dx matrix max = "<<convolve.result.max_Dx<<'\n';
    std::cout<<"Dx matrix min = "<<convolve.result.min_Dx<<'\n';

    std::cout<<"Dy matrix "<<'\n';
    for (const auto& row : convolve.result.Dy) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    std::cout<<"Dy matrix max = "<<convolve.result.max_Dy<<'\n';
    std::cout<<"Dy matrix min = "<<convolve.result.min_Dy<<'\n';

}