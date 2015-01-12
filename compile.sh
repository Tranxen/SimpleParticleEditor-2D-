rm -v *~ 2> /dev/null
gcc -g particlesystem.c shader.c main.c -o peditor -lGL -lglfw -lSOIL -lm
