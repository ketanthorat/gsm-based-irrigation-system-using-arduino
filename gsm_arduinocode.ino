#include <SoftwareSerial.h>
const String PHONE_NUM = "+911234567890";// Use your phone number where you will recieve the sms from the GSM System.
SoftwareSerial SIM800L(3, 2);
// tx rx
String smsStatus, senderNumber, receivedDate, msg;
boolean isReply = false;
#include <LiquidCrystal.h> // this header file er is used to drive the 16x2 LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // this function is used to assign the Pin of LCD
//part of ultrasonic sensor//
const int trigPin = A2; // Variable to inrtface level sensor pin
const int echoPin = A1;// Variable to inrtface level sensor pin
long duration; // conversion varible
double level, distanceCm; // conversion varible
float TankHeight = 20;
bool L_f_50 = 0;
// Part of Moisture Sensor //
int mostdata = A7;
float Moisture = 0;
float MoistureInPer = 0;
float MoistureInAbs = 0;
bool M_f_20 = 0;
bool M_f_80 = 0;
//int Pump = 5;
int state;
//float Light1;
String Motor = "Motor off";
String space = " ";
#define RELAY_1(D7) 6
#define RELAY_2(D8) 6
//int buzzer = 7;
int a = 0;
#define RefreshTime 0.1
void setup()
{
lcd.begin(16, 2); // this function is used to start the LCD operation for 16x2 lcd
Serial.begin(9600); // used to print the data on serial monitor of arduino IDE
// pinMode(Pump, OUTPUT);
digitalWrite(6, LOW);
digitalWrite(RELAY_1(D7), HIGH);
digitalWrite(RELAY_2(D8), HIGH);
delay(1000);
pinMode(RELAY_1(D7), OUTPUT);
pinMode(RELAY_2(D8), OUTPUT);
SIM800L.begin(9600);
Serial.println("SIM800L software serial initialize");
smsStatus = "";
senderNumber = "";
receivedDate = "";
msg = "";
SIM800L.print("AT+CMGF=1\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=1\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=2\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=3\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=4\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=5\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=6\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=7\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=8\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=9\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=10\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=11\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=12\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=13\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=14\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=15\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=16\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=17\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=18\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=19\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=20\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=21\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=22\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=23\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=24\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=25\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=26\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=27\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=28\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=29\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=30\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=31\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=32\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=33\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=34\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=35\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=36\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=37\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=38\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=39\r"); //SMS text mode
delay(100);
SIM800L.print("AT+CMGD=40\r"); //SMS text mode
delay(100);
// Part Of Level Sensor
pinMode(trigPin, OUTPUT); // to define as output
pinMode(echoPin, INPUT); // to define as input
//Name Printing on LCD//
lcd.clear(); // used to clea the data on LCD
lcd.setCursor(0, 0); // used to set the cursor position for data printing on LCD (column,Row)
lcd.print("GSM Based smart"); // used to print the data as it is
lcd.setCursor(0, 1); // used to set the cursor position for data printing on LCD (column,Row)
lcd.print("Irrigation Systm"); // used to print the data as it is
delay(3000); // delay is used to hold the data on LCD for 4 seconds
lcd.clear(); // used to clea the data on LCD
}
void loop()
{
while (SIM800L.available())
{
parseData(SIM800L.readString());
}
while (Serial.available())
{
SIM800L.println(Serial.readString());
}
a++;
if (a == 40)
{
//part of ultra sonic sensor
digitalWrite(trigPin, LOW); // to send the ultrasonic Wave
delayMicroseconds(2); // delay is used to wait in microsecond
digitalWrite(trigPin, HIGH); // to recieve the ultrasonic Wave
delayMicroseconds(10); // delay is used to wait in microsecond
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH); // measure the time of wave duration
distanceCm = (duration * 0.034 / 2) - 3; // to convert the time into distance
if (distanceCm < 0)
{
distanceCm = 0;
}
if (distanceCm > TankHeight)
{
distanceCm = TankHeight;
}
level = abs((((distanceCm / TankHeight) * 100) - 100));
//Serial.println(level);
// Part of Moisture Sensor
Moisture = analogRead(mostdata);
MoistureInPer = (((Moisture / 1024) * 100) - 100) ;
MoistureInAbs = (abs(MoistureInPer)) * 1.2500 ;
//Serial.println(Moisture);
if (MoistureInAbs > 100)
{
MoistureInAbs = 100;
}
if (MoistureInAbs > 70 && M_f_80 == 1)
{
Motor = "Motor Off";
digitalWrite(RELAY_2(D8), HIGH);
Reply("PUMP HAS TURNED OFF" + space + '\n' + '\n' + "TANK LEVEL = " + String(level) +
'\n' + "MOISTURE = " + String(MoistureInAbs) + '\n' + Motor);
M_f_80 = 0;
}
if (MoistureInAbs < 60)
{
M_f_80 = 1;
}
if (MoistureInAbs < 20 && M_f_20 == 0)
{
Reply("lOW MOISTURE LEVEL!" + space + '\n' + '\n' + "TANK LEVEL = " + String(level) +
'\n' + "MOISTURE = " + String(MoistureInAbs) + '\n' + Motor);
M_f_20 = 1;
}
if (MoistureInAbs > 24 )
{
M_f_20 = 0;
}
if (level < 50 && L_f_50 == 0)
{
Reply("lOW WATER LEVEL!" + space + '\n' + '\n' + "TANK LEVEL = " + String(level) + '\n' +
"MOISTURE = " + String(MoistureInAbs) + '\n' + Motor);
L_f_50 = 1;
}
if (level > 55 )
{
L_f_50 = 0;
}
// data printing on lcd//
//
lcd.clear();
lcd.setCursor(0, 0); lcd.print("M= ");
lcd.setCursor(2, 0); lcd.print(MoistureInAbs, 0);
lcd.setCursor(5, 0); lcd.print("%");
lcd.setCursor(0, 1); lcd.print("Tank lvl =");
lcd.setCursor(10, 1); lcd.print(level, 0);
lcd.setCursor(15, 1); lcd.print("%");
lcd.setCursor(8, 0); lcd.print(Motor);
}
if (a > 40)
{
a = 0;
}
delay(40);
}
void parseData(String Buffer)
{
Serial.println(Buffer);
unsigned int len, index;
//Remove sent "AT Command" from the response string.
index = Buffer.indexOf("\r");
Buffer.remove(0, index + 2);
Buffer.trim();
if (Buffer != "OK") {
index = Buffer.indexOf(":");
String cmd = Buffer.substring(0, index);
cmd.trim();
Buffer.remove(0, index + 2);
if (cmd == "+CMTI")
{
//get newly arrived memory location and store it in temp
index = Buffer.indexOf(",");
String temp = Buffer.substring(index + 1, Buffer.length());
temp = "AT+CMGR=" + temp + "\r";
//get the message stored at memory location "temp"
SIM800L.println(temp);
}
else if (cmd == "+CMGR")
{
extractSms(Buffer);
//if (senderNumber == PHONE_NUM)
{
doAction();
}
}
}
else
{
//The result of AT Command is "OK"
}
}
void extractSms(String Buffer)
{
unsigned int index;
index = Buffer.indexOf(","); //Locates a character or String within another String. By default,searches from the beginning of the String,//but can also start from a given index, allowing for the locating of all instances of the characteror String.
smsStatus = Buffer.substring(1, index - 1);
Buffer.remove(0, index + 2);
senderNumber = Buffer.substring(0, 13);
Buffer.remove(0, 19);
receivedDate = Buffer.substring(0, 20);
Buffer.remove(0, Buffer.indexOf("\r"));
Buffer.trim();
index = Buffer.indexOf("\n\r");
Buffer = Buffer.substring(0, index);
Buffer.trim();
msg = Buffer;
Buffer = "";
msg.toLowerCase();
Serial.println(msg);
}
void doAction()
{
if (msg == "motor on")
{
if (msg == "motor on" && MoistureInAbs < 70 && level > 50)
{
digitalWrite(RELAY_1(D7), LOW);
Motor = "Motor On";
// Reply("Relay 2 has been On");
Reply("PUMP HAS TURNED ON" + space + '\n' + '\n' + "TANK LEVEL = " + String(level) +
'\n' + "MOISTURE = " + String(MoistureInAbs) + '\n' + Motor);
}
else if (msg == "motor on" && MoistureInAbs > 70 && level < 50)
{
digitalWrite(RELAY_1(D7), HIGH);
Motor = "Motor Off";
// Reply("Relay 2 has been On");
Reply("LOW TANK LEVEL FILL THE TANK" + space + '\n' + '\n' + "TANK LEVEL = " +
String(level) + '\n' + "MOISTURE = " + String(MoistureInAbs) + '\n' + Motor);
}
else if (msg == "motor on" && MoistureInAbs > 70 && level > 50)
{
digitalWrite(RELAY_1(D7), HIGH);
Motor = "Motor Off";
// Reply("Relay 2 has been On");
Reply("SUFFICIENT MOISTURE AVAILABLE" + space + '\n' + '\n' + "TANK LEVEL = " +
String(level) + '\n' + "MOISTURE = " + String(MoistureInAbs) + '\n' + Motor);
}
else if (msg == "motor on" && MoistureInAbs < 70 && level < 50)
{
digitalWrite(RELAY_1(D7), HIGH);
Motor = "Motor Off";
// Reply("Relay 2 has been On");
Reply("LOW TANK LEVEL FILL THE TANK" + space + '\n' + '\n' + "TANK LEVEL = " +
String(level) + '\n' + "MOISTURE = " + String(MoistureInAbs) + '\n' + Motor);
}
}
else if (msg == "motor off")
{
if (msg == "motor off" && MoistureInAbs < 70)
{
digitalWrite(RELAY_2(D8), HIGH);
Motor = "Motor Off";
Reply("MOTOR HAS TURNED OFF" + space + '\n' + '\n' + "TANK LEVEL = " + String(level)
+ '\n' + "MOISTURE = " + String(MoistureInAbs) + '\n' + Motor);
}
else if (msg == "motor off" && MoistureInAbs > 70)
{
digitalWrite(RELAY_2(D8), HIGH);
Motor = "Motor Off";
Reply("MOTOR IS ALREADY OFF" + space + '\n' + '\n' + "TANK LEVEL = " + String(level) +
'\n' + "MOISTURE = " + String(MoistureInAbs) + '\n' + Motor);
}
}
else if (msg == "status")
{
Reply("TANK LEVEL = " + String(level) + '\n' + "MOISTURE = " + String(MoistureInAbs) + '\n'
+ Motor);
}
smsStatus = "";
senderNumber = "";
receivedDate = "";
msg = "";
}
void Reply(String text)
{
SIM800L.print("AT+CMGF=1\r");
delay(1000);
SIM800L.print("AT+CMGS=\"" + PHONE_NUM + "\"\r");
delay(1000);
SIM800L.print(text);
delay(1000);
SIM800L.write(0x1A); //ascii code for ctrl-26 //SIM800L.println((char)26); //ascii code for ctrl-26
delay(1000);
Serial.println("SMS Sent Successfully.");
}