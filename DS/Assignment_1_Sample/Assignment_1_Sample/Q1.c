#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a) > (b) ? (a) : (b))

int jump(int* leaves, int leavesSize)
{
    int maxBrokenLeaves = 0;
    for(int i=0, j=0; i<leavesSize; i++)
    {
        if(leaves[i] != 0)
        {
            if((leaves[i] | leaves[j]) == 3)
            {
                maxBrokenLeaves = max(maxBrokenLeaves, i-j-1);
            }
            j = i;
        }
    }
    return maxBrokenLeaves;
}

int main()
{
    int leavesSize;
    scanf("%d", &leavesSize);
    int *leaves = malloc(leavesSize * sizeof(int));
    for(int i=0; i<leavesSize; i++)
    {
        scanf("%d", &leaves[i]);
    }
    printf("%d", jump(leaves, leavesSize));
    free(leaves);
    return 0;
}
