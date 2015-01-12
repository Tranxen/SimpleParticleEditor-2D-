#ifndef DEF_PARTICLE
#define DEF_PARTICLE

#include "shader.h"
#include "linmath.h"


struct particle_t{

  float life;
  float pos[2];
  float vel[2];
  float col[3];
  float alpha;
  float siz;
  float rot;

  float size_factor;
  float color_factor[3];
};


struct particle_system_t{
  
  int count;
  int spawnrate;
  float nbspawned;
  
  struct particle_t* particle;
  float pos[2];
  float gravity[2];
  float forcemin[2];
  float forcemax[2];
  float colormin[3];
  float colormax[3];
  float ltmin;
  float ltmax;
  float sizemin;
  float sizemax;

  int tex;
  float uv[3];

  // OPENGL
  
  float* vertices;
  float* couleurs;
  float* coordTex;

  // AUX REG

  float reg1[8];
  float reg2[8];

};

void particle_system_gl_update(struct particle_system_t* ps);
void particle_system_reset(struct particle_system_t* ps);
struct particle_system_t* particle_system_create(float x, float y, int texture, float* uv, char* f);
void particle_system_update(struct particle_system_t* ps, float dt);
void particle_system_draw(struct particle_system_t* ps, mat4x4 p,mat4x4 m, int shdID);
void particle_system_destroy(struct particle_system_t* ps);
int parser_read(const char* filename, struct particle_system_t* ps);


#endif
