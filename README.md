 Smart Traffic Light System with Dynamic Congestion Control 

This project is a prototype of an intelligent traffic light system built using Arduino. It dynamically adjusts the green light duration based on real-time vehicle density, helping to manage congestion more efficiently than traditional fixed-timer systems.

 Project Summary

The system uses ultrasonic sensors to detect the presence of vehicles in four lanes. By counting vehicles and identifying which lanes are most congested, it prioritizes those lanes by assigning them longer green-light durations. This not only reduces traffic delays but also improves road efficiency and fuel usage in urban areas.

 How It Works

- Sensors: Each lane has an ultrasonic sensor to detect vehicles within a certain distance.
- Detection: If a vehicle is within 50 cm, it's counted for that lane (without double-counting).
- Decision-making: At the end of every cycle (30 seconds), the code checks which lanes are most congested and gives them priority.
- Timing: The green time is dynamically calculated (base time + extra time per car), with a maximum cap.
- Lights: LEDs simulate the red, yellow, and green lights for each lane.
- Serial Monitor: Displays vehicle counts for observation and debugging.

 Key Features

- Real-time traffic detection using ultrasonic sensors.
- Dynamic green light duration based on vehicle counts.
- Smooth light transitions: green → yellow → red.
- Energy-saving mode when no vehicles are detected.
- Modular and scalable for different intersections.


Status

You can simulate this project using platforms like Wokwi
Developed as part of a coursework project focused on embedded systems and microcontroller applications. Ideal for students exploring smart cities, automation, or IoT-based traffic control.




