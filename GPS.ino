float gps_lat, gps_lon, rtc_date, rtc_time, speed_kph;

String googleMapsQueryString = "http://maps.google.com/?q=";

String get_a_gps_reading() { //do not run more often than once every few seconds

  // if you ask for an altitude reading, getGPS will return false if there isn't a 3D fix
  boolean gps_success = fona.getGPS(&gps_lat, &gps_lon, &rtc_date, &rtc_time, &speed_kph);

  if (gps_success) {

    //    Serial.print(F("gps_lat: ")); Serial.println(gps_lat);
    //    Serial.print(F("gps_lon: ")); Serial.println(gps_lon);
    //    Serial.print(F("rtc_date: ")); Serial.println(rtc_date);
    //    Serial.print(F("rtc_time: ")); Serial.println(rtc_time);
    //    Serial.print(F("speed_kph: ")); Serial.println(speed_kph);
    //    Serial.println();

    String latlon = String(gps_lat, 6) + "," + String(gps_lon, 6);

    //    String speedKPH = String(2.0 * speed_kph, 2);
        String myString = "date: " + String(rtc_date, 0) + " time: " + String(rtc_time, 0) + " " + googleMapsQueryString + String(gps_lat, 6) + "," + String(gps_lon, 6);

    Serial.println(myString);
    return latlon;

  } else {
    Serial.println(F("Waiting for FONA GPS 3D fix..."));
  }
}


