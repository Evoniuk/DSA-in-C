/*
    You're given two crystal balls. You need to figure out the height from which
    they can be dropped in the most optimal way.

    What this equates to is searcing through an array of booleans, looking for
    the first true value, but only using two for loops. The optimal way to do
    this is to jump through the array in jumps of sqrt(len). The worst case
    then becomes jumping through sqrt(len) times, finding out you went to far,
    then going back through the last segment of the array, which is of length
    sqrt(len). This running time is O(sqrt(len) + sqrt(len)) = O(sqrt(len)).

    if you choose other roots, the running time in general is
    O(len^(1/n) + len^(n-1/n)), which is minimized when n = 2, the optimal case
    described above.
*/
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

int breakpoint(bool* breaks_arr, int length)
{
    // using the sqrt of the length gives 
    // the ideal running time of O(sqrt(N))
    int jump_amount = (int)floor(sqrt(length));

    int result = 0;
    for (; result < length; result += jump_amount)
        if (breaks_arr[result]) break;

    result -= jump_amount;

    for (int i = 0; i <= jump_amount; i++, result++)
        if (breaks_arr[result]) return result;

    return -1;
}

int main()
{
    bool breaks_arr[] = {false, false, false, false, true, true};
    printf("%d\n", breakpoint(breaks_arr, 6));
    
    return 0;
}
