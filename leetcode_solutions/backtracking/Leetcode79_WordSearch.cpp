#include <string>
#include <vector>

/*
    Leetcode 79 Word Search
    Given an m x n grid of characters board and a string word, return true if word exists in the grid.
    The word can be constructed from letters of sequentially adjacent cells,
    where adjacent cells are horizontally or vertically neighboring.
    The same letter cell may not be used more than once.

    Algorithm:
    DFS(r, c, i, set) :
        // Reached the end of the word.
        if (i == len(word)) {
            return true;
        }

        // r,c not equal to the ith letter.
        if ((r,c) != word[i]) {
            return false;
        }

        mark r, c before recursive DFS on child nodes.
        if(DFS(neighbour_1, i + 1) || DFS(neighbour_2, i + 1)) {
          return true;}

        // True essence of backtracking. In normal DFS you won't unmark after a possibility is
        explored.
        unmark r, c

*/


class Solution {
public:
    /**
     * @brief Determine whether the word exists in the grid.
     * @param board Grid of characters.
     * @param word Word to search.
     * @returns Boolean indicating whether the word exists.
     */
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        if (board.empty()) {
            return false;
        }

        int max_rows = board.size();
        int max_cols = board[0].size();
        int word_length = word.size();

        for (int i = 0; i < max_rows; i++) {
            for (int j = 0; j < max_cols; j++) {
                if (depth_first_search(board, word, 0, i, j, max_rows, max_cols, word_length)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    /**
     * @brief Depth first search at a grid cell with backtracking.
     * @param board Grid of characters.
     * @param word Word to search.
     * @param index Int index, the char at which needs to be queried.
     * @param row Int row index of current grid cell.
     * @param col Int col index of current grid cell.
     * @param max_row Int Number of rows
     * @param max_col Int Number of columns.
     * @param word_length Int Word size.
     * @returns Boolean indicating whether the word exists in the search.
     */
    bool depth_first_search(
        std::vector<std::vector<char>>& board,
        std::string &word,
        int index,
        int row, int col, int max_row, int max_col, int word_length) {

        if (index >= word_length) {
            return true;
        }

        // Current cell out of bounds.
        if (row >= max_row ||
            row < 0 ||
            col >= max_col ||
            col < 0) {
            return false;
        }

        // Current letter not equal to next letter in word
        if (board[row][col] != word[index]) {
            return false;
        }

        // Mark.
        board[row][col] = '#';

        // Search in all children
        if (depth_first_search(board, word, index + 1, row + 1, col, max_row, max_col, word_length) ||
            depth_first_search(board, word, index + 1, row, col + 1, max_row, max_col, word_length) ||
            depth_first_search(board, word, index + 1, row - 1, col, max_row, max_col, word_length) ||
            depth_first_search(board, word, index + 1, row, col - 1, max_row, max_col, word_length)) {
            return true;
        }

        // Unmark.
        board[row][col] = word[index];
        return false;
    }
};