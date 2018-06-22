#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"


// USER SETTINGS
const unsigned int LOGINTERVAL = 10000; //in milliseconds
String myMobileNum = "97974063"; //no need international code in front, just use local number. Number to send to. 

#define FONA_RX D6
#define FONA_TX D7
#define FONA_RST 4 //not used

SoftwareSerial fonaSS = SoftwareSerial(FONA_RX, FONA_TX);
SoftwareSerial *fonaSerial = &fonaSS;

Adafruit_FONA_3G fona = Adafruit_FONA_3G(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);
unsigned long lastLoggedTime;

void setup() {

  Serial.begin(115200);

  initializeGSM();

  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("Enabling GPS...allow up to 15min to get initial fix"));
  fona.enableGPS(true);
  Serial.println(F("FONA is ready"));

  print_menu();
}

void loop() { 

  run_menu();

}


