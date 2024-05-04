# MSP432-Project-SC2107

### RSLK MAX Robotic Kit Application:
This application demonstrates various tests and functionalities for the RSLK MAX Robotic Kit using UART communication with the MSP432 processor.

### Usage:
Main usage of the microcontroller includes:
   - **Motor Test:** `BSC_MotorTest()`
   - **IR Sensor Test:** `BSC_IRTest()`
   - **Bumper Test:** `BSC_BumperTest()`
   - **Reflectance Sensor Test:** `BSC_ReflectanceTest()`
   - **Tachometer Test:** `BSC_TachometerTest()`
   - **Simultaneous Bump Test:** `ADV_BumpTest()`
   - **Line Following Test:** `ADV_LineFollowTest()`

Follow the on-screen instructions to execute the selected test function.
Utilize the UART communication to view the test results and monitor the system behavior.


### Hardware Overview:
The RSLK MAX Robotic Kit includes the following components:

- MSP432 Processor: Utilizes the ARM Cortex-M4F core for processing tasks.
- Reflectance Sensors: Used for line following applications.
- Bump Sensors: Detect collisions and provide feedback to the system.
- IR Sensors: Measure distances between the robot and obstacles.
- DC Motors: Drive the robot's movement.
- Hall-Effect Tachometer: Tracks the speed of the motors.

### Setup:
- **Hardware Requirements**:
  - Ensure you have an MSP432 microcontroller and the necessary peripherals, including motors, IR sensors, bumpers, reflectance sensors, and tachometers.

- **Project Configuration**:
  - Check that the project is properly configured within CCS. Adjust project settings such as compiler options, build configurations, and target device settings as needed for your specific project requirements.

- **Building the Project**:
  - Compile the code within CCS to generate the required binary files for the MSP432 microcontroller.

- **Debugging and Loading**:
  - Click the 'debug' icon in CCS after the project has been successfully built. This will initiate the debugging process and load the code onto the MSP432 microcontroller.

- **Debugging Tools**:
  - Utilize the debugging tools provided by CCS to troubleshoot any issues, verify code behavior, and ensure proper functionality of the firmware.

- **Programming the Microcontroller**:
  - After debugging, use the CCS interface to load the compiled binary file onto the MSP432 microcontroller. This will program the microcontroller with the developed firmware.

- **Running the Program**:
  - In the debug mode of CCS, clicking on the 'resume' icon will execute the program on the MSP432 microcontroller.

---
"I stand on shoulders of giants"
