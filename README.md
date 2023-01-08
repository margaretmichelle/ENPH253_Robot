# Randall - A Fully Autonomous Treasure Seeking Robot - 

## The Competition :game_die:	
The **2022 ENPH 253 robotics competition** was designed to be the **most difficult** competition run over the 22-years the course has been established.  

Particularly, the **fully autonomous robots** were tasked to pick up and hold treasures, detect and avoid picking up magnetic bombs that looked exactly like treasures, overcome a chicken wire gap obstacle, follow black tape up a vertical 6-7” ramp, climb and descend onto a zipline, differentiate between a 1kHz and 10 kHz infrared beacon**, and be able to travel across a suspension bridge without the aid of black tape and signal processing. 

The following images illustrate the 3D layout of the competition surface as well as a diagram and legend of the surface details that helped the team to brainstorm strategies and specific functions required for Randall the Robot.

![image](https://user-images.githubusercontent.com/68613171/211223301-05f6ff98-2417-4f58-953b-05c52193fdb2.png)

**Figure 1:** _In depth illustration of the competition surface obstacles and treasures_

![image](https://user-images.githubusercontent.com/68613171/211223319-c9eca6b5-241b-49a8-a14e-0a2748117954.png)

**Figure 2:** _Illustration of the surface competition layout_

## Software Components :computer:	⌨️

## Abstraction & Code Structure 
Due to the extensive list of writing code for many functionalities of various complexities such as writing PID control algorithms, interrupt handling, claw mechanisms,  communicating between the two STM32 blue pill boards, each component was divided into separate libraries.

Through abstracting each component and function into modular libraries, this allows a better collaborative environment for the team while ensuring the software is clean, simple, easy-to-debug, bug-free, and elegant.

<img src = "https://user-images.githubusercontent.com/68613171/211224368-bd1b3522-ac0f-44d0-ba4b-c830fd7176af.png" width ="700" height="600">

**Figure 3:** _Project abstracted into separate libaries for different functional needs_


## User Interface :tv:	

*add text and images 

## Communication

*add text and images 


## Navigation
### Tape Following 
*add text and images 


### Edge Detection

*add text and images 


### Encoders 

*add text and images 


## Servo Control

*add text and images 


## Sonar Object Detection 

*add text and images 













