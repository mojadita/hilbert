/*
 * Hilbert curve -- Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Thu Apr  7 08:31:31 EEST 2016
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <complex.h>

static struct status {
    char *name; /* status name */
    int xy[4];
    struct status *next[4];
}   SA, SD, SU, SC;

static struct status
    SA = { "SA", { 0, 1, 3, 2 }, { &SD, &SA, &SA, &SC, } },
    SD = { "SD", { 0, 2, 3, 1 }, { &SA, &SD, &SD, &SU, } },
    SU = { "SU", { 3, 2, 0, 1 }, { &SC, &SU, &SU, &SD, } },
    SC = { "SC", { 3, 1, 0, 2 }, { &SU, &SC, &SC, &SA, } };

void hilbert(double r, double *x, double *y)
{
    double oldX, oldY;
    double factor = 1.0;
    struct status *st = &SA;
    int i;

    assert(r >= 0.0 && r < 1.0);
    *x = *y = 0.0;
    for(int i = 0; i < 56; i++) {
        int input;
        oldX = *x; oldY = *y;
        r *= 4.0;
        input = r; 
        /* printf("  State: %s, r: %0.17lg, ", st->name, r); */
        factor /= 2.0;
        *x += st->xy[input] & 2 ? factor : 0.0;
        *y += st->xy[input] & 1 ? factor : 0.0;
        st = st->next[input];
        /* printf("  x: %0.17g, y: %0.17g\n", *x, *y); */
        r -= input;
    }
} /* hilbert */

#define N   5
#define EXP2N   (1 << N)

double test_points[EXP2N+1];

double modulus(double x, double y) {
    return sqrt(x*x + y*y);
}

int main(int argc, char **argv)
{
    int opt, decimals = 5;
    char line[1024];

    while ((opt = getopt(argc, argv, "d:")) != EOF) {
        switch (opt) {
        case 'd': decimals = atoi(optarg); break;
        } /* switch */
    } /* for */

    if (decimals < 0) decimals = 0;

    /* FIRST, PREPARE THE TEST POINTS */
    {
        int i;
        double delta = 1.0/EXP2N;
        double acum = 0.0;
        for (i = 0; i < EXP2N+1; i++) {
            test_points[i] = acum;
            acum += delta;
        }
    }

#if 0
    /* THEN DO THE TESTS. */
    {
        int i;
        double delta = test_points[1] - test_points[0];
        for (; delta > 3.0e-13; delta /= 2.0) {
            printf("   Trying delta=%0.*g...\n", decimals, delta);
            double epsilon = 0.0;
            for (i = 0; i < EXP2N; i++) {
                double r = test_points[i];
                double x, y;
                hilbert(r, &x, &y);
                printf("Point r=%0.*g, image=(%0.*g, %0.*g):\n", 
                        decimals, r, decimals, x, decimals, y);
                double ri;
                double step = delta/4096;
                for (ri = r-delta; ri < r+delta; ri += step) {
                    if (ri < 0 || ri >= 1.0) continue;
                    double xi, yi;
                    hilbert(ri, &xi, &yi);
                    double dist = modulus(xi - x, yi -y);
                    if (epsilon < dist) epsilon = dist;
                }
            }
            printf("          epsilon >= %0.*g\n", decimals, epsilon);
        }
    }
#else

    while(fgets(line, sizeof line, stdin)) {
        double r, x, y;

        sscanf(line, "%lg", &r);
        hilbert(r, &x, &y);
        printf("%0.*lf\t%0.*lf\t%0.*lf\n",
                decimals, r, decimals, x, decimals, y);
    }
#endif
} /* main */
