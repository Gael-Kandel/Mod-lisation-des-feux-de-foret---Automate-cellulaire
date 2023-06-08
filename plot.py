import numpy as np
import random as rd

import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

#Initialisation des couleurs de carte
cmap_veg = ListedColormap([ "white","chartreuse", "forestgreen","darkgreen"])
cmap_den = ListedColormap(["black", "dimgrey", "silver", "white"])
cmap_feu = ListedColormap(["green", "red"])

#ouverture du fichier txt (un peu long)
matrice = np.zeros((2000, 1483, 2553), dtype = np.uint8)
f = open("c_array.txt", "r")
for i in range(2000): 
    for j in range(1483): 
        for k in range(2553): 
            matrice[i][j][k] = np.uint8(ord(f.read(1)))
f.close()

# Plot du type de vegetation (constant)
fig = plt.plot(squeeze = False, figsize = (7, 9))
plt.pcolormesh(matrice[0].T >> 2 & 3, cmap = cmap_veg)
plt.show()

# Plot en fonction du temps (densite et feu)

def plot(time_step):
    fig, ax = plt.subplots(1, 2, squeeze=False, figsize=(14, 9))
    
    ax[0][0].pcolormesh(matrice[time_step].T& 3, cmap = cmap_den)
    ax[0][0].set_xlabel('Index')
    ax[0][0].set_ylabel('Value')
    ax[0][0].set_title('Densitee au temps {}'.format(time_step))
    
    ax[0][1].pcolormesh((matrice[time_step].T >> 4) & 1, cmap = cmap_feu)
    ax[0][1].set_xlabel('Index')
    ax[0][1].set_ylabel('Value')
    ax[0][1].set_title('Feu au temps {}'.format(time_step))
 
    plt.show()

# Slider pour la selection du temps
from ipywidgets import interact, IntSlider
interact(plot, time_step=IntSlider(min=0, max=len(matrice), step=1, value=0))