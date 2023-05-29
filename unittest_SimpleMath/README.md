# IsoBoxFramework

Base project to realize a temperature controller on a generic device

Here comes from the following: 
Tools to be used – free choice. Requirement : ensure that the temperature in a room is always between a min and max adjustable temperature. 
When temp is too low, start heating, when temp is too high start cooling. 
How: 
1- create a component in cpp + api's 
2- create needed test-cases using google test (stub, mock,..) 
3- code must be build with cmake 
4- code is available in a git repo

Base component class under test is isolatedBoxCmake (.cpp, .h)
This component depends on a PidController class and an IsoActuator class that manages a PWM used by PID This classes are not fully implemented. They are only a skeleton of a supposed full temperature controller device

Project building by using Cmake File
IDE used Visual Studio 2019
... TO BE CONTINUED
