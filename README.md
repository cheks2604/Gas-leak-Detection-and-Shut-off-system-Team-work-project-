# Gas-leak-Detection-and-Shut-off-system-Team-work-project-\
## Overview
A team project to develop a gas safety system that detects leaks and automatically shuts off gas supply. The system uses Arduino, a gas sensor, and a solenoid valve to ensure safety in hazardous environments.

## Features
- **Gas detection sensor** triggers alerts  
- Red LED warning indicator for leaks  
- Wireless transmission of leak alerts to secondary Arduino  
- **Solenoid valve control** to close pipeline automatically  
- Collaborative team project (4 members)  

## Technologies Used
- Arduino Uno  
- C++  
- Gas sensor module  
- Solenoid valve  
- Wireless communication modules
- Piezoelectric speaker
## Note
The code is divided into two parts as a transmitter module and receiver module cannot be on the same arduino board and thus should be separated into two, one board for the gas sensor and transmitter module and one for the receiver module and solenoid valve
## How It Works
The primary Arduino reads data from the gas sensor. On detection of a leak, it activates an LED warning and sends a wireless signal to a receiver Arduino. The receiver controls a solenoid valve to shut off the gas pipeline.
The primary Arduino reads data from the gas sensor. On detection of a leak, it activates an LED warning and sends a wireless signal to a receiver Arduino. The receiver controls a solenoid valve to shut off the gas pipeline.
## Future Improvements
- Add GSM module for SMS alerts  
- Integrate IoT dashboard for remote monitoring
<img width="395" height="578" alt="image" src="https://github.com/user-attachments/assets/5fb9bdf8-f648-450c-b112-35c2d603e542" />

<img width="368" height="296" alt="image" src="https://github.com/user-attachments/assets/776dd30c-3b35-4b22-9909-89a01c762520" />

<img width="975" height="729" alt="image" src="https://github.com/user-attachments/assets/72ea2769-2720-4572-9187-6bf81e4d59f7" />
