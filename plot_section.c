#include <stdlib.h> //malloc(), size_t
#include <stdint.h> //uint8_t
#include <stdio.h> //fprintf(), sscanf()
#include <math.h> //fabsf()

#define max_iteration 256

int main(int argc, char *argv[]){
  int height,width;
  size_t dimensions;
  int column,row;
  int iteration;
  int i;
  float coord1x,coord1y,coord2x,coord2y;
  float width_scale_factor,height_scale_factor;
  float x0,y0,x,y,xtemp;
  uint8_t *image;
  
  if (argc < 7){
    fprintf(stderr,"wrong number of parameters: %d/7\n",argc);
    return 1;
  }

  sscanf(argv[1],"%d",&height);
  sscanf(argv[2],"%d",&width);
  sscanf(argv[3],"%f",&coord1x);
  sscanf(argv[4],"%f",&coord1y);
  sscanf(argv[5],"%f",&coord2x);
  sscanf(argv[6],"%f",&coord2y);

  dimensions = (size_t) (width*height);
  image = (uint8_t *) malloc(dimensions);

  width_scale_factor = fabsf(coord1x-coord2x)/((float)width);
  height_scale_factor = fabsf(coord1y-coord2y)/((float)height);

  i = 0;
  if (argc == 8){
    fprintf(stderr,"Amazing calculations taking place...\n");
  }
  for (column=0;column<height;column++){
    if (argc == 8){
      fprintf(stderr,"\r%.2f%%",((float)column)/((float)height)*100.0);
    }
    for (row=0;row<width;row++){
      x0 = row*width_scale_factor + coord1x;
      y0 = column*height_scale_factor + coord2y;
      x = 0.0;
      y = 0.0;
      iteration = 0;
      while (x*x+y*y < 4.0 && iteration < max_iteration){
	xtemp = x*x - y*y + x0;
	y = 2*x*y + y0;
	x = xtemp;
	iteration++;
      }
      //fputc(iteration-1,stdout); THIS IS BAD, THIS MESSES WITH RECURSIVITY
      image[i++] = iteration-1;
    }
  }
  if (argc == 8){
    fprintf(stderr,"\nFinished a process (more might still be going)\n");
  }
  for (i=0;i<dimensions;i++){
    fputc(image[i],stdout);
  }

  return 0;
}
