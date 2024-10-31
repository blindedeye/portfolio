#include <iostream>
#include "headers.h"

using namespace std;
using namespace std::chrono;

/**
 * @brief Initializes a maze with the given data.
 *
 * @param tempMazeData The data to initialize the maze with.
 * @param rows The number of rows in the maze.
 * @param cols The number of columns in the maze.
 * @return Pointer to the initialized 2D maze array.
 */
int** initializeMaze(int tempMazeData[][MAX_COLS], int rows, int cols)
{
    int** maze = new int*[rows];
    for (int i = 0; i < rows; ++i)
    {
        maze[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
        {
            maze[i][j] = tempMazeData[i][j];
        }
    }
    return maze;
}

/**
 * @brief Cleans up the dynamically allocated maze array.
 *
 * @param maze The maze array to clean up.
 * @param rows The number of rows in the maze.
 */
void cleanupMaze(int** maze, int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] maze[i];
    }
    delete[] maze;
}

/**
 * @brief Processes the maze by solving it and measuring the time taken.
 *
 * @param mazeData The maze data.
 * @param rows The number of rows in the maze.
 * @param cols The number of columns in the maze.
 */
void processMaze(int** mazeData, int rows, int cols)
{
    printMaze(mazeData, rows, cols);

    auto start = high_resolution_clock::now();

    solveMaze(mazeData, rows, cols);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken: " << duration.count() << " ms" << endl << endl;
}

/**
 * @brief Prints the maze to the console.
 *
 * @param maze The maze to print.
 * @param rows The number of rows in the maze.
 * @param cols The number of columns in the maze.
 */
void printMaze(int** maze, int rows, int cols)
{
    cout << "Maze: " << endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * @brief Checks if a given position in the maze is safe to move to.
 *
 * @param x The row index.
 * @param y The column index.
 * @param maze The maze array.
 * @param rows The number of rows in the maze.
 * @param cols The number of columns in the maze.
 * @param visited The array indicating visited positions.
 * @return true if safe, false otherwise.
 */
bool isSafe(int x, int y, int** maze, int rows, int cols, int** visited)
{
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 1 && visited[x][y] < 2);
}

/**
 * @brief Finds the entrance and exit points of the maze.
 *
 * @param maze The maze array.
 * @param rows The number of rows in the maze.
 * @param cols The number of columns in the maze.
 * @param entrance Reference to the entrance point variable.
 * @param exit Reference to the exit point variable.
 */
bool trameux(int x, int y, int** maze, int rows, int cols, int** visited, Point exit)
{
    if (x == exit.x && y == exit.y)
    {
        visited[x][y] = 1;
        return true;
    }

    if (isSafe(x, y, maze, rows, cols, visited))
    {
        visited[x][y]++;
        
        // Move Right
        if (y + 1 < cols && visited[x][y+1] == 0 && trameux(x, y + 1, maze, rows, cols, visited, exit))
            return true;

        // Move Down
        if (x + 1 < rows && visited[x+1][y] == 0 && trameux(x + 1, y, maze, rows, cols, visited, exit))
            return true;

        // Move Left
        if (y - 1 >= 0 && visited[x][y-1] == 0 && trameux(x, y - 1, maze, rows, cols, visited, exit))
            return true;

        // Move Up
        if (x - 1 >= 0 && visited[x-1][y] == 0 && trameux(x - 1, y, maze, rows, cols, visited, exit))
            return true;


        // Backtrack
        visited[x][y]--;
    }

    return false;
}

/**
 * @brief Finds the entrance and exit points of the maze.
 *
 * @param maze The maze array.
 * @param rows The number of rows in the maze.
 * @param cols The number of columns in the maze.
 * @param entrance Reference to the entrance point variable.
 * @param exit Reference to the exit point variable.
 */
void findEntranceExit(int** maze, int rows, int cols, Point &entrance, Point &exit)
{
    bool foundEntrance = false;

    for (int j = 0; j < cols; j++)
    {
        if (maze[0][j] == 1)
        {
            if (!foundEntrance)
            {
                entrance = {0, j};
                foundEntrance = true;
            } else
            {
                exit = {0, j};
            }
        }
        if (maze[rows - 1][j] == 1)
        {
            if (!foundEntrance)
            {
                entrance = {rows - 1, j};
                foundEntrance = true;
            } else
            {
                exit = {rows - 1, j};
            }
        }
    }

    for (int i = 1; i < rows - 1; i++)
    {
        if (maze[i][0] == 1)
        {
            if (!foundEntrance)
            {
                entrance = {i, 0};
                foundEntrance = true;
            } else
            {
                exit = {i, 0};
            }
        }
        if (maze[i][cols - 1] == 1)
        {
            if (!foundEntrance)
            {
                entrance = {i, cols - 1};
                foundEntrance = true;
            } else
            {
                exit = {i, cols - 1};
            }
        }
    }
}

/**
 * @brief Attempts to solve the maze.
 *
 * @param maze The maze array.
 * @param rows The number of rows in the maze.
 * @param cols The number of columns in the maze.
 * @return true if a solution is found, false otherwise.
 */
bool solveMaze(int** maze, int rows, int cols) {
    int** visited = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        visited[i] = new int[cols] {0};
    }

    Point entrance, exit;
    findEntranceExit(maze, rows, cols, entrance, exit);

    if (!trameux(entrance.x, entrance.y, maze, rows, cols, visited, exit))
    {
        cout << "Solution doesn't exist." << endl << endl;
        for (int i = 0; i < rows; i++)
        {
            delete[] visited[i];
        }
        delete[] visited;
        return false;
    }

    cout << "Solution Found: " << endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << visited[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < rows; i++)
    {
        delete[] visited[i];
    }
    delete[] visited;

    return true;
}
