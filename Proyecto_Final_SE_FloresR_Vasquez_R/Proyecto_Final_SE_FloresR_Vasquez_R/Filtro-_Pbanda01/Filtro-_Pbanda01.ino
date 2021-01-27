#define tam_sig 150
#define tam_imp 27

//Import signal to another .h file 
extern double sigint[tam_sig];
extern double sigaux[tam_imp];
double output[tam_sig+tam_imp]; //vector de salida
void convolution(double *sig_in, double *sig_out, double *imp, int sig_tam, int imp_tam); //Definir funcion
void plot_signal(void);
void setup() {
Serial.begin(9600);
}
void loop() {
  convolution((double *)&sigint[0], (double *)&output[0], (double *)&sigaux[0],(int) tam_sig, (int) tam_imp);
  plot_signal();
  delay(100);
}
void convolution (double *sig_in, double *sig_out, double *imp, int sig_tam, int imp_tam){
  int i,j;
  //Poner ceros a vector de salida
  for(i=0;i<sig_tam+imp_tam;i++){
    sig_out[i]=0;
  }
  //Convolucion
  for(i=0;i<sig_tam;i++){
    for(j=0;j<imp_tam;j++){
         sig_out[i+j]=sig_out[i+j]+sig_in[i]*imp[j];
    }
  }
}
//Graficar resultado
void plot_signal(void){
  int i;
  for(i=0;i<tam_sig;i++){
    Serial.print(sigint[i]+10);
    Serial.print(",");
    Serial.println(output[i]);
    delay(5);
  }
}
