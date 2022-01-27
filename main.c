#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char FILE_PATH[1000];
  if (argc > 1) strcpy(FILE_PATH,argv[1]);
  else {
    printf("Enter a directory:");
    int err = read(STDIN_FILENO, FILE_PATH, sizeof(FILE_PATH));
    if (err == -1) printf("Error %d: %s", errno, strerror(errno));
    FILE_PATH[strlen(FILE_PATH) - 1] = 0;
  }
  
  DIR *dir;
  struct dirent *d;
  struct stat stats;
  long long filesizes;

  dir = opendir(FILE_PATH);
  if (!dir) {
    printf("error: %s", strerror(errno));
    return 0;
  }

  while ((d=readdir(dir))!=NULL){
    if(d->d_type == 8) {
      stat(d->d_name, &stats);
      filesizes+=stats.st_size;
    }
  }
  printf("Statistics for directory: %s\n", FILE_PATH);
  printf("Total Directory Size: %lld Bytes\n", filesizes);

  rewinddir(dir);
  printf("Directories: \n");
  while ((d=readdir(dir))!=NULL){
    if(d->d_type == 4) printf("\t%s\n",d->d_name);
  }

  rewinddir(dir);
  printf("Regular Files: \n");
  while ((d=readdir(dir))!=NULL){
    if(d->d_type == 8) {
      stat(d->d_name, &stats);
      filesizes+=stats.st_size;
      printf("\t%s\n",d->d_name);
    }
  }

  return 0;
}
