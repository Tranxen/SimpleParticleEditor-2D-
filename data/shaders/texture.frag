// Version du GLSL

#version 150 core


// Entrée

in vec2 coordTexture;
in vec3 normal;
//in float boneId;


// Uniform

uniform sampler2D textures;


// Sortie 

out vec4 out_color;


// Fonction main

void main()
{

  out_color = texture(textures, coordTexture);

}
