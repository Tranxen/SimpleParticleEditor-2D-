# SimpleParticleEditor-2D-
Moteur de particule + editeur (à l'aide d'un fichier)

Compilation : compile.sh (requiert glfw et SOIL)

Exécution : peditor \-f \<fichier fps\>

_Syntaxe du fichier_

| KEY        | VALUE           | DESCRIPTION |
| ------------- |:-------------:| -----:|
| count         | \<nombre departicules\>                                         |  |
| spawnbox      | \<min x\> \<min y\> \<max x\> \<max y\>                         |   |
| spawncircle   | \<min radius\> \<max radius\>                                   |     |
| spawnsin      | \<x/y\> \<p1\> \<p2\> \<amp\> \<freq\>                          |     |
| force         | \<min force x\> \<min force y\> \<max force x\> \<max force y\> | |
| size          | \<min size\> \<max size\>                                       | |
| color         | \<min R\> \<min G\> \<min B\> \<max R\> \<max G\> \<max B\>     | |
| gravity       | \<x\> \<y\>                                                     | | 
| lifetime      | \<min time\> \<max time\>                                       | |
| magnet_point  | \<x\> \<y\>                                                     |    |
| end           |                                                                 | fin du fichier (facultatif)
 

