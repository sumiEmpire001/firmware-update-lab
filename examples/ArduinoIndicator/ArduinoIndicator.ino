#include "../../include/FirmwareUpdate.h"
// LED-only demonstration. No flash writes, OTA or bootloader activation.
firmware::Receiver receiver(1, 1024);
const int LED_PIN=LED_BUILTIN;
void setup(){pinMode(LED_PIN,OUTPUT);digitalWrite(LED_PIN,LOW);
 const uint8_t sample[]={1,2,3};
 receiver.begin({2,3,firmware::fnv1a(sample,3)});
 receiver.append(sample,3,0);
 if(receiver.finish())digitalWrite(LED_PIN,HIGH);
}
void loop(){}
