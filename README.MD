# Smart CI/CD Deploy Button


Installation Instructions
--------------------------

1. Install the Arduino IDE
    Windows Only:
    Extract ardruino zip file. Copy the java folder location and set it as JAVA_HOME environment variable using following steps.

    * In Search, search for and then select: System (Control Panel)
    * Click the Advanced system settings link.
    * Click Environment Variables. ...
    * In the New System Variable window, specify the value of the JAVA_HOME environment variable.

2. Install the USB driver
    MacOS: 
    Goto: https://github.com/adrianmihalko/ch340g-ch34g-ch34x-mac-os-x-driver
    Follow Readme

    Windows:
    https://sparks.gogo.co.nz/ch340.html
    Download and install

3. Install ESP8266 Board

    Arduino: Tools -> Board -> Boards Manager
    Search and install esp8266

4. Install the following libraries in Arduino IDE:
    Sketch -> Include Libraries -> Manage Libraries
        ArduinoJson -> version 5.13.3
        PubSubClient -> version 2.4
        FastLed -> version 3.1.6

5. Tools -> Boards -> Nodemcu v1.0 (ESP-12E module)

6. Connect the nodemcu (esp8266 module)

7. Choose the correct port:
    OSX: Tools -> Port -> <slab_usb_uart>
    Windows: Tools -> Port -> <some com port - try one by one>

8. Write code / open existing ino file and Upload

9. Use [ Tool -> Serial monitor ] to connect to the serial console.
