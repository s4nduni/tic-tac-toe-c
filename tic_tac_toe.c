#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Player{
    char player1;
    char player2;
}p;

/*  This will print the game board. */
void printBoard(char board[9])
{
    printf("\n\t %c | %c | %c ", board[0], board[1], board[2]);
    printf("\n\t---+---+---");
    printf("\n\t %c | %c | %c ", board[3], board[4], board[5]);
    printf("\n\t---+---+---");
    printf("\n\t %c | %c | %c \n", board[6], board[7], board[8]);
}

/*  This will check the winner. */
char checkWinner(char board[9])
{
    int pattern[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; i++)
        if (board[pattern[i][0]] != ' ' && board[pattern[i][0]] == board[pattern[i][1]] && board[pattern[i][0]] == board[pattern[i][2]])
            return (board[pattern[i][0]] == p.player1) ? p.player1 : p.player2;
    return ' ';
    
}

/*  This will mark the moves of players and computer. */
void gameMove(char board[9], char player, FILE *fp, int mode)
{   
    int gameMode;
    int move;
    while (1)
    {
        if (mode == 1)
        {
            printf("\n\nEnter Player %c Move : ", player);
            scanf("%d", &move);
        }
        else
        {
            srand(time(0));
            move = rand() % 10;
        }
        if (board[move - 1] == ' ')
        {
            board[move - 1] = player;
            break;
        }
        (mode == 1) ? printf("\nInvalid!\n"):1;
    }
    (!fp) ? printf("\n File Error!\n") : fprintf(fp, "\n%c %s Moved to %d", player, (mode == 1) ? "(Player)" : "(Computer)", move);
}

/*  main  */

int main()
{   
    int gameMode = 0;
    int n;
    time_t t;
    time(&t);
    printf("\n%s",ctime(&t));
    
    FILE *fp = fopen("tictactoe.txt", "a");
    
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    printf("\n\tTic Tac Toe \n");
   
    while (gameMode < 1 || gameMode > 2)
    {
        printf("\n Game Mode \n");
        printf("\n 1. Human vs Human");
        printf("\n 2. Human vs Computer \n");
        printf("\n Which option? 1 or 2 : ");
        scanf("%d", &gameMode);
        printf("\n X(1) or O(2)? : ");
        scanf("%d",&n);
    }
    if(n == 1){
        p.player1 = 'X';
        p.player2 = 'O';
    }
    else{
        p.player1 = 'O';
        p.player2 = 'X';
    }
    fprintf(fp,"%s",ctime(&t));
    printf("\n\tFirst player  is : %c",p.player1);
    fprintf(fp,"\nFirst player  is : %c",p.player1);
    printf("\n\tSecond player is : %c",p.player2);
    fprintf(fp,"\nSecond player  is : %c\n",p.player2);
    
    for (int i = 0; i < 9 && (checkWinner(board) == ' '); i++)
    {
        if (i % 2 == 0)
        {
            (gameMode == 1) ? gameMove(board,p.player1, fp, gameMode) : gameMove(board,p.player1, fp, 1);
            printBoard(board);
        }
        else
        {
            (gameMode == 1) ? gameMove(board,p.player2, fp, gameMode) : gameMove(board,p.player2, fp, 2);
            printBoard(board);
        }
    }
  
    if(checkWinner(board) == ' '){
        printf("\n\nDRAW !");
        fprintf(fp, "\n\nDRAW !\n");
    }else if(checkWinner(board) == p.player1){
        printf("\n\n%c IS THE WINNER !",p.player1);
        fprintf(fp, "\n\n%c IS THE WINNER !\n",p.player1);
    }else{
        printf("\n\n%c IS THE WINNER !",p.player2);
        fprintf(fp, "\n\n%c IS THE WINNER !\n",p.player2);
    }
    fclose(fp);
    return 0;
}
