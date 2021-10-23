# M5Interface
An interface for viewing the weather and other things on an M5Paper.

[![Build](https://github.com/WilcoMatthijssen/M5Interface/actions/workflows/platformio_run.yml/badge.svg)](https://github.com/WilcoMatthijssen/M5Interface/actions/workflows/platformio_run.yml)


![M5paper](https://camo.githubusercontent.com/82a324b30fa7188c14fa16ba0092fc4f683dc2c90fea1d7a859720e70226e9b6/68747470733a2f2f6d35737461636b2e6f73732d636e2d7368656e7a68656e2e616c6979756e63732e636f6d2f696d6167652f70726f647563745f6a70672f6173736574732f696d672f70726f647563745f706963732f636f72652f6d3570617065722f6d3570617065725f30312e6a7067)


## Intended features
### Date and time
The device contains an RTC which allows it to keep time. This can be used to get the time and display it on the epaper display. To sync the time I am intending to use an NTP server which can be contacted using the WiFi feature from the ESP32.

### Battery level
To keep the device working whilst not being connected with a usb cable it has a battery. But that battery does get empty at some point. To keep track of the status of the battery it is gonna get a display of its voltage converted to a percentage.

### Weather
The main feature I started this project for is a way to display the weather for the day. This I am intending to achieve by contacting an online weather API to retrieve weather info from an displaying it.

### Room temperature
The M5Paper contains a temperature sensor. I want to use this to display the temperature in the room it is in. It could be that the heat that the microcontroller generates interferes to much to get a representative number. This is yet to be determined.

### Game of life
To have some fun I want it to be able to display the game of life.

### Power efficiency
A big aspect of why I chose the M5paper is because of it's epaper display which is able to retain it's image when not being powered. I want to use this feature to extend the time between charges to the maximum.