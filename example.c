#include <stdlib.h>
#include <stdio.h>
#include "example.h"

typedef struct {
    unsigned sp_len;
    unsigned n_sp;
} context_t;


void *create_context(unsigned sp_len, unsigned n_sp)
{
    printf("Creating context, sp_len: %d, n_sp: %d\n", sp_len, n_sp);
    context_t *context;
    context = (context_t *)malloc(sizeof(context_t));
    context->sp_len = sp_len;
    context->n_sp = n_sp;
    return (void *)context;
}

void free_context(void *context)
{   
    printf("Freeing context\n");
    free(context);
}

void calc_argmax(void *context, double *array, double *out, int *status)
{
    context_t *ctx = (context_t *)context;
    unsigned n_sp = ctx->n_sp;
    unsigned sp_len = ctx->sp_len;
    double max;
    double *sp;
    int i, j;

    for (i = 0; i < n_sp; i++)
    {   
        sp = array + i * sp_len;
        max = sp[0];
        out[i] = 0;
        for(j = 1; j < sp_len; j++)
        {
            if(sp[j] > max)
            {
                out[i] = j;
                max = sp[j];
            }
        }
        status[i] = STATUS_OK;
    }
}

