#pragma once
#ifndef MAZE__H
#define MAZE_H

const int MAX_COLS = 1000;

/**
 * @brief Structure representing a point in a maze.
 */
struct Point {
    int x, y;
};

int** initializeMaze(int tempMazeData[][MAX_COLS], int rows, int cols);
void cleanupMaze(int** maze, int rows);
bool trameux(int x, int y, int** maze, int rows, int cols, int** visited, Point exit);
void printMaze(int** maze, int rows, int cols);
bool solveMaze(int** maze, int rows, int cols);
void processMaze(int** mazeData, int rows, int cols);

#endif