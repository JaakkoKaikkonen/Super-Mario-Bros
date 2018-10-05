#pragma once

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 928
#define WINDOW_TITLE "Super Mario Bros."

#define TILE_SIZE 64

#define PI 3.14159

#define TOP_ICON_FILEPATH "Resources/Images/icon.png"
#define MARIO_TEXTURES_FILEPATH "Resources/Images/mario.png"
#define BLOCK_TEXTURES_FILEPATH "Resources/Images/blocks.png"
#define TILE_TEXTURES_FILEPATH "Resources/Images/tileSet.png"
#define ITEM_TEXTURES_FILEPATH "Resources/Images/items.png"
#define CASTLE_TEXTURES_FILEPATH "Resources/Images/castle.png"

#define BACKGROUND_COLOR sf::Color(107, 140, 255)

#define POLE_TOP sf::IntRect(260, 136, 8, 8)
#define POLE sf::IntRect(263, 144, 2, 16)
#define POLE_FLAG sf::IntRect(128, 32, 16, 16)


#define PIPE_TOP sf::IntRect(0, 128, 32, 16)
#define PIPE_BOTTOM sf::IntRect(2, 144, 28, 16)

#define GROUND_TILE sf::IntRect(0, 0, 16, 16)

#define STAIR_TILE sf::IntRect(495, 0, 16, 16)

#define BRICK_PARTICLE_ANIMATION_TIME 0.2f
#define BRICK_TILE sf::IntRect(16, 0, 16, 16)
#define BRICK_PARTICLE1 sf::IntRect(451, 0, 8, 8)
#define BRICK_PARTICLE2 sf::IntRect(460, 0, 8, 8)

#define BOX_ANIMATION_TIME 0.7f
#define BOX_TILE1 sf::IntRect(384, 0, 16, 16)
#define BOX_TILE2 sf::IntRect(400, 0, 16, 16)
#define BOX_TILE3 sf::IntRect(416, 0, 16, 16)
#define BOX_TILE_OPENED sf::IntRect(432, 0, 16, 16)



#define CLOUD_TILE1 sf::IntRect(8, 320, 32, 24)
#define CLOUD_TILE2 sf::IntRect(248, 320, 48, 24)
#define CLOUD_TILE3 sf::IntRect(183, 320, 64, 24)

#define BUSH_TILE1 sf::IntRect(184, 144, 32, 16)
#define BUSH_TILE2 sf::IntRect(418, 144, 48, 16)
#define BUSH_TILE3 sf::IntRect(418, 128, 64, 16)

#define BUMP_TILE_SMALL sf::IntRect(418, 170, 48, 19)
#define BUMP_TILE_BIG sf::IntRect(417, 190, 80, 35)


#define COIN_ANIMATION_TIME 0.3f
#define COIN_ITEM1 sf::IntRect(4, 113, 8, 14)
#define COIN_ITEM2 sf::IntRect(20, 113, 8, 14)
#define COIN_ITEM3 sf::IntRect(36, 113, 8, 14)
#define COIN_ITEM4 sf::IntRect(52, 113, 8, 14)

#define MUSHROOM_ITEM sf::IntRect(0, 0, 16, 16)


enum Items { empty, coin, mushroom, fireSuit };


#define CAMERA_SPEED 300.0f

#define MARIO_SPEED_X 2500.0f

#define MARIO_RUN_ANIMATION_TIME 0.17f

#define SMALL_MARIO_IDLE_RIGHT sf::IntRect(80, 34, 16, 16)
#define SMALL_MARIO_IDLE_LEFT sf::IntRect(96, 34, -16, 16)

#define SMALL_MARIO_RUN_RIGHT_01 sf::IntRect(97, 34, 16, 16)
#define SMALL_MARIO_RUN_LEFT_01 sf::IntRect(113, 34, -16, 16)

#define SMALL_MARIO_RUN_RIGHT_02 sf::IntRect(114, 34, 16, 16)
#define SMALL_MARIO_RUN_LEFT_02 sf::IntRect(130, 34, -16, 16)

#define SMALL_MARIO_RUN_RIGHT_03 sf::IntRect(131, 34, 16, 16)
#define SMALL_MARIO_RUN_LEFT_03 sf::IntRect(147, 34, -16, 16)

#define SMALL_MARIO_TURN_RIGHT sf::IntRect(148, 34, 16, 16)
#define SMALL_MARIO_TURN_LEFT sf::IntRect(164, 34, -16, 16)

#define SMALL_MARIO_JUMP_RIGHT sf::IntRect(165, 34, 16, 16)
#define SMALL_MARIO_JUMP_LEFT sf::IntRect(181, 34, -16, 16)



#define BIG_MARIO_IDLE_RIGHT sf::IntRect(80, 1, 16, 32)
#define BIG_MARIO_IDLE_LEFT sf::IntRect(96, 1, -16, 32)

#define BIG_MARIO_RUN_RIGHT_01 sf::IntRect(97, 1, 16, 32)
#define BIG_MARIO_RUN_LEFT_01 sf::IntRect(113, 1, -16, 32)

#define BIG_MARIO_RUN_RIGHT_02 sf::IntRect(114, 1, 16, 32)
#define BIG_MARIO_RUN_LEFT_02 sf::IntRect(130, 1, -16, 32)

#define BIG_MARIO_RUN_RIGHT_03 sf::IntRect(131, 1, 16, 32)
#define BIG_MARIO_RUN_LEFT_03 sf::IntRect(147, 1, -16, 32)

#define BIG_MARIO_TURN_RIGHT sf::IntRect(148, 1, 16, 32)
#define BIG_MARIO_TURN_LEFT sf::IntRect(164, 1, -16, 32)

#define BIG_MARIO_JUMP_RIGHT sf::IntRect(165, 1, 16, 32)
#define BIG_MARIO_JUMP_LEFT sf::IntRect(181, 1, -16, 32)

#define BIG_MARIO_CROUCH_RIGHT sf::IntRect(182, 11, 16, 21)
#define BIG_MARIO_CROUCH_LEFT sf::IntRect(198 ,11, -16, 21)

#define POLE_CLIMBING_SPEED 240.0f

#define MARIO_CLIMB_POLE_ANIMATION_TIME 0.2f

#define BIG_MARIO_CLIMB_POLE1 sf::IntRect(199, 1, 16, 32)
#define BIG_MARIO_CLIMB_POLE2 sf::IntRect(216, 1, 16, 32)
#define BIG_MARIO_CLIMB_POLE_LEFT sf::IntRect(215, 1, -16, 32)

#define SMALL_MARIO_CLIMB_POLE1 sf::IntRect(201, 34, 13, 16)
#define SMALL_MARIO_CLIMB_POLE2 sf::IntRect(218, 34, 13, 16)
#define SMALL_MARIO_CLIMB_POLE_LEFT sf::IntRect(231, 34, -13, 16)


#define MARIO_GROWING_ANIMATION_TIME 0.7f 

#define SMALL_BIG_MARIO_RIGHT sf::IntRect(335, 1, 16, 32)
#define SMALL_BIG_MARIO_LEFT sf::IntRect(351, 1, -16, 32)

#define SMALL_CASTLE sf::IntRect(247, 863, 80, 80)
#define BIG_CASTLE sf::IntRect(79, 767, 148, 176)

#define CASTLE_FLAG sf::IntRect(129, 2, 13, 14)