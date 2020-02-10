//unsigned long curTime;
//const int ledPin = 13;
//const int beepPin = 12;
//char textString[128];  //BE CAREFUL NOT TO OVERFLOW THE MORSE BUFFER 256 DOTS+DASHES
//char morseBuild[256];
//const int NUMBER_OF_ELEMENTS = 38;
//const int MAX_SIZE = 6;
////char textLUT [NUMBER_OF_ELEMENTS] [MAX_SIZE] = {
//// { ".-" },//a    //0
//// { "-..." },//b
//// { "-.-." },//c
//// { "-.." },//d
//// { "." },//e
//// { "..-." },//f  //5
//// { "--." },//g
//// { "...." },//h
//// { ".." },//i
//// { ".---" },//j
//// { "-.-" },//k   //10
//// { ".-.." },//l
//// { "--" },//m
//// { "-." },//n
//// { "---" },//o
//// { ".--." },//p  //15
//// { "--.-" },//q
//// { ".-." },//r
//// { "..." },//s
//// { "-" },//t
//// { "..-" },//u   //20
//// { "...-" },//v
//// { ".--" },//w
//// { "-..-" },//x
//// { "-.--" },//y
//// { "--.." },//z  //25
//// { "|" },// letter break  //26
//// { "/" },// word break    //27
//// { ".----" },//1  //28
//// { "..---" },//2
//// { "...--" },//3  //30
//// { "....-" },//4
//// { "....." },//5
//// { "-...." },//6
//// { "--..." },//7
//// { "---.." },//8  //35
//// { "----." },//9
//// { "-----" },//0  //37
//// };
//
// 
//
//void setup() {
//  // put your setup code here, to run once:
//pinMode(ledPin, OUTPUT);
//pinMode(beepPin, OUTPUT);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  curTime = millis();
//  //strcpy(textString, "TESTSTRINGHERE");
//textToMorse(textString);
//morseLed(morseBuild);
//morseBeep(morseBuild);
//}
//
//void textToMorse(char *textIn){
//  char readChar[1];
//  int lutVal = 0;
//  for (int i = 0; i < 128 ; i++){
//    readChar[0] = textIn[i];
//    if (readChar[0] != "\0" && readChar[0] != " "){
//      ////do something
//      lutVal = asciiConvert(readChar);
//      if (lutVal == 100){ //checks for invalid character entrys
//        break;
//      }
//      strcat(morseBuild, textLUT[lutVal]);
//      //ascii A-Z 65-90, | 124, / 47, a-z 97-122
//      strcat(morseBuild, textLUT[26]);
//    }else if(readChar[0] = " "){
//      strcat(morseBuild, textLUT[27]);
//    }else{
//      break; //handle end of string
//    }
//    
//  }
//}
//int asciiConvert (char asciiIn){
//  int ascii = int(asciiIn);
//  int adjVal = 0;//adjusted value
//  //A=65->0
//  if (ascii != 124 && ascii != 47){
//    if(ascii > 64 && ascii < 91){
//      adjVal = ascii - 65;
//    }else if (ascii > 96 && ascii < 123){
//      ascii -= 32;  //convert lowercase to uppercase
//      adjVal = ascii - 65;
//    }
//  }else if (ascii == 124){
//    adjVal = 26;
//  }else if (ascii == 47){
//    adjVal = 27;
//  }else{
//    return 100; //error return on invalid characters
//  }
//  return adjVal;
//}
//void morseLed (char *morseString){
//  char readChar[1];
//  for (int i = 0; i < 256 ; i++){
//    readChar[0] = morseString[i];
//    if (readChar[0] != "\0"){
//      if(readChar[0] == "."){
//        //blink 1 time unit
//        digitalWrite(ledPin, HIGH);
//        timerPause(1, 300);
//        digitalWrite(ledPin, LOW);
//      }else if (readChar[0] == "-"){
//        //blink 3 time unit
//        digitalWrite(ledPin, HIGH);
//        timerPause(3, 300);
//        digitalWrite(ledPin, LOW);
//      }else if (readChar[0] == "|"){
//        //pause 3 time unit
//        timerPause(3, 300);
//      }else if (readChar[0] == "/"){
//        //pause 7 time unit
//        timerPause(7, 300);
//      }
//      //pause 1 time unit before next letter
//      timerPause(1, 300);
//    }else{
//      break; //handle end of string
//    }
//    
//  }
//}
//
//void morseBeep (char *morseString){
//  char readChar[1];
//  for (int i = 0; i < 256 ; i++){
//    readChar[0] = morseString[i];
//    if (readChar[0] != "\0"){
//      if(readChar[0] == "."){
//        //beep 1 time unit
//        tone(beepPin, 500);
//        timerPause(1, 300);
//        noTone(beepPin);
//      }else if (readChar[0] == "-"){
//        //beep 3 time unit
//        tone(beepPin, 500);
//        timerPause(3, 300);
//        noTone(beepPin);
//      }else if (readChar[0] == "|"){
//        //pause 3 time unit
//        timerPause(3, 300);
//      }else if (readChar[0] == "/"){
//        //pause 7 time unit
//        timerPause(7, 300);
//      }
//      //pause 1 time unit before next letter
//      timerPause(1, 300);
//    }else{
//      break; //handle end of string
//    }
//    
//  }
//}
//
//void timerPause (int unitsToPause, int timeScale){
//  //timeScale is how many milliseconds per unit
//  unsigned long unitfactor = (unsigned long)(unitsToPause * timeScale);
//    if(millis() >= curTime + unitfactor){
//        curTime += unitfactor;
//        return;
//    }
//}
