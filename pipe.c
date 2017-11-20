#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

  int sends[2];
  if (pipe(sends) == -1) {
    printf("Pipe failure!\n");
  }

  int backs[2];
  if (pipe(backs) == -1) {
    printf("Pipe failure!\n");
  }

  int READ = 0;
  int WRITE = 1;
  
  int f = fork();
  
  if (f != 0) {
    // parent
    close(sends[READ]);//can only write to sends file descriptors
    close(backs[WRITE]);//can only read from backs file descriptors
    int num = 10;
    printf("Parent sending the number %d...\n", num);
    write(sends[WRITE], &num, sizeof(num));
    read(backs[READ], &num, sizeof(num));
    printf("Parent received number %d!\n", num);
  }
  else {
    //child
    close(sends[WRITE]);//can only read from sends
    close(backs[READ]);//can only write to backs
    int num;
    read(sends[READ], &num, sizeof(num));
    printf("Child being forced to do maths for parent on: %d...\n", num);
    num = num * 10; //arithmetic operation
    write(backs[WRITE], &num, sizeof(num));
  }

  return 0;
}
