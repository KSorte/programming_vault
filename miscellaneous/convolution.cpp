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
    int max_DX;
    int min_DX;
    int max_Dy;
    int min_Dy;
};

class Convolution {
public:
    Convolution() {
        // TODO(KSorte):
        // Create a random matrix M here. Currently constant.
        // Should take in number of rows and columns too from cin.
        matrix_to_convolve = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };
    }

    ~Convolution() {

    }

    ConvolutionResult convolve_with_constant_filter_K(const const std::vector<std::vector<unsigned char>> M) {
        ConvolutionResult convolution_result;

        // for ()
    }

private:

    std::vector<std::vector<int>> matrix_to_convolve;
};