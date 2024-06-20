# Modélisation des feux de forêt - Automate cellulaire

J'ai réalisé ce projet en 2023 dans le cadre de mon TIPE, une épreuve commune à la plupart des concours d'entrée aux grandes écoles scientifiques. 

Le modèle : 
La forêt est divisée en cellules faisant parti d'une grille. Les caractéristiques d'une cellule (type et densité de végétation), ainsi que le nombre de cellules voisines en feu et la direction du vent, influent sur la propapagation de l'incendie.
Le modèle est inspiré de la littérature existante, j'ai ensuite ajusté ses paramètres.

J'ai ensuite comparé le modèle avec le feu de La Teste-De-Buche (juillet 2022).

Pour cela, j'ai travaillé avec une carte de 2600x1500 pixels (produite en m'appuyant sur différentes données cartographiques) et voulant enregistrer chaque étape des plus de 1200 itérations, j'ai été limité par les performances de Python.
J'ai alors converti ma carte en fichier texte, ce qui m'a permis de la charger dans une matrice C et d'effectuer la simulation (temps d'exécution entre 5 et 8 minutes).
Le fichier texte produit est alors lu sous Python (en environ 3h), et je peux alors utiliser matplotlib pour les affichages.

Le processus résumé : Carte coloriée -> png_vers_txt.py -> TDB avec vent.c -> plot.py

