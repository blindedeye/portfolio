"""
Polygon class for geometric calculations
HandleInput class for managing input
"""

__author__ = "Jake Peterson"
__date__ = ""
__license__ = "MIT"
__version__ = "0.1.0"
__maintainer__ = "Jake Peterson"


class Polygon:
    """
    Performs geometric calculations related to polygons.
    """

    def __init__(self, points: list[tuple[int, int]]) -> None:
        """Constructor for Polygon.

        Args:
            points (list[tuple[int, int]]): List of vertices as (x, y) tuples.
        """
        self.points = points

    def calculate_area(self) -> float:
        """Calculates the area of a polygon using its vertices.

        Returns:
            float: The calculated area of the polygon.
        """
        result = 0
        n = len(self.points)
        for i in range(n):
            j = (i + 1) % n
            xi = self.points[i][0]  # Since result line was too long
            xi_plus = self.points[j][1]  # Since result line was too long
            yi = self.points[i][1]  # Since result line was too long
            yi_plus = self.points[j][0]  # Since result line was too long
            result += ((xi * xi_plus) - yi * yi_plus)
        return abs(result) / 2


class HandleInput:
    """
    Handles all input-related tasks.
    """

    def get_cases(self) -> int:
        """Gets the number of cases from the user.

        Returns:
            int: Number of cases.
        """
        return int(input(""))

    def get_points(self) -> list[tuple[int, int]]:
        """Gets the points for a polygon from the user on a single line.

        The input format should be: number_of_points followed by x y coords
        Example: "3 1 1 2 1 2 2" means three points: (1, 1), (2, 1), (2, 2).

        Returns:
            list[tuple[int, int]]: List of points as (x, y) tuples.
        """
        data = list(map(int, input().split()))
        point_list = [(data[i], data[i + 1]) for i in range(1, len(data), 2)]
        return point_list