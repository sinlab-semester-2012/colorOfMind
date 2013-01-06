/**
* This example is yet to be improved. It does not handle exceptions and may prove faulty.
*/

//Import OSC libs
import oscP5.*;
import netP5.*;
//import Dmx libs
import dmxP512.*;
import processing.serial.*;

//DMX
DmxP512 dmxOutput;
int universeSize=128;
boolean DMXPRO=true;
String DMXPRO_PORT="/dev/ttyUSB0";//case matters ! on windows port must be upper cased.
int DMXPRO_BAUDRATE=57600;

//OSC
OscP5 oscP5;

float[] vals;


void setup() {
  //Graphical
  size(400 , 200);
  smooth();
  noStroke();
  //osc
  oscP5 = new OscP5(this, 9997);
  //dmx
  dmxOutput=new DmxP512(this,universeSize,false);
  dmxOutput.setupDmxPro(DMXPRO_PORT,DMXPRO_BAUDRATE);
  //hint(ENABLE_OPENGL_4X_SMOOTH);
  
  //Data structures
  vals = new float[400];
  for (int i = 0; i < vals.length; i++) {
      vals[i] = 0; 
  }

}

//Main function, draw frame
void draw(){
  background(255);
  
  // Draw lines connecting all points
  for (int i = 0; i < vals.length-1; i++) {
    stroke(0);
    strokeWeight(2);
    line(i,vals[i]+100,i+1,vals[i+1]+100);
  }

  //Update dmx channel
  // for(int i=0;i<nbChannel;i++){
  //    int value=(int)random(10)+((i%2==0)?mouseX:mouseY);
  //    dmxOutput.set(i,value);
  //    fill(value);
  //    rect(0,i*height/10,width,(i+10)
  
}

//If new OSC value, update happens here
void oscEvent(OscMessage msg){
  if(msg.checkAddrPattern("/emokit/channels")){
    println("1) Channel readings:");
    for(int i=0 ; i<14 ; i++){
      println("[" + i + "] : " + msg.get(i).intValue());
    }
    vals[vals.length-1] = (float)msg.get(2).intValue()/1374144519*50;
    println("value" + vals[vals.length-1]);
      // Slide everything down in the array
    for (int i = 0; i < vals.length-1; i++) {
      vals[i] = vals[i+1]; 
    }
    println();
  } else if(msg.checkAddrPattern("/emokit/gyro")){
    println("2) Gyro:");
    println("x: " + msg.get(0).intValue() + " ; y: " + msg.get(1).intValue());
    println();
  }
}

