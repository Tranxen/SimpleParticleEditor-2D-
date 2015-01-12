#ifndef DEF_SHADER
#define DEF_SHADER

//#include <GL/glew.h>
#include <GL/gl.h>


struct shader_t{

  GLuint vertexID;
  GLuint fragmentID;
  GLuint programID;

};


int shader_load(struct shader_t*, const char*, const char*);
int shader_compile(GLuint* shader , GLenum type, const char* filename);
void shader_destroy(struct shader_t* s);


#endif
