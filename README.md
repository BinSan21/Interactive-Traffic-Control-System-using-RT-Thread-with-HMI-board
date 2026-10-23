# Interactive HMI Traffic Control System

The Interactive HMI Traffic Control System is an embedded simulation designed to replicate real-world intersection logic using the Renesas HMI Board. 

This project is based on the RT-Thread Real-Time Operating System (RTOS) and showcases how contemporary embedded systems can manage both graphical user interfaces (GUI) and accurate timing logic at the same time. In contrast to basic sequential loops, this system employs multi-threading to keep the interface responsive to user interactions, such as requests for pedestrian crossings, even while the traffic timer is running.

## Hardware & Software Stack
* **Hardware:** Renesas HMI-Board (RA6M3)
* **Operating System:** RT-Thread IoT OS
* **Development Environment:** RT-Thread Studio
* **Graphics Library:** LVGL v8.3

---

## Prerequisites
This project requires the following packages to be installed in your RT-Thread Studio. Everything shown in the images below must be installed to ensure the creation of this project goes smoothly.

<img width="989" height="714" alt="image" src="https://github.com/user-attachments/assets/504be9c2-20e4-48d4-a2bb-ae3564e89613" />

<img width="991" height="709" alt="image" src="https://github.com/user-attachments/assets/e3311833-481b-4db4-8c23-63b262163da0" />

<img width="740" height="538" alt="image" src="https://github.com/user-attachments/assets/79a60436-bb3d-4b87-b4a5-3f09f730254a" />

---

## How It Works

The system utilizes the RT-Thread operating system to manage two primary threads running in parallel:
1. **The GUI Thread:** Handles the LVGL rendering, touch inputs, screen transitions (Welcome -> Simulation -> Credits), and dynamic text updates.
2. **The Logic Thread:** Manages the traffic timing (Red/Amber/Green) and listens for event flags.

### The "Interrupt" Logic
A key feature of this project is the **Pedestrian Priority System**. When the "Rush Red Light" button is pressed, an Event Flag is sent from the GUI thread to the Logic thread. This immediately interrupts the sleep timer and triggers a state change, simulating how modern smart traffic lights react to road demand.

### State Management
The system follows a strict Finite State Machine (FSM) to ensure safety and logic flow:

* **Welcome Screen:** Displays custom assets (CCS Logo) and navigation.
<br>
<img width="740" height="555" alt="image" src="https://github.com/user-attachments/assets/ccad2932-8287-457a-8d35-378b41363b70" />

* **Simulation Screen:** Runs the active traffic logic.
<br>
<img width="740" height="555" alt="image" src="https://github.com/user-attachments/assets/13f4aa5e-0d88-4ed7-b28d-866c78f0b7a7" />

### Hardware Setup
The software is deployed to the hardware by connecting the HMI board directly to the workstation via a USB-C interface, which facilitates both power delivery and real-time firmware flashing through the onboard debugger.

---

## Step-by-Step Instructions

*Make sure all the packages mentioned in the Prerequisites section are installed before starting.*

### 1. Create RT-Thread Project
<img width="740" height="371" alt="image" src="https://github.com/user-attachments/assets/e081cabc-a5d4-40f3-982e-65eaba74986e" />
<br>
<img width="441" height="555" alt="image" src="https://github.com/user-attachments/assets/dbd03667-c41b-4eb0-8655-c087b0cc3080" />

Follow the screenshots above and make sure everything matches. **"Base On Board"** must be selected, as it is critical for this project. Name the project however you want. After you are done, click finish, wait a bit until it finishes loading, and you will have successfully created an RT-Thread project.

### 2. Build and Flash to Check Setup (Optional)
Once it has finished creating, you should see the following workspace:

<img width="501" height="555" alt="image" src="https://github.com/user-attachments/assets/a6ba143b-cdfd-4799-a98d-84737f9b07b2" />

Click the **hammer icon** to build:

<img width="547" height="158" alt="image" src="https://github.com/user-attachments/assets/af049ccf-b18e-4b12-bb05-462f4ac4ac35" />

Once it finishes building, you should get a success message (ignore the 2 warnings):

<img width="645" height="308" alt="image" src="https://github.com/user-attachments/assets/6b405cfc-adf5-4f75-aa07-d248ef78d303" />

Connect your laptop and HMI board via the USB-C cable and click the **flash button** to upload the default RT-Thread demo code to your board:

<img width="732" height="179" alt="image" src="https://github.com/user-attachments/assets/14fdfbc6-8569-49c7-9660-efe04efa72ea" />

Once it has finished uploading, you should see an LVGL demo music player on your HMI board:

<img width="416" height="555" alt="image" src="https://github.com/user-attachments/assets/e10bfb05-5c98-49a8-851b-d1f5fce35602" />

If successful, there is no issue with your setup! If not, verify that you have installed the packages shown previously in the SDK manager.

### 3. Creating the Source File
In the project explorer on the left, find the `src` folder. Right-click it -> **New** -> **Source File**.

<img width="451" height="555" alt="image" src="https://github.com/user-attachments/assets/a6d8eb48-5159-4d40-99b1-e1bd6d9f5493" />

Name it `trafficlight.c`:

<img width="686" height="466" alt="image" src="https://github.com/user-attachments/assets/f9c4b1fe-a4db-4e07-821d-4a7896b59695" />

Click finish and it should show up inside the `src` folder:

<img width="681" height="555" alt="image" src="https://github.com/user-attachments/assets/e6209e4e-e78e-4f0c-b6e9-1918a50215cb" />

**Important Note:** Before you start coding in your C file, make sure to disconnect the default LVGL demo music player code. To do that, open `hal_entry.c` or `lv_demo.c` and do the following:

<img width="249" height="118" alt="image" src="https://github.com/user-attachments/assets/5042cda4-d43e-4e49-994b-495b468a81de" />
<br>
<img width="740" height="162" alt="image" src="https://github.com/user-attachments/assets/ca068815-2a70-4615-8ef6-ee05deb6fff4" />

At line 21, put a `//` before `lv_demo_music();`. Once you have done that, RT-Thread will automatically use your new C file as the main execution point.

### 4. Adding Images
<img width="604" height="555" alt="image" src="https://github.com/user-attachments/assets/7904e25d-2df6-49ae-8a6b-5519b3de2a2f" />

Adding custom images is important for designing your HMI background and assets. 
1. Resize your image width to be between **150-200 pixels** (e.g., using a tool like imageresizer.com).
2. Convert it into a C file using the [LVGL Image Converter](https://lvgl.io/tools/imageconverter). 

Follow the format below:

<img width="647" height="555" alt="image" src="https://github.com/user-attachments/assets/f519fda4-b684-427e-8daa-e9231c48ba10" />

After converting, copy the resulting C file and paste it inside your `src` folder.

<img width="219" height="101" alt="image" src="https://github.com/user-attachments/assets/3008d69c-2e41-4776-ab2d-0a11225d01a9" />

*Note: For this project, two additional developer profile images were also added to the source folder.*
<img width="236" height="142" alt="image" src="https://github.com/user-attachments/assets/d09f455d-41d3-469e-9a74-45849dfad202" />

### 5. Adding the Code
Open `trafficlight.c` and paste the main project code into it.

<img width="223" height="153" alt="image" src="https://github.com/user-attachments/assets/a0ba43e9-d616-46e9-b3ba-5fdbb173c8f7" />
<br>
<img width="740" height="533" alt="image" src="https://github.com/user-attachments/assets/25902a61-de95-4678-8cb1-89c1f5de2c5c" />

After pasting the code, build (Hammer) and flash (Play Button) the project to your board just like in Step 2.

### Final Output
You should get the following Welcome Screen output on your HMI:

<img width="740" height="555" alt="image" src="https://github.com/user-attachments/assets/ce98d4c1-a0c0-4439-b85a-53a4027aad96" />

* The **"Dev"** button on the top left takes you to the Credit Screen.
* The **"START SIMULATION"** button takes you to the Simulation Screen.

<img width="740" height="555" alt="image" src="https://github.com/user-attachments/assets/7cd5c2ea-0073-46ba-a27c-dc5a21cdbed8" />

This is the simulation screen. It simulates how real-life traffic lights operate. The **"RUSH RED LIGHT"** button only works during a red light phase, quickening the timer for waiting pedestrians so they can quickly cross.

<img width="272" height="555" alt="image" src="https://github.com/user-attachments/assets/c6b9946b-b3bc-414b-a807-1f21ebe99dbd" />

The Credit Screen showcases the developers of this project.

**Congratulations! You have successfully created your own traffic light simulation.**

---

## Conclusion
The Interactive HMI Traffic Control System successfully demonstrates the power of combining the Renesas HMI-Board with the RT-Thread Operating System.

By transitioning from basic "super-loops" to implementing RTOS multi-threading, we developed a system that allows the user interface to stay smooth and responsive (processing touch interrupts immediately) while maintaining the accuracy of the traffic signal timing. This project establishes a solid basis for grasping the architecture of contemporary appliance displays and industrial control panels.

## Future Improvements
* **Physical GPIO Integration:** Connecting real LEDs to the board's extension pins so the physical lights blink in sync with the screen.
* **Night Mode:** Using the board's light sensor to automatically dim the screen brightness when the room gets dark.
* **Network Control:** Using the board's Wi-Fi module to control the traffic light remotely from a web browser.



Project Developer :
Binyusoph Sansarona
Ken Jhim Villanueva
