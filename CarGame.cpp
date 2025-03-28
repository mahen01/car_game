#include<iostream>  
#include<conio.h>  
#include<dos.h>   
#include <windows.h>  
#include <time.h>  
  
#define SCREEN_WIDTH 90  // Defines the width of the game screen
#define SCREEN_HEIGHT 26  // Defines the height of the game screen
#define WIN_WIDTH 70   // Defines the width of the playable window
  
using namespace std;   
   
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);  // Handle for console operations
COORD CursorPosition;  // Stores cursor position

// Arrays to store enemy positions and flags to indicate if an enemy is present
  
int enemyY[3];  
int enemyX[3];  
int enemyFlag[3];

// Car representation as a 2D array  
char car[4][4] = { ' ','±','±',' ',   
                    '±','±','±','±',   
                    ' ','±','±',' ',  
                    '±','±','±','±' };   
// Current position of the car                      
int carPos = WIN_WIDTH/2;  // Initial car position

// Player's score  
int score = 0;   

// Function to set the cursor position on the console 
void gotoxy(int x, int y){  
    CursorPosition.X = x;  
    CursorPosition.Y = y;  
    SetConsoleCursorPosition(console, CursorPosition);  
}  

// Function to set the cursor visibility and size
void setcursor(bool visible, DWORD size) {  
    if(size == 0)  
        size = 20;    
      
    CONSOLE_CURSOR_INFO lpCursor;     
    lpCursor.bVisible = visible;  
    lpCursor.dwSize = size;  
    SetConsoleCursorInfo(console,&lpCursor);  
}  

// Function to draw the border of the game screen
void drawBorder(){    
    for(int i=0; i<SCREEN_HEIGHT; i++){  
        for(int j=0; j<17; j++){  
            gotoxy(0+j,i); cout<<"±";  // Left border
            gotoxy(WIN_WIDTH-j,i); cout<<"±";  // Right border
        }  
    }   
    for(int i=0; i<SCREEN_HEIGHT; i++){  
        gotoxy(SCREEN_WIDTH,i); cout<<"±";  // Rightmost border
    }   
} 

// Function to generate a random enemy position 
void genEnemy(int ind){  
    enemyX[ind] = 17 + rand()%(33);    // Generate a random X position for enemy
}  

// Function to draw an enemy at the given index
void drawEnemy(int ind){  
    if( enemyFlag[ind] == true ){  
        gotoxy(enemyX[ind], enemyY[ind]);   cout<<"****";    
        gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** ";   
        gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"****";   
        gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";    
    }   
}  

// Function to erase an enemy at the given index
void eraseEnemy(int ind){  
    if( enemyFlag[ind] == true ){  
        gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";    
        gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    ";   
        gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    ";   
        gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    ";   
    }   
} 

// Function to reset an enemy at the given index 
void resetEnemy(int ind){  
    eraseEnemy(ind);  
    enemyY[ind] = 1;  
    genEnemy(ind);  
}  

// Function to draw the car on the screen  
void drawCar(){  
    for(int i=0; i<4; i++){  
        for(int j=0; j<4; j++){  
            gotoxy(j+carPos, i+22); cout<<car[i][j];  
        }  
    }  
} 

// Function to erase the car from the screen 
void eraseCar(){  
    for(int i=0; i<4; i++){  
        for(int j=0; j<4; j++){  
            gotoxy(j+carPos, i+22); cout<<" ";  
        }  
    }  
}  

// Function to check if there is a collision with an enemy   
int collision(){  
    if( enemyY[0]+4 >= 23 ){  
        if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){  
            return 1;  // Collision detected
        }  
    }  
    return 0;  
}  

// Function to display the game over screen 
void gameover(){  
    system("cls");  
    cout<<endl;  
    cout<<"\t\t--------------------------"<<endl;  
    cout<<"\t\t-------- Game Over -------"<<endl;  
    cout<<"\t\t--------------------------"<<endl<<endl;  
    cout<<"\t\tPress any key to go back to menu.";  
    getch();  
} 

// Function to update the score display 
void updateScore(){  
    gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;  
}  

// Function to display game instructions  
void instructions(){  
    system("cls");  
    cout<<"Instructions";  
    cout<<"\n----------------";  
    cout<<"\n Avoid Cars by moving left or right. ";  
    cout<<"\n\n Press 'a' to move left";  
    cout<<"\n Press 'd' to move right";  
    cout<<"\n Press 'escape' to exit";  
    cout<<"\n\nPress any key to go back to menu";  
    getch();  
}  

// Function to PLAY the game  
void play(){  
    // Initialization
    carPos = -1 + WIN_WIDTH/2;  
    score = 0;  
    enemyFlag[0] = 1;  
    enemyFlag[1] = 0;  
    enemyY[0] = enemyY[1] = 1;  
    
    system("cls");   
    drawBorder();   
    updateScore();  
    genEnemy(0);  
    genEnemy(1);  
}  

int main()  
{  
    setcursor(0,0);   
    srand( (unsigned)time(NULL));   
    
    do{  
        system("cls");  
        gotoxy(10,5); cout<<" -------------------------- ";   
        gotoxy(10,6); cout<<" |        Car Game        | ";   
        gotoxy(10,7); cout<<" --------------------------";  
        gotoxy(10,9); cout<<"1. Start Game";  
        gotoxy(10,10); cout<<"2. Instructions";      
        gotoxy(10,11); cout<<"3. Quit";  
        gotoxy(10,13); cout<<"Select option: ";  
        char op = getche();  
    }while(1);  
    
    return 0;  
}
