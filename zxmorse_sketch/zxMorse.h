/*
 * zxMorse.h - morse code interpreting library
 * by zxsq, 2020
 */


#ifndef zxMorse_h

//  The #define statement defines this file as the myFirstLibrary
//  Header File so that it can be included within the source file.                                           
#define zxMorse_h

#include "Arduino.h"

//  The class is where all the functions for the library are stored,
//  along with all the variables required to make it operate
class zxMorse{

  //  'public:' and 'private:' refer to the security of the functions
  //  and variables listed in that set. Contents that are public can be 
  //  accessed from a sketch for use, however private contents can only be
  //  accessed from within the class itself.
  public:
  
    //  The first item in the class is known as the constructor. It shares the
    //  same name as the class and is used to create an instance of the class.
    //  It has no return type and is only used once per instance. 
    zxMorse(unsigned long curTime, int ledPin, int beepPin, char textString, char morseBuild);
    
    //  Below are the functions of the class. They are the functions available
    //  in the library for a user to call.    
    void textToMorse(char *textIn);              
    void morseLed(char *morseString);
    void morseBeep(char *morseString);
    void timerPause (int unitsToPause, int timeScale);

    static int NUMBER_OF_ELEMENTS;
    static int MAX_SIZE;
    static char textLUT;

  private:                  
    
    //  When dealing with private variables, it is common convention to place
    //  an underscore before the variable name to let a user know the variable
    //  is private.   
    //unsigned long _curTime;

    
};

//  The end wrapping of the #ifndef Include Guard
#endif
