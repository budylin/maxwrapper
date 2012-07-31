#include <stdio.h>
#include <stdarg.h>

#define STATUS_OK 0
#define STATUS_NOISY 1

typedef struct {
    unsigned sp_len;
    unsigned n_sp;
    double treshhold;
} context_t;


void *create_context(unsigned sp_len, unsigned n_sp, ...)
{
    double treshhold;
    context_t *context;
    va_list argp;
    va_start(argp, n_sp);
    treshhold = va_arg(argp, double);
    va_end(argp);
    context = (context_t *)malloc(sizeof(context_t));
    context->sp_len = sp_len;
    context->n_sp = n_sp;
    context->treshhold = treshhold;
}

void free_context(void *context)
{
    free(context);
}

void calc_argmax(void *context, double *array, double *out, int *status)
{
    context_t *ctx = (context_t *)context;
    unsigned n_sp = ctx->n_sp;
    unsigned sp_len = ctx->sp_len;
    double treshhold = ctx->treshhold;
    double average, stddevsq, maxdevsq, max, tmp;
    int i, j;

    for (i = 0; i < n_sp; i++)
    {
        average = out[i] = array[i * sp_len + 0];
        for(j = 1; j < sp_len; j++)
        {
            if(array[i * sp_len + j] > out[i])
                out[i] = j;
            average += array[i * sp_len + j];
        }
        average /= sp_len;
        max = out[i];
        stddevsq = 0.;
        for(j = 0; j < sp_len; j++)
        {   
            tmp = array[i * sp_len + j] - average;
            stddevsq += tmp * tmp;
        }
        stddevsq = stddevsq / sp_len;
        maxdevsq = (max - average) * (max - average);
        if (maxdevsq <= treshhold * treshhold * stddevsq)
            status[i] = STATUS_NOISY;
        else
            status[i] = STATUS_OK;
        

    }

}

int main()
{
    double out[2];
    int status[2];
    double arr[2 * 5] = {0,0,0,0,0,  0,0,0,1,0};
    void *ctx = create_context(5,2,1.);
    int i;
    calc_argmax(ctx, arr, out, status);
    free_context(ctx);
    for (i = 0; i < 2; i++)
        printf("%d's array: maximum at %lf, status %d\n", i, out[i], status[i]);
    return 0;
}
