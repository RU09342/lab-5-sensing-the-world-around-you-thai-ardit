## Ardit Pranvoku and Thai Nghiem LCD display

### LCD Display on the MSP430FR6989

For this part of the lab, we used the 6989 because it is the only board with an LCD display. For the code, the LCDDriver.h and stdlib.h header files must be imported. 

Our LCD display takes the analog value that our photoresistor generates and converts it to a digital signal with a 12 bit ADC. This digital value is then output on the LCD display on the 6989.

In the main function, we use the showChar() method to output values on the LCD display. We initially put the character 0 on all 6 rows. 

```c
    showChar('0',0);
    showChar('0',1);
    showChar('0',2);
    showChar('0',3);
    showChar('0',4);
    showChar('0',5);
    showChar('0',6);
```


After, we initalize the 12 bit ADC. 
```c
  REFCTL0=REFON + REFVSEL_2;       //Sets reference voltage to 2.5V
  ADC12CTL0 = ADC12SHT0_2 | ADC12ON;   // Sampling rate, S&H=16, ADC12 on
  ADC12CTL1 = ADC12SHP;                // ADC12SC conversion start, clock=OSC
  ADC12CTL2 |= ADC12RES_2;             // Saves 12-bit conversion results
  ADC12MCTL0 |= ADC12INCH_3;           // input to the ADC
  ADC12IER0 |= ADC12IE0;               // Enables interrupt when ADC conversion completes.
  ADC12CTL0 |= ADC12ENC;               //Enable conversion
  P1SEL0 |=BIT3;                      //Configure pin 1.3 for input channel 3
  P1SEL1 |=BIT3;
```




The reference voltage is set to 2.5V. Whenever the ADC completes a conversion of an analog signal, it will save the digital value to ADC12MEM0 and generate an interrupt that outputs its converted digital sign to the LCD display. Vector 12 will activate the code that outputs to the LCD.

```c
switch(__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG))
    {
        case ADC12IV_NONE:        break;    // Vector  0:  No interrupt
        case ADC12IV_ADC12OVIFG:  break;    // Vector  2:  ADC12MEMx Overflow
        case ADC12IV_ADC12TOVIFG: break;    // Vector  4:  Conversion time overflow
        case ADC12IV_ADC12HIIFG:  break;    // Vector  6:  ADC12BHI
        case ADC12IV_ADC12LOIFG:  break;    // Vector  8:  ADC12BLO
        case ADC12IV_ADC12INIFG:  break;    // Vector 10:  ADC12BIN
        case ADC12IV_ADC12IFG0:             // Vector 12:  ADC12MEM0 Interrupt
```


Whenever the interrupt for the ADC is generated, ADC12MEM0 (12 bits) is saved to int adc_int. This value is saved to an array named adcArray by putting the one's place into the first index, the tenth place into the second, and the hundredth place into the third index. No more precision is used.

```c
int index = 0;
        do{
             adcArray[count]=(adc_int%10);
             adc_int/=10;
             count++;
       }while(adc_int>0);
```


Finally, the contents of adcArray are output to the LCD display using showChar().

```c
  showChar(toChar(adcArray[2]), 1);
  showChar(toChar(adcArray[1]), 2);
  showChar(toChar(adcArray[0]), 3);

```

The toChar method simply converts the value in adcArray to a char so it can be output to the LCD display.

### How to implement the code
Buid a photoresistor circuit follow the schematic provided below <br />
![photoresistor_schem](https://user-images.githubusercontent.com/30231031/32694162-bd1aedba-c706-11e7-89a6-ed677d297f9a.png)
<br />
The out put of the circuit should be connected to Pin 1.3 of the 6989. Run the code and the results below should be collected. 

### Results
When the Photoresistor is not covered: <br />
![img_1703](https://user-images.githubusercontent.com/30231031/32694179-527623ca-c707-11e7-8f25-d7939c13da5d.JPG)
<br />
When the Photoresistor is covered: <br />
![img_1709](https://user-images.githubusercontent.com/30231031/32694183-69b7857e-c707-11e7-816e-3a7ab8762314.JPG)