#include <stdio.h>
#include <stdlib.h>
int main(){
    char* datakun=(char*)calloc(1000000,sizeof(char));
    char* datameirei_ptr=datakun;
    //++*datameirei_ptr;
    *datameirei_ptr=getchar();
    ++datameirei_ptr;
    while(*datameirei_ptr){
        ++datameirei_ptr;
        --datameirei_ptr;
        ++*datameirei_ptr;
    }
    free(datakun);
    return 0;
}