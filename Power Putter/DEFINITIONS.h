#pragma once

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024

#define PI 3.14

// main menu screen
#define MAIN_MENU_BACKGROUND "texture/background.jpg"
#define PLAY_BUTTON "texture/play_button.png"

// ball class
#define BALL_FRAME_FILEPATH "texture/ball_up.png"
#define ROTATION_SPEED 100.0f
#define BALL_STATE_STILL 1
#define BALL_STATE_MOVING 2
#define BALL_STATE_STOPPED 3

// arrow class
#define ARROW_FILEPATH "texture/arrow.png"
#define ROTATING 1
#define NOT_ROTATING 2
#define SHOT 3

// power bar class
#define POWER_BAR_FRAME1 "texture/power_bar1.png"
#define POWER_BAR_FRAME2 "texture/power_bar2.png"
#define POWER_BAR_FRAME3 "texture/power_bar3.png"
#define POWER_BAR_FRAME4 "texture/power_bar4.png"
#define POWER_BAR_FRAME5 "texture/power_bar5.png"
#define POWER_BAR_FRAME6 "texture/power_bar6.png"
#define POWER_BAR_FRAME7 "texture/power_bar7.png"
#define POWER_BAR_FRAME8 "texture/power_bar8.png"
#define POWER_BAR_FRAME9 "texture/power_bar9.png"
#define POWER_BAR_FRAME10 "texture/power_bar10.png"

#define POWER_BAR_DURATION 1.0f

// target class
#define GOLD_TARGET "texture/gold.png"
#define SILVER_TARGET "texture/silver.png"
#define BRONZE_TARGET "texture/bronze.png"

// game over screen
#define GAME_OVER_TITLE "texture/game_over_title.png"

// square obstacle class
#define SQUARE_OBSTACLE "texture/square.png"

// fan class
#define FAN_1 "texture/fan_1.png"
#define FAN_2 "texture/fan_2.png"
#define FAN_3 "texture/fan_3.png"
#define FAN_4 "texture/fan_4.png"
#define FAN_SPIN_SPEED 0.4f
#define FAN_STRENGTH 446

// wind class
#define WIND_LOW "texture/wind_low.png"
#define WIND_HIGH "texture/wind_high.png"
#define WIND_SPEED 0.3f

// springboard
#define SPRINGBOARD_LOW "texture/springboard_low.png"
#define SPRINGBOARD_MED "texture/springboard_medium.png"
#define SPRINGBOARD_HIGH "texture/springboard_high.png"
#define SPRINGBOARD_COLLISION_LOW "texture/springboard_collisionLow.png"
#define SPRINGBOARD_COLLISION_MEDIUM "texture/springboard_collisionMedium.png"
// spring board springs every 3 seconds
#define SPRINGBOARD_MOVE 3.0f
#define SPRINGBOARD_ANIMATION 0.8f
// every 1/4 of a second the ball can be slowed down by a springboard
#define SPRINGBOARD_SLOWDOWN 0.25f

// door class
#define DOOR_CLOSED "texture/door_closed.png"
#define DOOR_OPENING "texture/door_opening.png"
#define DOOR_OPEN "texture/door_open.png"
#define RIGHT_OPEN_DOOR "texture/door_open_right.png"
#define LEFT_OPEN_DOOR "texture/door_open_left.png"
// door opens and closes every 4 seconds
#define DOOR_TIMER 4.0f
#define DOOR_ANIMATION 0.3f
