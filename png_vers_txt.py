import numpy as np
from PIL import Image as PIL_Image

# choisir un fichier image
fichierImage =  "Carte_coloriee_r.png"
#ouverture dans PIL
img = PIL_Image.open(fichierImage)
# Recuperation de la x_taille et y_taille de l'image
x_taille, y_taille = img.size 
print(x_taille, y_taille)

def pixel2couleur(x, y) : #regarde la couleur du pixel
    couleur = img.getpixel((x, y))
    return couleur

def couleur2int8(a): #renvoie l'entier correspondant
    r,g,b = a
    return g/60 + 4*b/60

#creation de la carte 
matrice = np.zeros((x_taille, y_taille), dtype=np.uint8)
for x in range(x_taille): 
    for y in range(y_taille):
        matrice[x][y_taille-y-1] = couleur2int8(pixel2couleur(x, y))
        
#sauvegarde dans un fichier txt
out = open("out.txt", "w")
for x in range(x_taille): 
        for y in range(y_taille): 
            out.write(chr(matrice[x][y]+97))        
out.close()