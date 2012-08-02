#include <stdio.h>
#include "example.h"

int main()
{
    double out[2];
    int status[2];
    double arr[2 * 20] = {1,1,1,1,1,1,1,1,1,1.1,1,1,1,1,1,1,1,1,1,1,\
                          0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    void *ctx = create_context(20,2);
    int i;
    calc_argmax(ctx, arr, out, status);
    free_context(ctx);
    for (i = 0; i < 2; i++)
        printf("%d's array: maximum at %lf, status %d\n", i, out[i], status[i]);
    return 0;
}
