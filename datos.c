#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

int decimals = 5;
double a = 0.0;
double b = 1.0; 
double step = 0.0001;

int main(int argc, char **argv)
{
    int opt;
    double x;
    while((opt = getopt(argc, argv, "a:b:s:d:")) != EOF) {
        switch(opt) {
        case 'a': sscanf(optarg, "%lg", &a); break;
        case 'b': sscanf(optarg, "%lg", &b); break;
        case 's': sscanf(optarg, "%lg", &step); break;
        case 'd': sscanf(optarg, "%d", &decimals); break;
        } /* switch */
    } /* while */

    if (step >= 0.0) {
        for (x = a; x < b; x += step) {
            printf("%0.*lg\n", decimals, x);
        }
    } else {
        for (x = b; x > a; x += step) {
            printf("%0.*lg\n", decimals, x);
        }
    }
} /* main */
