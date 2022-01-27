#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>

int print_dir(char open[100], char str_dir[100], char str_file[100]){ 
    DIR *d = opendir(open);
    if (errno != 0) { 
        printf("%s\n", strerror(errno));
        return -1;
    }
    struct dirent * dir;
    int size = 0;
    while((dir = readdir(d)) != NULL){
        struct stat file;
        stat(dir->d_name, &file);
        if(dir->d_type == 4){
            printf("\t%s", strcat(str_dir, "\n"));
            strcat(str_dir, dir->d_name);
        } else {
            printf("\t%s", strcat(str_file,"\n"));
            strcat(str_file, dir->d_name);
        }
        size += file.st_size;
    }
    return size;
}

int main(int argc, char * argv[]){ 
    char str_dir[100] = "";
    char str_file[100] = "";
    char buffer[100] = "";
    if(argc <= 1){
        printf("Statistics for directory:\n ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strlen(buffer)-1] = 0;
    } else {
        strcpy(buffer, argv[1]);
    }
    int x = print_dir(buffer, str_dir, str_file);
    printf("Total Directory Size: %ul Bytes\n", x);
    printf("Directories: %s\n", str_dir);
    printf("Regular Files: %s\n", str_file);
    return 0;
}
