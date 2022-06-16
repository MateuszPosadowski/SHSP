# SHSP
Smart Home System Project 

The project includes 3 devices: a relay driver, a thermometer and a humidity meter.

## Relay Driver

The driver code is in the ESP_Time.ino file. The controller 
switches the relay either manually or at a preset time.

### Connection to the network

On first run, the driver broadcasts its own network called "ESP_relay_driver", network password has been set as "password".
After connecting to the sensor network, go to "192.168.4.1", There will be a list of available Wi-Fi networks.
Choose your home network, enter a password and click "submit"
The network name and password will be saved in the device memory
Then you need to reset the device.
If the network name (ssid) and password have been saved correctly,
after re-joining the sensor network and going to the address
"192.168.4.1", you should see the home page of the device along
with the IP address where you can find it in your home network.

### Home page

On the main page you can see the current time, set the time of
switching on / off the relay, go to the settings and go to the
subpage that allows you to manually switch the relay

### Settings
Here you can set the switch-on / switch-off time for the relay and
choose which of the two available intervals is to apply (only the first, only the second, both or neither)

### Manual

Here you can turn on or off the relay yourself.


## Thermometer

A temperature measuring device that allows you to send a request under certain conditions

### Connection to the network

On first run, the driver broadcasts its own network called "ESP_temp_sensor", network password has been set as "password".
After connecting to the sensor network, go to "192.168.4.1", There will be a list of available Wi-Fi networks.
Choose your home network, enter a password and click "submit"
The network name and password will be saved in the device memory
Then you need to reset the device.
If the network name (ssid) and password have been saved correctly,
after re-joining the sensor network and going to the address
"192.168.4.1", you should see the home page of the device along
with the IP address where you can find it in your home network.

### Home page

On the main page you can see the current time, the current temperature and go to the settings 

### Settings

Here it is possible to set the condition and the request

Enter a condition whether the temperature value is to be lower (<), greater (>) or equal (=) to the set value. For example, "<25" will mean that the request will be sent when the read temperature exceeds 25 degrees.

Then enter the ip address and command. For example 192.168.1.44 /on

