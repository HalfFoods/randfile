#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "random.h"

int random_number(){
  int file = open("/dev/random", O_RDONLY);
  if (file < 0) {
    printf("Opening /dev/random error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  int n;
  int b = read(file, &n, sizeof(int));
  if (b < 0){
    printf("Reading file error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  close(file);
  return n;
}

int main(){
  printf("Generating random numbers:\n");
  int arr[10];
  for (int i = 0; i<10; i++) {
    arr[i] = random_number();
    printf("\trandom %d: %d\n", i, arr[i]);
  }

  printf("\nWriting numbers to file...\n\n");
  int fd = open("output.txt", O_CREAT|O_EXCL|O_WRONLY, 0755);
  if (fd < 0) {
    fd = open("output.txt", O_WRONLY);
  }
  int b = write(fd, arr, 10 * sizeof(int));
  if (b < 0) {
    printf("Writing to output.txt error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  close(fd);

  printf("Reading numbers from file...\n\n");
  fd = open("output.txt", O_RDONLY);
  if (b < 0) {
    printf("Opening output.txt error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  int newArr[10];
  b = read(fd, newArr, 10 * sizeof(int));
  if (b < 0) {
    printf("Reading output.txt error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  close(fd);

  printf("Verification that written values were the same:\n");
  for (int i = 0; i<10; i++) {
    printf("\trandom %d: %d\n", i, newArr[i]);
  }
}
