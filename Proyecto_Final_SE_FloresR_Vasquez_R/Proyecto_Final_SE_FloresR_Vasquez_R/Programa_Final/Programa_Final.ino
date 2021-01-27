
#include<LiquidCrystal.h>
#include "datos.h"
#include<avr/power.h>       //Librerias
#include<avr/sleep.h>      //Librerias
#include<avr/wdt.h>       //Librerias
#include<EEPROM.h>       //Librerias


LiquidCrystal lcd(13,12,11,10,9,8);   //RS,E,D4,D5,D6,D7
int dato;            //variable 1
int k;              //variable 2 
int i=0;
int led1 = 4;
int led2 = 5;
float a;
float b;
extern double filtro[29];
double signalin [15];
double signalin2 [15];
int enviar;
double output[15+29]; 
double output_signal[15];
double output2[15+29]; 
double output_signal2[15];
int respuesta;

void (* resetFunc)(void)=0;
int knn (int k, int etiquetas, int tam_col, int col_fil); 
void moving_average (double *sig_in, double *output_signal, int sig_tam, int filter);
void moving_average2 (double *sig_in, double *output_signal, int sig_tam, int filter);


void setup() {  
  //EEPROM.write(0,0);          // Escritura de dato inicial, se realiza una sola vez 
  dato=EEPROM.read(0);          //Lectura del dato 0, para activacion del sistema completo
  Serial.begin(9600);          //Velocidad del cx
  if(dato==0){              //Condicion de activacion de metodo
    EEPROM.update(0,1);
    sistema();              //Activacion de metodo
    Serial.begin(9600);
    lcd.begin(16,2);
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    for(i=0;i<15;i++)
      {
        signalin[i]=analogRead(0);
        signalin2[i]=analogRead(1);
      }
      moving_average ((double *)&signalin[0], (double *)&output_signal[0], (int) 15,9);
      moving_average2 ((double *)&signalin2[0], (double *)&output_signal2[0], (int) 15,9);
      a=output_signal[8];
      b=output_signal2[8];
      respuesta=knn(3,2,3,182); // numero de k, numero de etiquetas, tamano de la matriz  
      delay(250);
      Serial.write(respuesta);
    EEPROM.write(1,0);     //Actualizacion dato auxiliar
    k=EEPROM.read(1);     //Lectura de dato auxiliar
  }else{
    k=EEPROM.read(1);    //LEctura de dato auxiliar
    k=k+1;               //Aumento de dato auxiliar
    EEPROM.update(1,k);  //Actualizacion dato auxiliar
  }
  if(k<(1+1)){           //Condicion de activacion del modo sleep (1) * 4 + (x) * 4 = 4 segundos activado y  2x secundos desactivado  
  delay(100);        
  modo();           //Metodo de activacion de modo sleep
  }else{
    EEPROM.update(0,0);       //Actualizacion dato principal para el sistema
    wdt_enable(WDTO_15MS);   //Condicion reinicio del sistema.
  }
}

void loop() {
  
 }


//FILTRADO Señal 1
void moving_average (double *sig_in, double *output_signal, int sig_tam, int filter){
  int i,j;
  for(i=floor(filter/2);i<sig_tam-floor(filter/2)-1;i++){
    output_signal[i]=0;
    for(j=-floor(filter/2);j<floor(filter/2);j++){
        output_signal[i]=output_signal[i]+sig_in[i+j];
      }
      output_signal[i]=output_signal[i]/filter;
    }
  }


//FILTRADO Señal 2
void moving_average2 (double *sig_in, double *output_signal2, int sig_tam, int filter){
  int i,j;
  for(i=floor(filter/2);i<sig_tam-floor(filter/2)-1;i++){
    output_signal2[i]=0;
    for(j=-floor(filter/2);j<floor(filter/2);j++){
        output_signal2[i]=output_signal2[i]+sig_in[i+j];
      }
      output_signal2[i]=output_signal2[i]/filter;
    }
  }
//Aprendizaje de maquina 
int knn (int k, int etiquetas, int tam_col, int tam_fil){
float datos_prueba [3]={a,b,0.0};
int col;
int fil=0;
int i=0;
int j;
float aux;
float aux_etiqueta;
float potencia;
float raiz;
int label;
String salida="";


 float matriz_k [3][k];
 for(;i<k;i++){
  matriz_k[0][i]=i+1.00;  //  |   1 |   2   |   3   |
  matriz_k[1][i]=0; //     |  0  |   0   |   0   |
  matriz_k[2][i]=2500.0+i;// |2500 | 25001 | 25002 | 
  }
  i=0;

  float matriz_eti[2][etiquetas];
  for(;i<etiquetas;i++){
      matriz_eti[0][i]=i+1.0; // |  1 |  2 |  3  |
      matriz_eti[1][i]=0.0;   // |  0 |  0 |  0  |
    }

   for(;fil<tam_fil;fil++){
      for(col=0;col<tam_col-1;col++){ // menos la ultima columna que corresponde a la etiqueta
          potencia=potencia+pow(matriz[fil][col]-datos_prueba[col],2);
        }
        raiz=sqrt(potencia);
        potencia=0;
        // comparacion de la nueva distancia con solo la mayor distancia almacenada en matriz_k
        if(raiz<matriz_k[2][k-1]){
          matriz_k[2][k-1]=raiz;
          matriz_k[1][k-1]=matriz[fil][tam_col-1]; 
          // ordenar matriz por metodo de burbuja
          for(i=0;i<k;i++){
             for(j=i+1;j<k;j++){
               if(matriz_k[2][i]>matriz_k[2][j]){
                 // distancia
                  aux=matriz_k[2][i];
                  matriz_k[2][i]=matriz_k[2][j];
                  matriz_k[2][j]=aux;
                  //etiqueta
                  aux_etiqueta=matriz_k[1][i];
                  matriz_k[1][i]=matriz_k[1][j];
                  matriz_k[1][j]=aux_etiqueta;
                }//end if
              } //end for j
            } // end for i
        } // end if
    } // end lectura matriz.h
    //buscar etiqueta con mayor repitencia
    for(i=0;i<etiquetas;i++){
      for(j=0;j<k;j++){
          if(matriz_eti[0][i]==matriz_k[1][j]){
            matriz_eti[1][i]++;
          }
        }
      }

    for(i=0;i<etiquetas-1;i++){
       if(matriz_eti[1][i]<matriz_eti[1][i+1]) // buscar el valor menor entre conteo de etiquetas
        label=(int)matriz_eti[0][i+1];    //asgina a label la etiqueta de mayor valor
        else 
        label=(int)matriz_eti[0][i];      //asgina a label la etiqueta de mayor valor
      }  
 switch(label){
  case 1:
    lcd.clear();
    lcd.setCursor(0,0);     //Ubicarse en la lcd
    lcd.print("Aire Limpio");      //Envía mensaje
    lcd.setCursor(0,1);//
    lcd.print(String("MQ7 ")+String (a));
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);     //Ubicarse en la lcd
    lcd.print("Aire Limpio");      //Envía mensaje
    lcd.setCursor(0,1);//
    lcd.print(String("MQ135 ")+String (b));
    digitalWrite(led1,HIGH);
  
  break;
  case 2:
    lcd.clear();
    lcd.setCursor(0,0);     //Ubicarse en la lcd
    lcd.print("Aire Contaminado");      //Envía mensaje
    lcd.setCursor(0,1);//
    lcd.print(String("MQ7 ")+String (a));
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);     //Ubicarse en la lcd
    lcd.print("Aire Contaminado");      //Envía mensaje
    lcd.setCursor(0,1);//    
    lcd.print(String("MQ135 ")+String (b));
    digitalWrite(led2,HIGH);
  break;
  }
 
  return label;
};
//PERRO GUARDIAN
void modo(){
    wdt_enable(WDTO_4S);     // modo sleep por 4 segundos
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);  //Seleccion modo sleep
    sleep_enable();     //Activacion modo sleep
    sleep_mode();      //Funcionamiento modo sleep 
    sleep_disable();   //Desactivar modo sleep 
    wdt_disable();    //Desactivar perro guiardian
}
void sistema(){
  delay(100);
  EEPROM.update(0,1);           //Actualizacion dato principal del sistema
}
void encender(){
  resetFunc();       //Funcion reiniciar arduino
}
