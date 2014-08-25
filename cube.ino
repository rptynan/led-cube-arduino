/*
   4x4x4 LED Cube Controller
   LED Cube controller for 4x4x4 with support for one button.
*/




// Set Column and Layer Levels, (HIGH or LOW)
const int collev = LOW;
const int laylev = HIGH;
// Set Layer Pins, (Z axis co-ordinate: l0; l1; l2; l3)
const int l0 = A0, l1 =A1, l2 = A2, l3 = A3;
// Set Column Pins, (X and Y co-ordinate, eg: c00; c02; c03; c10)
const int c00 = 0, c01 = 1, c02 = 2, c03  = 3, c10 = 4, c11 = 5, c12 = 6, c13 = 7, c20 = 8, c21 = 9, c22 = 10, c23 = 11, c30 = 12, c31 = 13, c32 = A4, c33 = A5; 
// Setup for Arrays
const int layarray[] = {l0,l1,l2,l3};
const int colarray[] = {c00, c01, c02, c03, c10, c11, c12, c13, c20, c21, c22, c23, c30, c31, c32, c33};
// Set Button Input Pin (bip), Level When Closed (lwc) and Delay for Button Input Timeout (buttondelay)
const int bip = 8;
const int lwc = LOW;
const int buttondelay = 1000;
// Set Column and Layar Indicators (colind & layind)
const int colind = c00;
const int layind = l0;
// Setup for Mode Counter
int mode=0;
unsigned long start = 0;
// Setup for array to hold pin order
int order[20];



//Various Functions for turning on and off LEDs

void onoff(int ColCo, int LayCo, int dela){
  digitalWrite(ColCo, collev);
  digitalWrite(LayCo, laylev);
  delay(dela);
  digitalWrite(ColCo, laylev);
  digitalWrite(LayCo, collev);
}

void onoff1(int ColCo, int LayCo){
  digitalWrite(ColCo, collev);
  digitalWrite(LayCo, laylev);
  digitalWrite(ColCo, laylev);
  digitalWrite(LayCo, collev);
}

void off(int ColCo, int LayCo){
  digitalWrite(ColCo, laylev);
  digitalWrite(LayCo, collev);
}

void on(int ColCo, int LayCo){
  digitalWrite(ColCo, collev);
  digitalWrite(LayCo, laylev);
}
  
void offon(int ColCo, int LayCo, int dela){
  digitalWrite(ColCo, laylev);
  digitalWrite(LayCo, collev);
  delay(dela);
  digitalWrite(ColCo, collev);
  digitalWrite(LayCo, laylev);
}

//Overloaded for x,y,z
void on(int x, int y, int z){
  digitalWrite(colarray[4*y+x], collev);
  digitalWrite(layarray[z], laylev);
}

void off(int x, int y, int z){
  digitalWrite(colarray[4*y+x], laylev);
  digitalWrite(layarray[z], collev);
}
	




void setup(){
  //Sets a Random Seed for random() function from any random pin (except button pin which is tied)
  randomSeed(analogRead(c00));
  
  //Sets the Pins Modes that we need
  pinMode(bip, INPUT);
  pinMode(layind, OUTPUT);
  pinMode(colind, OUTPUT);
 //Turns off pin 13 because the arduino writes it low during the setup, making it appear on to us
  digitalWrite(13,laylev);
  //The mode counting part, counts how many times the button is pushed
  on(colind, layind);                                        //turns on indicator LED
  while(1){
    if(digitalRead(bip)==lwc){ //&& millis()-start<buttondelay){ //if button pressed within timeout
      mode++;
      offon(colind, layind, 200);                            //flashes indicator LED off to acknowledge button press
      start=millis();}                                       //resets timer
    else if(millis()-start>buttondelay && mode>0){
      break;}                                                //breaks loop if no button press within timeout and if button has been pressed at least once
  }
  off(colind, layind);
  delay(500);
  //Blink Mode Number
  for(int i=0; i<mode; i++){
    onoff(colind, layind, 100);
    delay(100);}
    
  //Actual Layar pinModes
  for(int i=0; i<4; i++){
    pinMode(layarray[i], OUTPUT);}
  //Actual Column pinModes
  for(int i=0; i<17; i++){
    pinMode(colarray[i], OUTPUT);}
  //Sets all LEDs to off
  for(int x=0; x<4; x++){
    for(int y=0; y<16; y++){
      off(colarray[y], layarray[x]);
    }
  }
}



void loop(){
//MODE 1 - Solid Cube
  if(mode==0 || mode==1){
    int prevc=colarray[0], prevl=layarray[0];
    while(1){
      for(int x=0; x<4; x++){
        for(int y=0; y<16; y++){
          on(colarray[y], layarray[x]);
          delay(1);
          off(prevc, prevl);
          prevc=colarray[y];
          prevl=layarray[x];
          //onoff1(colarray[y], layarray[x]);
        }
      }
    }
  }
//MODE 2 - Flashing Cube -----v2
/*  if(mode==2){
    for(int x=0; x<4; x++){
      order[x] = layarray[x];   //find way to append to arrays
      for(int y=0; y<16; y++){
          order[x = colarray[y];
      }
    }
    int prevcol;
    int prevlay;
    int cur
    while(1){
      for(int x=0; x<order.length(); x++){
        cur = &order[x];
        if(cur[0]=="l"){
          digitalWrite(prevlay, collev);
          digitalWrite(cur, laylev);
          prevlay* = cur;}
        if(cur[0]=="c"){
          digitalWrite(cur, collev);
          digitalWrite(prevcol, laylev);
          prevcol* = cur;}
      }
    }
  }*/
//MODE 3 - Flittering
  if(mode==3){
    while(1){
      for(int x=0; x<4; x++){
        for(int y=0; y<16; y++){
          onoff(colarray[y], layarray[x], 12);
        }
      }
    }
  }
//MODE 4 - Random
  if(mode==4){
    while(1){
      int x=random(16);
      int y=random(4);
      onoff(colarray[x], layarray[y], 30);
    }
  }
//MODE 5 - Faster Random
  if(mode==5){
    while(1){
      int x=random(16);
      int y=random(4);
      onoff(colarray[x], layarray[y], 4);
    }
  }
//MODE 6 - Falling Random Columns
  if(mode==6){
    while(1){
      int x=random(16);
      for(int y=3; y>=0; y--){
        onoff(colarray[x], layarray[y], 75);}
    }
  }
//MODE 7 - 3D Conway's Game
  if(mode==7){  
		bool ar[4][4][4], nar[4][4][4], nm, past[4][4][4];
		int t=0;
		while(1){

				for(int x=0; x<4; ++x)
					for(int y=0; y<4; ++y)
						for(int z=0; z<4; ++z)
							ar[x][y][z]=random(2);

				while(1){
						for(int x=0; x<4; ++x){
							for(int y=0; y<4; ++y){
								for(int z=0; z<4; ++z){
									t=0;
									for(int q=x-1; q<x+2; ++q){
										for(int w=y-1; w<y+2; ++w){
											for(int e=z-1; e<z+2; ++e){
												t+=ar[(4+q)%4][(4+w)%4][(4+e)%4];
											}
										}
									}
									t-=ar[x][y][z];
									if(t==5) nar[x][y][z]==1;
									else if(t<2 || t>7) nar[x][y][z]==0;
									else nar[x][y][z]=ar[x][y][z];
								}
							}
						}
						
						nm=1;
						for(int x=0; x<4; ++x){
							for(int y=0; y<4; ++y){
								for(int z=0; z<4; ++z){
									if(nar[x][y][z]!=ar[x][y][z]) nm=0;
									ar[x][y][z]=nar[x][y][z];
								}
							}
						}
						
						if(nm) break;
						
						start=millis();
						while(millis()<start+200){
							for(int x=0; x<4; ++x){
								for(int y=0; y<4; ++y){
										if(ar[x][y][0]) on( colarray[(0*4)+x], layarray[y]);
										if(ar[x][y][1]) on( colarray[(1*4)+x], layarray[y]);
										if(ar[x][y][2]) on( colarray[(2*4)+x], layarray[y]);
										if(ar[x][y][3]) on( colarray[(3*4)+x], layarray[y]);
										if(ar[x][y][0]) off( colarray[(0*4)+x], layarray[y]);
										if(ar[x][y][1]) off( colarray[(1*4)+x], layarray[y]);
										if(ar[x][y][2]) off( colarray[(2*4)+x], layarray[y]);
										if(ar[x][y][3]) off( colarray[(3*4)+x], layarray[y]);
								}
							}
						}

				}
		}
	}
//Mode 8 - Random Walk Snake
  const int slen=4, del=100;
  int snake[slen][3]; //[3]=x,y,z
  int next, dir, prevdir=-1;
  int head=0; //location of head in snake array
  bool bad;
  for(int i=0; i<slen; ++i){
  	snake[i][0]=0; snake[i][1]=0; snake[i][2]=0;
  }
  while(1){
    bad=0;
	dir=random(6);
  	next=(head+1)%slen;
  	snake[next][0]=snake[head][0];
  	snake[next][1]=snake[head][1];
  	snake[next][2]=snake[head][2];
  	if(dir==0) snake[next][0]=snake[head][0]+1;
  	if(dir==1) snake[next][0]=snake[head][0]-1;
  	if(dir==2) snake[next][1]=snake[head][1]+1;
  	if(dir==3) snake[next][1]=snake[head][1]-1;
  	if(dir==4) snake[next][2]=snake[head][2]+1;
  	if(dir==5) snake[next][2]=snake[head][2]-1;
	for(int i=0; i<3; ++i){
	  if(snake[next][i]<0 || snake[next][i]>=4){
		bad=1;
		break;
	  }
	}
	for(int i=0; i<slen; ++i){
	  if(i==next) continue;
	  if(snake[i][0]==snake[next][0] && snake[i][1]==snake[next][1] && snake[i][2]==snake[next][2]){
	    bad=1;
		break;
	  }
	}
	if(bad) continue;
	start=millis();
	while(millis()<start+del){
		for(int i=0; i<slen; ++i){
			on(snake[i][0],snake[i][1],snake[i][2]);
			off(snake[i][0],snake[i][1],snake[i][2]);
		}
	}
  	head=next;
  }
	

}//End of Loop


