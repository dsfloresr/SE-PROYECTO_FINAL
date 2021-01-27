
import processing.serial.*;
import ddf.minim.*;

PImage img,img1,img2; 
int alt = 0;

Serial port;
void setup(){
port=new Serial(this,"COM4",9600);
 size (700,700);
 background(#BBF2F7);
 img=loadImage("utn.png");//pegar imagen
 img1=loadImage("airp.png");//pegar imagen
 img2=loadImage("airc.png");//pegar imagen
 fill(1);
 textSize(25);
 text("UNIVERSIDAD TÉCNICA DEL NORTE",135,50);
 text("SISTEMAS EMBEBIDOS",225,90);
 text("PROYECTO FINAL",255,170);
 text("DETECTOR DE GASES",230,130);
 text("STEVEN FLORES",100,600);
 text("MERCEDES VASQUEZ",100,650);
 
 regresion();
}
void draw(){
  fill(255);
  rect(100,200,500,350);
  image(img,50,30,80,80);
  regresion();
}
void regresion(){
  
    switch(alt){
      case 0:
      fill(1);
      textSize(25);
      text("ESPERANDO DATO",233,300);
      
      break;
      case 1:
      fill(1);
      textSize(25);
      text("AIRE LIMPIO",233,300);
      image(img1,300,310,120,120);
      
      break;
      case 2:
      fill(1);
      textSize(25);
      text("AIRE CONTAMINADO",233,300);
      image(img2,300,310,120,120);
      break;
    }
}
void serialEvent(Serial port){
  alt = port.read();
  println(alt);
}
