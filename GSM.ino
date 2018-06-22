bool initializeGSM() {
  char *command[] = { "AT", "ATE0", "AT+CPIN?", "AT+CLIP=1", "AT+CMEE=0", "AT+CMGF=1", "AT+CPBS=\"SM\"", "AT+CMGD=,4" };
  char *response[] = { "OK", "OK", "READY", "OK", "OK", "OK", "OK", "OK" };
  int  time[] = { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 5000 };

  // test if baud rate is 115200
  fonaSS.begin(115200);
  sendATCommandWaitResponse("AT+IPR=9600", "OK", 1000);
  fonaSS.begin(9600);
  Serial.print("Initializing GSM.. ");
  for (int i = 0; i < 8; i++) {
    int tries = 0;
    // try each command for 5 times
    while (sendATCommandWaitResponse(command[i], response[i], time[i]) == false) {
      tries++;

      // if fail 10 times, exit
      if (tries == 10) {
        Serial.println("FAILED!");
        return false;
      }
    }
  }
  Serial.println("OK!");
  Serial.print("Waiting for Network.. ");
  // wait for gsm to connect to network
  while (!sendATCommandWaitResponse("AT+CREG?", "+CREG: 0,1", 1000));
  Serial.println("OK!");
  return true;
}

bool sendATCommandWaitResponse(char* command, char* response, long timeout) {
  char reply[100];

  fonaSS.println(command);

  long startTime = millis();
  int pointer = 0;

  // if not timed out, check for reply
  while (millis() - startTime < timeout) {
    if (fonaSS.available()) {
      char c = fonaSS.read();
      reply[pointer++] = c;
      reply[pointer] = '\0';
    }

    // check reply for the response we want
    if (strstr(reply, response) != NULL) {
      return true;
    }

    yield();
  }

  return false;
}
