// Version du GLSL

#version 150 core


// Entrée

in vec3 coordTexture;
in vec3 color;
//in vec3 normal;
//in float boneId;


// Uniform

uniform sampler2D textures;


// Sortie 

out vec4 out_color;


// Fonction main

void main()
{

  vec4 tmp;
  tmp = texture(textures, coordTexture.xy);
  out_color = tmp * vec4(color, coordTexture.z);
  //out_color = texture(textures, coordTexture);
}
