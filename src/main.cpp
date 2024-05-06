#include <cstdlib>
#include <ctime>
#include <raylib.h>

#define MAX_HEIGHT 22
#define MAX_LENGTH 32

static void UpdateDrawFrame(int matrix[][MAX_HEIGHT]);

void InitMatrix(int matrix[][MAX_HEIGHT]){
    //0 = dead, 1 = red, 2 = blue
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 22; j++){
            if (i == 4 && j == 5){
                matrix[i][j] = 1;
            }
            else if (i == 4 && j == 6){
                matrix[i][j] = 1;
            }
            else if (i == 4 && j == 7){
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
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 22; j++){
            int randomNum = std::rand() / ((RAND_MAX + 1u) / 3);
            matrix[i][j] = randomNum;
        }
    }
}

int getNeighbors(int matrix[][MAX_HEIGHT], int i, int j){
    int reds = 0;
    int blues = 0;
    if (i == 0 && j == 0){ // ┏
        //1
        if (matrix[i][j+1] == 1){
            reds++;
        }
        else if (matrix[i][j+1] == 2){
            blues++;
        }
        //2
        if (matrix[i+1][j+1] == 1){
            reds++;
        }
        else if (matrix[i+1][j+1] == 2){
            blues++;
        }
        //3
        if (matrix[i+1][j] == 1){
            reds++;
        }
        else if (matrix[i+1][j] == 2){
            blues++;
        }
    }
    else if (i == 0 && j == MAX_HEIGHT){ // ┓
        //1
        if (matrix[i][j-1] == 1){
            reds++;
        }
        else if (matrix[i][j-1] == 2){
            blues++;
        }
        //2
        if (matrix[i+1][j-1] == 1){
            reds++;
        }
        else if (matrix[i+1][j-1] == 2){
            blues++;
        }
        //3
        if (matrix[i+1][j] == 1){
            reds++;
        }
        else if (matrix[i+1][j] == 2){
            blues++;
        }
    }
    else if (i == 0){ //﹉
        //1
        if (matrix[i][j-1] == 1){
            reds++;
        }
        else if (matrix[i][j-1] == 2){
            blues++;
        }
        //2
        if (matrix[i+1][j-1] == 1){
            reds++;
        }
        else if (matrix[i+1][j-1] == 2){
            blues++;
        }
        //3
        if (matrix[i+1][j] == 1){
            reds++;
        }
        else if (matrix[i+1][j] == 2){
            blues++;
        }
        //4
        if (matrix[i][j+1] == 1){
            reds++;
        }
        else if (matrix[i][j+1] == 2){
            blues++;
        }
        //5
        if (matrix[i+1][j+1] == 1){
            reds++;
        }
        else if (matrix[i+1][j+1] == 2){
            blues++;
        }
    }
    else if (i == MAX_LENGTH && j == 0){ // ┗
        //1
        if (matrix[i-1][j] == 1){
            reds++;
        }
        else if (matrix[i-1][j] == 2){
            blues++;
        }
        //2
        if (matrix[i][j+1] == 1){
            reds++;
        }
        else if (matrix[i][j+1] == 2){
            blues++;
        }
        //3
        if (matrix[i+1][j+1] == 1){
            reds++;
        }
        else if (matrix[i+1][j+1] == 2){
            blues++;
        }
    }
    else if (i == MAX_LENGTH && j == MAX_HEIGHT){ // ┛
        //1
        if (matrix[i-1][j-1] == 1){
            reds++;
        }
        else if (matrix[i-1][j-1] == 2){
            blues++;
        }
        //2
        if (matrix[i][j-1] == 1){
            reds++;
        }
        else if (matrix[i][j-1] == 2){
            blues++;
        }
        //3
        if (matrix[i-1][j] == 1){
            reds++;
        }
        else if (matrix[i-1][j] == 2){
            blues++;
        }
    }
    else if (i == MAX_LENGTH){ //_
        //1
        if (matrix[i-1][j-1] == 1){
            reds++;
        }
        else if (matrix[i-1][j-1] == 2){
            blues++;
        }
        //2
        if (matrix[i][j-1] == 1){
            reds++;
        }
        else if (matrix[i][j-1] == 2){
            blues++;
        }
        //3
        if (matrix[i-1][j] == 1){
            reds++;
        }
        else if (matrix[i-1][j] == 2){
            blues++;
        }
        //4
        if (matrix[i-1][j+1] == 1){
            reds++;
        }
        else if (matrix[i-1][j+1] == 2){
            blues++;
        }
        //5
        if (matrix[i][j+1] == 1){
            reds++;
        }
        else if (matrix[i][j+1] == 2){
            blues++;
        }
    }
    else if (j == 0){// |<-
        //1
        if (matrix[i-1][j] == 1){
            reds++;
        }
        else if (matrix[i-1][j] == 2){
            blues++;
        }
        //2
        if (matrix[i+1][j] == 1){
            reds++;
        }
        else if (matrix[i+1][j] == 2){
            blues++;
        }
        //3
        if (matrix[i-1][j+1] == 1){
            reds++;
        }
        else if (matrix[i-1][j+1] == 2){
            blues++;
        }
        //4
        if (matrix[i][j+1] == 1){
            reds++;
        }
        else if (matrix[i][j+1] == 2){
            blues++;
        }
        //5
        if (matrix[i+1][j+1] == 1){
            reds++;
        }
        else if (matrix[i+1][j+1] == 2){
            blues++;
        }
    }
    else if (j == MAX_HEIGHT){// ->|
        //1
        if (matrix[i-1][j-1] == 1){
            reds++;
        }
        else if (matrix[i-1][j-1] == 2){
            blues++;
        }
        //2
        if (matrix[i][j-1] == 1){
            reds++;
        }
        else if (matrix[i][j-1] == 2){
            blues++;
        }
        //3
        if (matrix[i+1][j-1] == 1){
            reds++;
        }
        else if (matrix[i+1][j-1] == 2){
            blues++;
        }
        //4
        if (matrix[i-1][j] == 1){
            reds++;
        }
        else if (matrix[i-1][j] == 2){
            blues++;
        }
        //5
        if (matrix[i+1][j] == 1){
            reds++;
        }
        else if (matrix[i+1][j] == 2){
            blues++;
        }
    }
    else{
        //1
        if (matrix[i-1][j-1] == 1){
            reds++;
        }
        else if (matrix[i-1][j-1] == 2){
            blues++;
        }
        //2
        if (matrix[i][j-1] == 1){
            reds++;
        }
        else if (matrix[i][j-1] == 2){
            blues++;
        }
        //3
        if (matrix[i+1][j-1] == 1){
            reds++;
        }
        else if (matrix[i+1][j-1] == 2){
            blues++;
        }
        //4
        if (matrix[i-1][j] == 1){
            reds++;
        }
        else if (matrix[i-1][j] == 2){
            blues++;
        }
        //5
        if (matrix[i+1][j] == 1){
            reds++;
        }
        else if (matrix[i+1][j] == 2){
            blues++;
        }
        //6
        if (matrix[i-1][j+1] == 1){
            reds++;
        }
        else if (matrix[i-1][j+1] == 2){
            blues++;
        }
        //7
        if (matrix[i][j+1] == 1){
            reds++;
        }
        else if (matrix[i][j+1] == 2){
            blues++;
        }
        //8
        if (matrix[i+1][j+1] == 1){
            reds++;
        }
        else if (matrix[i+1][j+1] == 2){
            blues++;
        }
    }
}

int main()
{
    int matrix[MAX_LENGTH][MAX_HEIGHT];
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib");

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
    InitMatrix(matrix);

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
}
