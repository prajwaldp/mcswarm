# Investigation and Design of Swarm Intelligence Methodologies applying Machine Learning for Terrain Mapping

[Report](https://github.com/prajwaldp/mcswarm/blob/master/report.pdf)

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

### Software

#### Machine Learning

- [OpenAI](https://openai.com/)
- [Mountain Car Problem](https://en.wikipedia.org/wiki/Mountain_Car)
- Kernel Functions
- Using linear approximators to do nonlinear classification

#### Swarm simulation

- [ARGoS Simulator](http://www.argos-sim.info/index.php)
- [How it works](http://www.argos-sim.info/user_manual.php#_using_argos_basics)
