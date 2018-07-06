#include<bits/stdc++.h>
using namespace std;
 
struct Move
{
    int row, col;
};
 
char player = 'x', opponent = 'o';
 
bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='_')
                return true;
    return false;
}
 
int evaluate(char b[3][3])
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row<3; row++)
    {
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==player)
                return +10;
            else if (b[row][0]==opponent)
                return -10;
        }
    }
 
    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==player)
                return +10;
 
            else if (b[0][col]==opponent)
                return -10;
        }
    }
 
    // Checking for Diagonals for X or O victory.
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==player)
            return +10;
        else if (b[0][0]==opponent)
            return -10;
    }
 
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==player)
            return +10;
        else if (b[0][2]==opponent)
            return -10;
    }
 
    // Else if none of them have won then return 0
    return 0;
}
 
int minimax(char board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);
 
    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;
    if (score == -10)
        return score;
 
    if (isMovesLeft(board)==false)
        return 0;
 
    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;
 
        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = player;
 
                    // Call minimax recursively and choose
                    // the maximum value
                    best = max( best,
                        minimax(board, depth+1, !isMax) );  
                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
 
    // If this minimizer's move
    else
    {
        int best = 1000;
 
        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = opponent;
 
                    // Call minimax recursively and choose
                    // the minimum value
                    best = min(best,
                           minimax(board, depth+1, !isMax));
 
                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}
 
// This will return the best possible move for the player
Move findBestMove(char board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
 
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if celll is empty
            if (board[i][j]=='_')
            {
                // Make the move
                board[i][j] = player;
 
                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, 0, false);
 
                // Undo the move
                board[i][j] = '_';
 
                if (moveVal > bestVal)
                {  
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
 
    if(bestVal==10) cout<<"Bot has win\n";
    else {
    	if(bestVal==0) cout<<"Draw \n";
    	else cout<<"You win\n";
	}
 
    return bestMove;
}
 
// Driver code
int main()
{  
    char board[3][3] =
    {
        { '_', '_', 'o' },
        { '_', 'x', 'x' },
        { '_', 'o', 'o' }
    };
    
    for(int i=0;i<3;i++){
    	for(int j=0;j<3;j++) cout<<board[i][j]<<" ";
    	cout<<"\n";
	}
	cout<<"\n";
    Move bestMove = findBestMove(board);
   
   
    printf("The Optimal Move is :n");
    printf("ROW: %d COL: %d\n", bestMove.row,
                                  bestMove.col );
                                  
                                  int x=bestMove.row;
                                  int y=bestMove.col;
                 cout<<" \n";                 
     for(int i=0;i<3;i++){
    	for(int j=0;j<3;j++) {
		if(i==x&&y==j) cout<<"x ";
		else cout<<board[i][j]<<" ";}
    	cout<<"\n";
	}
    return 0;
}
