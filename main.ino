#include <TMRpcm.h>
#include <SD.h>
#include <SPI.h>
TMRpcm audio;
int file_number = 0;
char filePrefixname[50] = "spy";
char exten[10] = ".wav";
const int recordLed = 2;
const int mic_pin = A0;
const int sample_rate = 84000;

#define SD_CSPin 4
void wait_min(int mins) {
  int count = 0;
  int secs = mins * 60;
  while (1) {
    Serial.print('.');
    delay(1000);
    count++;
    if (count == secs) {
      count = 0;
      break;
    }
  }
  Serial.println();
  return ;
}
void setup() {
  Serial.begin(9600);
  pinMode(mic_pin, INPUT);
  pinMode(recordLed, OUTPUT);
  Serial.println("loading... SD card");
  if (!SD.begin(SD_CSPin)) {
    Serial.println("An Error has occurred while mounting SD");
  }
  while (!SD.begin(SD_CSPin)) {
    Serial.print(".");
    delay(500);
  }
  audio.CSPin = SD_CSPin;
}
void loop() {
  Serial.println("######################################################################################");
  char fileSlNum[20] = "";
  itoa(file_number, fileSlNum, 10);
  char file_name[50] = "";
  strcat(file_name, filePrefixname);
  strcat(file_name, fileSlNum);
  strcat(file_name, exten);
  Serial.print("New File Name: ");
  Serial.println(file_name);
  digitalWrite(recordLed, HIGH);
  audio.startRecording(file_name, sample_rate, mic_pin);
  Serial.println("startRecording ");
  wait_min(1);
  digitalWrite(recordLed, LOW);
  audio.stopRecording(file_name);
  Serial.println("stopRecording");
  file_number++;
  Serial.println("########################################################################################");
}
