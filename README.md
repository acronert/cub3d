# cub3D

A simplified 3D game engine built using **C** and **MiniLibX**, inspired by **Wolfenstein 3D**.  
This project is part of the 42 curriculum and introduces basic concepts in **raycasting**, **graphics rendering**, and **event-driven programming**.

---

## 🎮 Overview

`cub3D` is a mini raycasting engine that renders a 3D scene from a 2D map using player perspective, simulating depth and motion similar to early FPS games.

Key features include:

- Player movement with collision
- Wall rendering using raycasting
- Texture-mapped walls
- Window display
- Mouse/keyboard controls
- Map parsing from `.cub` file
- Flashlight and map consuming battery
- Collectible batteries
- Enemy entity roaming in the map, following the player if in sight
- If the player is out of battery, the entity automatically closes in on its location

---

## 📷 Demo

![cub3D Demo](cub3d_demo.gif)  
*Basic movement and rendering in a textured environment*

---

## 📦 Requirements

- Linux (with X11)
- `make`

---

## ⚙️ Building

```bash
make
