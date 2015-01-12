#include <stdio.h>
#include <stdlib.h>

#include "shader.h"
#include <string.h>

int shader_load(struct shader_t* s, const char* vs, const char *fs)
{
  s->vertexID = 0;
  s->fragmentID = 0;
  s->programID = 0;

  // Compilation des shaders

  if(shader_compile(&s->vertexID, GL_VERTEX_SHADER, vs) == -1){
    printf("FAILED TO COMPILE VERTEX\n");
    return -1;
  }


  if(!shader_compile(&s->fragmentID, GL_FRAGMENT_SHADER, fs)){
    printf("FAILED TO COMPILE FRAGMENT\n");
    return -1;
  }


 
  // Création du programme

  s->programID = glCreateProgram();



  // Association des shaders

  glAttachShader(s->programID, s->vertexID);
  glAttachShader(s->programID, s->fragmentID);


  // Verrouillage des entrées shader


  /*
  glBindAttribLocation(s->programID, 0, "in_Vertex");
  glBindAttribLocation(s->programID, 1, "in_Color");
  glBindAttribLocation(s->programID, 2, "in_TexCoord0");
  glBindAttribLocation(s->programID, 3, "in_aux0");
  glBindAttribLocation(s->programID, 4, "in_normals");
  */


  // Linkage du programme

  glLinkProgram(s->programID);


  // Vérification du linkage

  GLint erreurLink=0;
  glGetProgramiv(s->programID, GL_LINK_STATUS, &erreurLink);


  // S'il y a eu une erreur

  if(erreurLink != GL_TRUE)
    {
      // Récupération de la taille de l'erreur

      GLint tailleErreur=0;
      glGetProgramiv(s->programID, GL_INFO_LOG_LENGTH, &tailleErreur);


      // Allocation de mémoire

      char *erreur = malloc(sizeof(char) * tailleErreur + 1);


      // Récupération de l'erreur

      glGetShaderInfoLog(s->programID, tailleErreur, &tailleErreur, erreur);
      erreur[tailleErreur] = '\0';


      // Affichage de l'erreur

      printf("erreur : %s\n",erreur);


      // Libération de la mémoire et retour du booléen false

      free(erreur);
      glDeleteProgram(s->programID);

      return -1;
    }



  // Sinon c'est que tout s'est bien passé

  else{
    printf("loading shader \"%s\" : ok\n", vs);
    return 1;

  }
}


int shader_compile(GLuint *shader, GLenum type, const char* filename)
{
    // Création du shader

  *shader = glCreateShader(type);
  
  // Vérification du shader
  
    if(*shader == 0)
      {
	printf("Erreur, le type de shader (%d) n'existe pas\n", type);
        return -1;
    }
    
    FILE* fichier;

    fichier = fopen(filename, "r");

    
    // Test d'ouverture

    if(!fichier)
    {
      printf("Erreur le fichier %s est introuvable\n", filename);
      glDeleteShader(*shader);

      return -1;
    }



    // Lecture

    char codeSource[1024];
    memset(codeSource, '\0', 1024);
    char line[256];

    while (fgets(line, 256, fichier) != NULL){
      
      strcat(codeSource, line);
      //strcat(codeSource, "\n");

    }

    //printf("code source \n %s \n", codeSource);

    // Fermeture du fichier

    fclose(fichier);


    // Récupération de la chaine C du code source

    const GLchar* chaineCodeSource = codeSource;


    // Envoi du code source au shader

    glShaderSource(*shader, 1, &chaineCodeSource, 0);


    // Compilation du shader

    glCompileShader(*shader);


    // Vérification de la compilation

    GLint erreurCompilation=0;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &erreurCompilation);


    // S'il y a eu une erreur

    if(erreurCompilation != GL_TRUE)
    {
        // Récupération de la taille de l'erreur

        GLint tailleErreur=0;
        glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &tailleErreur);


        // Allocation de mémoire

        char *erreur = malloc(sizeof(char)*tailleErreur + 1);


        // Récupération de l'erreur

        glGetShaderInfoLog(*shader, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';


        // Affichage de l'erreur

        printf("%s\n",erreur);


        // Libération de la mémoire et retour du booléen false

        free(erreur);
        glDeleteShader(*shader);

        return (-1);
    }
    else
      return 1;
}


void shader_destroy(struct shader_t* s)
{

  glDeleteShader(s->vertexID);
  glDeleteShader(s->fragmentID);
  glDeleteProgram(s->programID);

}

