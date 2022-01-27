#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buffer[1000];

  if (argc > 1) strcpy(buffer,argv[1]);
  else {
    printf("Enter a directory:\n");
    int err = read(STDIN_FILENO, buffer, sizeof(buffer));
    if (err == -1) printf("error: %s", strerror(errno));
    buffer[strlen(buffer) - 1] = 0;
  }
  
  DIR *dir;
  struct dirent *d;
  struct stat file;
  long long file_size;

  dir = opendir(buffer);
  if (!dir) {
    printf("error: %s", strerror(errno));
    return 0;
  }
  while ((d=readdir(dir))!=NULL){
    if(d->d_type == 8) {
      stat(d->d_name, &file);
      file_size += file.st_size;
    }
  }
    
  printf("Statistics for directory: %s\n", buffer);
  printf("Total Directory Size: %lld Bytes\n", file_size);

  rewinddir(dir);
  printf("Directories: \n");
  while ((d=readdir(dir))!=NULL){
    if(d->d_type == 4) printf("\t%s\n",d->d_name);
  }
  rewinddir(dir);
  printf("Regular Files: \n");
  while ((d=readdir(dir))!=NULL){
    if(d->d_type == 8) {
      stat(d->d_name, &file);
      file_size += file.st_size;
      printf("\t%s\n",d->d_name);
    }
  }
  
  return 0;
}
