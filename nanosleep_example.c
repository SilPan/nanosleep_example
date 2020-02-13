#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

bool got_sleep_duration = false;
double sleep_duration;  /* in seconds */
struct timespec timespec_req, timespec_rem;

void usage(void){
  fprintf(stderr, "fuck off\n");
}

int main(int argc, char** argv){

  if(argc != 2){
    perror("1 argument needed\n");
    exit(EXIT_FAILURE);
  }

  fprintf(stderr, "sleep argument is %s\n", argv[1]);
  got_sleep_duration = true;
  char *endptr;
  errno = 0;
  sleep_duration = strtod(argv[1], &endptr);
  if (errno != 0) {
       perror("Coult not parse delay time");
       usage();
       exit(EXIT_FAILURE);
   }

   if (endptr == argv[1]) {
       fprintf(stderr, "No digits were found\n");
       exit(EXIT_FAILURE);
   }

  if(sleep_duration < 0){
    fprintf(stderr, "There are no negative delays.");
    exit(EXIT_FAILURE);
  }

  /** Split double of seconds into timespec's (long) seconds and (long) nanoseconds. **/
  timespec_req.tv_sec = (time_t) sleep_duration;
  timespec_req.tv_nsec = (long) ((sleep_duration - (long) sleep_duration) * 1000000000);
  fprintf(stderr, "sleep argument got parsed to %lf\n", sleep_duration);


  fprintf(stderr, "sleeping with %li, %li\n", timespec_req.tv_sec, timespec_req.tv_nsec);
  if(nanosleep(&timespec_req, &timespec_rem) != 0){
    if(errno==EINTR){
      /*Just exit if we've got interrupted, we don't have a signal handler*/
      //TODO:restart sleep
      exit(EXIT_FAILURE);
    }else{
      fprintf(stderr, "errno is EINVAL: %s\n", errno==EINVAL?"true":"false");
      perror("Could not sleep");
      exit(EXIT_FAILURE);
    }
  }

  return 0;
}
