The Interactive HMI Traffic Control System is an embedded simulation designed to replicate real-world intersection logic using the Renesas HMI Board.This project is based on the RT-Thread Real-Time Operating System (RTOS) and showcases how contemporary embedded systems can manage both graphical user interfaces (GUI) and accurate timing logic at the same time. In contrast to basic sequential loops, this system employs multi-threading to keep the interface responsive to user interactions, such as requests for pedestrian crossings, even while the traffic timer is running.

Hardware & Software Stack:- Hardware: Renesas HMI-Board(RA6M3)- Operating System: RT-Thread IoT OS- Development Environment: RT-Thread Studio- Graphics Library: LVGL v8.3

How it works:
This projects requires the following to be installed in your RT-Thread Studio

Scroll down

Scroll down again

Everything that is installed in the images above must be installed in order to make sure the creation of this project is smooth

The system utilizes the RT-Thread operating system to manage two primary threads running in parallel:1. The GUI Thread: Handles the LVGL rendering, touch inputs, screen transitions (Welcome -> Simulation -> Credits), and dynamic text updates.2. The Logic Thread: Manages the traffic timing (Red/Amber/Green) and listens for event flags.

The "Interrupt" Logic - A key feature of this project is the Pedestrian Priority System. When the "Rush Red Light" button is pressed, an Event Flag is sent from the GUI thread to the Logic thread. This immediately interrupts the sleep timer and triggers a state change, simulating how modern smart traffic lights react to road demand.

State Management
The system follows a strict Finite State Machine (FSM) to ensure safety and logic flow:

Welcome Screen: Displays custom assets (CCS Logo) and navigation.

Simulation Screen: Runs the active traffic logic.

Hardware Setup: The software is deployed to the hardware by connecting the HMI board directly to the workstation via a USB-C interface, which facilitates both power delivery and real-time firmware flashing through the onboard debugger.

Step-by-step Instructions:
Make sure all the packages mentioned before are installed before making this project

1. Create RT-Thread Project

Follow the screenshots above make sure everything is the same, especially the "Base On Board" part which critical for this project, name the project however you want. After you're done click finish, wait a bit till it finishes loading, and you have successfully created an RT-Thread project.

2. Build and Flash to check if no issue with RT-Thread(can skip this)Once it finished creating you should see the following:

click the hammer icon to build

once it finishes building you should get this

ignore the 2 warnings, connect your laptop and HMI board via USB- C cable and click the flash button to upload the default code RT-Thread puts as a demo for testing into your HMI board

once it finished uploading you should get an LVGL demo music player shown in your HMI board

if successful then there is no issue with your setup, if not then, again, make sure you have installed the packages shown before in the SDK manager

3. Creating source file

In the project explorer on the left, find the src folder, right click -> New -> Source FIle

name it trafficlight.c

click finish and it should show up inside the src folder

It's important to note that before you start coding in your c fille make sure to remove the connection of the LVGL demo music player code to the system. In order to do that do the following:

at line 21, put a // before lv_demo_music();once you have done that, RT-Thread should automatically use your c file as the main c file.4. Adding images

Adding images to RT-Thread is important if you want to design your HMI, like adding backgrounds and such. First you must resize the image you want, resize its width within 150-200 by pixels. In my case, I used imageresizer.com to resize my images.

Like so, make sure you change the width within 150-200. Once you have resized your image, you must now convert it into a c file, use https://lvgl.io/tools/imageconverter to convert your image to a file.

Follow the formats below:

after you're done, copy the converted file and paste it inside the src folder, right click src folder to paste

in my case I added another two images which I use to show image of the developers of the project.

5. Adding the code Go to trafficlight.c and paste the code I uploaded below in the attachments

After you finish pasting the code into the trafficlight.c file, you may build and flash, just like what you did in step 2.

You should get the following output in your HMI:

"Dev" button on the top left takes you to the Credit Screen while the "Start Simulation" button takes you to the Simulation Screen

This is the simulation screen, it simulates how real life traffic light works, the "Rush Red Light" only works during red light, it quickens the red light timer for pedestrians waiting even though nothing is passing by to quickly cross.

The Credit Screen shows the developer of this project

Now there you have it, you should have successfully created your own traffic light simulation by following this instructions.

Conclusion
The Interactive HMI Traffic Control System successfully demonstrates the power of combining the Renesas HMI-Board with the RT-Thread Operating System.

By transitioning from basic "super-loops" to implementing RTOS multi-threading, we developed a system that allows the user interface to stay smooth and responsive (processing touch interrupts immediately) while maintaining the accuracy of the traffic signal timing. This project establishes a solid basis for grasping the architecture of contemporary appliance displays and industrial control panels.

Future Improvements:
- Physical GPIO Integration: Connecting real LEDs to the board's extension pins so the physical lights blink in sync with the screen.
- Night Mode: Using the board's light sensor to automatically dim the screen brightness when the room gets dark.
- Network Control: Using the board's Wi-Fi module to control the traffic light remotely from a web browser.
