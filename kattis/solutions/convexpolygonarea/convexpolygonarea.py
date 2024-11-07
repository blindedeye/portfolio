"""
Main script to execute the polygon area calculation program.
"""

__author__ = "Jake Peterson"
__date__ = ""
__license__ = "MIT"
__version__ = "0.1.0"
__maintainer__ = "Jake Peterson"

from polygon import HandleInput, Polygon


def main() -> None:
    """
    Doc
    """
    input_handler = HandleInput()
    cases = input_handler.get_cases()
    areas = []

    for _ in range(cases):
        points = input_handler.get_points()
        polygon = Polygon(points)
        area = polygon.calculate_area()
        areas.append(area)

    for area in areas:
        # Since we can have a float (0.5) and an int (52): check if int
        print(f"{int(area) if area.is_integer() else area}")


if __name__ == "__main__":
    main()