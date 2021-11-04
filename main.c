#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>

//argc: number of command line args
//argv: array of command line args as strings
int main(int argc, char* argv[]){
  char buffer[100];

  if(argc > 1) strcpy(buffer, argv[1]);
  else{
    printf("Enter a directory: ");
    //fgets reads in data from file stream and stores it as strings
    fgets(buffer, sizeof(buffer), stdin);
  }


  DIR *dir;
  //struct dirent contains the information stored in a directory file
  struct dirent *entry;
  struct stat file;
  int file_size = 0;

  //open directories
  dir = opendir(buffer);
  if(!dir){
    printf("error: %s", strerror(errno));
    return -1;
  }

  while(entry){
    if(entry->d_type == 8){
      stat(entry->d_name, &file);
      file_size += file.st_size;
    }
  }
  printf("Statistics for directory: %s\n", buffer);
  printf("Total Directory Size: %d Bytes", file_size);

  printf("Directories: \n");
  rewinddir(dir);
  while(entry){
    // 4 is directory
    if(entry->d_type == 4) printf("\t%s\n", entry->d_name);
  }

  printf("Regular Files: \n");
  //rewinddir resets the directory stream of d to the beginning
  rewinddir(dir);
  while(entry){
    // 8 is regular file
    if(entry->d_type == 8) printf("\t%s\n", entry->d_name);
  }

  
  closedir(dir);
  return 0;
}