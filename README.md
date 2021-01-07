# Audio Connection Visualizer
---
## About
#### General
Audio connection graph is a fun visualization that can be paired with music or without. The basic functionality
of the app includes generating random nodes that float through space. These nodes make connections with their
nearest neighbors and you too can create connections with other nodes through mouse inputs.

#### Using Music
The app is designed to be used with music but will function (just display a non-musically dynamic graph)
without music provided by the user. Upon starting up the application, you will be prompted for a file input of 
which you can choose any .mp3 or .wav file. Immediately the music will start. Node connection strength is
scaled based on the RMS (root mean squared) volume of the music.

#### User Controls - Color Picking
The app has some user input controls. Outside of mouse inputs for generating new connections, there are two
color pickers displayed on the screen for changing the colors of the display. The upper color picker will
allow you to change the overall background color while the color picker below will allow you to change the 
node and connection color.

---
## Demo
![photo](gifs/demo.gif)

---
## Set-Up
#### Cinder
This project was developed through c++'s Cinder platform. It was written using the latest version
of cinder found [here](https://github.com/cinder/Cinder). 

#### Quick Start
After downloading Cinder, clone the repo in a folder inside Cinder. Build project, 
run, choose music (or not), and enjoy!
