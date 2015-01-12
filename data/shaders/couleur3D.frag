// Version du GLSL

#version 150 core


// Entrée

in vec3 color;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{

    //vec3 defcolor = vec3(0.0, 0.0, 0.0);

    // Couleur finale du pixel

    out_Color = vec4(color, 5.2);
}
