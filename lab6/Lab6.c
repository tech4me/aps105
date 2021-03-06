/*
 * File:   Lab6.c
 * Author: Shizhang Yin (shizhang.yin@mail.utoronto.ca)
 * Date: October 30, 2015
 * Course: APS105
 *
 * Summary of File:
 *
 * This program is part of the the reversi game. It takes user's board configuration
 * and output the possible moves for the user. It also allows the user to make one
 * move and the program will determine if the move is legal and flip the board
 * accordingly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static const int MAX_BOARD_SIZE=26;//board size constant
static const int DELTA[8][2]={-1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1};//array for all eight directions

//declare functions
void boardInitialize(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
void printBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
void boardConfig(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
void legalMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
bool legalCases(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], char i, char j, char bwType, int n);
void makeMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
void moveFlip(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char row, char col, char colour);
bool positionInBounds(int N,char row, char col);
bool checkLegalInDirection(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int N, char row, char col, char colour, int deltaRow, int deltaCol);

int main(void)
{
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int boardSize;
    printf("Enter the board dimension: ");
    scanf("%d",&boardSize);
    boardInitialize(board,boardSize);
    boardConfig(board,boardSize);
    legalMove(board,boardSize);
    makeMove(board,boardSize);
    return 0;
}

void boardInitialize(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)//initialize stardard starting board configuration
{
    int i,j,k,m;
    for(i=0;i<MAX_BOARD_SIZE;i++)
    {
        for(j=0;j<MAX_BOARD_SIZE;j++)
            board[i][j]='\0';
    }
    for(k=0;k<n;k++)
    {
        for(m=0;m<n;m++)
            board[k][m]='U';
    }
    board[(n/2)-1][(n/2-1)]='W';//set up defult board config
    board[(n/2)-1][n/2]='B';
    board[n/2][(n/2)-1]='B';
    board[n/2][n/2]='W';
    printBoard(board,n);
}

void printBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)//print current board
{
    int i,j,k;
    printf("  ");
    for(i=0;i<n;i++)//print label
        printf("%c", 'a'+i);
    printf("\n");
    for(j=0;j<n;j++)//row++
    {
        printf("%c ",'a'+j);
        for(k=0;k<n;k++)//col++
            printf("%c",board[j][k]);
        printf("\n");
    }

}
void boardConfig(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)//get config and change the board
{
    int i,j;
    char inputLine[3]={0};
    bool inputState=true;
    printf("Enter board configuration: \n");
    while(inputState==true)
    {
        for(i=0;i<3;i++)
            scanf(" %c", &inputLine[i]);
        if((inputLine[0]=='!')&&(inputLine[1]=='!')&&(inputLine[2]=='!'))//find the end of the input
            inputState=false;
        else
            board[inputLine[1]-'a'][inputLine[2]-'a']=inputLine[0];
    }
    printBoard(board,n);
}

void legalMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)//find the legal moves on the current board
{
    char a,b,c,d;
    printf("Available moves for W: \n");
    for(a='a';a<'a'+n;a++)
    {
        for(b='a';b<'a'+n;b++)
        {
            if(legalCases(board,a,b,'W',n))
                printf("%c%c\n",a,b);
        }
    }
    printf("Available moves for B: \n");
    for(c='a';c<'a'+n;c++)
    {
        for(d='a';d<'a'+n;d++)
       {
           if(legalCases(board,c,d,'B',n))
                printf("%c%c\n", c,d);
       }
    }
}

bool legalCases(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], char row, char col , char bwType, int n)
{
    int i;
    bool result=false;
    for(i=0;i<8;i++)
    {
        result=result||checkLegalInDirection(board,n,row,col,bwType,DELTA[i][0],DELTA[i][1]);
    }
    if(result)//if any case match, the location is legal
        return true;
    else
        return false;
}

bool positionInBounds(int N, char row, char col)//check if the input location belongs to the board
{
    if((row>='a')&&(row<='a'+N-1)&&(col>='a')&&(col<='a'+N-1))
        return true;
    else
        return false;
}


bool checkLegalInDirection(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int N, char row, char col, char colour, int deltaRow, int deltaCol)//check legal in one direc
{
    if(board[row-'a'][col-'a']!='U')
        return false;
    else
    {
        char bwType;
        if(colour=='B')
            bwType='W';
        else if(colour=='W')
            bwType='B';
        int i,counter=0;
        if(!positionInBounds(N,row+deltaRow,col+deltaCol))
            return false;
        for(i=0;positionInBounds(N,row+deltaRow,col+deltaCol);i++)
        {
            if(board[row-'a'+deltaRow][col-'a'+deltaCol]==bwType)//BW* or WB* case
            {
                counter++;
                row=row+deltaRow;
                col=col+deltaCol;
            }
            else if(board[row-'a'+deltaRow][col-'a'+deltaCol]==colour && counter<1)//BB or WW case
                return false;
            else if(board[row-'a'+deltaRow][col-'a'+deltaCol]==colour && counter>=1)//B*B or W*W case
                return true;
            else if(board[row-'a'+deltaRow][col-'a'+deltaCol]=='U')//BU or WU case
                return false;
        }
        if(board[row-'a'][col-'a']==bwType && counter>=1)
            return false;
    }
}

void makeMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)//user make move and update the move
{
    int i;
    bool caseState=false;
    char userInput[3];
    printf("Enter a move: \n");
    for(i=0;i<3;i++)
        scanf(" %c", &userInput[i]);
    if(positionInBounds(n, userInput[1], userInput[2]))//check if input is inbound
    {
        if(legalCases(board, userInput[1], userInput[2], userInput[0], n))
            caseState=true;
        else
            caseState=false;
    }
    else
        caseState=false;
    if(caseState)
    {
        printf("Valid move.\n");
        board[userInput[1]-'a'][userInput[2]-'a']=userInput[0];
        moveFlip(board, n, userInput[1], userInput[2], userInput[0]);
    }
    else
        printf("Invalid move.\n");
    printBoard(board, n);
}

void moveFlip(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char row, char col, char colour)//flip possibles in all direction
{
    int i,j,counter=0;
    char bwType;
    char rowTemp;
    char colTemp;
    if(colour=='W')
        bwType='B';
    else if(colour=='B')
        bwType='W';
    for(i=0;i<8;i++)//loop for all 8 cases for each point
    {
        rowTemp=row;
        colTemp=col;
        counter=0;
        while(positionInBounds(n,rowTemp+DELTA[i][0],colTemp+DELTA[i][1]))
        {
            if(board[rowTemp+DELTA[i][0]-'a'][colTemp+DELTA[i][1]-'a']==bwType)//BW or WB case
            {
                counter++;
                rowTemp=rowTemp+DELTA[i][0];
                colTemp=colTemp+DELTA[i][1];
            }
            else if(board[rowTemp+DELTA[i][0]-'a'][colTemp+DELTA[i][1]-'a']=='U')//BU or WU case
                break;
            else if(board[rowTemp+DELTA[i][0]-'a'][colTemp+DELTA[i][1]-'a']==colour&&counter<1)//BB or WW case
                break;
            else if(board[rowTemp+DELTA[i][0]-'a'][colTemp+DELTA[i][1]-'a']==colour&&counter>=1)//B*B or W*W caes
            {
                for(j=0;j<counter;j++)
                    board[rowTemp-j*DELTA[i][0]-'a'][colTemp-j*DELTA[i][1]-'a']=colour;// flip
                break;
            }
        }
    }
}
