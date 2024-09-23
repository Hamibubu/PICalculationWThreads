// Abraham de León Gutiérrez
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

// CALCULATE THE HEIGHT f(x) = sqrt(1-y2)
long double f(long double  x){
    return sqrt(1.0 - x*x);
}

// FUNTION TO CALCULATE PI
long double calculate_pi(long long int subintervals){
    long double base = 1.0 / subintervals; // GET THE BASE OF EACH RECTANGLE
    long double halfbase=0.0, heigth=0.0, area=0.0; // INITIALIZATION ALL VARIABLES

    for (long long int i=0; i<subintervals; i++){ // CALCULATE THE AREA OF EACH RECTANGLE
        halfbase=(i*base)+(base/2.0); // GET THE HALF OF THE BASE (Xi + Base) / 2
        heigth = f(halfbase); // GET THE HEIGHT 
        area += (heigth * base); // AREA OF THE RECTANGLE AREA = BASE * HEIGHT
    }

    return area*4.0; // GET THE VALUE OF PI ACCORDING TO THE FORMULA AREA=PI/4
}

int main(int argc, char **argv){
    struct timeval start, end; // INITIALIZATION OF TIME VARIABLES
    double elapsed_time;

    long long int subintervals; // TOTAL OF SUBINTERVALS
    long double pi; // DECLARATION OF THE VARIABLE FOR PI

    if (argc != 2) { // CHECK WHETHER THE USER HAS ENTERED THE NUMBER OF INTERVALS OR NOT
        fprintf(stderr, "usage: ./piserial <# of subintervals>\r\n");
		exit(1);
    }
    subintervals = atoll(argv[1]); // GET THE NUMBER OF INTERVALS

    gettimeofday(&start, NULL); // GET CURRENT TIME

    printf("[+] Calculating pi with %lld subintervals...\n",subintervals);
    printf("--------------------------------------------------\n");

    pi=calculate_pi(subintervals); // CALL THE FUNCTION

    gettimeofday(&end, NULL); // GET CURRENT TIME

    printf("[!] The result is %.15LF :)\n",pi);

    // GET THE TIME IT TOOK FOR THE EXECUTION TO COMPLETE
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    
    printf("\n    [i] It lasted:\n\n");
    printf("-----------------");
    printf("|     %6f secs    |",elapsed_time);
    printf("-----------------\n\r");
}