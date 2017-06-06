# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Solution summary

My first attempt was to find the PID gains manually by observing car behavior while running simulator. As a result the steering PID coefficients found were: Kp=0.12, Ki=0.0001, Kd=4.2 for speeds up to 25 mph. A simple proportional gain controller was implemented to control the speed.

### PID tuning approach
The approach used for tuning was to first find a value of Kp that brings the car to the center-line letting it to oscillate. Then Kd was tuned to reduced oscillation and then Ki to reduce steady-state error.

### Choosing final hyper-parameters
A class implementing twiddling algorithm was used to automate the PID gains tuning. Because of some issues with reseting the simulation this was not pursued any further.
