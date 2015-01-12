#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "linmath.h"
#include "particlesystem.h"

static float angle_progress = 0.0f;

void particle_system_gl_update(struct particle_system_t* tmp){

  int i = 0;

  for(i = 0; i < tmp->count; i++){

    //printf("BAIN\n");

    tmp->vertices[i*12+0] = tmp->particle[i].pos[0] - tmp->particle[i].siz;
    tmp->vertices[i*12+1] = tmp->particle[i].pos[1] - tmp->particle[i].siz;   
    tmp->vertices[i*12+2] = 0.0f;

    tmp->vertices[i*12+3] = tmp->particle[i].pos[0] + tmp->particle[i].siz;
    tmp->vertices[i*12+4] = tmp->particle[i].pos[1] - tmp->particle[i].siz;
    tmp->vertices[i*12+5] = 0.0f;

    tmp->vertices[i*12+6] = tmp->particle[i].pos[0] + tmp->particle[i].siz;
    tmp->vertices[i*12+7] = tmp->particle[i].pos[1] + tmp->particle[i].siz;
    tmp->vertices[i*12+8] = 0.0f;

    tmp->vertices[i*12+9] = tmp->particle[i].pos[0] - tmp->particle[i].siz;         
    tmp->vertices[i*12+10] = tmp->particle[i].pos[1] + tmp->particle[i].siz;           
    tmp->vertices[i*12+11] = 0.0f;

    tmp->couleurs[i*12+0] = tmp->particle[i].col[0];
    tmp->couleurs[i*12+1] = tmp->particle[i].col[1];
    tmp->couleurs[i*12+2] = tmp->particle[i].col[2];

    tmp->couleurs[i*12+3] = tmp->particle[i].col[0];
    tmp->couleurs[i*12+4] = tmp->particle[i].col[1];
    tmp->couleurs[i*12+5] = tmp->particle[i].col[2];

    tmp->couleurs[i*12+6] = tmp->particle[i].col[0];
    tmp->couleurs[i*12+7] = tmp->particle[i].col[1];
    tmp->couleurs[i*12+8] = tmp->particle[i].col[2];

    tmp->couleurs[i*12+9] =  tmp->particle[i].col[0];    
    tmp->couleurs[i*12+10] = tmp->particle[i].col[1];        
    tmp->couleurs[i*12+11] = tmp->particle[i].col[2];

    tmp->coordTex[i*12+0] = 0.0f;
    tmp->coordTex[i*12+1] = 0.0f;
    tmp->coordTex[i*12+2] = tmp->particle[i].alpha; 
    
    tmp->coordTex[i*12+3] = 1.0f;
    tmp->coordTex[i*12+4] = 0.0f;
    tmp->coordTex[i*12+5] = tmp->particle[i].alpha;

    tmp->coordTex[i*12+6] = 1.0f;
    tmp->coordTex[i*12+7] = 1.0f;
    tmp->coordTex[i*12+8] = tmp->particle[i].alpha;

    tmp->coordTex[i*12+9] = 0.0f;
    tmp->coordTex[i*12+10] = 1.0f;
    tmp->coordTex[i*12+11] = tmp->particle[i].alpha;

  }

  /*

  for(i = 0; i < tmp->count; i++){



  }

  for(i = 0; i < tmp->count; i++){
    

    


  }
  */

}

void particle_system_init(struct particle_system_t* tmp){

  int i = 0;

  float vel[2];

  float lifeinc = 0.0f;
  float liferation = tmp->ltmax / tmp->count;
  
  for(i = 0; i < tmp->count; i++){

    tmp->particle[i].pos[0] = tmp->pos[0];tmp->particle[i].pos[1] = tmp->pos[1];
    
    tmp->particle[i].life = (getRandomValue((int)(0), (int)(tmp->ltmin*100)))/100.0f;

    //tmp->particle[i].life = lifeinc; lifeinc += liferation;
    
    tmp->particle[i].vel[0] = (getRandomValue((int)(tmp->forcemin[0]*10), (int)(tmp->forcemax[0]*10)))/10.0f;
    tmp->particle[i].vel[1] = (getRandomValue((int)(tmp->forcemin[1]*10), (int)(tmp->forcemax[1]*10)))/10.0f;

    tmp->particle[i].col[0] = (getRandomValue((int)(tmp->colormin[0]*10), (int)(tmp->colormax[0]*10)))/10.0f;
    tmp->particle[i].col[1] = (getRandomValue((int)(tmp->colormin[1]*10), (int)(tmp->colormax[1]*10)))/10.0f;
    
    tmp->particle[i].col[2] = (getRandomValue((int)(tmp->colormin[2]*10), (int)(tmp->colormax[2]*10)))/10.0f;

    //tmp->particle[i].col[0] = 2.0f;

    tmp->particle[i].siz = (getRandomValue((int)(tmp->sizemin*10), (int)(tmp->sizemax*10)))/10.0f;
     

  }

}

struct particle_system_t* particle_system_create(float x, float y, int texture, float* uv, int nb){

  struct particle_system_t* tmp = malloc(sizeof(struct particle_system_t));
  
  tmp->count = nb; // cette ligne est totalement inutile
  
  tmp->pos[0] = x; tmp->pos[1] = y;
  tmp->gravity[0] = 0.0f; tmp->gravity[1] = 0.0f;
  tmp->forcemin[0] = 0.0f; tmp->forcemin[1] = 0.0f;
  tmp->forcemax[0] = 0.0f; tmp->forcemax[1] = 0.0f;
  tmp->colormin[0] = 0.0f; tmp->colormin[1] = 0.0f; tmp->colormin[2] = 0.0f;
  tmp->colormax[0] = 0.0f; tmp->colormax[1] = 0.0f; tmp->colormax[2] = 0.0f;
  tmp->ltmin = 0.0f; tmp->ltmax = 0.0f;
  tmp->sizemin = 0.0f; tmp->sizemax = 0.0f;

  tmp->tex = texture;
  //tmp->uv[0] = uv[0];tmp->uv[1] = uv[1];tmp->uv[2] = uv[2];

  parser_read("particle.fps", tmp);

  tmp->particle = malloc(sizeof(struct particle_t)*tmp->count);

  /*
  printf("count : %d (%d/%d/%d)\n",
	 tmp->count,
	 sizeof(float)*4*3*tmp->count,
	 sizeof(float)*4*3*tmp->count,
	 sizeof(float)*4*3*tmp->count);
  */

  tmp->vertices = malloc(sizeof(float)*4*3*tmp->count);
  tmp->couleurs = malloc(sizeof(float)*4*3*tmp->count);
  tmp->coordTex = malloc(sizeof(float)*4*3*tmp->count);

  printf("    %d\n", sizeof(struct particle_system_t));
  printf("+   %d\n", sizeof(struct particle_t)*tmp->count);
  printf("+   3x%d\n", sizeof(float)*4*3*tmp->count);
  printf("-------------------\n");
  int total = sizeof(struct particle_system_t) + sizeof(struct particle_t)*tmp->count + sizeof(float)*4*3*tmp->count;
  
  printf("=   %d (%.2f ko)\n", total, total / 1000.0f);
    
    
  
  

  printf("--\n");

  particle_system_init(tmp);

  particle_system_gl_update(tmp);

  return tmp;

}

void particle_system_update(struct particle_system_t* ps, float dt){

  int i = 0;

  angle_progress += dt;

  for(i = 0; i < ps->count; i++){
    
    ps->particle[i].life -= dt;

    //ps->particle[i].siz *= 0.975f;

    if(ps->particle[i].life <= 0.5f){
      ps->particle[i].alpha = ps->particle[i].life * 2.0f;
    }

    /*
    if(ps->particle[i].siz <= 0.01f)
      ps->particle[i].life = 0.0f;
    else
      if(ps->particle[i].alpha <= 0.1f)
	ps->particle[i].life = 0.0f;
    */

    if(ps->particle[i].life <= 0.0f){

      ps->particle[i].life = (getRandomValue((int)(ps->ltmin*1000), (int)(ps->ltmax*1000)))/1000.0f;
      ps->particle[i].siz = (getRandomValue((int)(ps->sizemin*10), (int)(ps->sizemax*10)))/10.0f;
      ps->particle[i].vel[0] = (getRandomValue((int)(ps->forcemin[0]*10), (int)(ps->forcemax[0]*10)))/10.0f;
      ps->particle[i].vel[1] = (getRandomValue((int)(ps->forcemin[1]*10), (int)(ps->forcemax[1]*10)))/10.0f;
      ps->particle[i].vel[2] = (getRandomValue((int)(ps->forcemin[2]*10), (int)(ps->forcemax[2]*10)))/10.0f;

      ps->particle[i].col[0] = (getRandomValue((int)(ps->colormin[0]*10), (int)(ps->colormax[0]*10)))/10.0f;
      ps->particle[i].col[1] = (getRandomValue((int)(ps->colormin[1]*10), (int)(ps->colormax[1]*10)))/10.0f;
      ps->particle[i].col[2] = (getRandomValue((int)(ps->colormin[2]*10), (int)(ps->colormax[2]*10)))/10.0f;

      ps->particle[i].pos[0] = ps->pos[0];
      ps->particle[i].pos[1] = ps->pos[1];

      ps->particle[i].alpha = 1.0f;

      if(ps->reg1[0] == 1.0){ // SPAWN BOX
	
	float ppx = (getRandomValue((int)(ps->reg1[1]*1000), (int)(ps->reg1[3]*1000)))/1000.0f;
	float ppy = (getRandomValue((int)(ps->reg1[2]*1000), (int)(ps->reg1[4]*1000)))/1000.0f;

	ps->particle[i].pos[0] += ppx;
	ps->particle[i].pos[1] += ppy;
	
      }
      else if(ps->reg1[0] == 2.0){ // SPAWN CIRCLE
	
	float radius = (getRandomValue((int)(ps->reg1[1]*1000), (int)(ps->reg1[2]*1000)))/1000.0f;
	float angle = (getRandomValue(0, (int)(6.28f*1000)))/1000.0f;
	
	float ppx = radius*cosf(angle);
	float ppy = radius*sinf(angle);
	
	ps->particle[i].pos[0] += ppx;
	ps->particle[i].pos[1] += ppy;
	
      }
      else if(ps->reg1[0] == 3.0){ // SPAWN SIN

	//axe, &ps->reg1[2], &ps->reg1[3], &ps->reg1[4], &ps->reg1[5]);

	float ppx = (getRandomValue((int)(ps->reg1[2]*1000), (int)(ps->reg1[3]*1000)))/1000.0f;
	float angle = (getRandomValue(0, (int)(6.28f*1000)))/1000.0f;

	float tmp1 = fabs(ps->reg1[2] - ps->reg1[3]);
	float tmp2 = ppx*(6.28f / tmp1);
	

	float ppy = ps->reg1[4]*sinf(ps->reg1[5]*tmp2);
	//float ppy = ps->reg1[4]*sinf(ps->reg1[5]*angle_progress);

	if(ps->reg1[1] == 0){
	  ps->particle[i].pos[0] += ppx;
	  ps->particle[i].pos[1] += ppy;
	}
	else{
	  ps->particle[i].pos[0] += ppy;
	  ps->particle[i].pos[1] += ppx;
	}
	
      }
      
    }
    
    ps->particle[i].vel[0] -= ps->gravity[0]*dt;
    ps->particle[i].vel[1] -= ps->gravity[1]*dt;

    if(ps->reg2[0] == 1.0f){

      vec3 target = {ps->reg2[1], ps->reg2[2], 0.0f};
      vec3 vector1 = {0.0f, 0.0f, 0.0f};
      vec3 vector2 = {0.0f, 0.0f, 0.0f};
      vector1[0] = target[0] - ps->particle[i].pos[0];
      vector1[1] = target[1] - ps->particle[i].pos[1];

      vec4_norm(vector2, vector1);
      vec4_scale(vector2, vector2, 0.2f);

      ps->particle[i].vel[0] += vector2[0];
      ps->particle[i].vel[1] += vector2[1];

    }
    
    ps->particle[i].pos[0] += ps->particle[i].vel[0] * dt;
    ps->particle[i].pos[1] += ps->particle[i].vel[1] * dt;

    
    
  }

  particle_system_gl_update(ps);

}

void particle_system_draw(struct particle_system_t* ps, mat4x4 p,  mat4x4 m, int shdID){
  
  glUseProgram(shdID);


  glUniformMatrix4fv(glGetUniformLocation(shdID, "u_projection"),
		     1, GL_FALSE, (float*)p);
 
  glUniformMatrix4fv(glGetUniformLocation(shdID, "u_modelview"),
		     1, GL_FALSE, (float*)m);
  
  int vert_loc = glGetAttribLocation(shdID, "in_Vertex");
  int tex_loc = glGetAttribLocation(shdID, "in_TexCoord0");
  int col_loc = glGetAttribLocation(shdID, "in_Color");
  

  if(vert_loc == -1 || tex_loc == -1 || col_loc == -1){
    printf("ERREUR particle draw\n");
  }
  
  glVertexAttribPointer(vert_loc, 3, GL_FLOAT, GL_FALSE, 0, ps->vertices);
  glEnableVertexAttribArray(vert_loc);
  
  glVertexAttribPointer(tex_loc, 3, GL_FLOAT, GL_FALSE, 0, ps->coordTex);
  glEnableVertexAttribArray(tex_loc);

  
  glVertexAttribPointer(col_loc, 3, GL_FLOAT, GL_FALSE, 0, ps->couleurs);
  glEnableVertexAttribArray(col_loc);
  
  
  glBindTexture(GL_TEXTURE_2D, ps->tex);
  
  glDrawArrays(GL_QUADS, 0, 4*ps->count);
  
  glBindTexture(GL_TEXTURE_2D, 0);

  glDisableVertexAttribArray(col_loc);
  glDisableVertexAttribArray(tex_loc);
  glDisableVertexAttribArray(vert_loc);
  
  glUseProgram(0);


}

void particle_system_destroy(struct particle_system_t* ps){

  free(ps->particle);
  free(ps->vertices);
  free(ps->coordTex);
  free(ps->couleurs);
  free(ps);


}


int parser_read(const char* filename, struct particle_system_t* ps){

  FILE* fd = NULL;

  fd = fopen(filename, "r");
  
  if(!fd){
    printf("error : %s : no such file\n", fd);
    return -1;
  }

  int end = 0;

  ps->reg1[0] = 0.0f;

  while(!end){

    char lineHeader[64];

    int res = fscanf(fd, "%s", lineHeader);
    if (res == EOF)
      break;

    if(strcmp(lineHeader, "end\n") == 0 || strcmp(lineHeader, "end") == 0){
      break;
    }
  
    if(strcmp(lineHeader, "count") == 0){
      fscanf(fd, "%d\n", &ps->count);
      continue;
    }

    if(strcmp(lineHeader, "force") == 0){
      fscanf(fd, "%f %f %f %f\n", &ps->forcemin[0], &ps->forcemin[1], &ps->forcemax[0], &ps->forcemax[1]);
      continue;
    }

    if(strcmp(lineHeader, "size") == 0){
      fscanf(fd, "%f %f\n", &ps->sizemin, &ps->sizemax);
      continue;
    }

    if(strcmp(lineHeader, "color") == 0){

      int cmin[3];
      int cmax[3];
      
      fscanf(fd, "%d %d %d %d %d %d\n", &cmin[0], &cmin[1], &cmin[2], &cmax[0], &cmax[1], &cmax[2]);

      ps->colormin[0] = (float)((float)cmin[0] / 255.0f);
      ps->colormin[1] = (float)((float)cmin[1] / 255.0f);
      ps->colormin[2] = (float)((float)cmin[2] / 255.0f);

      ps->colormax[0] = (float)((float)cmax[0] / 255.0f);
      ps->colormax[1] = (float)((float)cmax[1] / 255.0f);
      ps->colormax[2] = (float)((float)cmax[2] / 255.0f);
      
      
      continue;
    }

    if(strcmp(lineHeader, "gravity") == 0){
      fscanf(fd, "%f %f\n", &ps->gravity[0], &ps->gravity[1]);
      continue;
    }

    if(strcmp(lineHeader, "lifetime") == 0){
      int tmin;
      int tmax;
      
      fscanf(fd, "%d %d\n", &tmin, &tmax);
      ps->ltmin = (float)(tmin / 1000);
      ps->ltmax = (float)(tmax / 1000);
      
      continue;
    }

    if(strcmp(lineHeader, "spawnbox") == 0){

      ps->reg1[0] = 1.0f;
      
      fscanf(fd, "%f %f %f %f\n", &ps->reg1[1], &ps->reg1[2], &ps->reg1[3], &ps->reg1[4]);

      continue;
      
    }

    if(strcmp(lineHeader, "spawncircle") == 0){

      ps->reg1[0] = 2.0f;
      
      fscanf(fd, "%f %f\n", &ps->reg1[1], &ps->reg1[2]);

      continue;
      
    }

    if(strcmp(lineHeader, "spawnsin") == 0){

      ps->reg1[0] = 3.0f;

      char axe;

      // <axes:('x'/'y')> <point1:float> <point2:float> <amp:float> <freq:float>
      
      fscanf(fd, "%f %f %f %f %f\n", &ps->reg1[1], &ps->reg1[2], &ps->reg1[3], &ps->reg1[4], &ps->reg1[5]);

      //ps->reg1[1] = (axe == 'x') ? 0.0f : 1.0f;

      printf("==> %f %f %f %f %f\n", ps->reg1[1], ps->reg1[2], ps->reg1[3], ps->reg1[4], ps->reg1[5]);
      
      continue;
      
    }

    if(strcmp(lineHeader, "magnet_point") == 0){

      ps->reg2[0] = 1.0f;
      
      fscanf(fd, "%f %f\n", &ps->reg2[1], &ps->reg2[2]);

      continue;
      
    }
    
  }

  printf("================ RECAP ==================\n\n");

  printf("count : %d\n", ps->count);
  printf("force : %f / %f - %f / %f\n", ps->forcemin[0], ps->forcemin[1], ps->forcemax[0], ps->forcemax[1]);
  printf("size : %f - %f\n", ps->sizemin, ps->sizemax);
  printf("color : %f / %f / %f - %f / %f / %f\n", ps->colormin[0], ps->colormin[1], ps->colormin[2],
	 ps->colormax[0], ps->colormax[1], ps->colormax[2]);
  printf("gravity : %f / %f\n", ps->gravity[0], ps->gravity[1]);
  printf("lifetime : %f - %f\n", ps->ltmin, ps->ltmax);

  printf("\n\n");
  

  return 0;

}
			     
