#include <main.h>

const int SMALL   = 2;  
const int MEDIUM  = 3;
const int LARGE   = 6;
  
void update(uint8_t state, uint32_t speed,  uint8_t sats) {
  uint32_t is;
   
  display.setTextSize(LARGE);
  display.setCursor(0, 12);
  is = SPEED_CONVERSION*speed; 
  if (sats > 9) { sats = 9; }
  display.clearDisplay();
  if (state) { display.invertDisplay(true); } else { display.invertDisplay(false); }
  if (is < 10 ) { display.print(' '); }
  if (is < 100) { display.print(' '); }
  display.print(is);
  display.setCursor(108, 40);
  display.setTextSize(MEDIUM);
  display.print(sats);
  display.display();
  // display.setCursor(0, 8);
  // display.print("lon: ");      
  // display.print((float)pvt.lon/10000000.0f, 6);
  // display.setCursor(0, 16);
  // display.print("lat: ");      
  // display.print((float)pvt.lat/10000000.0f, 6);
  }

  void setup() {
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);
  delay(1000);
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println("SSD1306 Initialisation Success");
  display.display();
  display.setTextSize(SMALL);
  display.setTextColor(WHITE);
  // display.setRotation(2);
  if (!driver.init()) { Serial.println("init failed"); } else { Serial.println("Init success!"); }
  delay(2000);
  display.clearDisplay();
  display.setCursor(0,0);
  digitalWrite(LED_RED, HIGH);
  update(pkt.state, pkt.speed, pkt.numSV);
  display.display();
 }

void loop() {

  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv((uint8_t *)&pkt, &buflen)) // Non-blocking
    {
    Serial.print("buflen: "); Serial.print(buflen);   
    Serial.print(", State "); Serial.print(pkt.state);  
    Serial.print(", Speed "); Serial.print((uint32_t)pkt.speed*SPEED_CONVERSION);   
    Serial.print(", #Sats "); Serial.print(pkt.numSV);
    Serial.println(); 
    update(pkt.state, pkt.speed, pkt.numSV);
}
}