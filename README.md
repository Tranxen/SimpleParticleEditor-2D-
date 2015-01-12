# SimpleParticleEditor-2D-
Moteur de particule + editeur (à l'aide d'un fichier)

Compilation : compile.sh (requiert glfw et SOIL)

Exécution : peditor \-f \<fichier fps\>

_Syntaxe du fichier_

| KEY        | VALUE           | DESCRIPTION |
| ------------- |:-------------:| -----:|
| count         | \<nombre departicules\>                                         |  |
| spawnbox      | \<min x\> \<min y\> \<max x\> \<max y\>                         |   |
| spawnrate      | \<nb particule par seconde\>                          |   |
| spawncircle   | \<min radius\> \<max radius\>                                   |     |
| spawnsin      | \<x/y\> \<p1\> \<p2\> \<amp\> \<freq\>                          |     |
| force         | \<min force x\> \<min force y\> \<max force x\> \<max force y\> | |
| size          | \<min size\> \<max size\>                                       | |
| color         | \<min R\> \<min G\> \<min B\> \<max R\> \<max G\> \<max B\>     | |
| gravity       | \<x\> \<y\>                                                     | | 
| lifetime      | \<min time\> \<max time\>                                       | en milliseconde|
| magnet_point  | \<x\> \<y\>                                                     |    |
| end           |                                                                 | fin du fichier (facultatif)
 

BUGS : 

L'option "time" n'est pas valide si \<min time\> ou \<max time\> est inférieur à 1000 ms

PROCHAINEMENT : 

Ajout de l'option "endScale" et "endColor"

Ajout de l'option "fadeIn" et "fadeOut". "FadeOut" est déjà implémenté mais ne peut pour l'instant pas être desactivé.
