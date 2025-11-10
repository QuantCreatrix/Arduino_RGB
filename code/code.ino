#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ALL COMPONENTS DEFINITION
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define VRX A0
#define VRY A1
int x, y, lineX, lineFX;
int cc = 1;
int R, G, B = 0;
int linePositions[3][2] = {{0,24}, {47,72}, {95,120}};

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // // create SSD1306 display object connected to I2C

void RGB(){
  oled.setTextSize(3);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(4,5);
  oled.print("R");
  oled.setCursor(50,5);
  oled.print("G");
  oled.setCursor(100,5);
  oled.print("B");
  // Initializing values
  oled.setTextSize(1);
  oled.setCursor(2, 50);
  oled.print(R);
  oled.setCursor(48, 50);
  oled.print(G);
  oled.setCursor(98, 50);
  oled.print(B);
  oled.display();
  return;
}

int getDirection(int x, int y) {
  //Resultant OUTPUT = 1 (RIGHT) 2 (LEFT) 3 (UP) 4 (DOWN)
  if (x >= 1000) {
    return 1; // RIGHT
  } else if (x <= 200) {
    return 2; // LEFT
  }
  if (y >= 1000) {
    return 4; // DOWN
  } else if (y <= 200) {
    return 3; // UP
  }

  return 5;
}

void lineDraw(int x, int x1){
  oled.clearDisplay();
  RGB();
  oled.drawLine(x,35,x1,35,WHITE);
  oled.display();
  return;
}


int leftRight(int dir, int cc){
  if(dir == 1){
    if(cc == 1){
      cc = 2;
      lineDraw(linePositions[1][0], linePositions[1][1]);
      return cc;
    }if(cc == 2){
      cc = 3;
      lineDraw(linePositions[2][0], linePositions[2][1]);
      return cc;
    }if(cc == 3){
      cc = 1;
      lineDraw(linePositions[0][0], linePositions[0][1]);
      return cc;
    }
  }
  if(dir == 2){
    if(cc == 1){
      cc = 3;
      lineDraw(linePositions[2][0], linePositions[2][1]);
      return cc;
    }if(cc == 2){
      cc = 1;
      lineDraw(linePositions[0][0], linePositions[0][1]);
      return cc;
    }if(cc == 3){
      cc = 2;
      lineDraw(linePositions[1][0], linePositions[1][1]);
      return cc;
    }
  }
}

int up(int cc){
  oled.clearDisplay();
  if(cc == 1){
    R = min(R++, 255);
    lineDraw(linePositions[0][0], linePositions[0][1]);
    oled.setCursor(2,50);
    oled.print(R);
    oled.display();
  }

  if(cc == 2){
    G = min(G++, 255);
    lineDraw(linePositions[1][0], linePositions[1][1]);
    oled.setCursor(48,50);
    oled.print(G);
    oled.display();
  }

  if(cc == 3){
    B = min(B++, 255);
    lineDraw(linePositions[2][0], linePositions[2][1]);
    oled.setCursor(98,50);
    oled.print(B);
    oled.display();
  }
}

int down(int cc){
  oled.clearDisplay();
  if(cc == 1){
    R = max(0,R--);
    lineDraw(linePositions[0][0], linePositions[0][1]);
    oled.setCursor(2,50);
    oled.print(R);
    oled.display();
  }

  if(cc == 2){
    G = max(0,G--);
    lineDraw(linePositions[1][0], linePositions[1][1]);
    oled.setCursor(48,50);
    oled.print(G);
    oled.display();
  }

  if(cc == 3){
    B = max(0,B--);
    lineDraw(linePositions[2][0], linePositions[2][1]);
    oled.setCursor(98,50);
    oled.print(B);
    oled.display();
  }
}


int upDown(int dir, int cc){
  if(dir == 3){
    up(cc);
    return cc;
  }
  if(dir == 4){
    down(cc);
  }
}

void setup() {
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  RGB();
  oled.drawLine(2, 35, 24, 35, WHITE);
  oled.display();
}

void loop() {
  // lineX = 0; lineFX = 25;
  // oled.drawLine(lineX, 35, lineFX, 35, WHITE);
  // oled.display();
  x = analogRead(VRX);
  y = analogRead(VRY);

// Serial Print Code
  Serial.print("x = ");
  Serial.print(x);
  Serial.print(", y = ");
  Serial.println(y);
  Serial.println();
 

// Getting direction
  int direction = 5;
  direction = getDirection(x, y);
  Serial.print(direction);
  Serial.print(" ");
  Serial.print(cc);

// Calling respective functions
  if(direction == 1 || direction == 2){
    Serial.print(cc);
    cc = leftRight(direction, cc);
  }
  if(direction == 3 || direction == 4){
    Serial.print(cc);
    cc = upDown(direction, cc);
  }
  oled.display();

  
  analogWrite(3, R);
  analogWrite(5, G);
  analogWrite(6, B);
  

  //delay(100);
}


