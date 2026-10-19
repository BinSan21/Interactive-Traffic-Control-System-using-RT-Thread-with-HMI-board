The Interactive HMI Traffic Control System is an embedded simulation designed to replicate real-world intersection logic using the Renesas HMI Board.This project is based on the RT-Thread Real-Time Operating System (RTOS) and showcases how contemporary embedded systems can manage both graphical user interfaces (GUI) and accurate timing logic at the same time. In contrast to basic sequential loops, this system employs multi-threading to keep the interface responsive to user interactions, such as requests for pedestrian crossings, even while the traffic timer is running.

Hardware & Software Stack:- Hardware: Renesas HMI-Board(RA6M3)- Operating System: RT-Thread IoT OS- Development Environment: RT-Thread Studio- Graphics Library: LVGL v8.3

How it works:
This projects requires the following to be installed in your RT-Thread Studio
<img width="989" height="714" alt="image" src="https://github.com/user-attachments/assets/504be9c2-20e4-48d4-a2bb-ae3564e89613" />

Scroll down
<img width="991" height="709" alt="image" src="https://github.com/user-attachments/assets/e3311833-481b-4db4-8c23-63b262163da0" />

Scroll down again
<img width="740" height="538" alt="image" src="https://github.com/user-attachments/assets/79a60436-bb3d-4b87-b4a5-3f09f730254a" />

Everything that is installed in the images above must be installed in order to make sure the creation of this project is smooth

The system utilizes the RT-Thread operating system to manage two primary threads running in parallel:1. The GUI Thread: Handles the LVGL rendering, touch inputs, screen transitions (Welcome -> Simulation -> Credits), and dynamic text updates.2. The Logic Thread: Manages the traffic timing (Red/Amber/Green) and listens for event flags.

The "Interrupt" Logic - A key feature of this project is the Pedestrian Priority System. When the "Rush Red Light" button is pressed, an Event Flag is sent from the GUI thread to the Logic thread. This immediately interrupts the sleep timer and triggers a state change, simulating how modern smart traffic lights react to road demand.

State Management
The system follows a strict Finite State Machine (FSM) to ensure safety and logic flow:

Welcome Screen: Displays custom assets (CCS Logo) and navigation.
<img width="740" height="555" alt="image" src="https://github.com/user-attachments/assets/ccad2932-8287-457a-8d35-378b41363b70" />

Simulation Screen: Runs the active traffic logic.
<img width="740" height="555" alt="image" src="https://github.com/user-attachments/assets/13f4aa5e-0d88-4ed7-b28d-866c78f0b7a7" />

Hardware Setup: The software is deployed to the hardware by connecting the HMI board directly to the workstation via a USB-C interface, which facilitates both power delivery and real-time firmware flashing through the onboard debugger.

Step-by-step Instructions:
Make sure all the packages mentioned before are installed before making this project

1. Create RT-Thread Project
<img width="740" height="371" alt="image" src="https://github.com/user-attachments/assets/e081cabc-a5d4-40f3-982e-65eaba74986e" />
<img width="441" height="555" alt="image" src="https://github.com/user-attachments/assets/dbd03667-c41b-4eb0-8655-c087b0cc3080" />

Follow the screenshots above make sure everything is the same, especially the "Base On Board" part which critical for this project, name the project however you want. After you're done click finish, wait a bit till it finishes loading, and you have successfully created an RT-Thread project.

2. Build and Flash to check if no issue with RT-Thread(can skip this)Once it finished creating you should see the following:
<img width="501" height="555" alt="image" src="https://github.com/user-attachments/assets/a6ba143b-cdfd-4799-a98d-84737f9b07b2" />

click the hammer icon to build
<img width="547" height="158" alt="image" src="https://github.com/user-attachments/assets/af049ccf-b18e-4b12-bb05-462f4ac4ac35" />

once it finishes building you should get this
<img width="645" height="308" alt="image" src="https://github.com/user-attachments/assets/6b405cfc-adf5-4f75-aa07-d248ef78d303" />

ignore the 2 warnings, connect your laptop and HMI board via USB- C cable and click the flash button to upload the default code RT-Thread puts as a demo for testing into your HMI board
<img width="732" height="179" alt="image" src="https://github.com/user-attachments/assets/14fdfbc6-8569-49c7-9660-efe04efa72ea" />

once it finished uploading you should get an LVGL demo music player shown in your HMI board
<img width="416" height="555" alt="image" src="https://github.com/user-attachments/assets/e10bfb05-5c98-49a8-851b-d1f5fce35602" />

if successful then there is no issue with your setup, if not then, again, make sure you have installed the packages shown before in the SDK manager

3. Creating source file

In the project explorer on the left, find the src folder, right click -> New -> Source FIle
<img width="451" height="555" alt="image" src="https://github.com/user-attachments/assets/a6d8eb48-5159-4d40-99b1-e1bd6d9f5493" />

name it trafficlight.c
<img width="686" height="466" alt="image" src="https://github.com/user-attachments/assets/f9c4b1fe-a4db-4e07-821d-4a7896b59695" />

click finish and it should show up inside the src folder
<img width="681" height="555" alt="image" src="https://github.com/user-attachments/assets/e6209e4e-e78e-4f0c-b6e9-1918a50215cb" />

It's important to note that before you start coding in your c fille make sure to remove the connection of the LVGL demo music player code to the system. In order to do that do the following:
<img width="249" height="118" alt="image" src="https://github.com/user-attachments/assets/5042cda4-d43e-4e49-994b-495b468a81de" />
<img width="740" height="162" alt="image" src="https://github.com/user-attachments/assets/ca068815-2a70-4615-8ef6-ee05deb6fff4" />

at line 21, put a // before lv_demo_music();once you have done that, RT-Thread should automatically use your c file as the main c file.4. Adding images
<img width="604" height="555" alt="image" src="https://github.com/user-attachments/assets/7904e25d-2df6-49ae-8a6b-5519b3de2a2f" />

Adding images to RT-Thread is important if you want to design your HMI, like adding backgrounds and such. First you must resize the image you want, resize its width within 150-200 by pixels. In my case, I used imageresizer.com to resize my images.

Like so, make sure you change the width within 150-200. Once you have resized your image, you must now convert it into a c file, use https://lvgl.io/tools/imageconverter to convert your image to a file.

Follow the formats below:
<img width="647" height="555" alt="image" src="https://github.com/user-attachments/assets/f519fda4-b684-427e-8daa-e9231c48ba10" />

after you're done, copy the converted file and paste it inside the src folder, right click src folder to paste
<img width="219" height="101" alt="image" src="https://github.com/user-attachments/assets/3008d69c-2e41-4776-ab2d-0a11225d01a9" />

in my case I added another two images which I use to show image of the developers of the project.
  <img width="236" height="142" alt="image" src="https://github.com/user-attachments/assets/d09f455d-41d3-469e-9a74-45849dfad202" />

5. Adding the code Go to trafficlight.c and paste the code I uploaded below in the attachments
<img width="223" height="153" alt="image" src="https://github.com/user-attachments/assets/a0ba43e9-d616-46e9-b3ba-5fdbb173c8f7" />
<img width="740" height="533" alt="image" src="https://github.com/user-attachments/assets/25902a61-de95-4678-8cb1-89c1f5de2c5c" />

After you finish pasting the code into the trafficlight.c file, you may build and flash, just like what you did in step 2.

You should get the following output in your HMI:
<img width="740" height="555" alt="image" src="https://github.com/user-attachments/assets/ce98d4c1-a0c0-4439-b85a-53a4027aad96" />

"Dev" button on the top left takes you to the Credit Screen while the "Start Simulation" button takes you to the Simulation Screen
<img width="740" height="555" alt="image" src="https://github.com/user-attachments/assets/7cd5c2ea-0073-46ba-a27c-dc5a21cdbed8" />

This is the simulation screen, it simulates how real life traffic light works, the "Rush Red Light" only works during red light, it quickens the red light timer for pedestrians waiting even though nothing is passing by to quickly cross.
<img width="272" height="555" alt="image" src="https://github.com/user-attachments/assets/c6b9946b-b3bc-414b-a807-1f21ebe99dbd" />

The Credit Screen shows the developer of this project

Now there you have it, you should have successfully created your own traffic light simulation by following this instructions.

Conclusion
The Interactive HMI Traffic Control System successfully demonstrates the power of combining the Renesas HMI-Board with the RT-Thread Operating System.

By transitioning from basic "super-loops" to implementing RTOS multi-threading, we developed a system that allows the user interface to stay smooth and responsive (processing touch interrupts immediately) while maintaining the accuracy of the traffic signal timing. This project establishes a solid basis for grasping the architecture of contemporary appliance displays and industrial control panels.

Future Improvements:
- Physical GPIO Integration: Connecting real LEDs to the board's extension pins so the physical lights blink in sync with the screen.
- Night Mode: Using the board's light sensor to automatically dim the screen brightness when the room gets dark.
- Network Control: Using the board's Wi-Fi module to control the traffic light remotely from a web browser.
