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

![image](https://github.com/Gael-Kandel/Mod-lisation-des-feux-de-foret---Automate-cellulaire/assets/104364286/f9246564-0c51-4688-9266-7806ce807655)
![image](https://github.com/Gael-Kandel/Mod-lisation-des-feux-de-foret---Automate-cellulaire/assets/104364286/6232b8e0-7bdc-4567-966e-94414554d86d)
![image](https://github.com/Gael-Kandel/Mod-lisation-des-feux-de-foret---Automate-cellulaire/assets/104364286/32913260-43c5-47d4-9b1e-7802587df01f)
![image](https://github.com/Gael-Kandel/Mod-lisation-des-feux-de-foret---Automate-cellulaire/assets/104364286/4d9494d8-e615-4928-baad-79cb88445518)


