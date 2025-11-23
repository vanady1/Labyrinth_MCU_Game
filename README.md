Labyrinth_MCU_Game

Grid-based mini-game written in C for an AVR microcontroller (Arduino Mega2560–compatible).
The player moves through a maze, collects randomly spawning coins, and triggers LED animations after winning.

🎮 Gameplay Overview

Player moves in four directions using external hardware buttons

Walls block movement

Coins spawn at random valid positions

Collecting 8 coins triggers a win state

A set of LED animations plays when the game ends

The entire game runs on a microcontroller using direct register access.

🧩 Features

10×10 grid map

Manual rendering over serial terminal

Randomized item spawn

Hardware button input (4 directions)

LED animations using bit masks on PORTB

Debounce-safe button logic

Fully written in C without Arduino libraries

💡 Technical Notes

Uses DDRx, PORTx, PINx registers

Runs at high serial speed (500000 baud)

LED strip / 8-bit output driven through bit masks

Code is optimized for low-RAM environments
