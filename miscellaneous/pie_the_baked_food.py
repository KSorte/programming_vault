from math import pi as PI

class Pie():
    def __init__(self,
                 radius:float,
                 height:float,
                 percentage:float = 100.0):

        if radius < 0 or height < 0:
            raise ValueError("Invalid radius/height argument in constructor")

        if percentage < 0 or percentage > 100:
            raise ValueError("Invalid percentage argument in constructor")

        self.radius = radius
        self.height = height
        self.percentage = percentage

    def __str__(self) -> str:
        return f"\nPie attributes:\nradius : {self.radius} m\nheight : {self.height} m\npercent : {self.percentage} %"

    def slice(self, angle:float):
        if angle < 0:
            raise ValueError("Invalid angle argument in slice")

        slice_percentage = (angle/360)*100

        if slice_percentage > self.percentage:
            raise ValueError(f"slice percentage ({slice_percentage})% > pie percentage ({self.percentage})%")

        self.percentage -= slice_percentage
        return Pie(self.radius, self.height, slice_percentage)

class SugarPie(Pie):
    def __init__(self,
                 radius:float,
                 height:float,
                 sugar_per_cubic_meter:float,
                 percentage:float = 100.0):

        super().__init__(radius, height, percentage)
        self.sugar_per_cubic_meter = sugar_per_cubic_meter

    def __str__(self):
        return super().__str__() + f"\nsugar : {self.sugar():.2f} g"

    def slice(self, angle):
        pie = super().slice(angle)
        return SugarPie(pie.radius, pie.height, self.sugar_per_cubic_meter, pie.percentage)

    def sugar(self):
        pie_volume = PI * (self.radius**2) * self.height
        current_volume = pie_volume * (self.percentage/100)

        return current_volume * self.sugar_per_cubic_meter

if __name__ == "__main__":
    print("Pie Test")
    print("------------------------------------------------")
    try:
        pie = Pie(radius=0.2, height=0.1)

        slice_pie = pie.slice(180)
        print(f"Original pie after slicing = {pie} \n")
        print(f"slice_pie = {slice_pie}\n")

        # Try slicing a bigger slice than remaining.
        slice_pie_2 = pie.slice(270)
        print(f"Original pie after slicing = {pie} \n")
        print(f"slice_pie_2 = {slice_pie_2}\n")

    except ValueError as e:
        print(f"{ValueError.__name__}:\n", e)

    print("\nSuger Pie Test")
    print("------------------------------------------------")
    try:
        sugar_pie = SugarPie(radius=1, height=1, sugar_per_cubic_meter=100)

        slice_suger_pie = sugar_pie.slice(180)
        print(f"Original sugar pie after slicing = {sugar_pie} \n")
        print(f"slice_pie = {slice_suger_pie}\n")

        # Try slicing a bigger slice than remaining.
        slice_suger_pie_2 = pie.slice(250)
        print(f"Original pie after slicing = {sugar_pie} \n")
        print(f"slice_pie_2 = {slice_suger_pie_2}\n")
    except ValueError as e:
        print(f"{ValueError.__name__}:\n", e)


    print("\nConstructor Test Pie")
    print("------------------------------------------------")
    try:
        pie = Pie(radius=1, height=-1)
    except ValueError as e:
        print(f"{ValueError.__name__}: \n", e)

    print("\nConstructor Test Suger Pie")
    print("------------------------------------------------")
    try:
        sugar_pie = SugarPie(radius=-1, height=1, sugar_per_cubic_meter=100)
    except ValueError as e:
        print(f"{ValueError.__name__}:\n", e)