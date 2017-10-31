## PCB Read me - Ardit Pranvoku and Thai Nghiem

### PCB Schematic

The PCB consists of an MSP430FR2311, two 8-pin headers, a bypass capacitor, a bulk capacitor, a capacitor used to stop debouncing, and a pull-up resistor.

The primary function of this PCB is to be a breakout board for the MSP430FR2311. It has some useful
features that help the MSP430 function. One of these is the bulk capacitor which will provide
emergency voltage to the MSP430 in case of a voltage dip from the power supply. The bypass filter will filter out AC noise by becoming a short to ground. 

This PCB also uses the reset header on the MSP430 by using a 47k Ohm pullup resistor, so that the MSP430 
reads a logical 1 when the reset button is turned off, and is reset when a button is pressed. 
A 1 nF cap is also used here to send any AC noise to ground.

Below is a bill of materials, as well as a link to a mouser cart for all the parts.


![bom](https://user-images.githubusercontent.com/14367479/32194650-5d6b3484-bd91-11e7-843d-a7de2c1c28c3.png)

### Material Cart (Mouser)

https://www.mouser.com/ProjectManager/ProjectDetail.aspx?AccessID=6f11333891



