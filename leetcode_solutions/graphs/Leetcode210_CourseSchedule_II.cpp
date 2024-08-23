#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

/*
    Leetcode 210 Course Schedule II
    There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
    You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course
    bi first if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
    Return the ordering of courses you should take to finish all courses. If there are many valid answers,
    return any of them. If it is impossible to finish all courses, return an empty array

    Algorithm:
    Refer to Leetcode 207 Course Schedule problem, the algorithm is largely based on that one.
    DFS is used to explore the entire prerequisite dependency graph.
    If a course has no prerequisites, or if the prerequisites are feasible (DFS yields positive for the neighbors)
    the course is marked true.

    When it is marked true, add it to the array at to be outputted.
    The array thus created is the topological sort of the dependency graph.
*/

class Solution {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        is_course_feasible.resize(numCourses);
        // Create DAG.
        createDAG(prerequisites);

        // Apply DFS on each course.
        for (int i = 0; i < numCourses; i++) {
            if (!depth_first_search(i)
            ) {
                topological_sort.clear();
                return topological_sort;
            }
        }
        return topological_sort;
    }

private:
    // Map to store directed acyclic graph.
    std::unordered_map<int, std::vector<int>> directed_acyclic_graph;

    // Vector of flags to store the feasibility of each course.
    std::vector<bool> is_course_feasible;

    // unordered_set to store the courses on a particular dfs path.
    std::unordered_set<int> courses_on_dfs_path;

    // Vector to store the order of taking courses.
    std::vector<int> topological_sort;

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
     * @param course_index Int course index to check for feasibility.
     * @returns Boolean indicating whether a course is feasible or not.
     */
    bool depth_first_search(int course_index) {

        // Check if course present in set.
        if (courses_on_dfs_path.find(course_index) != courses_on_dfs_path.end()) {
            // Course exists on the path, cycle detected
            return false;
        }

        if (is_course_feasible[course_index]) {
            // Course is doable found out previously.
            return true;
        }

        if (directed_acyclic_graph[course_index].empty()) {
            // Course with no prerequisite
            topological_sort.emplace_back(course_index);
            is_course_feasible[course_index] = true;
            return true;
        }

        // Add to path.
        courses_on_dfs_path.insert(course_index);

        for (const auto & neighbor : directed_acyclic_graph[course_index]) {
            if (!depth_first_search(neighbor)) {
                return false;
            }
        }

        // Backtrack.
        courses_on_dfs_path.erase(course_index);

        // Declare feasible.
        is_course_feasible[course_index] = true;
        topological_sort.emplace_back(course_index);
        return true;
    }
};