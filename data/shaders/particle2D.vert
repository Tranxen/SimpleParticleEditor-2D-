// Version du GLSL

#version 150 core

// Entrées

in vec3 in_Vertex;
in vec3 in_Color;
in vec3 in_TexCoord0;

// Uniform

uniform mat4 u_projection;
uniform mat4 u_modelview;

// Sortie

out vec3 coordTexture;
out vec3 color;

// Fonction main

void main()
{
  // Position finale du vertex en 3D

  gl_Position = u_modelview * vec4(in_Vertex, 1.0);


  // Envoi des coordonnées de texture au Fragment Shader

  coordTexture = in_TexCoord0;
  color = in_Color;  	    
}

