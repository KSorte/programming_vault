#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/**
 * @brief Determine if a 9 x 9 Sudoku board is valid.
 * Only the filled cells need to be validated according to the following rules:
 * Each row must contain the digits 1-9 without repetition.
 * Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
 * Link: https://leetcode.com/problems/valid-sudoku/description/
 *
 * Steps:
 * This is a straightforward brute force solution that combs through all the numbers one by one.
 *
 * Unordered maps mapping each row, col and box to an unordered set containing numbers.
 * A double for loop goes through rows(i) and cols (j).
 * While checking a number at (i, j), if the number already exists in the ith row, or the jth col
 * or in the box, then return false.
 * If none of the above, then add the number to the ith row, jth col and current box in their resp
 * sets in the respective hash maps.
 *
 * Box index is defined from 0 to 8 and is calculated from row and col indices.
 * Unordered (hash) maps and Unordered (hash) sets are used which make the look up operation
 * and the search operations within sets O(1) time complexity.
 *
 * @param board Vector of char vector holding the sudoku board to assess.
 * @returns Boolean indicating whether the sudoku board is valid.
 */

class Solution {
public:

    bool isValidSudoku(std::vector<std::vector<char>>& board) {

        // Create maps to hold numbers in each row, column and box.
        // Row map.
        std::unordered_map<int, std::unordered_set<int>> row_map;
        // Column map.
        std::unordered_map<int, std::unordered_set<int>> column_map;
        // Box map.
        std::unordered_map<int, std::unordered_set<int>> box_map;

        // Populate maps with 9 rows, columns and boxes.
        for (int k = 0; k < 9; ++k) {
            row_map[k] = {};
            column_map[k] = {};
            box_map[k] = {};
        }

        // Iterate over the rows of the sudoku.
        for (int i = 0; i < 9; i++){
            // Iterate over the columns of the sudoku.
            for (int j = 0; j < 9; j++){
                if (board[i][j] == '.') {
                    // Continue if not a number.
                    continue;
                }

                // Extract the number as integer.
                auto num = static_cast<int>(board[i][j] - '0');

                // Check if number exists in row.
                if (row_map[i].find(num) != row_map[i].end()){  // O(1) search
                    // if ith row has the number already, return false.
                    return false;
                }

                // Check if number exists in col.
                if (column_map[j].find(num) != column_map[j].end()){ // O(1) search
                    // if jth column has the number already, return false.
                    return false;
                }

                // Get the current box.
                auto current_box = ((i / 3) * 3) + j / 3;
                // Check if number exists in box.
                if (box_map[current_box].find(num) != box_map[current_box].end()){ // O(1) search
                    // if box has the number already, return false.
                    return false;
                }

                // if element not in ith row, jth col and current box, add element to all three.
                row_map[i].insert(num);
                column_map[j].insert(num);
                box_map[current_box].insert(num);
            }
        }
        return true;
    }
};

/*
This solution even though having comparable time complexity to the previous one actually executes way faster
because I suspect it doesn't have to create maps, sets or insert elements in them. This adds an additional
overhead in the above solution making it slow.

Downside of below is the fixed size of arrays.
Downside of above is that hashtables can be cumbersome for large n.

o(1) lookup of arrays is slightly faster than the same in hash maps in practice.

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        const int cnt = 9;
        bool row[cnt][cnt] = {false};
        bool col[cnt][cnt] = {false};
        bool sub[cnt][cnt] = {false};

        for(int r = 0; r < cnt; ++r){
            for(int c = 0; c < cnt; ++c){
                if(board[r][c] == '.')
                    continue; // if not number pass

                int idx = board[r][c] - '0' - 1; //char to num idx
                int area = (r/3) * 3 + (c/3);

                //if number already exists
                if(row[r][idx] || col[c][idx] || sub[area][idx]){
                    return false;
                }

                row[r][idx] = true;
                col[c][idx] = true;
                sub[area][idx] = true;
            }
        }
        return true;
    }
};

*/

int main() {
    Solution sol;

    // Test case: Valid Sudoku board
    std::vector<std::vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    std::cout << "Is the board valid? " << (sol.isValidSudoku(board) ? "Yes" : "No") << std::endl;

    return 0;
}