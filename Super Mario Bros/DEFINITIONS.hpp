#pragma once
#include <SFML/Audio.hpp>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 928
#define WINDOW_TITLE "Super Mario Bros."

#define TILE_SIZE 64

#define PI 3.14159

#define FONT_FILE_PATH "Resources/Fonts/font.ttf"

#define TOP_ICON_FILEPATH "Resources/Images/icon.png"
#define MARIO_TEXTURES_FILEPATH "Resources/Images/mario.png"
#define BLOCK_TEXTURES_FILEPATH "Resources/Images/blocks.png"
#define TILE_TEXTURES_FILEPATH "Resources/Images/tileSet.png"
#define ITEM_TEXTURES_FILEPATH "Resources/Images/items.png"
#define CASTLE_TEXTURES_FILEPATH "Resources/Images/castle.png"
#define ENEMY_TEXTURES_FILEPATH "Resources/Images/enemies.png"
#define HUD_TECTURES_FILEPATH "Resources/Images/HUD.png"
#define MENU_BACKGROUND_FILEPATH "Resources/Images/menu.png"

#define JUMP_SMALL_SOUND_FILEPATH "Resources/Sounds/smb_jump-small.wav"
#define JUMP_BIG_SOUND_FILEPATH "Resources/Sounds/smb_jump-super.wav"
#define COIN_SOUND_FILEPATH "Resources/Sounds/smb_coin.wav"
#define POWERUP_APPEARS_SOUND_FILEPATH "Resources/Sounds/smb_powerup_appears.wav"
#define POWERUP_SOUND_FILEPATH "Resources/Sounds/smb_powerup.wav"
#define BREAK_BLOCK_SOUND_FILEPATH "Resources/Sounds/smb_breakblock.wav"
#define FIREBALL_SOUND_FILEPATH "Resources/Sounds/smb_fireball.wav"
#define KICK_SOUND_FILEPATH "Resources/Sounds/smb_kick.wav"
#define STOMP_SOUND_FILEPATH "Resources/Sounds/smb_stomp.wav"
#define BUMP_SOUND_FILEPATH "Resources/Sounds/smb_bump.wav"
#define MARIO_DIE_SOUND_FILEPATH "Resources/Sounds/smb_mariodie.wav"
#define PIPE_SOUND_FILEPATH "Resources/Sounds/smb_pipe.wav"
#define FLAGPOLE_SOUND_FILEPATH "Resources/Sounds/smb_flagpole.wav"
#define STAGE_CLEAR_SOUND_FILEPATH "Resources/Sounds/smb_stage_clear.wav"
#define WARNING_SOUND_FILEPATH "Resources/Sounds/smb_warning.wav"
#define GAMEOVER_SOUND_FILEPATH "Resources/Sounds/smb_gameover.wav"
#define OW_THEME_MUSIC_FILEPATH "Resources/Sounds/OW_theme.oga"
#define UG_THEME_MUSIC_FILEPATH "Resources/Sounds/UG_theme.ogg"

#define BACKGROUND_COLOR01 sf::Color(107, 140, 255)
#define BACKGROUND_COLOR02 sf::Color(0, 0, 0)

#define HIGH_SCORE_FILEPATH "Resources/HighScore.txt"


extern sf::Color backgroundColor;

#define LOADINGSCREEN_TIME 2.2f

#define LEVEL_TIME 400

#define POLE_TOP sf::IntRect(260, 136, 8, 8)
#define POLE sf::IntRect(263, 144, 2, 16)
#define POLE_FLAG sf::IntRect(128, 32, 16, 16)


#define PIPE_TOP sf::IntRect(0, 128, 32, 16)
#define PIPE_BOTTOM sf::IntRect(2, 144, 28, 16)

#define PIPE_TOP_UG sf::IntRect(0, 160, 32, 16)
#define PIPE_BOTTOM_UG sf::IntRect(2, 176, 28, 16)

#define GROUND_TILE sf::IntRect(0, 0, 16, 16)

#define GROUND_TILE_BLUE sf::IntRect(0, 32, 16, 16)

#define STAIR_TILE sf::IntRect(495, 0, 16, 16)
#define STAIR_TILE_UG sf::IntRect(495, 32, 16, 16)

#define BRICK_PARTICLE_ANIMATION_TIME 0.2f
#define BRICK_TILE sf::IntRect(16, 0, 16, 16)
#define BRICK_PARTICLE1 sf::IntRect(451, 0, 8, 8)
#define BRICK_PARTICLE2 sf::IntRect(460, 0, 8, 8)

#define BRICK_TILE_UG sf::IntRect(32, 32, 16, 16)
#define BRICK_PARTICLE1_UG sf::IntRect(451, 33, 8, 8)
#define BRICK_PARTICLE2_UG sf::IntRect(460, 33, 8, 8)
#define BRICK_TILE_OPENED_UG sf::IntRect(48, 32, 16, 16)

#define BOX_ANIMATION_TIME 0.7f
#define BOX_TILE1 sf::IntRect(384, 0, 16, 16)
#define BOX_TILE2 sf::IntRect(400, 0, 16, 16)
#define BOX_TILE3 sf::IntRect(416, 0, 16, 16)
#define BOX_TILE_OPENED sf::IntRect(432, 0, 16, 16)

#define BOX_TILE1_UG sf::IntRect(384, 32, 16, 16)
#define BOX_TILE2_UG sf::IntRect(400, 32, 16, 16)
#define BOX_TILE3_UG sf::IntRect(416, 32, 16, 16)
#define BOX_TILE_OPENED_UG sf::IntRect(432, 32, 16, 16)

#define PLATFORM_SPEED 200.0f
#define PLATFORM sf::IntRect(420, 230, 48, 8)

#define CLOUD_TILE1 sf::IntRect(8, 320, 32, 24)
#define CLOUD_TILE2 sf::IntRect(248, 320, 48, 24)
#define CLOUD_TILE3 sf::IntRect(183, 320, 64, 24)

#define BUSH_TILE1 sf::IntRect(184, 144, 32, 16)
#define BUSH_TILE2 sf::IntRect(418, 144, 48, 16)
#define BUSH_TILE3 sf::IntRect(418, 128, 64, 16)

#define BUMP_TILE_SMALL sf::IntRect(418, 170, 48, 19)
#define BUMP_TILE_BIG sf::IntRect(417, 190, 80, 35)


#define COIN_ITEM_ANIMATION_TIME 0.3f
#define COIN_ITEM1 sf::IntRect(4, 113, 8, 14)
#define COIN_ITEM2 sf::IntRect(20, 113, 8, 14)
#define COIN_ITEM3 sf::IntRect(36, 113, 8, 14)
#define COIN_ITEM4 sf::IntRect(52, 113, 8, 14)


#define COIN_ANIMATION_TIME 0.8f
#define COIN01 sf::IntRect(3, 98, 10, 14)
#define COIN02 sf::IntRect(19, 98, 10, 14)
#define COIN03 sf::IntRect(35, 98, 10, 14)
#define COIN04 sf::IntRect(51, 98, 10, 14)
#define COIN_UG_01 sf::IntRect(147, 98, 10, 14)
#define COIN_UG_02 sf::IntRect(163, 98, 10, 14)
#define COIN_UG_03 sf::IntRect(179, 98, 10, 14)
#define COIN_UG_04 sf::IntRect(195, 98, 10, 14)

#define MUSHROOM_ITEM sf::IntRect(0, 0, 16, 16)

#define FIREFLOWER_ANIMATION_TIME 0.4f

#define FIREFLOWER01 sf::IntRect(0, 32, 16, 16)
#define FIREFLOWER02 sf::IntRect(16, 32, 16, 16)
#define FIREFLOWER03 sf::IntRect(32, 32, 16, 16)
#define FIREFLOWER04 sf::IntRect(48 ,32, 16, 16)

#define FIREFLOWER01_UG sf::IntRect(144, 32, 16, 16)
#define FIREFLOWER02_UG sf::IntRect(160, 32, 16, 16)
#define FIREFLOWER03_UG sf::IntRect(176, 32, 16, 16)
#define FIREFLOWER04_UG sf::IntRect(192 ,32, 16, 16)


enum class Items { empty, coin, powerUp };

enum class Dir { Right, Left };

enum class Setting { OW, UG };


#define CAMERA_SPEED 300.0f

#define MARIO_SPEED_X 2500.0f

#define MARIO_RUN_ANIMATION_TIME 0.17f

#define SMALL_MARIO_IDLE_RIGHT sf::IntRect(80.5, 34, 16, 16)
#define SMALL_MARIO_IDLE_LEFT sf::IntRect(96.5, 34, -16, 16)

#define SMALL_MARIO_RUN_RIGHT_01 sf::IntRect(97.5, 34, 16, 16)
#define SMALL_MARIO_RUN_LEFT_01 sf::IntRect(113.5, 34, -16, 16)

#define SMALL_MARIO_RUN_RIGHT_02 sf::IntRect(114.5, 34, 16, 16)
#define SMALL_MARIO_RUN_LEFT_02 sf::IntRect(130.5, 34, -16, 16)

#define SMALL_MARIO_RUN_RIGHT_03 sf::IntRect(131.5, 34, 16, 16)
#define SMALL_MARIO_RUN_LEFT_03 sf::IntRect(147.5, 34, -16, 16)

#define SMALL_MARIO_TURN_RIGHT sf::IntRect(148.5, 34, 16, 16)
#define SMALL_MARIO_TURN_LEFT sf::IntRect(164.5, 34, -16, 16)

#define SMALL_MARIO_JUMP_RIGHT sf::IntRect(165.5, 34, 16, 16)
#define SMALL_MARIO_JUMP_LEFT sf::IntRect(181.5, 34, -16, 16)



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

#define BIG_MARIO_CROUCH_RIGHT sf::IntRect(182, 11, 16, 22)
#define BIG_MARIO_CROUCH_LEFT sf::IntRect(198 ,11, -16, 22)

#define POLE_CLIMBING_SPEED 300.0f

#define MARIO_CLIMB_POLE_ANIMATION_TIME 0.175f

#define BIG_MARIO_CLIMB_POLE1 sf::IntRect(199, 1, 16, 32)
#define BIG_MARIO_CLIMB_POLE2 sf::IntRect(216, 1, 16, 32)
#define BIG_MARIO_CLIMB_POLE_LEFT sf::IntRect(215, 1, -16, 32)

#define SMALL_MARIO_CLIMB_POLE1 sf::IntRect(201, 34, 13, 16)
#define SMALL_MARIO_CLIMB_POLE2 sf::IntRect(218, 34, 13, 16)
#define SMALL_MARIO_CLIMB_POLE_LEFT sf::IntRect(231, 34, -13, 16)

#define SMALL_MARIO_DEAD sf::IntRect(182, 34, 16, 16)


#define MARIO_GROWING_ANIMATION_TIME 0.7f 
#define MARIO_SHRINKING_ANIMATION_TIME 1.0f

#define SMALL_BIG_MARIO_RIGHT sf::IntRect(335, 1, 16, 32)
#define SMALL_BIG_MARIO_LEFT sf::IntRect(351, 1, -16, 32)



#define FIRE_MARIO_IDLE_RIGHT sf::IntRect(80, 129, 16, 32)
#define FIRE_MARIO_IDLE_LEFT sf::IntRect(96, 129, -16, 32)

#define FIRE_MARIO_RUN_RIGHT_01 sf::IntRect(97, 129, 16, 32)
#define FIRE_MARIO_RUN_LEFT_01  sf::IntRect(113, 129, -16, 32)

#define FIRE_MARIO_RUN_RIGHT_02 sf::IntRect(114, 129, 16, 32)
#define FIRE_MARIO_RUN_LEFT_02  sf::IntRect(130, 129, -16, 32)

#define FIRE_MARIO_RUN_RIGHT_03 sf::IntRect(131, 129, 16, 32)
#define FIRE_MARIO_RUN_LEFT_03  sf::IntRect(147, 129, -16, 32)

#define FIRE_MARIO_TURN_RIGHT sf::IntRect(148, 129, 16, 32)
#define FIRE_MARIO_TURN_LEFT sf::IntRect(164, 129, -16, 32)

#define FIRE_MARIO_JUMP_RIGHT sf::IntRect(165, 129, 16, 32)
#define FIRE_MARIO_JUMP_LEFT sf::IntRect(181, 129, -16, 32)

#define FIRE_MARIO_CROUCH_RIGHT sf::IntRect(182, 139, 16, 22)
#define FIRE_MARIO_CROUCH_LEFT sf::IntRect(198, 139, -16, 22)

#define FIRE_MARIO_CLIMB_POLE1 sf::IntRect(199, 129, 16, 32)
#define FIRE_MARIO_CLIMB_POLE2 sf::IntRect(216, 129, 16, 32)
#define FIRE_MARIO_CLIMB_POLE_LEFT sf::IntRect(215, 129, -16, 32)

#define FIRE_MARIO_THROW_RIGHT01 sf::IntRect(352, 129, 16, 32)
#define FIRE_MARIO_THROW_LEFT01 sf::IntRect(368, 129, -16, 32)

#define FIRE_MARIO_THROW_RIGHT02 sf::IntRect(369, 129, 16, 32)
#define FIRE_MARIO_THROW_LEFT02 sf::IntRect(385, 129, -16, 32)

#define FIRE_MARIO_THROW_RIGHT03 sf::IntRect(386, 129, 16, 32)
#define FIRE_MARIO_THROW_LEFT03 sf::IntRect(402, 129, -16, 32)

#define FIRE_MARIO_JUMP_THROW_RIGHT sf::IntRect(420, 129, 16, 32)
#define FIRE_MARIO_JUMP_THROW_LEFT sf::IntRect(436, 129, -16, 32)

#define FIREBALL_EXPLOSION_TIME 0.15f
#define FIREBALL_ANIMATION_TIME 0.2f
#define FIREBALL_SPEED 875.0f

#define FIREBALL01 sf::IntRect(96, 144, 8, 8)
#define FIREBALL02 sf::IntRect(104, 144, 8, 8)
#define FIREBALL03 sf::IntRect(96, 152, 8, 8)
#define FIREBALL04 sf::IntRect(104, 152, 8, 8)

#define FIREBALL_EXPLOSION01 sf::IntRect(116, 148, 8, 8)
#define FIREBALL_EXPLOSION02 sf::IntRect(114, 161, 12, 14)
#define FIREBALL_EXPLOSION03 sf::IntRect(112, 176, 16, 16)



#define EMPTY sf::IntRect(0, 0, 16, 32)

#define SMALL_CASTLE sf::IntRect(247, 863, 80, 80)
#define BIG_CASTLE sf::IntRect(79, 767, 148, 176)

#define CASTLE_FLAG sf::IntRect(129, 2, 13, 14)




#define GOOMBA_ANIMATION_TIME 0.4f
#define GOOMBA1 sf::IntRect(0, 16, 16, 16)
#define GOOMBA2 sf::IntRect(16, 16, 16, 16)
#define GOOMBA_UPSIDEDOWN sf::IntRect(0, 32, 16, -16)
#define GOOMBA_DEAD sf::IntRect(32, 16, 16, 16)

#define GOOMBA1_UG sf::IntRect(0, 48, 16, 16)
#define GOOMBA2_UG sf::IntRect(16, 48, 16, 16)
#define GOOMBA_UPSIDEDOWN_UG sf::IntRect(0, 64, 16, -16)
#define GOOMBA_DEAD_UG sf::IntRect(32, 48, 16, 16)



#define KOOPA_SLIDING_SPEED 450.0f
#define KOOPA_ANIMATION_TIME 0.3f
#define KOOPA1_LEFT sf::IntRect(96, 8, 16, 24)
#define KOOPA2_LEFT sf::IntRect(112, 8, 16, 24)
#define KOOPA1_RIGHT sf::IntRect(112, 8, -16, 24)
#define KOOPA2_RIGHT sf::IntRect(128, 8, -16, 24)
#define KOOPA_SHELL sf::IntRect(160 , 17, 16, 14)
#define KOOPA_SHELL_UPSIDEDOWN sf::IntRect(160, 31, 16, -14)

#define KOOPA1_LEFT_UG sf::IntRect(96, 40, 16, 24)
#define KOOPA2_LEFT_UG sf::IntRect(112, 40, 16, 24)
#define KOOPA1_RIGHT_UG sf::IntRect(112, 40, -16, 24)
#define KOOPA2_RIGHT_UG sf::IntRect(128, 40, -16, 24)
#define KOOPA_SHELL_UG sf::IntRect(160, 49, 16, 14)
#define KOOPA_SHELL_UPSIDEDOWN_UG sf::IntRect(160, 63, 16, -14)


#define PIRANHA_ANIMATON_TIME 0.25f
#define PIRANHA1 sf::IntRect(192, 8, 16, 24)
#define PIRANHA2 sf::IntRect(208, 8, 16, 24)

#define PIRANHA1_UG sf::IntRect(192, 40, 16, 24)
#define PIRANHA2_UG sf::IntRect(208, 40, 16, 24)


#define HUD_CROSS sf::IntRect(0, 89, 5, 5)

#define MENU_LOGO sf::IntRect(0, 0, 176, 88)

#define MENU_CURSOR sf::IntRect(0, 95, 8, 8)




#define SCORE_SPEED -200.0f