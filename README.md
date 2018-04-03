<p align="center"><img src="https://upload.wikimedia.org/wikipedia/commons/7/7e/NodeMCU_DEVKIT_1.0.jpg"></p>
<hr>


# Arduino-save-data-to-mysql-sample
Connect your microcontroller to the internet by  ESP8266 WiFi Module, And save the data to database(mysql) 

# Intro 

The ESP8266 Wifi module is a complete Wi­Fi network where you can easily connect as a serving Wi- Fi adapter, wireless internet access interface to any microcontroller­ based design on its simple connectivity through Serial Communication or UART interface.

Adding this module to your Arduino UNO will open you to more and exciting projects.

While broadcasting data over a dedicated web page on your home network is useful for a home project,
fundamentals of an advanced project are to be able to store data you read from your connected sensors. 
This way you can monitor live data, but are also able to get historic information. 
It also allows you to capture data from multiple data input devices and display them when and how you want.
Even though this could also be done with a dedicated web page by adding a little more code to your Arduino,
it is easier to store it to a database and create a web page (or user interface) that reads data from the database.


# Description of project
Here i use 'NodeMCU esp8266' with a flow meter madule(Model: YF-S201) ,And send the sensor data to webserber and saved it.

At first, I get data from sensor(flow meter) and then do some work on it, then send request to the my server and save data
to database .

## You Need These


- **[Arduino bord with wifi shield](https://www.arduino.cc/)**
- **[Or esp8266 (or nodeMCU 12e)](https://en.wikipedia.org/wiki/NodeMCU)**
- **[C or C++ knowledge for arduino coding](https://www.tutorialspoint.com/cplusplus/index.htm)**
- **[PHP knowledge for server codes](http://www.php.net/)**
- **[Database knowledge for store data](https://www.mysql.com/)
- **[A little electronic tricks](https://circuits.io/lab/)


