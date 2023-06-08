#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>   


int x_taille = 1483; int y_taille = 2553; //taille de la carte
uint8_t rand_num; float rand_float;  //variables pour les fonctions random

#define PI 3.14159
int v = 10; float c1 = 0.045; float c2 = 0.191; float theta = -PI/2;  
// vitesse du vent ; parametres de vent 1 et 2 ; direction du vent (rad)
int indice(int x,int y){return x*y_taille+y;}   
//fonction qui renvoie l'indice d'une case de coordonnees (x,y) dans le tableau


float compute_veg(int val){
    int veg_type = (val >> 2) & 3; float p_veg; 
    if (veg_type == 0) {p_veg = -1.;}
    if (veg_type == 1) {p_veg = -0.3;}
    if (veg_type == 2) {p_veg = .0;}
    if (veg_type == 3) {p_veg = 0.4;}
    return p_veg;}
// fonction qui renvoie la probabilite de bruler a cause de la vegetation
float compute_den(int val){
    int den_type = val & 3; float p_den; 
    if (den_type == 0) {p_den = -1.;}
    if (den_type == 1) {p_den = -0.4;}
    if (den_type == 2) {p_den = .0;}
    if (den_type == 3) {p_den = 0.3;}
    return p_den;}
// fonction qui renvoie la probabilite de bruler a cause de la densite

float fire_angle(int x, int y){
    if (x==0 && y==1)  {return fmod(theta, 2 * PI);}
    if (x==-1 && y==1) {return fmod(theta - PI/4, 2 * PI);}
    if (x==-1 && y==0) {return fmod(theta - PI/2, 2 * PI);}
    if (x==-1 && y==-1){return fmod(theta - 3*PI/4, 2 * PI);}
    if (x==0 && y==-1) {return fmod(theta - PI, 2 * PI);}
    if (x==1 && y==-1) {return fmod(theta - 5*PI/4, 2 * PI);}
    if (x==1 && y==0)  {return fmod(theta - 3*PI/2, 2 * PI);}
    if (x==1 && y==1)  {return fmod(theta - 7*PI/4, 2 * PI);}
} // fonction qui renvoie l'angle du feu par rapport au vent

bool catch_fire(int val, float angle) {
    float ph = .58;                               // parametre
    float p_veg = compute_veg(val); // probabilite de bruler a cause de la vegetation
    float p_den = compute_den(val); // ou de la densite
    float p_vent = exp(v*(c1+c2*(cos(angle)-1))); // probabilite de bruler a cause du vent
    float p_burn = ph*p_vent*(1+p_veg)*(1+p_den); // probabilite de bruler
    rand_float = (float) rand() / RAND_MAX;       // random float entre 0 et 1
    return rand_float<p_burn;}                    // renvoie true si le feu prend


// Operateurs bit a bit : << n : decalage a gauche de n bits; & : et
void prop(uint8_t carte[]){
    bool *li = malloc(x_taille*y_taille*sizeof(bool)); 
    for (int i =0; i<x_taille; i++){
        for (int j=0; j<y_taille; j++){li[indice(i, j)] = 0;}
    } // tableau indiquant les cases qui vont bruler
    
for (int x =1; x<x_taille-1; x++){
    for (int y=1; y<y_taille-1; y++){
	if (((carte[indice(x, y)] >> 4) & 1 )==1){
        int val1 = carte[indice(x-1, y)]; int val2 = carte[indice(x, y-1)];
        int val3 = carte[indice(x+1, y)]; int val4 = carte[indice(x, y+1)];
        int val5 = carte[indice(x-1, y-1)]; int val6 = carte[indice(x+1, y-1)];
        int val7 = carte[indice(x+1, y+1)]; int val8 = carte[indice(x-1, y+1)];
        
        if (!((val1 >> 4) & 1)){if (catch_fire(val1, fire_angle(-1, 0))) {li[indice(x-1, y)]=1;}}
	if (!((val2 >> 4) & 1)){if (catch_fire(val2, fire_angle(0, -1))) {li[indice(x, y-1)]=1;}}
	if (!((val3 >> 4) & 1)){if (catch_fire(val3, fire_angle(1, 0)))  {li[indice(x+1, y)]=1;}}
	if (!((val4 >> 4) & 1)){if (catch_fire(val4, fire_angle(0, 1)))  {li[indice(x, y+1)]=1;}}
	if (!((val5 >> 4) & 1)){if (catch_fire(val5, fire_angle(-1, -1))) {li[indice(x-1, y-1)]=1;}}
        if (!((val6 >> 4) & 1)){if (catch_fire(val6, fire_angle(+1, -1))) {li[indice(x+1, y-1)]=1;}}
	if (!((val7 >> 4) & 1)){if (catch_fire(val7, fire_angle(+1, +1))) {li[indice(x+1, y+1)]=1;}}
        if (!((val8 >> 4) & 1)){if (catch_fire(val8, fire_angle(-1, +1))) {li[indice(x-1, y+1)]=1;}}
    }}} // on parcourt les cases en feu et on regarde si les cases voisines vont bruler
    for (int x =0; x<x_taille; x++){  
        for (int y=0; y<y_taille; y++){
            int val = carte[indice(x, y)]; 
            if (((val >> 4) & 1) ==1){                
	            if ((val & 3) >0){carte[indice(x, y)] -= 1;}         
                else {carte[indice(x, y)] -= 16 ;}
            }  
            if (li[indice(x, y)]) {carte[indice(x, y)] += 16; 
            }}} // on met a jour la carte
    free(li);  // on libere la memoire
}

void to_fichier(uint8_t (*liste)[x_taille][y_taille],int longueur ){
  FILE* fic = fopen("c_array.txt","w");
  for (int l = 0; l<longueur; l++){
    for (int i =0; i<x_taille; i++){
      for (int j = 0; j<y_taille; j++){
	    fprintf(fic, "%c", liste[l][i][j]);
      }}}  
    fclose(fic);
}  // on ecrit la liste dans un fichier

void tabcpy(uint8_t carte[], uint8_t (*liste)[x_taille][y_taille], int where){
  for (int i = 0; i < x_taille; i++){
    for (int j = 0; j< y_taille; j++){
      liste[where][i][j] = carte[indice(i, j)]; 
    }
  }
}  // on copie la carte dans la liste


int main()
{
    uint8_t *c = malloc(x_taille*y_taille*sizeof(uint8_t)); 
    FILE *file = fopen("out.txt", "r"); 
    uint8_t matrix[x_taille][y_taille]; 
    for (int x = 0; x < x_taille; x++) {
        for (int y = 0; y < y_taille; y++) {
            matrix[x][y] = (int) fgetc(file); 
            matrix[x][y] -= 97; 
            c[indice(x, y)] = matrix[x][y];
        }}
    fclose(file);
    // on lit la carte obtenue par python et on la met dans un tableau
    c[indice(960, 1433)] +=16;   // position estimee du depart de feu


    uint8_t (*liste)[x_taille][y_taille] = malloc(2000 * sizeof(*liste)); 
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < x_taille; j++) {
           for (int k = 0; k < y_taille; k++) {
               liste[i][j][k] = 0;
    }}} // initialisation de la liste de sauvegarde des cartes

    tabcpy(c, liste,0);
    for (int i = 1 ; i< 2000; i++) {
        prop(c); tabcpy(c, liste, i);
        if (i == 500){theta = +PI/2;}
        if (i == 1000){theta = -PI/4;}
    }
    to_fichier(liste, 2000); // sauvegarde de la liste dans un fichier
    free(liste);  
    free(c); // liberation de la memoire allouee
    return 0;
}



