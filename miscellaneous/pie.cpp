#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

/*
    Write a class called “Pie” (the baked food) with:
    ● A constructor that accepts positive float arguments “radius”, “height”, and “percentage”
    where radius and height are both in meters and percentage specifies the percentage of
    the full circular pie that is remaining (initially 100 for a newly baked pie)

    ● A method “slice” that accepts a positive float “angle” which cuts away a circular sector
    piece of pie with the specified central angle “angle” (in degrees), returns a new Pie
    object representing the slice, and modifies the “percentage” variable of the original Pie
    object to take away the slice from the original pie.

    ● Both the constructor and the slice() method should raise/throw an exception on any
    invalid input arguments (including if you try to “slice” a bigger angle of pie than is left)

    ----------------------------------------------------------------------------------------------
    Next, write a class called “SugarPie” that inherits from Pie and has
    ● An additional constructor argument “sugar_per_cubic_meter” specifying the average
    quantity of sugar (in grams) per cubic meter of the pie

    ● An additional method “sugar” that returns the total amount of sugar in the SugarPie
    object (assuming the pie is in the shape of a perfect disk with the radius and height given
    in the Pie object)
*/

const double PI = 3.14159265358979323846;

class Pie {
public:
    /**
     * @brief Constructs a Pie object with specified dimensions and remaining percentage.
     * @param radius Float radius of the pie. Must be positive.
     * @param height Float height of the pie. Must be positive.
     * @param percentage The percentage of the pie that remains. Default is 100%.
     * @throws std::invalid_argument if radius, height, or percentage are out of valid range.
     */
    Pie(float radius, float height, float percentage = 100.0f) {
        if (radius <= 0 || height <= 0) {
            throw std::invalid_argument("Radius and height must be positive");
        }
        if (percentage < 0 || percentage > 100) {
            throw std::invalid_argument("Percentage must be between 0 and 100");
        }

        this->radius = radius;
        this->height = height;
        this->percentage = percentage;
    }

    /**
     * @brief Slices a portion of the pie based on the specified angle.
     * @param angle Float angle of the slice in degrees. Must be positive.
     * @returns A Pie object representing the sliced portion.
     * @throws std::invalid_argument if angle is non-positive or exceeds available percentage.
     */
    Pie slice(float angle) {
        if (angle <= 0) {
            throw std::invalid_argument("Angle must be positive");
        }

        // Calculate what percentage of the pie this angle represents.
        // Sticking to float literals.
        float slice_percentage = (angle / 360.0f) * 100.0f;

        if (slice_percentage > percentage) {
            throw std::invalid_argument("Cannot slice " + std::to_string(slice_percentage) +
                          "% when only " + std::to_string(percentage) + "% remains");
        }

        // Create new pie object for the slice
        Pie slice_pie(radius, height, slice_percentage);

        // Update the original pie's remaining percentage
        percentage -= slice_percentage;
        // TODO(KSorte): Use Pointers.
        return slice_pie;
    }

    /**
     * @brief Gets the radius of the pie.
     * @return The radius of the pie.
     */
    float getRadius() const { return radius; }

    /**
     * @brief Gets the height of the pie.
     * @return The height of the pie.
     */
    float getHeight() const { return height; }

    /**
     * @brief Gets the remaining percentage of the pie.
     * @return The remaining percentage of the pie.
     */
    float getPercentage() const { return percentage; }

protected:
    // Pi radius in meters
    float radius;
    // Pi height in meters
    float height;
    // Remaining percentage of the pie, initialized to 100.
    float percentage = 100;
    };

class SugarPie : public Pie {

public:
    SugarPie(float radius, float height, float sugar_per_cubic_meter, float p = 100.0f)
        : Pie(radius, height, p) {
        if (sugar_per_cubic_meter < 0) {
            throw std::invalid_argument("Sugar density cannot be negative");
        }
        sugar_density = sugar_per_cubic_meter;
    }

    /**
     * @brief Takes a slice out of the Sugar Pie using the float input angle.
     * @param angle Float input angle in degrees.
     * @return SugarPie Object.
     */
    SugarPie slice(float angle) {
        // Call parent class method.
        auto pie = Pie::slice(angle);

        return SugarPie(pie.getRadius(), pie.getHeight(), sugar_density, pie.getPercentage());
    }

    /**
     * @brief Calculates the sugar content based on the remaining pie volume.
     * @return Float total sugar content in the remaining portion of the pie.
     */
    float sugar() const {
        // Calculate the volume of the remaining portion of the pie
        float full_volume = PI * radius * radius * height;
        float remaining_volume = full_volume * (percentage / 100.0f);

        // Calculate total sugar content
        return remaining_volume * sugar_density;
    }

    /**
     * @brief Get the sugar density value.
     * @return float Sugar density.
     */
    float get_sugar() {
        return sugar_density;
    }

private:
    // grams per cubic meter
    float sugar_density;
};

int main() {
    std::cout << std::fixed << std::setprecision(2);

    // Test Pie class
    try {
        // TODO(KSorte): Use pointers.
        Pie pie(0.15f, 0.05f, 25.0f);  // 15cm radius, 5cm height, 25 % remaining.
        std::cout << "Initial pie percentage: " << pie.getPercentage() << "%\n";

        Pie slice = pie.slice(45.0f);  // Take a half of the pie
        std::cout << "After 45-degree slice:\n";
        std::cout << "Original pie remaining: " << pie.getPercentage() << "%\n";
        std::cout << "Slice size: " << slice.getPercentage() << "%\n\n";

        // Will throw an exception.
        Pie new_slice = pie.slice(55.0f);
        std::cout << "After 55-degree slice:\n";
        std::cout << "Original pie remaining: " << pie.getPercentage() << "%\n";
        std::cout << "Slice size: " << slice.getPercentage() << "%\n\n";

    } catch (const std::invalid_argument& e) {
        std::cout << "Pie Error: " << e.what() << "\n\n";
    }

    // Test SugarPie class
    try {
        SugarPie sugar_pie(0.15f, 0.05f, 500.0f, 75.0f);  // 500g sugar per cubic meter
        std::cout << "Initial sugar content: " << sugar_pie.sugar() << "g\n";

        sugar_pie.slice(120.0f);  // Take a third of the pie
        std::cout << "Sugar content after 120-degree slice: " << sugar_pie.sugar() << "g\n";

        // Will throw an exception.
        Pie new_slice = sugar_pie.slice(180.0f);
        std::cout << "After 180-degree slice:\n";
        std::cout << "Original pie remaining: " << sugar_pie.getPercentage() << "%\n";
        std::cout << "Slice size: " << new_slice.getPercentage() << "%\n\n";

    } catch (const std::invalid_argument& e) {
        std::cout << "SugarPie Error: " << e.what() << "\n";
    }

    return 0;
}