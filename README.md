# Labyrinth-Sammler (Microcontroller Game)

A simple maze-collection game developed as a school GFS project.  
The game runs on a microcontroller and uses external hardware buttons to move the player inside a 10×10 labyrinth.  
The goal is to collect a predefined amount of coins while avoiding walls.  
Includes win-state LED animation and real-time map rendering via serial output.

---

## Features

- 10×10 maze with walls and open paths  
- Player movement using four hardware buttons (up, down, left, right)  
- Randomized coin spawning on valid cells  
- LED display showing collected coins  
- Win-state animation with multiple LED patterns  
- Clean separation of game logic, rendering, and hardware control  

---

## Technical Overview

- Written in C for an AVR microcontroller  
- Direct port manipulation (`PORTB`, `PINE`, `PINK`)  
- Serial output used for drawing the game map  
- LED bar controlled via bitmasks  
- Debounced hardware button input  
- Fixed update intervals for rendering and movement  

---

## Project Structure

- `main.c` — full game logic, rendering, input handling, and LED animations  
- Game map stored as a 2D char array  
- Movement and collision with walls  
- Randomized money placement  
- LED animations implemented with shifting bitmasks  

---

## Notes

The original hardware setup (buttons + LED bar + microcontroller board) is no longer available,  
so the project is preserved here for reference, learning, and demonstration of embedded C programming.
