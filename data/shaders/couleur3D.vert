// Version du GLSL

#version 150 core


// Entrées

in vec3 vtx;
in vec3 col;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;


// Sortie

out vec3 color;


// Fonction main

void main()
{
    // Position finale du vertex en 3D

    gl_Position = projection * modelview * vec4(vtx, 1.0);


    // Envoi de la couleur au Fragment Shader

    color = col;
}
