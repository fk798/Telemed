#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
// MySQL Connection Start ----------------------
IPAddress server_addr(192,168,1,236);  // IP of the MySQL *server* here
char user[] = "arduino";
char password[] = "password";

bool stop = false;

// WiFi card example
char ssid[] = "786";         // your SSID
char pass[] = "SKBKFKFKFK786";     // your SSID Password

WiFiClient client;                 // Use this for WiFi instead of EthernetClient
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;
// MySQL Connection End ------------------------

// Pulse Start ---------------------------------
int Signal;
int Threshold = 550;
int PulseSensorPin = 0;
int beats[500];
int counter = 0;
// Pulse End -----------------------------------

// Combo
int pulseBaudRate = 9600;
int sqlBaudRate = 115200;

void setup()
{
  Serial.begin(pulseBaudRate);
  //while (!Serial); // wait for serial port to connect. Needed for Leonardo only
}

void loop()
{
  if (counter < 500) {
    Signal = analogRead(PulseSensorPin);
    Serial.println(Signal);
    beats[counter] = Signal;
    counter++;
  }
  if (counter >= 500 && stop == false) {
    Serial.flush();
    delay(2);
    Serial.begin(sqlBaudRate);
    // Begin WiFi section
    Serial.printf("\nConnecting to %s", ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    // print out info about the connection:
    Serial.println("\nConnected to network");
    Serial.print("My IP address is: ");
    Serial.println(WiFi.localIP());
  
    Serial.print("Connecting to SQL...  ");
    if (conn.connect(server_addr, 3306, user, password))
      Serial.println("OK.");
    else
      Serial.println("FAILED.");
    
    // create MySQL cursor object
    String data;
    for (size_t i = 0; i < 500 - 1; ++i) {
      data.concat(beats[i]);
      data.concat(",");
    }
    data.concat(beats[499]);

    // Query
    String sqlStatement = "INSERT INTO pulseScan.users (name, data) VALUES ('Faisal','";
    sqlStatement.concat(data);
    sqlStatement.concat("')");
    Serial.println(sqlStatement);
    char INSERT_SQL[sqlStatement.length()];
    sqlStatement.toCharArray(INSERT_SQL, sqlStatement.length() + 1); 
    Serial.println(INSERT_SQL);
    cursor = new MySQL_Cursor(&conn);
    if (conn.connected())
      cursor->execute(INSERT_SQL);
    stop = true;
  }   

  delay(10);
}
