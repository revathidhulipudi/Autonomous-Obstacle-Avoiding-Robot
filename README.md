# Autonomous Obstacle Avoiding Robot

An Arduino-based autonomous robotic car designed to detect obstacles and automatically change its direction to navigate through a given path.

## Overview

The robot uses an **Arduino UNO** as the main controller. An **ultrasonic sensor** detects obstacles in front of the robot, while **two IR sensors** detect obstacles on the left and right sides.

Based on the sensor inputs, the Arduino makes a real-time decision and controls two gear motors through an **L298N motor driver** to avoid obstacles and continue moving.

## Key Features

- Autonomous obstacle detection
- Real-time distance measurement
- Left and right side obstacle detection
- Automatic direction selection
- Two-wheel motor control
- Arduino-based embedded system
- Simple and low-cost robotic design

## Components

- Arduino UNO
- Ultrasonic Sensor
- 2 × IR Sensors
- L298N Motor Driver
- 2 × Gear Motors
- Car Chassis
- Li-ion Battery
- Jumper Wires

## Working
          Ultrasonic Sensor
                 │
                 ▼
        ┌─────────────────┐
        │   Arduino UNO   │
        │ Main Controller │
        └────────┬────────┘
                 │
        ┌────────┴────────┐
        │                 │
     IR Left           IR Right
        │                 │
        └────────┬────────┘
                 │
                 ▼
           ┌──────────┐
           │  L298N   │
           │   Motor  │
           │  Driver  │
           └────┬─────┘
                │
          ┌─────┴─────┐
          ▼           ▼
       Left Motor   Right Motor

The robot normally moves forward. When an obstacle is detected within the defined distance, it stops and checks the left and right sides using the IR sensors. It then selects a suitable direction, turns, and continues moving. It is all done in a fraction of seconds.



