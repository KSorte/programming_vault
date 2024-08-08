#include <iostream>
#include <vector>

/*

Create character matrix. First let it be a constant. To help debug.
(Later turn it into a randomized matrix.)

Initialize filter K as a vector of ints. (You may not need this, we can leverage K in logic).
*/

struct ConvolutionResult {
    std::vector<std::vector<unsigned char>> Dx;
    std::vector<std::vector<unsigned char>> Dy;
    int computation_time_Dx;
    int computation_time_Dy;
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
    Convolution() {
        // TODO(KSorte):
        // Create a random matrix M here. Currently constant.
        // Take number of rows and columns too from cin and initialize.
        rows = 3;
        columns = 3;
        matrix_to_convolve = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };

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
private:

    std::vector<std::vector<int>> matrix_to_convolve;
    int rows;
    int columns;
};

int main() {
    Convolution convolve;

    convolve.convolve_rows_with_constant_filter_K();
    convolve.convolve_columns_with_constant_filter_K();

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