#include <stdlio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//int main(int argc, char** argv)



int parser_read(const char* filename){

  FILE* fd = NULL;

  fd = fopen(filename, "r");
  
  if(!fd){
    printf("error : %s : no such file\n", fd);
    return -1;
  }

  int end = 0;

  while(!end){

    char lineHeader[64];

    int res = fscanf(fd, "%s", lineHeader);
    if (res == EOF)
      break;

    if(strcmp(lineHeader, "end\n") == 0 || strcmp(lineHeader, "end") == 0){
      break;
    }
  
    if(strcmp(lineHeader, "count") == 0){
      fscanf(fd, "%d\n", ps.count);
      continue;
    }

    if(strcmp(lineHeader, "force") == 0){
      fscanf(fd, "%d %d %d %d\n", ps.forcemin[0], ps.forcemin[1], ps.forcemax[0], ps.forcemax[1]);
      continue;
    }

    if(strcmp(lineHeader, "size") == 0){
      fscanf(fd, "%d %d\n", ps.sizemin, ps.sizemax);
      continue;
    }

    if(strcmp(lineHeader, "color") == 0){
      fscanf(fd, "%d %d %d %d %d %d\n", ps.colormin[0], ps.colormin[1], ps.colormin[2],
	     ps.colormax[0], ps.colormax[1], ps.colormax[2]);
      continue;
    }

    if(strcmp(lineHeader, "gravity") == 0){
      fscanf(fd, "%d %d\n", ps.gravity[0], ps.gravity[1]);
      continue;
    }

    if(strcmp(lineHeader, "lifetime") == 0){
      fscanf(fd, "%d %d\n", ps.ltmin, ps.ltmax);
      continue;
    }
    
  }

  return 0;

}
			     
