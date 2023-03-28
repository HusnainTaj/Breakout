# Programming Fundamentals Project 
BREAKOUT Game 

## Running
- Create a new Empty C++ Project
- Add the `youregraphics.h` library to the Header Files
- Add `Source.cpp` to the Source Files
- Also copy the `bgsound.wav` and `hit.wav` files to the project directory for background music and hit sound
- Press F5 to build and run the game

## Controls
- Use W/S or Up/Down Arrow keys to traverse the menu
- Use A/D or Left/Right Arrow keys to move the Paddle
- Press Spacebar to Start
- Press `P` to Pause
- Press `R` to Resume
- Press `S` to Save



## Paddle
Player has 3 lives shown on the top right. If player misses the ball and it touches the bottom of the screen, player will lose a life.

## Bricks
There are 3 different types of bricks depending on thier health

- Green = 3 health
- Blue  = 2 health
- Red   = 1 health

## PowerUps
All the powerups last for 10 seconds. and no new powerup will be spawned during this period.
There is a 40% chance a power up will be dropped when you break a brick.

The game has following powerups:

- Elongate 	  = Increases size of the paddle.
- Shorten  	  = Decreases size of the paddle.
- Fireball  	= Increase Speed and size of the ball. Can one shot destroy any brick
- Projectile 	= Launchs a fast projectile from the paddle that destorys every brick in its path
- Life		    = Increase player lives by one. (max lives are capped at 3)

## Scoring
Score is displayed at the top left corner of the game screen.
Every Brick broken rewards 5 points, unless you break multiple bricks within 1 second then you get 5 bonus points (10 in total)

5 Highest scores are saved on the disk. Which are displayed in the main menu.

## Scoring
![Main Menu](https://github.com/HusnainTaj/PFProject/blob/master/imgs/1.png?raw=true)

![Game](https://github.com/HusnainTaj/PFProject/blob/master/imgs/2.png?raw=true)

![Lose Screen](https://github.com/HusnainTaj/PFProject/blob/master/imgs/3.png?raw=true)

![Win Screen](https://github.com/HusnainTaj/PFProject/blob/master/imgs/4.png?raw=true)
