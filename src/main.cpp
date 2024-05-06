#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <raylib.h>

#define MAX_HEIGHT 22
#define MAX_LENGTH 32

static void UpdateDrawFrame(int matrix[][MAX_HEIGHT]);

void ClearMatrix(int matrix[][MAX_HEIGHT]){
    //0 = dead, 1 = red, 2 = blue
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        for (int j = 0; j < MAX_HEIGHT; j++){
            matrix[i][j] = 0;
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

    InitWindow(screenWidth, screenHeight, "game of life");

    RandomMatrix(matrix);

    SetTargetFPS(3);
    
    while (!WindowShouldClose())
    {
        UpdateDrawFrame(matrix);
    }

    CloseWindow();

    return 0;
}

bool pause = false;

static void UpdateDrawFrame(int matrix[][MAX_HEIGHT])
{
    std::vector<Rectangle> rectangles;
    for (int i = 0; i < MAX_LENGTH; i++){
        for (int j = 0; j < MAX_HEIGHT; j++){
            Rectangle rect = {i*25, j*25, 25, 25};
            rectangles.push_back(rect);
        }        
    }

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

        Rectangle pauseButton = {25, 555, 100, 40};
        DrawRectangle(25, 555, 100, 40, DARKGRAY);
        DrawText("Pause", pauseButton.x + pauseButton.width / 2 - MeasureText("Pause", 20) / 2, pauseButton.y + pauseButton.height / 2 - 10 , 20, WHITE);
        
        Rectangle nextButton = {187, 555, 100, 40};
        DrawRectangle(187, 555, 100, 40, DARKGRAY);
        DrawText("Next", nextButton.x + nextButton.width / 2 - MeasureText("Next", 20) / 2, nextButton.y + nextButton.height / 2 - 10 , 20, WHITE);
        
        Rectangle clearButton = {350, 555, 100, 40};
        DrawRectangle(350, 555, 100, 40, DARKGRAY);
        DrawText("Clear", clearButton.x + clearButton.width / 2 - MeasureText("Clear", 20) / 2, clearButton.y + clearButton.height / 2 - 10 , 20, WHITE);
        
        Rectangle randomButton = {512, 555, 100, 40};
        DrawRectangle(512, 555, 100, 40, DARKGRAY);
        DrawText("Random", randomButton.x + randomButton.width / 2 - MeasureText("Random", 20) / 2, randomButton.y + randomButton.height / 2 - 10 , 20, WHITE);
        
        Rectangle quitButton = {675, 555, 100, 40};
        DrawRectangle(675, 555, 100, 40, DARKGRAY);
        DrawText("Quit", quitButton.x + quitButton.width / 2 - MeasureText("Quit", 20) / 2, quitButton.y + quitButton.height / 2 - 10 , 20, WHITE);
        
    EndDrawing();

    if (!pause){
        nextMatrix(matrix);
    }

    for (Rectangle r : rectangles){
        if (CheckCollisionPointRec(GetMousePosition(), r) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            std::cout << (r.x)/25 << ',' << (r.y)/25 << std::endl;
            matrix[(int)((r.x)/25)][(int)((r.y)/25)] = 1;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), r) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            std::cout << (r.x)/25 << ',' << (r.y)/25 << std::endl;
            matrix[(int)((r.x)/25)][(int)((r.y)/25)] = 2;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), pauseButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        pause = !pause;
    }

    if (CheckCollisionPointRec(GetMousePosition(), nextButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        nextMatrix(matrix);
    }

    if (CheckCollisionPointRec(GetMousePosition(), clearButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        ClearMatrix(matrix);
    }

    if (CheckCollisionPointRec(GetMousePosition(), randomButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        RandomMatrix(matrix);
    }

    if (CheckCollisionPointRec(GetMousePosition(), quitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        CloseWindow();
    }
}
