#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

/*
    Leetcode 695 Max Area of Island.
    An approach similar to Leetcode 200 Number of Islands. Refer 200.
*/

class Solution {
public:
    /**
     * @brief Calculate maximum area of island on grid.
     * @param grid std::vector<std::vector<int>> with integer 1 and 0 for land and water.
     * @returns Maximum area of island on the grid.
     */
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {

        int max_island_area = 0;

        if (grid.empty()) {
            // Empty grid.
            return 0;
        }

        int grid_width = grid[0].size() - 1;
        int grid_height = grid.size() - 1;

        for (int row = 0; row <= grid_height; row ++) {
            for (int col = 0; col <= grid_width; col++) {
                if (grid[row][col] == 1) {
                    // Land fall.
                    int island_area = bfs(grid, row, col, grid_width, grid_height);
                    max_island_area = std::max(island_area, max_island_area);
                }
            }
        }
        return max_island_area;
    }

private:
    /**
     * @brief Breadth First Search from a grid cell marked 1 to the rest of the island.
     * Marks 2 for all contigious cells including itself and calculates area of island.
     * @param grid std::vector<std::vector<int>>  with characters 1 and 0 for land and water.
     * @param row Integer row number.
     * @param col Integer index on the row given by row number.
     * @param width Integer width of the grid.
     * @param height Integer height of the grid (number of rows - 1.)
     * @returns Integer area of island.
     */
    int bfs(std::vector<std::vector<int>>& grid,
    int row, int col,
    int width, int height) {
        // Area of current island
        int area_of_island = 0;

        std::queue<std::pair<int, int> > bfs_queue;

        // Add current node to queue and increment island area.
        bfs_queue.push({row, col}); area_of_island ++;

        // Mark the grid cell as visited with 2.
        grid[row][col] = 2;

        while (bfs_queue.size() > 0) {
            auto cell = bfs_queue.front();
            bfs_queue.pop();

            // Current coordinates.
            int current_row = cell.first;
            int current_col = cell.second;

            // Get neighbors
            // r + 1, c
            if (current_row + 1 <= height && grid[current_row + 1][current_col] == 1) {
                grid[current_row + 1][current_col] = 2;
                bfs_queue.push({current_row + 1, current_col});
                area_of_island ++;
            }

            // r, c + 1
            if (current_col + 1 <= width && grid[current_row][current_col + 1] == 1) {
                grid[current_row][current_col + 1] = 2;
                bfs_queue.push({current_row, current_col + 1});
                area_of_island ++;
            }

            // r - 1, c
            if (current_row - 1 >= 0 && grid[current_row - 1][current_col] == 1) {
                grid[current_row - 1][current_col] = 2;
                bfs_queue.push({current_row - 1, current_col});
                area_of_island ++;
            }

            // r, c - 1
            if (current_col - 1 >=0 && grid[current_row][current_col - 1] == 1) {
                grid[current_row][current_col - 1] = 2;
                bfs_queue.push({current_row, current_col - 1});
                area_of_island ++;
            }
        }
        return area_of_island;
    }

};