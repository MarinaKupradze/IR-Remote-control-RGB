#include <IRremote.hpp>

// IR receiver
const int irPin = 2;

// RGB LED pins (PWM)
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 6;

#define IR_RECEIVE_PIN irPin

// RGB brightness values: 0-255
int redVal = 0;
int greenVal = 0;
int blueVal = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);

  // Start IR receiver
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {

    // Print received IR command
    Serial.print("Command: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    // Preset colors
    if (IrReceiver.decodedIRData.command == 0x0C) {        // Red
      redVal = 255;
      greenVal = 0;
      blueVal = 0;
    }
    else if (IrReceiver.decodedIRData.command == 0x18) {   // Green
      redVal = 0;
      greenVal = 255;
      blueVal = 0;
    }
    else if (IrReceiver.decodedIRData.command == 0x5E) {   // Blue
      redVal = 0;
      greenVal = 0;
      blueVal = 255;
    }
    else if (IrReceiver.decodedIRData.command == 0x08) {   // Magenta
      redVal = 255;
      greenVal = 0;
      blueVal = 255;
    }
    else if (IrReceiver.decodedIRData.command == 0x1C) {   // Cyan
      redVal = 0;
      greenVal = 255;
      blueVal = 255;
    }
    else if (IrReceiver.decodedIRData.command == 0x5A) {   // Yellow
      redVal = 255;
      greenVal = 255;
      blueVal = 0;
    }
    else if (IrReceiver.decodedIRData.command == 0x16) {   // White
      redVal = 255;
      greenVal = 255;
      blueVal = 255;
    }

    // Red brightness
    else if (IrReceiver.decodedIRData.command == 0x45) {   // Red -
      redVal = max(redVal - 25, 0);
    }
    else if (IrReceiver.decodedIRData.command == 0x46) {   // Red +
      redVal = min(redVal + 25, 255);
    }

    // Blue brightness
    else if (IrReceiver.decodedIRData.command == 0x40) {   // Blue +
      blueVal = min(blueVal + 25, 255);
    }
    else if (IrReceiver.decodedIRData.command == 0x44) {   // Blue -
      blueVal = max(blueVal - 25, 0);
    }

    // Green brightness
    else if (IrReceiver.decodedIRData.command == 0x15) {   // Green +
      greenVal = min(greenVal + 25, 255);
    }
    else if (IrReceiver.decodedIRData.command == 0x07) {   // Green -
      greenVal = max(greenVal - 25, 0);
    }

    // Update LED brightness
    analogWrite(redPin, redVal);
    analogWrite(greenPin, greenVal);
    analogWrite(bluePin, blueVal);

    Serial.print("Red: ");
    Serial.println(redVal);

    Serial.print("Green: ");
    Serial.println(greenVal);

    Serial.print("Blue: ");
    Serial.println(blueVal);

    // Ready for the next IR command
    IrReceiver.resume();
  }
}
