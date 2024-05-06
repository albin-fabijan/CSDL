#include <cstdlib>
#include <ctime>
#include <vector>
#include <raylib.h>

#define MAX_HEIGHT 22
#define MAX_LENGTH 32

static void UpdateDrawFrame(int matrix[][MAX_HEIGHT]);

void InitMatrix(int matrix[][MAX_HEIGHT]){
    //0 = dead, 1 = red, 2 = blue
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        for (int j = 0; j < MAX_HEIGHT; j++){
            if (i == 4 && j == 5){
                matrix[i][j] = 1;
            }
            else if (i == 4 && j == 6){
                matrix[i][j] = 1;
            }
            else if (i == 4 && j == 7){
                matrix[i][j] = 1;
            }
            else if (i == 3 && j == 7){
                matrix[i][j] = 1;
            }
            else if (i == 2 && j == 6){
                matrix[i][j] = 1;
            }
            else{
                matrix[i][j] = 0;
            }
        }
    }
}

void RandomMatrix(int matrix[][MAX_HEIGHT]){
    //0 = dead, 1 = red, 2 = blue
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        for (int j = 0; j < MAX_HEIGHT; j++){
            int randomNum = std::rand() / ((RAND_MAX + 1u) / 3);
            matrix[i][j] = randomNum;
        }
    }
}

std::vector<int> getNeighbors(int matrix[][MAX_HEIGHT], int i, int j){
    std::vector<int> result;
    if (i == 0 && j == 0){ // ┏
        result.push_back(matrix[i][j+1]);
        result.push_back(matrix[i+1][j+1]);
        result.push_back(matrix[i+1][j]);        
    }
    else if (i == 0 && j == MAX_HEIGHT-1){ // ┓
        result.push_back(matrix[i][j-1]);
        result.push_back(matrix[i+1][j-1]);
        result.push_back(matrix[i+1][j]);
    }
    else if (i == 0){ //﹉
        result.push_back(matrix[i][j-1]);
        result.push_back(matrix[i+1][j-1]);
        result.push_back(matrix[i+1][j]);
        result.push_back(matrix[i][j+1]);
        result.push_back(matrix[i+1][j+1]);
    }
    else if (i == MAX_LENGTH-1 && j == 0){ // ┗
        result.push_back(matrix[i-1][j]);
        result.push_back(matrix[i][j+1]);
        result.push_back(matrix[i-1][j+1]);
    }
    else if (i == MAX_LENGTH-1 && j == MAX_HEIGHT-1){ // ┛
        result.push_back(matrix[i-1][j-1]);
        result.push_back(matrix[i][j-1]);
        result.push_back(matrix[i-1][j]);
    }
    else if (i == MAX_LENGTH-1){ //_
        result.push_back(matrix[i-1][j-1]);
        result.push_back(matrix[i][j-1]);
        result.push_back(matrix[i-1][j]);
        result.push_back(matrix[i-1][j+1]);
        result.push_back(matrix[i][j+1]);
    }
    else if (j == 0){// |<-
        result.push_back(matrix[i-1][j]);
        result.push_back(matrix[i+1][j]);
        result.push_back(matrix[i-1][j+1]);
        result.push_back(matrix[i][j+1]);
        result.push_back(matrix[i+1][j+1]);
    }
    else if (j == MAX_HEIGHT-1){// ->|
        result.push_back(matrix[i-1][j-1]);
        result.push_back(matrix[i][j-1]);
        result.push_back(matrix[i+1][j-1]);
        result.push_back(matrix[i-1][j]);
        result.push_back(matrix[i+1][j]);
    }
    else{
        result.push_back(matrix[i-1][j-1]);
        result.push_back(matrix[i][j-1]);
        result.push_back(matrix[i+1][j-1]);
        result.push_back(matrix[i-1][j]);
        result.push_back(matrix[i+1][j]);
        result.push_back(matrix[i-1][j+1]);
        result.push_back(matrix[i][j+1]);
        result.push_back(matrix[i+1][j+1]);
    }
    result.push_back(0);
    return result;
}

int getNextState(int matrix[][MAX_HEIGHT], int i, int j){
    int reds = 0;
    int blues = 0;
    std::vector<int> neighbors = getNeighbors(matrix, i, j);
    if (matrix[i][j] == 0){
        for (int i = 0; i < neighbors.size(); i++){
            if (neighbors[i] == 1){
                reds++;
            }
            else if (neighbors[i] == 2){
                blues++;
            }
        }
        if (reds+blues == 3){
            if (reds > blues){
                return 1;
            }
            return 2;
        }
        return 0;
    }
    else{
        for (int i = 0; i < neighbors.size(); i++){
            if (neighbors[i] == 1){
                reds++;
            }
            else if (neighbors[i] == 2){
                blues++;
            }
        }
        if (reds+blues == 2 || reds+blues == 3){
            if (reds > blues){
                return 1;
            }
            else if (blues == reds){
                return matrix[i][j];
            }
            return 2;
        }
        return 0;
    }
}

void nextMatrix(int matrix[][MAX_HEIGHT]){
    int newMatrix[MAX_LENGTH][MAX_HEIGHT];
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        for (int j = 0; j < MAX_HEIGHT; j++){
            newMatrix[i][j] = getNextState(matrix, i, j);
        }
    }
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        for (int j = 0; j < MAX_HEIGHT; j++){
            matrix[i][j] = newMatrix[i][j];
        }
    }
}

int main()
{
    int matrix[MAX_LENGTH][MAX_HEIGHT];
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib");

    InitMatrix(matrix);

    SetTargetFPS(2);
    
    while (!WindowShouldClose())
    {
        UpdateDrawFrame(matrix);
    }

    CloseWindow();

    return 0;
}

static void UpdateDrawFrame(int matrix[][MAX_HEIGHT])
{
    BeginDrawing();

        ClearBackground(BLACK);

        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 22; j++){
                if (matrix[i][j] == 1){
                    DrawRectangle(1+(25*i), 1+(25*j), 23, 23, RED);
                }
                else if (matrix[i][j] == 2){
                    DrawRectangle(1+(25*i), 1+(25*j), 23, 23, BLUE);
                }
                else{
                    DrawRectangle(1+(25*i), 1+(25*j), 23, 23, WHITE);
                }
            }
        }

        DrawRectangle(25, 555, 100, 40, DARKGRAY);
        DrawRectangle(187, 555, 100, 40, DARKGRAY);
        DrawRectangle(350, 555, 100, 40, DARKGRAY);
        DrawRectangle(512, 555, 100, 40, DARKGRAY);
        DrawRectangle(675, 555, 100, 40, DARKGRAY);

    EndDrawing();

    nextMatrix(matrix);
}
