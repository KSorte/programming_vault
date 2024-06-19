#include <algorithm>
#include <iostream>
#include <vector>

/*
    Leetcode 853 Car Fleet
    The basic idea is to arrange all the cars in sorted order of position.
    Create a vector of pairs (position, speed) and sort it by position.
    Begin your loop from the car closest to the target.
    while i >= 0; i --;
        1. curr pos = ith.
        2. time = time for p to reach target.
        3. if time > current max time:
            increment num fleet
            max time = time.

    return result.size()
*/

class Solution {
public:
    /**
     * @brief returns the number of car fleets that reach the target.
     * @param position vector of positions.
     * @param speed vector of speeds.
     * @returns Integer number of car fleets.
     */
    int carFleet(int target, std::vector<int>& position, std::vector<int>& speed) {
        // Vector storing cars as pair of position and speed.
        std::vector<std::pair<int, int>> cars;
        // Populate cars vector.
        for (int p = 0; p < position.size(); p++){
            auto pos = position[p];
            auto sp = speed[p];
            cars.push_back({pos, sp});
        }

        // Sort cars (pos, speed pairs) by ascending order of position.
        std::sort(cars.begin(), cars.end());

        // Initialize number of car fleets and max time to 0.
        int num_car_fleets = 0;
        double time_max = 0.0;

        // Iterate through the cars vector from back.
        for (int i = cars.size() - 1; i >= 0; i--){
            // Note down time to reach target for current car.
            double time = (double) (target - cars[i].first)/cars[i].second;

            // If time to reach target for the current car is greater than the max,
            // this is the start of a new fleet.
            if (time > time_max) {
                num_car_fleets++;
                time_max = time;
            }
        }
        return num_car_fleets;
    }
};