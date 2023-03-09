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
 if(0!= SDL_QueryTexture(texture,NULL, NULL,&width_texture,&height_texture)){
  printf("QueryTexture Error in find_sprite_grid\n");
  return 1;
 }
 //printf("total texture height: %d total texture width: %d\n",height_texture,width_texture);

  *row_height = height_texture/num_rows;
  *column_width = width_texture/num_columns;

  //printf("row height: %d colm width: %d\n",*row_height,*column_width);
 return 0;
}

int initialize_animation(animation* loop,
                          int num_rows,int num_col,int row_number){
  //initialize an animation, num_rows, num_col, row_number num_frames, 
  //and frames_loop content must be set individually for each animation  
  //assume the texture, num frames and frame loop parameters are already set
  
  //bounds check the initialization
  if (row_number >num_rows){
    printf("row number too large for texture\n");
    return 1;

  }
  int row_height;
  int column_width;
  if (find_sprite_grid(loop->texture,&row_height,&column_width,num_rows,num_col)){
    printf("Error Initializing animation\n");
    return 1;
  }
  printf("got here 2\n");
  //initialize to frame 0 in loop
  loop->width = column_width;
  loop->height = row_height;
  loop->ypos = row_height*row_number;
  //initialize to first frame
  loop->frame_index = 0;
  loop->super_animation_index =0;

  return 0;
}

void end_program(SDL_Texture *texture, SDL_Surface *image,
                 SDL_Renderer *renderer, SDL_Window *window) {
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  printf("successfully exited program\n");
}

void loop_Animation(animation *loop, SDL_Renderer *renderer,
                    SDL_Rect *box_ptr) {

  int xpos;

  xpos = loop->frames_loop[loop->frame_index] * loop->width;
  // printf("%d\n", xpos);

  SDL_Rect crop_sprite = {
      .x = xpos, .y = loop->ypos, .w = loop->width, .h = loop->height};

  if (0 != SDL_RenderCopy(renderer, loop->texture, &crop_sprite, box_ptr)) {
    printf("error animating\n");
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
    printf("Surface creation error for %s\n",filepath);
    return NULL;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL){
    printf("Texture creation error for %s\n",filepath);
    return NULL;
  }

  SDL_FreeSurface(image);
  return texture;

}

int make_animation_box(SDL_Rect * box,animation *loop,int xpos, int ypos,float scale){

  box->x = xpos;
  box->y = ypos;
  box->w = floor(loop->width * scale);
  box->h = floor(loop->height * scale);

  return 0;

}

void animate_sequential(SDL_Renderer * renderer,animation animations[10],SDL_Rect *box,int num_animations){

  //first frame's super animation index tracks the total state,
  //will not work if the first

  int frame_sum = -1;
  int current_animation = 0;
  int not_found = 1;

  

  for (int i =0; i <num_animations;i++){
    frame_sum += animations[i].num_frames;
    //animations[0]->super_animation_index
    //animations[0].super_animation_index
    
    if (not_found && animations[0].super_animation_index < frame_sum){
      //find the index of the current animation
      current_animation = i;
      not_found = 0;
    }
  }
  loop_Animation(&(animations[current_animation]),renderer,box);

  animations[0].super_animation_index++;
  animations[0].super_animation_index = animations[0].super_animation_index %frame_sum;
}

void make_sequential_animation(animation animation_list[10],animation * uninitialized_animation,int num_rows, int num_cols,int num_sequential_rows){

  //makes a sequential animation, initialize a bunch of animation objects

  for (int i = 0; i <num_sequential_rows;i++){
    //copy the struct

    printf("cat %d initialization\n",i);
    //(*animation_list)[i].texture
    //(animation_list[i])->num_frames

    animation_list[i].texture = uninitialized_animation->texture;
    printf("got here 1\n");
    animation_list[i].num_frames = uninitialized_animation->num_frames;
    for(int j=0; j<uninitialized_animation->num_frames;j++){
          *(animation_list[i].frames_loop + j) = *(uninitialized_animation->frames_loop +j);

          printf("%d %d\n",animation_list[i].frames_loop[j],uninitialized_animation->frames_loop[j]);
    }//*/
    
    

    initialize_animation(&(animation_list[i]),num_rows,num_cols,i);
    //initialize for each row
  }
  printf("sequential animation created");

}
