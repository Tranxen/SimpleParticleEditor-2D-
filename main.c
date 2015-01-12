#include <stdlib.h>
#include <stdio.h>
#include "shader.h"
#include "linmath.h"
#include <GLFW/glfw3.h>
#include <string.h>
#include <SOIL.h>
#include "particlesystem.h"


void error_callback(int error, const char* description){
  fputs(description, stderr);
}


void drawLine(mat4x4 p, mat4x4 m, vec3 p1, vec3 p2, vec3 col, struct shader_t* shd){
 
  glUseProgram(shd->programID);

  glUniformMatrix4fv(glGetUniformLocation(shd->programID, "projection"),
		     1, GL_FALSE, (float*)p);
  glUniformMatrix4fv(glGetUniformLocation(shd->programID, "modelview"),
		     1, GL_FALSE, (float*)m);

  int vert_loc = glGetAttribLocation(shd->programID, "vtx");
  int colr_loc = glGetAttribLocation(shd->programID, "col");

  if(vert_loc == -1 || colr_loc == -1){
    printf("ERREUR\n");
    printf("%d / %d / %d \n", vert_loc, colr_loc, shd->programID);
    printf("%d / %d / %d \n", glGetUniformLocation(shd->programID, "projection"),
	   glGetUniformLocation(shd->programID, "modelview"), shd->programID);
  }

  float vertices[] = {p1[0], p1[1], p1[2], p2[0], p2[1], p2[2]};
  float color[] = {col[0], col[1], col[2], col[0], col[1], col[2]};

  glVertexAttribPointer(vert_loc, 3, GL_FLOAT, GL_FALSE, 0, vertices);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(colr_loc, 3, GL_FLOAT, GL_FALSE, 0, color);
  glEnableVertexAttribArray(1);

  glDrawArrays(GL_LINES, 0, 2);

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glUseProgram(0);

}


int main(int argc, char** argv){

  // ============================ INIT ==============================

  GLFWwindow* context = NULL;
  if( !glfwInit() )
    {
      return -1;
    }

  glfwSetErrorCallback(error_callback);
  float x = 800;
  float y = 600;

  if(!(context = glfwCreateWindow(x, y, "fabiengine",NULL, NULL))){
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(context);
  glfwSetWindowPos(context, 200, 200);

  // =========================== ISHADER ===========================

  struct shader_t line_shader;
  struct shader_t tex_shader;
  struct shader_t pcl_shader;

  if(shader_load(&line_shader, "data/shaders/couleur3D.vert","data/shaders/couleur3D.frag") == -1){
    printf("failed(1)\n");
    exit(-1);    
  }

  if(shader_load(&tex_shader, "data/shaders/texture.vert","data/shaders/texture.frag") == -1){
    printf("failed(2)\n");
    exit(-1);    
  }


  if(shader_load(&pcl_shader, "data/shaders/particle2D.vert","data/shaders/particle2D.frag") == -1){
    printf("failed(3)\n");
    exit(-1);    
  }

  // ============================ MATRICES ================================
 
  mat4x4 projection;
  mat4x4 modelview;
  mat4x4 modelview_raw;
  mat4x4 mv_tmp;

  //mat4x4_perspective(projection, 70.0f, (double)((double)800.0 / (double)600.0), 0.1f, 200.0f);
  mat4x4_identity(projection);
  mat4x4_identity(modelview_raw);
  mat4x4_identity(modelview);

  // SCALING !!!!
  
  modelview[0][0] = 0.1f;
  modelview[1][1] = 0.1f;

  
  //mat4x4_scale(modelview, modelview_raw, 0.4f);

  {
  
  int i, j;

  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      printf("%f ", modelview[i][j]);

    }
    printf("\n");
  }

  }

  // ======================= TEXTURE ======================

  int particleTex = SOIL_load_OGL_texture
    (
     "data/textures/Particle.bmp",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS// | SOIL_FLAG_INVERT_Y //| SOIL_FLAG_NTSC_SAFE_RGB// | SOIL_FLAG_COMPRESS_TO_DXT 
 
     );

  glBindTexture(GL_TEXTURE_2D, particleTex);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);
  
 
  
  if(particleTex < 0){

    printf("ERREUR chargement texture ");
    exit(-1);

  }

  // =========================== DIVERS ================================


  int running = 1;

  char* foption = NULL;

 
  if(argv[1] != NULL && strcmp(argv[1], "-f") == 0){

    printf("option detecte\n");
    foption = malloc(sizeof(char)*255);
    memset(foption, '\0', 255);
    if(argv[2] != NULL)
      strcat(foption, argv[2]);
    else{
      foption = NULL;
      printf("Erreur: \t-f attend un argument\n\t\t peditor -f <fichier>\n");
      return -1;
    }

  }
  
  struct particle_system_t* particle = particle_system_create(0.0f, 0.0f, particleTex , NULL, foption);

  glEnable (GL_DEPTH_TEST);

  int d;
  printf("#################################\n");


  float debutBoucle = 0, finBoucle = 0, dt = 0;
  dt = 0.016f;
  
  float mspeed = 0.0f;

  // ============================ MAIN LOOP ==============================

  while( running ){

    debutBoucle = glfwGetTime();
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearColor(0.0f, 0.0f, 0.2f, 1.0f);


    vec3 posA1 = { 0.5f, -0.1f, 0.0 };
    vec3 posA2 = { 0.7f, 0.1f, 0.0 };

    //drawImage(projection, modelview, posA1, posA2, tex_shader.programID, particleTex);

    {vec3 pos1 = {0.0f, 0.0f, 0.0f};vec3 pos2 = {1.0f, 0.0f, 0.0f};
      drawLine(projection, modelview, pos1, pos2, pos2, &line_shader);}
    {vec3 pos1 = {0.0f, 0.0f, 0.0f};vec3 pos2 = {0.0f, 1.0f, 0.0f};
      drawLine(projection, modelview, pos1, pos2, pos2, &line_shader);}
    
    particle_system_update(particle, dt);

    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glBlendEquation(GL_FUNC_ADD);
    particle_system_draw(particle, projection, modelview, pcl_shader.programID);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    

    running = !glfwGetKey(context, GLFW_KEY_ESCAPE );

    
    if(glfwGetKey(context, GLFW_KEY_SPACE )){
      int i = 0;
      for(i = 0; i < particle->count; i++){
	printf("\nPOSITION : \n");
	printf("%f / %f / %f \n %f / %f / %f \n %f / %f / %f \n %f / %f / %f \n\n",
	       particle->vertices[i*12+0],particle->vertices[i*12+1],particle->vertices[i*12+2],
	       particle->vertices[i*12+3],particle->vertices[i*12+4],particle->vertices[i*12+5],
	       particle->vertices[i*12+6],particle->vertices[i*12+7],particle->vertices[i*12+8],
	       particle->vertices[i*12+9],particle->vertices[i*12+10],particle->vertices[i*12+11]);
	printf("\nCOULEUR : \n");
	printf("%f / %f / %f \n %f / %f / %f \n %f / %f / %f \n %f / %f / %f \n",
	       particle->couleurs[i*12+0],particle->couleurs[i*12+1],particle->couleurs[i*12+2],
	       particle->couleurs[i*12+3],particle->couleurs[i*12+4],particle->couleurs[i*12+5],
	       particle->couleurs[i*12+6],particle->couleurs[i*12+7],particle->couleurs[i*12+8],
	       particle->couleurs[i*12+9],particle->couleurs[i*12+10],particle->couleurs[i*12+11]);
	printf("\nTEXTURE : \n");
	printf("%f / %f \n %f / %f \n %f / %f \n %f / %f \n\n",
	       particle->coordTex[i*8+0],particle->coordTex[i*8+1],
	       particle->coordTex[i*8+2],particle->coordTex[i*8+3],
	       particle->coordTex[i*8+4],particle->coordTex[i*8+5],
	       particle->coordTex[i*8+6],particle->coordTex[i*8+7]);
      }

    }
    

    glfwPollEvents();

    glfwSwapBuffers(context);

    finBoucle =  glfwGetTime();
    dt = finBoucle - debutBoucle;

    char winname[25];
    sprintf(winname, "FabiEngine - FPS : %4.2f \0", 1/dt); 
    glfwSetWindowTitle(context, winname);

  }

  particle_system_destroy(particle);

  glfwTerminate();

  return 0;

}
