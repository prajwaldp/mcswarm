# Investigation and Design of Swarm Intelligence Methodologies applying Machine Learning for Terrain Mapping

## Abstract

Our goal in this project is to build a system of robots that can autonomously
generate a map of an unknown location. We use three ground robots with movement
and obstacle avoiding capabilities.

We have used and tested various swarm dispersion and exploration algorithms,
both in simulations and in physical robots. These algorithms allow the robots to
use simple behaviours to efficiently cover a given environment.

Two types of terrain mapping, namely radar and computer vision systems were
evaluated.  We concluded that a computer vision system that performs visual SLAM
(Simultaneous Localization And Mapping) is preferable to a radar-based system.

We have also implemented a machine learning system that is capable of traversing
uneven terrain in simulation by solving the mountain car problem from OpenAI
gym.

## Implementation

### Hardware

The arduino code for the 3 robots are in the `arduino` folder.

- **robot_1**: The one with the Lead Acid Battery and motor shield
- **robot_2**: The one which is painted black
- **robot_3**: The tractor

### Software

#### Machine Learning

- [OpenAI](https://openai.com/)
- [Mountain Car Problem](https://en.wikipedia.org/wiki/Mountain_Car)
- Kernel Functions
- Using linear approximators to do nonlinear classification

#### Swarm simulation

- [ARGoS Simulator](http://www.argos-sim.info/index.php)
- [How it works](http://www.argos-sim.info/user_manual.php#_using_argos_basics)


## Things to remember for external viva day

### Hardware

- [ ] `robot_2` - fix those ultrasonic sensors to the base (don't make it ugly)
- [ ] Fix the delay in recognising obstacles in front

### Software

- [ ] Add kurento/flask app to this repository
- [ ] How do we reference ORB-SLAM

### Others

- [ ] Hall Tickets
- [ ] Project Reports

