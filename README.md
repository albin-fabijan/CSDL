# CSDL

Ce projet est une implémentation du célèbre jeu Game of Life en langage C++. Le jeu de la vie a été inventé par le mathématicien britannique John Conway en 1970. Le jeu se déroule sur une grille bidimensionnelle où chaque cellule peut être dans l'un des deux états possibles : vivante ou morte. Les états des cellules évoluent en fonction d'un ensemble de règles simples.

Dans ce projet, nous avons apporté des modifications personnelles pour permettre à deux couleurs (bleu et rouge) de s'affronter sur une grille de 22 lignes sur 32 colonnes. Les cellules vivantes sont représentées par la couleur correspondante à la couleur de l'équipe, tandis que les cellules mortes sont représentées par une couleur neutre.

## Règles du jeu

Les règles du jeu sont les suivantes :
- Toute cellule vivante avec moins de deux voisins vivants meurt, par sous-population.
- Toute cellule vivante avec deux ou trois voisins vivants reste vivante pour la prochaine génération.
- Toute cellule vivante avec plus de trois voisins vivants meurt, par surpopulation.
- Toute cellule morte avec exactement trois voisins vivants devient une cellule vivante, par reproduction.

## Installation et exécution

1. Assurez-vous que vous disposez d'un compilateur C++ installé sur votre système.
2. Clonez ce dépôt vers votre machine locale.
3. Compilez le programme à l'aide de votre compilateur C++ préféré. Par exemple :
4. Exécutez le programme :main.exe

## Remerciements

Ce projet a été réalisé dans le cadre de notre formation en programmation C++. Nous remercions tous les contributeurs qui ont participé à son développement.

Pour plus d'informations sur le jeu de la vie, vous pouvez consulter [la page Wikipedia correspondante](https://fr.wikipedia.org/wiki/Jeu_de_la_vie).

Amusez-vous bien !
