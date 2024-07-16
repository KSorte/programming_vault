#include <queue>
#include <utility>
#include <vector>

/*
Leetcode 200 Number of Islands.
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water),
return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water.

Algorithm:
- Traverse through the grid row by row.
- Once you hit a 1, do BFS on it and mark all the contigious 1's to it as visited
and increment num islands by 1. We have effectively marked this island as visited.
- In the subsequent row-by-row traversal, BFS is only triggered if it is not already in visited.

There are TWO types of traversals in this algorithm.
First is the methodic row-by-row traversal in search of islands
Second is the BFS traversal that explores and marks the island once one of its pixels is found.\

NOTE: DFS is also a good method to proceed here. We need to explore the whole island,
and both DFS and BFS work.
Instead of a visited array, we can mark the cells as '0' to mark as visited.

for r in row:
    for c in col:
        if cell == 1
            dfs or bfs
            num islands ++;
return
*/

class Solution {
public:
    /**
     * @brief Calculate number of islands on grid.
     * @param grid std::vector<std::vector<char>> with characters '1' and '0' for land and water.
     * @returns Integer number of islands.
     */
    int numIslands(std::vector<std::vector<char>>& grid) {
        int number_of_islands = 0;

        if (grid.empty()) {
            // Empty grid.
            return 0;
        }

        int grid_width = grid[0].size() - 1;
        int grid_height = grid.size() - 1;

        for (int row = 0; row <= grid_height; row ++) {
            for (int col = 0; col <= grid_width; col++) {
                if (grid[row][col] == '1') {
                    // Land fall.
                    // bfs(grid, row, col, grid_width, grid_height);
                    dfs(grid, row, col, grid_width, grid_height);
                    number_of_islands ++;
                }
            }
        }
        return number_of_islands;
    }

private:
    /**
     * @brief Breadth First Search from a grid cell marked 1 to the rest of the island.
     * Marks 2 for all contigious cells including itself.
     * @param grid std::vector<std::vector<char>> with characters '1' and '0' for land and water.
     * @param row Integer row number.
     * @param col Integer index on the row given by row number.
     * @param width Integer width of the grid.
     * @param height Integer height of the grid (number of rows - 1.)
     */
    void bfs(std::vector<std::vector<char>>& grid,
    int row, int col,
    int width, int height) {
        std::queue<std::pair<int, int> > bfs_queue;
        bfs_queue.push({row, col});

        // Mark the grid cell as visited with '2'.
        grid[row][col] = '2';

        while (bfs_queue.size() > 0) {
            auto cell = bfs_queue.front();
            bfs_queue.pop();

            // Current coordinates.
            int current_row = cell.first;
            int current_col = cell.second;

            // Get neighbors
            // r + 1, c
            if (current_row + 1 <= height && grid[current_row + 1][current_col] == '1') {
                grid[current_row + 1][current_col] = '2';
                bfs_queue.push({current_row + 1, current_col});
            }

            // r, c + 1
            if (current_col + 1 <= width && grid[current_row][current_col + 1] == '1') {
                grid[current_row][current_col + 1] = '2';
                bfs_queue.push({current_row, current_col + 1});
            }

            // r - 1, c
            if (current_row - 1 >= 0 && grid[current_row - 1][current_col] == '1') {
                grid[current_row - 1][current_col] = '2';
                bfs_queue.push({current_row - 1, current_col});
            }

            // r, c - 1
            if (current_col - 1 >=0 && grid[current_row][current_col - 1] == '1') {
                grid[current_row][current_col - 1] = '2';
                bfs_queue.push({current_row, current_col - 1});
            }
        }
    }

    /**
     * @brief Recursive Depth First Search from a grid cell marked 1 to the rest of the island.
     * Marks 2 for all contigious cells including itself.
     * @param grid std::vector<std::vector<char>> with characters '1' and '0' for land and water.
     * @param row Integer row number.
     * @param col Integer index on the row given by row number.
     * @param width Integer width of the grid.
     * @param height Integer height of the grid (number of rows - 1.)
     */
    void dfs(std::vector<std::vector<char>>& grid,
    int row, int col,
    int width, int height) {

        // Cell Validity.
        if (row > height || row < 0 ||
            col > width || col < 0 ||
            grid[row][col] != '1') {
                // Invalid cell
                return;
            }

        grid[row][col] = '2';

        // Run Depth First Search on neighbors.
        dfs(grid, row + 1, col, width, height);
        dfs(grid, row, col + 1, width, height);
        dfs(grid, row - 1, col, width, height);
        dfs(grid, row, col - 1, width, height);
    }
};