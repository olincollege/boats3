/*
Contains the model of our system including the location of sprite, status of
sprite (what image it is), the intended direction of movement of the sprite,
etc.
*/

#include "model.h"

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h> /* printf and fprintf */
#include <stdlib.h>
/*
typedef struct sprite {
  SDL_Texture *texture;
  SDL_Rect *rect;
  const char *path;
} sprite;*/



int find_sprite_grid(SDL_Texture *texture, int*row_height,int*column_width,int num_rows, int num_columns){
 //function for automatically finding frame rectangles dimensions
 int height_texture;
 int width_texture;
 if(0!= SDL_QueryTexture(texture,NULL, NULL, &height_texture, &width_texture)){
  printf("QueryTexture Error in find_sprite_grid\n");
  return 1;
 }
 printf("total texture height: %d total texture width: %d\n",height_texture,width_texture);

  *row_height = height_texture/num_rows;
  *column_width = width_texture/num_columns;

  printf("row height: %d colm width: %d\n",*row_height,*column_width);
 return 0;
}

int initialize_animation(animation* loop,
                          int num_rows,int num_col,int row_number){
  //initialize an animation, num_rows, num_col, row_number num_frames, 
  //and frames_loop content must be set individually for each animation  
  //assume the texture, num frames and frame loop parameters are already set
  
  //bounds check the initialization
  if (row_number >num_rows){
    printf("row number too large for texture");
    return 1;

  }
  int row_height;
  int column_width;
  if (find_sprite_grid(loop->texture,&row_height,&column_width,num_rows,num_col)){
    printf("Error Initializing animation");
    return 1;
  }
  //initialize to frame 0 in loop
  loop->width = column_width;
  loop->height = row_height;
  loop->ypos = row_height*row_number;
  //initialize to first frame
  loop->frame_index = 0;

  return 0;
}

void end_program(SDL_Texture *texture, SDL_Surface *image,
                 SDL_Renderer *renderer, SDL_Window *window) {
  SDL_DestroyTexture(texture);
  printf("got here 4\n");
  SDL_FreeSurface(image);
  printf("got here 5\n");
  SDL_DestroyRenderer(renderer);
  printf("got here 6\n");
  SDL_DestroyWindow(window);
  printf("got here 7\n");
  SDL_Quit();
  printf("got here 8\n");
}

void loop_Animation(animation *loop, SDL_Renderer *renderer,
                    SDL_Rect *box_ptr) {

  int xpos;

  xpos = loop->frames_loop[loop->frame_index] * loop->width;
  // printf("%d\n", xpos);

  SDL_Rect crop_sprite = {
      .x = xpos, .y = loop->ypos, .w = loop->width, .h = loop->height};

  if (0 != SDL_RenderCopy(renderer, loop->texture, &crop_sprite, box_ptr)) {
    printf("error animating");
  }
  //printf("animated frame %d\n",loop->frame_index);
  // update the position in the loop
  loop->frame_index = loop->frame_index + 1;
  loop->frame_index = loop->frame_index % loop->num_frames;

  
}

SDL_Texture * initialize_texture(const char* filepath, SDL_Renderer * renderer){
  //initialize an SDL_texture from a filepath

  SDL_Surface* image = IMG_Load(filepath);
  if (image == NULL){
    printf("Surface creation error");
    return NULL;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL){
    printf("Texture creation error");
    return NULL;
  }

  SDL_FreeSurface(image);
  return texture;

}
