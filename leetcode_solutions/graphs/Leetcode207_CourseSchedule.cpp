#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/*
    Leetcode 207 Course Schedule
    There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
    You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must
    take course bi first if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
    Return true if you can finish all courses. Otherwise, return false.

    Algorithm:
    Use DFS. Can also be solved using BFS which becomes a version of Topological Sort.
    1. Create an unordered map to represent a Directed Acyclic Graph (DAG).
    2. Create an unordered set to hold all courses on a path on DFS.
    2. Call bool DFS(dag, set, 0th element)

    DFS(dag, set, ith) {
        if ith present in set:
            return false; // Cycle present
        add ith to set.
        // Call DFS on all neighbors.
        DFS(dag, set, n1);
        DFS(dag, set, n2);
        .
        .
        DFS(dag, set, nn);
        remove ith from the set.
        return DFS1 && DFS2 &&..DFSn
    }

*/

class Solution {
public:
    /**
     * @brief Determine whether a list of courses with prerequisite relations can be undertaken without circular dependencies.
     * @param numCourses Int number of courses.
     * @param prerequisites Vector of int vectors determining prerequisite relations between courses.
     * @returns Boolean indicating whether the curriculum can be finished.
     */
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        // Create DAG.
        createDAG(prerequisites);
        std::unordered_set<int> courses_on_dfs_path;

        // List of flags denoting feasibility of all courses.
        std::vector<bool> is_course_feasible(numCourses);

        for (int i = 0; i < numCourses; i++) {
            if (!depth_first_search(is_course_feasible, courses_on_dfs_path, i)) {
                return false;
            }
        }
        return true;
    }

private:
    // Map to store directed acyclic graph.
    std::unordered_map<int, std::vector<int>> directed_acyclic_graph;

    /**
     * @brief Create a DAG out of list of prerequisites.
     * @param prerequisites Vector of int vectors determining prerequisite relations between courses.
     */
    void createDAG(std::vector<std::vector<int>>& prerequisites) {
        for (const auto & prerequisite : prerequisites) {
            directed_acyclic_graph[prerequisite[0]].emplace_back(prerequisite[1]);
        }
    }

    /**
     * @brief Implement DFS to determine if a particular course is doable or not.
     * A DFS path needs to be acyclic for the course to be doable.
     * @param is_course_feasible Vector of bools storing feasibility flags for each course.
     * @param courses_on_dfs_path Vector of ints denoting courses on a particular DFS path.
     * @param course_index Int course index to check for feasibility.
     * @returns Boolean indicating whether a course is feasible or not.
     */
    bool depth_first_search(
        std::vector<bool> &is_course_feasible,
        std::unordered_set<int> &courses_on_dfs_path,
        int course_index) {

        // Check if course present in set.
        if (courses_on_dfs_path.find(course_index) != courses_on_dfs_path.end()) {
            // Course exists on the path, cycle detected
            return false;
        }

        if (directed_acyclic_graph[course_index].empty()) {
            // Course with no prerequisite
            is_course_feasible[course_index] = true;
            return true;
        }

        if (is_course_feasible[course_index]) {
            // Course is doable found out previously.
            return true;
        }

        // Add to path.
        courses_on_dfs_path.insert(course_index);

        for (const auto & neighbor : directed_acyclic_graph[course_index]) {
            if (!depth_first_search(is_course_feasible, courses_on_dfs_path, neighbor)) {
                return false;
            }
        }

        // Backtrack.
        courses_on_dfs_path.erase(course_index);
        // Declare feasible.
        is_course_feasible[course_index] = true;
        return true;
    }
};

// How did I make it efficient?
/**
 * Create the is_course_feasible vector to store flags whether a course is feasible or not.
 Previously, to mark that a course is feasible, its prerequisites were emptied from the dag, which is inefficient.
 * Use .find on course on dfs path set.
 Previously, std::find function which is used on sequential containers was used which is naturally slow.
 * These two checks were added which minimized the the operations for leaf nodes or courses with no prerequisites.
    if (directed_acyclic_graph[course_index].empty()) {
        // Course with no prerequisite
        is_course_feasible[course_index] = true;
        return true;
    }

    if (is_course_feasible[course_index]) {
        // Course is doable found out previously.
        return true;
    }
 * Creating an unordered map pointing from int to an unordered set.(Below).
 Erasing an element from vector is slower than from an unordered set. This would make it faster.
 (This is slower for some reason.)
 */

// Using unordered set to store neighbors instead of vectors.
// class Solution {
// public:
//     bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
//         createDAG(prerequisites);
//         std::unordered_set<int> courses_on_dfs_path;

//         std::vector<bool> is_course_doable(numCourses);

//         for (int i = 0; i < numCourses; i++) {
//             if (!depth_first_search(is_course_doable, courses_on_dfs_path, i)) {
//                 return false;
//             }
//         }
//         return true;
//     }

// private:
//     // std::unordered_map<int, std::vector<int>> directed_acyclic_graph;
//     std::unordered_map<int, std::unordered_set<int>> directed_acyclic_graph;

//     void createDAG(std::vector<std::vector<int>>& prerequisites) {
//         for (const auto & prerequisite : prerequisites) {
//             // directed_acyclic_graph[prerequisite[0]].emplace_back(prerequisite[1]);
//             directed_acyclic_graph[prerequisite[0]].insert(prerequisite[1]);
//         }
//     }

//     bool depth_first_search(
//         std::vector<bool> &is_course_doable,
//         std::unordered_set<int> &courses_on_dfs_path,
//         int course_index) {

//         // Check if course present in set.
//         if (courses_on_dfs_path.find(course_index) != courses_on_dfs_path.end()) {
//             // Course exists on the path, cycle detected
//             return false;
//         }

//         if (directed_acyclic_graph[course_index].empty()) {
//             // Course with no prerequisite
//             is_course_doable[course_index] = true;
//             return true;
//         }

//         if (is_course_doable[course_index]) {
//             return true;
//         }

//         courses_on_dfs_path.insert(course_index);

//         for (const auto & neighbor : directed_acyclic_graph[course_index]) {
//             if (!depth_first_search(is_course_doable, courses_on_dfs_path, neighbor)) {
//                 return false;
//             }
//         }

//         courses_on_dfs_path.erase(course_index);
//         is_course_doable[course_index] = true;
//         return true;
//     }
// };
