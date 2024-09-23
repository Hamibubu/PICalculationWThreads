// Abraham de León Gutiérrez
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

// Number of threads used
int nthreads=4;
pthread_mutex_t mutex; // MUTEX
long double areas = 0.0; // SUM OF AREAS
long long int subintervals; // TOTAL OF SUBINTERVALS

/// ARGUMENTS TO PASS TO FUNCTION, STARTING POINT AND TOTAL OF SUBINTERVALS ASSIGNED
struct args {
    long long int portion;
    long long int start;
};

// CALCULATE THE HEIGHT f(x) = sqrt(1-y2)
long double f(long double  x){
    return sqrt(1.0 - x*x);
}

// FUNTION TO CALCULATE PI
void *calculate_pi(void *argss){
    long double base = 1.0 / subintervals; // GET THE BASE OF EACH RECTANGLE

    long long int inicio,fin; // DECLARATION OF START AND END

    struct args *nargs = (struct args *)argss; // PASS THE STRUCT

    long double halfbase=0.0, height=0.0, area=0.0; // INITIALIZATION ALL VARIABLES

    inicio = nargs->start; // STARTING POINT OF THE GIVEN PORTION TO THE THREAD
    fin= nargs->start + nargs-> portion; // END OF THE PORTION
    
    for (long long int i=inicio; i<fin; i++){ // CALCULATE THE AREA OF EACH RECTANGLE
        halfbase=(i*base)+(base/2.0); // GET THE HALF OF THE BASE (Xi + Base) / 2
        height = f(halfbase); // GET THE HEIGHT
        area += (height * base); // AREA OF THE RECTANGLE AREA = BASE * HEIGHT
    }

    pthread_mutex_lock(&mutex); // LOCK MUTEX
    areas+=area; // SUM THE AREA
    pthread_mutex_unlock(&mutex); // UNLOCK MUTEX
    return NULL;
}

int main(int argc, char **argv){
    struct timeval start, end; // INITIALIZATION OF TIME VARIABLES
    double elapsed_time;

    pthread_mutex_init(&mutex, NULL); // INITIALIZATION OF MUTEX

    struct args *nargs; // INITIALIZATION OF THREAD-RELATED VARIABLES
    pthread_t *tid;
    tid=malloc(nthreads * sizeof(pthread_t));
    nargs=(struct args *)malloc(nthreads * sizeof(struct args));

    if (argc != 2) { // CHECK WHETHER THE USER HAS ENTERED THE NUMBER OF INTERVALS OR NOT
        fprintf(stderr, "usage: ./piserial <# of subintervals>\r\n");
		exit(1);
    }

    subintervals = atoll(argv[1]); // GET THE NUMBER OF INTERVALS

    gettimeofday(&start, NULL); // GET CURRENT TIME

    printf("[+] Calculating pi with %lld subintervals...\n",subintervals);
    printf("--------------------------------------------------\n");

    long long int intervals_portion = subintervals/nthreads; // CALCUTE THE INTERVALS FOR EACH THREAD
    long long int residuo = subintervals % nthreads; // GET THE REMAINING INTERVALS
    long long int current_start = 0; // VARIABLE TO CHECK THE STARTING POINT

    for (int i = 0; i < nthreads; i++) {
        if (residuo > 0) { // IF THERE ARE INTERVALS MISSING, INCREASE THE PORTION FOR THE THREAD
            nargs[i].portion=intervals_portion+1;
            residuo-=1;
        } else { // IF THERE ARE NO INTERVALS MISSING, SET THE NORMAL PORTION
            nargs[i].portion= intervals_portion;
        }
        nargs[i].start=current_start; // SET THE STARTING POINT
        current_start+=nargs[i].portion; // INCREASE THE STARTING POINT FOR THE NEXT STRUCT
        pthread_create(&tid[i], NULL, calculate_pi, (void *) &nargs[i]); // CALL THE FUNCTION
    }

    for(int i=0;i<nthreads;i++) // WAIT FOR THE THREADS TO FINISH
		pthread_join(tid[i],NULL);

    gettimeofday(&end, NULL); // GET CURRENT TIME

    long double pi = areas *4.0; // GET THE VALUE OF PI ACCORDING TO THE FORMULA AREA=PI/4

    printf("[!] The result is %.15LF :)\n",pi); 

    // GET THE TIME IT TOOK FOR THE EXECUTION TO COMPLETE
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    
    printf("\n    [i] It lasted:\n\n");
    printf("-----------------");
    printf("|     %6f secs    |",elapsed_time);
    printf("-----------------\n\r");
}