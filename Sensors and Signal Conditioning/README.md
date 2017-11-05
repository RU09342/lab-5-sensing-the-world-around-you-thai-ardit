# Sensors and Signal Conditioning 
## Ardit Pranvoku and Thai

## Sensors' Measurements
Physical light-sensor circuits were built and measured, with results recorded in the table below:
![measurevaluesensor](https://user-images.githubusercontent.com/30231031/32411817-330231d8-c1bb-11e7-8b2d-5091f39aff3c.png)

## How ADC was implement
When going from analog to digital, the divided voltage value must be multiplied by 2^n bits, where n is the size of the register for which the digital signal will be saved. Divided voltage simply means that if the analog input range is from 0 to 5v, and that if one wants to find the digital conversion of 2.5V, then the divided voltage will be 0.5, or 2.5V/5V.
If the size of the register for which we would like to save the analog value is 6 bits, then the  value that the divided voltage must be multiplied by is 2^6-1, or 63. If the resultant answer is a decimal, (such as in our example, 31.5) it must be truncated down to 31. Finally, this decimal number can be converted into binary, 0001 1111, and you have your digital value.  

## Photoresistor
Tested using voltage divider. The max voltage of the photoresistor needed to be kept below the 3.3V range.
The correct resistor values were used to divide the voltage, so the output would stay below the range under any condition.

### Breadboard
![photoresistor](https://user-images.githubusercontent.com/30231031/32254022-a67b18f4-be74-11e7-8356-d9d35f2204d2.jpg)

### Schematic
![photoresistor_schem](https://user-images.githubusercontent.com/30231031/32254216-b76719dc-be75-11e7-8ed3-7f3e1b88f87c.png)

### Photoresistor Serial 
With light on: <br />
![resistoron](https://user-images.githubusercontent.com/30231031/32411738-42b32a08-c1b9-11e7-92bb-09c31271f055.png)
<br />
With light off:<br />
![resistoroff](https://user-images.githubusercontent.com/30231031/32411700-8c39cd04-c1b8-11e7-8477-36ca4148185c.png)
<br />
As it can be seen, the voltage output from the Photoresistor circuit drops (from ED to 15) as the light is turned off. 
This confirms with our measured values. 
The Photoresistor gives us the best readings out of the 3 light sensors.
## Photodiode
Photodiodes convert light(photons) into electrical current. Photodiodes can be used as sensors,  since the 
amount of current emitted varies depending on how much light the photodiode receives. A buffer circuit was built to test the 
photodiode and how it could be used to create a sensor for the lab. The buffer helps maintain the output voltage of the diode. 
### Breadboard
![photodiode](https://user-images.githubusercontent.com/30231031/32254052-d187fd50-be74-11e7-8acb-23b467f7013d.jpg)


### Schematic
![photodiode_schem](https://user-images.githubusercontent.com/30231031/32254217-b950eea8-be75-11e7-80d7-ca4648ef938c.png)

### Photodiode Serial
With light on: <br />
![diodeon](https://user-images.githubusercontent.com/30231031/32411770-0b758bde-c1ba-11e7-8856-08e2f500ab04.png)
<br />
With light off: <br />
![diodeoff](https://user-images.githubusercontent.com/30231031/32411735-3b7783c4-c1b9-11e7-9004-4703c728a6a9.png)
<br />
It's clearly to see that the voltage rises (from CF to D3) as the light is turned off. Though it's not a big change 
but it comfirms with our measurements in the first table.

## Phototransistor
A light sensitive transistor can be used to create a sensor as well. Only the gate and drain were connected
so that the transistor behaved as a diode.
### Breadboard
![phototransistor](https://user-images.githubusercontent.com/30231031/32254055-d3ccef6c-be74-11e7-9407-9838f6c70633.jpg)

### Schematic
![phototransistor_schem](https://user-images.githubusercontent.com/30231031/32254218-bbadad58-be75-11e7-9eed-a369d74b8bc1.png)

### Phototransistor Serial
With light on: <br />
![transistoron](https://user-images.githubusercontent.com/30231031/32411782-6d1f9000-c1ba-11e7-8f97-83799a8809f7.png)
<br />
With light off: <br />
![transistoroff](https://user-images.githubusercontent.com/30231031/32411783-6dc70ca4-c1ba-11e7-9337-fa504f26bd93.png)
<br />
The voltage again rises (from F9 to FE)as the light is turned off. Once again, the measured value is confirmed, though the difference is not clear. 

## How to implement the code
Run the code in CCS and import it into your MSP. Connect and power the sensor cicuit (the output of the circuit should go into P6.1). Open RealTerm and read the output values. 