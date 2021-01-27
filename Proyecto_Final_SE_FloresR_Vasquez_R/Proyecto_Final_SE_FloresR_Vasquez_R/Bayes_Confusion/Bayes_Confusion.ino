#include <ListLib.h>
#include "datos.h"
#include "prueba.h"
int resultado;
int porcent;
List <int> list; // listar, tipo de dato, el nombre de lista
int cont;
void setup() {
Serial.begin(9600);
  for(cont=0;cont<42;cont++){
  bayes(); // llamada al metodo 
  }
  Serial.println("El porcentaje es ");
  Serial.println(porcent/42);
}

void loop() {
  
}
void bayes(){
 list=0;
 float datos_prueba [3]={matriz1[cont][0],matriz1[cont][1],matriz1[cont][2]}; // creacion de metodo
 int etiquetas=2;
 int columnas=3;
 int filas=182;
 float r=0.2;
 int i=0; // variable de recorrido en matriz
 int j=0; // variable de recorrido en matriz
 int k=0; // variable de recorrido en matriz
 int t=0; // variable de recorrido en matriz
 float p_x=0.0; // probabilidad marginal
 float distancia=0.0; 
 float sumatoria=0.0;
 float normalizador=0.0;
 float dist_mayor=0.0001;
 int resultado; // resultado de etiqueta
 float aux=0; // auxiliar de cambio de variable

   float prob [4][etiquetas];
   //encerar matriz y asignar etiquetas a la fila 0
    for(i=0;i<4;i++){
       for(j=0;j<etiquetas;j++){   // |    1   |   2    |    3   |
          prob[i][j]=0;            // |    0   |   0    |    0   |
          if(i==0)                 // |    0   |   0    |    0   |
          prob[i][j]=j+1;          // |    0   |   0    |    0   |
        }
      }
    // sumar el valor del total por etiqueta en la matriz
    for(i=0;i<etiquetas;i++){               // |    1   |   2    |    3   |
        for(j=0;j<filas;j++){               // |   40   |   40   |   40   |
          if(matriz[j][columnas-1]==i+1)    // |    0   |   0    |    0   |
            prob[1][i]++;                   // |    0   |   0    |    0   |
          }
      }


    //encontrar la distancia mayor 
    for(i=0;i<filas;i++){
       for(j=0;j<columnas-1;j++){
         sumatoria=sumatoria+pow(matriz[i][j]-datos_prueba[j],2); // realizar la sumatoria de potencia
        }
        distancia=sqrt(sumatoria); // raiz cuadrada para distancia entre dos puntos
        sumatoria=0;
        if(distancia>dist_mayor)
          dist_mayor=distancia; // encuentro distancia mayor
      }
      distancia=0; 
    // normalizar la distancia en toda la matriz 
    for(i=0;i<filas;i++){
       for(j=0;j<columnas-1;j++){
         sumatoria=sumatoria+pow(matriz[i][j]-datos_prueba[j],2);// realizar la sumatoria de potencia
       }
        distancia=sqrt(sumatoria); // raiz cuadrada para distancia entre dos puntos
        sumatoria=0;
        normalizador=distancia/dist_mayor; // distancias entre 0 y 1
        if(normalizador<r)
            list.Add(i); // almancenar la fila de los datos que son parte de la circunferencia
    }
    // sumar por etiqueta a todos los datos que se encuentran en la circuferencia
    for(i=0;i<list.Count();i++){                          // |    1   |   2    |    3   |
      for(j=0;j<etiquetas;j++){                           // |   40   |   40   |   40   |
          if(matriz[list[i]][columnas-1]==prob[0][j])     // |    4   |   1    |    0   |
            prob[2][j]++;                                 // |    0   |   0    |    0   |
        }
      }
      // probabilidades por cada etiqueta
      p_x=float(list.Count())/float(filas); 
   for(k=0;k<etiquetas;k++){  // encontrar la probabilidad por etiqueta
      prob[3][k]=((prob[1][k]/filas)*(prob[2][k]/prob[1][k]))/p_x;
    }

      // busqueda de probabilidad por etiqueta
      for(k=0;k<etiquetas;k++){
         if(prob[3][k]>aux){
           resultado=int(prob[0][k]);
           aux=prob[3][k];
          }   
        }
    //retorna el resultado de etiqueta
  Serial.println(resultado);
  switch(resultado){
    case 1:
      Serial.println("Aire Puro"); 
    break;
    case 2:
    Serial.println("Aire Contaminado");
    break;
    }
    if(resultado==matriz1[cont][2]){
      porcent++;
    }
   r=0.2;
   i=0; // variable de recorrido en matriz
   j=0; // variable de recorrido en matriz
   k=0; // variable de recorrido en matriz
   t=0; // variable de recorrido en matriz
   p_x=0.0; // probabilidad marginal
   distancia=0.0; 
   sumatoria=0.0;
   normalizador=0.0;
   dist_mayor=0.0001;
   resultado; // resultado de etiqueta
   aux=0; // auxiliar de cambio de variable
    return resultado;
 }
