#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a) > (b) ? (a) : (b))

int jump(int** leaves, int rows, int cols)
{
    int maxBrokenLeaves = 0;

    for(int row=0; row<rows; row++)
    {
        for(int i=0, j=0; i<cols; i++)
        {
            if(leaves[row][i] != 0)
            {
                if((leaves[row][i] | leaves[row][j]) == 3)
                {
                    maxBrokenLeaves = max(maxBrokenLeaves, i-j-1);
                }
                j = i;
            }
        }
    }

    for(int col=0; col<cols; col++)
    {
        for(int i=0, j=0; i<rows; i++)
        {
            if(leaves[i][col] != 0)
            {
                if((leaves[i][col] | leaves[j][col]) == 3)
                {
                    maxBrokenLeaves = max(maxBrokenLeaves, i-j-1);
                }
                j = i;
            }
        }
    }

    return maxBrokenLeaves;
}

int main()
{
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    int **leaves;
    leaves = malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++)
    {
        leaves[i] = malloc(cols * sizeof(int));
        for(int j=0; j<cols; j++)
        {
            scanf("%d", &leaves[i][j]);
        }
    }
    printf("%d", jump(leaves, rows, cols));
    for(int i=0; i<rows; i++)
    {
        free(leaves[i]);
    }
    free(leaves);
    return 0;
}
