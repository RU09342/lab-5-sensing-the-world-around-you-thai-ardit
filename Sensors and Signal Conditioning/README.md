# Sensors and Signal Conditioning 
## Ardit Pranvoku and Thai

## Sensors' Measurements
Physical light-sensor circuits were built and measured, with results recorded in the table below:
![measurevaluesensor](https://user-images.githubusercontent.com/14367479/32997336-d1736894-cd5c-11e7-8f13-eccbdd7da703.png)

## How ADC was implement
When going from analog to digital, the divided voltage value must be multiplied by 2^n bits, where n is the size of the register for which the digital signal will be saved. Divided voltage simply means that if the analog input range is from 0 to 5v, and that if one wants to find the digital conversion of 2.5V, then the divided voltage will be 0.5, or 2.5V/5V.
If the size of the register for which we would like to save the analog value is 6 bits, then the  value that the divided voltage must be multiplied by is 2^6-1, or 63. If the resultant answer is a decimal, (such as in our example, 31.5) it must be truncated down to 31. Finally, this decimal number can be converted into binary, 0001 1111, and you have your digital value.  

## Photoresistor
We implemented the photoresistor by configuring it so that when under maximum lighting, the output of the photoresistor will be 3.3V. A photoresistor's resistance will decrease when it is exposed to more light, so if used in a voltage divider configuration, the voltage drop across the photoresistor will be relatively small at high light levels and relatively big at low light levels. A small voltage drop across the photoresistor will result in a high voltage at the output of the circuit. Because the MSP430 operates at a voltage of 3.3 Volts, we chose a resistor value of 5.5k Ohms that would divide the voltage coming off of the photoresistor at a maximum light setting to be no more than 3.3V. As we dimmed the lights, this output voltage would only decrease as the resistance of the photoresistor increased. 

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
Photodiodes work by converting ambient light into electrical current. This effect is called the photovoltaic effect. A major problem with photodiodes is that because they're essentially current generators, they have to rely entirely on ambient light to power a circuit. This produces an amperage on the order of nanoamps to a few microamps. Due to this, we built a circuit that amplified the current of our photodiode by 0.1V/1 uA generated, or essentially 100,000 using an op-amp. We were able to see a voltage difference of about half a millivolt from ambient room lighting to bright flashlight lighting, so we calculated that the current increase from these two conditions was 5 nA using the photodiode. 
(0.5mV)*(10nA/mV).

When we hooked the photodiode up to an op-amp configured as a buffer without any gain, the voltage difference was negligible, and could be attributed to measurement error.
<br />
### Breadboard
![pdiode](https://user-images.githubusercontent.com/14367479/32997322-95c9df4e-cd5c-11e7-9da0-24d3af855d79.jpg)


### Schematic
![photodiode_schem](https://user-images.githubusercontent.com/14367479/32997338-d4bba336-cd5c-11e7-816c-4d0a55e1f48e.png)

### Photodiode Serial
With light on: <br />
![diodeon](https://user-images.githubusercontent.com/30231031/32411770-0b758bde-c1ba-11e7-8856-08e2f500ab04.png)
<br />
With light off: <br />
![diodeoff](https://user-images.githubusercontent.com/30231031/32411735-3b7783c4-c1b9-11e7-9004-4703c728a6a9.png)
<br />
It's clear to see that the voltage rises (from CF to D3) as the light is turned off. Though it's not a big change but it confirms our measurements in the first table.

## Phototransistor
If the source of a phototransistor is left hanging, and the gate and drain are connected to a circuit, it will act exactly the same as the photodiode described above. The major difference we saw between the two was that the phototransistor was a much stronger photodiode than the original photodiode. Between ambient room lighting and flashlight lighting, we saw a voltage increase of about 270 mV. This is 540x stronger than the photodiode. Using our equation of .1V/uA, the current increase from dim to bright lighting was 2.7uA, much higher than the 0.5nA of the original photodiode.
### Breadboard
![ptransistor](https://user-images.githubusercontent.com/14367479/32997323-97d4295c-cd5c-11e7-9860-a2a475ad471a.jpg)

### Schematic
![phototransistor_schem](https://user-images.githubusercontent.com/14367479/32997337-d2ef3644-cd5c-11e7-9270-63708e190920.png)

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