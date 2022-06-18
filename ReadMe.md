-------------To upload the code-------------------\n
Step 1: Download Ardunio ide by visiting "https://www.arduino.cc/en/software" and download Ardunio according to your oprating system.
Step 2: Install the Ardunio software.
Step 3: Open "AutoConnectNodeMCU.ino"
Step 4: Goto File>>Preferences. And Put "http://arduino.esp8266.com/stable/package_esp8266com_index.json" in Additional Boards Manager URLs
Step 5: Click ok.
Step 6:Goto Tools>>Boards>>Boards Manager. And type esp8266 and click on install after selecting version.
Step 7: Now, Again goto and select Tools>>Boards>>ESP8266 Boards>>NodeMCU 1.0(ESP-12E Module).
Step 8: Now, Connect NodeMCU with PC.
Step 9: Select the port number on Tools>>Port.
Step 10: Click on upload button.

------------To add WiFi SSID and Pass---------------
Step 1: Open "AutoConnectNodeMCU.ino"
Step 2: Change any of the ssid and password which you don't required (From 4 to 14 Line of code).
step 3: Save the file and upload the code.

-------------To change static IP Address------------
1. If you are using hotspot change IP Address to 192.168.43.xxx
2. If you are using WiFi/Router keep the same.
