WeatherStation Version 0.2

This project consists of a mostly functional weather station using a BME-280 sensor, ESP8266 module, web server, nucleo f091rc and a database. The goal of the project is to collect weather data such as temperature, humidity, and pressure from the sensor, send it to a database via the ESP8266, and display the data in an application.

New Features:

    Database: The database has been set up to store all the collected weather data from the ESP8266. It supports queries for historical weather dataa.

    Web Server: A web server has been implemented to be able to send data from the esp8266 to the database.

    ESP8266 Integration: The ESP8266 module communicates with the BME-280 sensor, via the nucleo f091rc, to collect weather data and sends this data to the database via Wi-Fi.
    The database, web server, and ESP8266 code have been successfully implemented and can now be used together. Simply connect the ESP8266 to the BME-280 sensor and the stm32, deploy the web server, and ensure the database is running. The weather data will flow from the ESP8266 to the database and be viewable on the web interface.
