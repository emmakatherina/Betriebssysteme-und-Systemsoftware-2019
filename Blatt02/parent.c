#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

extern char **environ; // standard libc process environment

int main(void) {
  pid_t child1;
  pid_t child2;
  char const* args[] = { "./child1", NULL };
  char const* args2[] = { "./child2", NULL };

  int ret = posix_spawn(&child1, *args, NULL, NULL, (char* const*)args, environ);
  int ret2 = posix_spawn(&child2, *args2, NULL, NULL, (char* const*)args2, environ);
  if(ret != 0) {
    fprintf(stderr, "Could not start child process!\n");
    abort();
  }else if(ret == 0){
	printf("child1: %i\n", child1);
	if(ret2 == 0){
	printf("child1: %i\n", child2);
	}
 }


  /*while(true) {
    //write(fileno(stdout), "B", 1);
    return 0;
  }*/
}
