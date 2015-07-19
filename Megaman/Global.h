﻿#pragma once

#include <d3dx9.h>
#include <stdio.h>
#include <vector>
#include <dinput.h>
#include <stdarg.h>
#include <windows.h>
#include <cmath>

using namespace std;


#define GAME_NAME "Megaman"
#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 224
#define GAME_FPS 60
#define GRAVITY  -600.0f

#define KEYBOARD_BUFFER_SIZE 1024 
#define FRAMERATE 60

// ID đối tượng
#define ID_LAND 1

typedef LPDIRECT3DDEVICE9		Device;
typedef LPDIRECT3DSURFACE9		Surface;
typedef LPDIRECT3DTEXTURE9		Texture;
typedef LPD3DXSPRITE			Sprite;
typedef LPD3DXFONT				SpriteFont;
typedef LPDIRECT3D9				DirectX9;
typedef D3DXIMAGE_INFO			ImageInfo;
typedef D3DXVECTOR2				Vector2;
typedef D3DXVECTOR3				Vector3;
typedef D3DXVECTOR4				Vector4;
typedef LPDIRECTINPUT8			Input;
typedef LPDIRECTINPUTDEVICE8	InputDevice;
typedef DIDEVICEOBJECTDATA		DeviceObjectData;
typedef D3DXMATRIX				Matrix;
typedef D3DCOLOR				Color;
typedef RECT					Rect;

#define FONT_SIZE	8


#define	ID_KEY_CODE_UP			DIK_I
#define	ID_KEY_CODE_DOWN		DIK_K
#define	ID_KEY_CODE_LEFT		DIK_J
#define	ID_KEY_CODE_RIGHT		DIK_L
#define	ID_KEY_CODE_FIRE		DIK_Z
#define	ID_KEY_CODE_JUMP		DIK_X
#define	ID_KEY_CODE_ENTER		DIK_RETURN
#define	ID_KEY_CODE_PAUSE		DIK_SPACE

#define GRAVITY			(9.8f / powf(1000.0f, 2.0f))

#pragma region INPUT_DEVICE

#define KEYBOARD_BUFFER_SIZE 1024

#pragma endregion

#pragma region Các định danh ID của các đối tượng trong Game - Giá trị bắt đầu từ 0

#define ID_ROCKMAN								-1
#define ID_CUTMAN			5000
#define ID_GUTSMAN		    5001
#define ID_BOOMMAN			5002

// map boom
#define ID_ENEMY_BALL							1
#define ID_ENEMY_BOOM_BLUE						2
#define ID_ENEMY_EYE_RED_UP						3
#define ID_ENEMY_EYE_RED_RIGHT					501 
#define ID_ENEMY_FISH_ORANGE					4
#define ID_ENEMY_INK_RED						5
#define ID_ENEMY_MACHINE_AUTO_BLUE_TOP			6
#define ID_ENEMY_MACHINE_ORANGE					7
#define ID_ENEMY_NINJA_GREEN					8
// map cut 
#define ID_ENEMY_BUBBLE_BLUE					9
#define ID_ENEMY_CUT							10
#define ID_ENEMY_INK_BLUE						12
#define ID_ENEMY_MACHINE_AUTO_ORGANGE_TOP		13
#define ID_ENEMY_ROBOT_RED						14
#define ID_ENEMY_EYE_RED						50
#define ID_ENEMY_WALL_SHOOTER_LEFT				40
#define ID_ENEMY_WALL_SHOOTER_RIGHT				41
// map guts 
#define ID_ENEMY_BUBBLE_GREEN					15
#define ID_ENEMY_HAT							19
#define ID_ENEMY_ROBOT_BLUE						20
#define ID_ENEMY_WORKER							21
#define ID_BLOCK_TROUBLE_OF_ELEVATOR			36
#define ID_ELEVATOR								38
#define ID_ELEVATOR_TROUBLE						39
// oder
#define ID_BLOCK								22
#define ID_STAIR								23
#define ID_ITEM_LIFE							24
#define ID_ITEM_BLOOD_BIG						25
#define ID_ITEM_BLOOD_SMALL						26
#define ID_ITEM_MANA_BIG						27
#define ID_ITEM_MANA_SMALL						28
#define ID_ROCK									29
#define ID_DIE_ARROW							30
#define ID_ITEM_BONUS							33
#define ID_FALLING_POINT						341
#define ID_DEBUG_BOX							998
#define ID_ITEM_BOSS_CUT						600
#define ID_ITEM_BOSS_GUTS						601
#define ID_ITEM_BOSS_BOOM						602
#define ID_ROCK_IN_GUT_STAGE					60

#define ID_BAR_BLOOD_ROCKMAN					503
#define ID_BAR_BLOOD_CUTMAN						504
#define ID_BAR_BLOOD_GUTSMAN					505
#define ID_BAR_BLOOD_BOOMMAN					506
#define ID_BAR_WEAPONS_CUT						507
#define ID_BAR_WEAPONS_GUTS						508
#define ID_BAR_WEAPONS_BOOM						509
// add 
#define ID_ENEMY_INK_SIT						31
#define ID_ENEMY_INK_STAND						32
// Thêm ID door
#define ID_DOOR1_CUTMAN							541
#define ID_DOOR1_GUTSMAN						542
#define ID_DOOR1_BOOMMAN						543
#define ID_DOOR2_BOOMMAN						544
#define ID_DOOR2_CUTMAN							545
#define ID_DOOR2_GUTSMAN						546
#define ID_ENEMY_SNAPPER						344 // hộp kéo

#define ID_ENEMY_MACHINE_AUTO_BLUE_BOTTOM		34
#define ID_ENEMY_MACHINE_AUTO_ORGANGE_BOTTOM	35

#pragma endregion

#pragma region Các định danh ID của Sprite - Giá trị bắt đầu từ 1000

#define ID_SPRITE_ROCKMAN_STAND						1004
#define ID_SPRITE_ROCKMAN_STAND_CUT					1005
#define ID_SPRITE_ROCKMAN_STAND_GUTS				1006
#define ID_SPRITE_ROCKMAN_STAND_GUTS_ROCK			1007
#define ID_SPRITE_ROCKMAN_STAND_BOOM				1008

#define ID_SPRITE_ROCKMAN_STAND_FIRE				1009
#define ID_SPRITE_ROCKMAN_STAND_FIRE_CUT			1010
#define ID_SPRITE_ROCKMAN_STAND_FIRE_GUTS			1011
#define ID_SPRITE_ROCKMAN_STAND_FIRE_BOOM			1012

#define ID_SPRITE_ROCKMAN_PREPARE_RUN				1013
#define ID_SPRITE_ROCKMAN_PREPARE_RUN_CUT			1014
#define ID_SPRITE_ROCKMAN_PREPARE_RUN_GUTS			1015
#define ID_SPRITE_ROCKMAN_PREPARE_RUN_GUTS_ROCK		1015
#define ID_SPRITE_ROCKMAN_PREPARE_RUN_BOOM			1016

#define ID_SPRITE_ROCKMAN_RUN					1017
#define ID_SPRITE_ROCKMAN_RUN_CUT				1018
#define ID_SPRITE_ROCKMAN_RUN_GUTS				1019
#define ID_SPRITE_ROCKMAN_RUN_GUTS_ROCK			1020
#define ID_SPRITE_ROCKMAN_RUN_BOOM				1021

#define ID_SPRITE_ROCKMAN_RUN_FIRE				1022
#define ID_SPRITE_ROCKMAN_RUN_FIRE_CUT			1023
#define ID_SPRITE_ROCKMAN_RUN_FIRE_GUTS			1024
#define ID_SPRITE_ROCKMAN_RUN_FIRE_BOOM			1025

#define ID_SPRITE_ROCKMAN_JUMP					1026
#define ID_SPRITE_ROCKMAN_JUMP_CUT				1027
#define ID_SPRITE_ROCKMAN_JUMP_GUTS				1028
#define ID_SPRITE_ROCKMAN_JUMP_BOOM				1029

#define ID_SPRITE_ROCKMAN_JUMP_FIRE				1030
#define ID_SPRITE_ROCKMAN_JUMP_FIRE_CUT			1031
#define ID_SPRITE_ROCKMAN_JUMP_FIRE_GUTS		1032
#define ID_SPRITE_ROCKMAN_JUMP_FIRE_BOOM		1033

#define ID_SPRITE_ROCKMAN_STAIR				1034
#define ID_SPRITE_ROCKMAN_STAIR_CUT			1035
#define ID_SPRITE_ROCKMAN_STAIR_GUTS		1036
#define ID_SPRITE_ROCKMAN_STAIR_BOOM		1037

#define ID_SPRITE_ROCKMAN_STAIR_END			1038
#define ID_SPRITE_ROCKMAN_STAIR_END_CUT		1039
#define ID_SPRITE_ROCKMAN_STAIR_END_GUTS	1040
#define ID_SPRITE_ROCKMAN_STAIR_END_BOOM	1041

#define ID_SPRITE_ROCKMAN_STAIR_FIRE		1042
#define ID_SPRITE_ROCKMAN_STAIR_FIRE_CUT	1043
#define ID_SPRITE_ROCKMAN_STAIR_FIRE_GUTS	1044
#define ID_SPRITE_ROCKMAN_STAIR_FIRE_BOOM	1045

#define ID_SPRITE_ROCKMAN_HURT				1046
#define ID_SPRITE_ROCKMAN_HURT_CUT			1047
#define ID_SPRITE_ROCKMAN_HURT_GUTS			1048
#define ID_SPRITE_ROCKMAN_HURT_BOOM			1049

#define ID_SPRITE_ROCKMAN_CONFUSE			1150

#define ID_SPRITE_ROCKMAN_START				1054
#define ID_SPRITE_ROCKMAN_START_BOOM		1055
#define ID_SPRITE_ROCKMAN_START_CUT			1056
#define ID_SPRITE_ROCKMAN_START_GUTS		1057

#define ID_SPRITE_ROCKMAN_FALL				1058
#define ID_SPRITE_ROCKMAN_FALL_CUT			1059
#define ID_SPRITE_ROCKMAN_FALL_GUTS			1060
#define ID_SPRITE_ROCKMAN_FALL_BOOM			1061


//Id Sprite của BULLET bắt đầu từ 1200
#define ID_SPRITE_EXPLODING_EFFECT_BASE			1201
#define ID_SPRITE_EXPLODING_EFFECT_ROCKMAN		1202
#define ID_SPRITE_EXPLODING_EFFECT_CUTMAN		1203
#define ID_SPRITE_EXPLODING_EFFECT_BOOMMAN		1204
#define ID_SPRITE_EXPLODING_EFFECT_GUTSMAN		1205
#define ID_SPRITE_BULLET_BOOM					1206
#define ID_SPRITE_BULLET_NINJA					1207
#define ID_SPRITE_BULLET_ROCKMAN_NORMAL			1208
#define ID_SPRITE_BULLET_ROCKMAN_CUT			1209
#define ID_SPRITE_BULLET_ROCKMAN_BOOM			1210
#define ID_SPRITE_BULLET_ROCKMAN_GUTS_BIG		1211
#define ID_SPRITE_BULLET_ROCKMAN_GUTS_STAGE_BIG	1212
#define ID_SPRITE_BULLET_ROCKMAN_GUTS_SMALL		1213
#define ID_SPRITE_BULLET_ENEMY_HAT				1214
#define ID_SPRITE_BULLET_ENEMY_FISH				1215
#define ID_SPRITE_BULLET_ENEMY_SNAPPER			1216
#define ID_SPRITE_BULLET_ENEMY_NINJA			1217
#define ID_SPRITE_BULLET_WORKER					1218
#define ID_SPRITE_BULLET_RED_COLOR				1219
#define ID_SPRITE_BULLET_ORANGE_COLOR			1220
#define ID_SPRITE_BULLET_BLUE_COLOR				1221


//Id sprite của ENEMY bắt đầu từ 1300
#define ID_SPRITE_ENEMY_MACHINE_AUTO_BLUE		1300
#define ID_SPRITE_ENEMY_MACHINE_AUTO_ORGANGE	1301
#define ID_SPRITE_ENEMY_BUBBLE_BLUE				1302
#define ID_SPRITE_ENEMY_ROBOT_RED				1303
#define ID_SPRITE_ENEMY_ROBOT_BLUE				1304
#define ID_SPRITE_ENEMY_EYE				        1305
#define ID_SPRITE_ENEMY_INK_BLUE				1306
#define ID_SPRITE_ENEMY_INK_RED				    1307
#define ID_SPRITE_ENEMY_HAT				        1308
#define ID_SPRITE_ENEMY_BOOM_BLUE				1309
#define ID_SPRITE_ENEMY_FISH				    1310
#define ID_SPRITE_ENEMY_MACHINE				    1311
#define ID_SPRITE_ENEMY_NINJA_STAND			    1312
#define ID_SPRITE_ENEMY_NINJA_JUMP				1313
#define ID_SPRITE_ENEMY_NINJA_FIRE				1314
#define ID_SPRITE_ENEMY_WALL_SHOOTER		    1315
#define ID_SPRITE_ENEMY_WORKER					1316
#define ID_SPRITE_ENEMY_BUBBLE_GREEN			1317
#define ID_SPRITE_ENEMY_BALL					1318


//Boss cut man bắt đầu từ 1400
#define ID_SPRITE_CUTMAN_STAND0				1401
#define ID_SPRITE_CUTMAN_RUN0				1402
#define ID_SPRITE_CUTMAN_JUMP0				1403
#define ID_SPRITE_CUTMAN_FIRE0				1404
#define	ID_SPRITE_CUTMAN_STAND1				1405
#define ID_SPRITE_CUTMAN_RUN1				1406
#define ID_SPRITE_CUTMAN_JUMP1				1407
#define ID_SPRITE_CUTMAN_COLLIDE			1408

//Boss Boom man bắt đầu từ 1500
#define ID_SPRITE_BOOMMAN_JUMP_HEIGHT		1500
#define ID_SPRITE_BOOMMAN_JUMP_LOW			1501
#define ID_SPRITE_BOOMMAN_JUMP_STAND		1502
#define ID_SPRITE_BOOMMAN_FIRE				1503
#define ID_SPRITE_BOOMMAN_BOOM_BURST		1504
#define ID_SPRITE_BOOMMAN_BOOM_PUSH			1505


//Boss guts man bắt đầu từ 1600
#define ID_SPRITE_GUSTMAN_STOMING			1600
#define ID_SPRITE_GUSTMAN_THROW				1601
#define ID_SPRITE_GUSTMAN_ROCKFIRE			1602
#define ID_SPRITE_WEAPON_GUTS_PART			1603
#define ID_SPRITE_GUSTMAN_STAND				1604

// ID sprite bullet bắt đầu từ 1700
#define ID_SPRITE_BULLET_NORMAL				1700
#define ID_SPRITE_BULLET_CUT				1701
#define ID_SPRITE_BULLET_BOSS_BOOM			1702
#define ID_SPRITE_BULLET_GUTS				1704

// ID sprite Door bắt đầu từ 1800
#define ID_SPRITE_DOOR_CUTMAN				1800
#define ID_SPRITE_DOOR_GUTSMAN				1801
#define ID_SPRITE_DOOR1_BOOMMAN				1802
#define ID_SPRITE_DOOR2_BOOMMAN				1803

// ID sprite Item bắt đầu từ 1900
#define ID_SPRITE_ITEM_BLOOD_BIG			1900
#define ID_SPRITE_ITEM_BLOOD_SMALL			1901
#define ID_SPRITE_ITEM_MANA_BIG				1902
#define ID_SPRITE_ITEM_MANA_SMALL			1903
#define ID_SPRITE_ITEM_BONUS_ORANGE			1904
#define ID_SPRITE_ITEM_BONUS_RED			1905
#define ID_SPRITE_ITEM_BONUS_BLUE			1906
#define ID_SPRITE_ITEM_BONUS_GREEN			1907
#define ID_SPRITE_ITEM_LIFE					1908
#define ID_SPRITE_ITEM_BOSS_CUT				1909
#define ID_SPRITE_ITEM_BOSS_GUTS			1910
#define ID_SPRITE_ITEM_BOSS_BOOM			1911

//ID sprite Elevetor 
#define ID_SPRITE_ELEVATOR					1912

#define ID_SPRITE_BAR_BACKGROUND_VERTICAL	1913
#define ID_SPRITE_BAR_ROCKMAN_VERTICAL		1914
#define ID_SPRITE_BAR_BOOM_VERTICAL			1915
#define ID_SPRITE_BAR_CUT_VERTICAL			1916
#define ID_SPRITE_BAR_GUTS_VERTICAL			1917

#define ID_SPRITE_ROOM_BOOM_STAGE			1918
#define ID_SPRITE_ROOM_CUT_STAGE			1919
#define ID_SPRITE_ROOM_GUTS_STAGE			1920


#pragma endregion

#pragma region Các định danh ID của Sound - Giá trị bắt đầu từ 2000

#define ID_EFFECT_ONE_UP						2000

#define ID_SOUND_BEAM_IN					2001
#define ID_SOUND_DEAD						2002
#define ID_SOUND_DISAPPEARING_BLOCK			2003
#define ID_SOUND_ENEMY_HIT					2004
#define ID_SOUND_HEALTH						2005
#define ID_SOUND_HURT						2006
#define ID_SOUND_LAND						2007
#define ID_SOUND_PAUSE						2008
#define ID_SOUND_POWER_UP					2009
#define ID_SOUND_SHOOT						2010
#define ID_SOUND_SHOT_BLOCKED				2011
#define ID_SOUND_STAGE_SELECT				2012
#define ID_SOUND_GAME_START					2013
#define ID_SOUND_CUTMAN_STAGE				2014
#define ID_SOUND_GUTSMAN_STAGE				2015
#define ID_SOUND_BOMBMAN_STAGE				2016
#define ID_SOUND_BOSS						2017
#define ID_SOUND_STAGE_CLEAR				2018
#define ID_SOUND_ENDING						2019
#define ID_SOUND_GAME_OVER					2020

#define ID_EFFECT_ANIMATION_SCORE					2050
#define ID_EFFECT_BIG_ROBOT_ON_LAND					2051
#define ID_EFFECT_BOSS_DIE							2052
#define ID_EFFECT_BULLET_BOOM_EXPLODING				2053
#define ID_EFFECT_BULLET_BOSS_CUTMAN				2054
#define ID_EFFECT_BULLET_HIT_ENEMY_WITH_SHIELD		2055
#define ID_EFFECT_CAMERA_VIBRATE					2056
#define ID_EFFECT_ELEVATOR_RUNNING					2057
#define ID_EFFECT_ENEMY_EXPLODING					2058
#define ID_EFFECT_ENEMY_FIRE						2059
#define ID_EFFECT_ENEMY_HIT							2060
#define ID_EFFECT_FOCUS_STAGE						2062
#define ID_EFFECT_GET_BLOOD							2063
#define ID_EFFECT_GET_ITEM							2064
#define ID_EFFECT_HEALTH							2065
#define ID_EFFECT_INCREASE_POWER_ENEMY				2066
#define ID_EFFECT_INTRO_STAGE						2067
#define ID_EFFECT_LAND								2068
#define ID_EFFECT_OPEN_THE_DOOR						2069
#define ID_EFFECT_PAUSE								2070
#define ID_EFFECT_POPUP_APPEAR						2071
#define ID_EFFECT_POWER_UP							2072
#define ID_EFFECT_ROCKMAN_APPEAR					2073
#define ID_EFFECT_ROCKMAN_COLLIDE_WITH_ENEMY		2074
#define ID_EFFECT_ROCKMAN_DIE						2075
#define ID_EFFECT_ROCKMAN_FIRE_BULLET_NORMAL		2076
#define ID_EFFECT_ROCKMAN_FIRE_BULLET_CUT			2077
#define ID_EFFECT_ROCKMAN_FIRE_BULLET_GUTS			2078
#define ID_EFFECT_SELECT_STAGE						2079
#define ID_EFFECT_VICTORY							2080
#define ID_EFFECT_ANIMATION_TEXT					2081

#pragma endregion

#pragma region Các định danh ID của Level - Giá trị bắt đầu từ 3000

#define ID_LEVEL_CUT		3001
#define ID_LEVEL_GUTS		3002
#define ID_LEVEL_BOOM		3003
#define ID_END_GAME			3004

#define ID_SCREEN_MENU			3005
#define ID_SCREEN_GAME_OVER		3006
#define ID_SCREEN_GAME_START	3007
#define ID_SCREEN_INTRO_SCREEN	3008
#define ID_SCREEN_PLAY			3009

#pragma endregion

#pragma region Các định danh ID của đạn - Giá trị bắt đầu từ 4000

#define ID_BULLET_CUTMAN				4000
#define ID_BULLET_GUTSMAN				4002
#define ID_BULLET_BOOMMAN				4004
#define ID_BULLET_MACHINE_AUTO			4006
#define ID_BULLET_BOOM					4007
#define ID_BULLET_NINJA					4008
#define ID_BULLET_ENEMY_HAT				4009
#define ID_BULLET_ENEMY_FISH			4010
#define ID_BULLET_ROCKMAN_NORMAL		4011
#define ID_BULLET_ROCKMAN_CUT			4012
#define ID_BULLET_ROCKMAN_BOOM			4014
#define ID_BULLET_ROCKMAN_BOOM_NONE		4015
#define ID_BULLET_ROCKMAN_GUTS			4016
#define ID_BULLET_WALL_SHOOTER			4018
#define ID_BULLET_ENEMY_SNAPPER			4019
#define ID_BULLET_ENEMY_NINJA			4020
#define ID_BULLET_WORKER				4021
#define ID_BULLET_BALL					4022

#pragma endregion

#pragma region Thiết lập các giá trị cho Enemy của Uy

#define SPACE_X_TO_BUBBLE_ENEMY_ATTACK				50//Đơn vị là Pixel
#define SPACE_X_TO_MACHINE_AUTO_ENEMY_ATTACK		70//Đơn vị là Pixel
#define VX_INCREASE_OF_BUBBLE_ENEMY_ATTACKING		40.0f //Đơn vị là Pixel/giây
#define SPACE_X_JUMP_OF_ROBOT_ENEMY					30.0f	//Khoảng cách chiều x (ngang) nhảy tối đa của EnemyRobot. Đơn vị là Pixel
#define ANGLE_OF_JUMP_OF_ROBOT_ENEMY				11.0f*PI/24.0f		//Góc nhảy của EnemyRobot
#define TIME_ATTACK_OF_MACHINE_AUTO_ENEMY			2500// Đơn vị là Tick
#define TIME_DELAY_ATTACK_OF_MACHINE_AUTO_ENEMY		1100// Đơn vị là Tick
#define TIME_DELAY_FIRE_OF_MACHINE_AUTO_ENEMY		800// Đơn vị là Tick	
#define TIME_DELAY_ATTACK_OF_BOOM_ENEMY				2100// Đơn vị là Tick	
#define HMAX_FLY_OF_BOOM_ENEMY						180// Đơn vị là Pixel
#define TIME_STANDING_OF_ROBOT_ENEMY				1000// Đơn vị là Tick	
#define TIME_DELAY_FIRE_OF_WALL_SHOOTER_ENEMY		1000// Đơn vị là Tick	
#define TIME_DEFENSE_OF_WALL_SHOOTER_ENEMY			2000// Đơn vị là Tick	
#define TIME_DELAY_FIRE_OF_WORKER_ENEMY				1000// Đơn vị là Tick	
#define TIME_DEFENSE_OF_BALL_ENEMY					1300// Đơn vị là Tick		
#define TIME_ATTACK_OF_BALL_ENEMY					500// Đơn vị là Tick	

#pragma endregion

#pragma region Vùng định nghĩa DAME và BLOOD, WEAPONS, ITEM VALUE, SCORE

#define SCORE_DEFAULT				200
#define BLOOD_DEFAULT				27
#define	WEASPON_DEFAULT				27
#define VALUE_ITEM_BLOOD_BIG		10
#define VALUE_ITEM_BLOOD_SMALL		2
#define VALUE_ITEM_MANA_BIG			10
#define VALUE_ITEM_MANA_SMALL		2
#define LIFE_DEFAULT				10

#define DAME_BULLET_ROCKMAN			2
#define DAME_BULLET_CUTMAN			(4*BLOOD_DEFAULT)/27
#define DAME_BULLET_BOOMMAN			(4*BLOOD_DEFAULT)/27
#define DAME_BULLET_GUTSMAN			(4*BLOOD_DEFAULT)/27
#define DAME_BULLET_CUT_ROCKMAN		BLOOD_DEFAULT/3
#define DAME_BULLET_BOOM_ROCKMAN	BLOOD_DEFAULT/3
#define DAME_BULLET_GUTS_ROCKMAN	BLOOD_DEFAULT/3
#define DAME_BULLET_BALL			BLOOD_DEFAULT/9
#define DAME_BULLET_BOOM			BLOOD_DEFAULT/6
#define DAME_BULLET_MACHINE_AUTO	BLOOD_DEFAULT/9
#define DAME_BULLET_WALL_SHOOTER	BLOOD_DEFAULT/9
#define DAME_BULLET_WORKER			BLOOD_DEFAULT/7
#define DAME_ENEMY_HAT				(2*BLOOD_DEFAULT)/27
#define DAME_BOSS_CUTMAN			(2*BLOOD_DEFAULT)/27
#define DAME_SNAPPER				(2*BLOOD_DEFAULT)/27
#define DAME_ENEMY_BALL				BLOOD_DEFAULT/6
#define DAME_ENEMY_BUBBLE			BLOOD_DEFAULT/6
#define DAME_ENEMY_BOOM				BLOOD_DEFAULT/6
#define DAME_ENEMY_MACHINE_AUTO		BLOOD_DEFAULT/6
#define DAME_ENEMY_ROBOT			BLOOD_DEFAULT/1
#define DAME_ENEMY_WALL_SHOOTER		BLOOD_DEFAULT/6
#define DAME_ENEMY_WORKER			BLOOD_DEFAULT/6
#define DAME_ENEMY_INK				(2*BLOOD_DEFAULT)/27
#define DAME_ENEMY_EYE				(2*BLOOD_DEFAULT)/27
#define DAME_ENEMY_HAT				(2*BLOOD_DEFAULT)/27
#define DAME_ENEMY_MACHINE			(2*BLOOD_DEFAULT)/27
#define DAME_ENEMY_NINJA			(2*BLOOD_DEFAULT)/27
#define DAME_ENEMY_FISH				(2*BLOOD_DEFAULT)/27
#define DAME_ENEMY_SNAPPER			(2*BLOOD_DEFAULT)/27
#define DAME_BULLET_HAT				(2*BLOOD_DEFAULT)/27
#define DAME_BULLET_NINJA			(2*BLOOD_DEFAULT)/27
#define DAME_BULLET_SNAPPER			(2*BLOOD_DEFAULT)/27

#define BLOOD_ROCKMAN				BLOOD_DEFAULT
#define BLOOD_CUTMAN				BLOOD_DEFAULT
#define BLOOD_BOOMMAN				BLOOD_DEFAULT
#define BLOOD_GUTSMAN				BLOOD_DEFAULT
#define BLOOD_ENEMY_BALL			DAME_BULLET_ROCKMAN*1
#define BLOOD_ENEMY_BUBBLE			DAME_BULLET_ROCKMAN*1
#define BLOOD_ENEMY_BOOM			DAME_BULLET_ROCKMAN*1
#define BLOOD_ENEMY_MACHINE_AUTO	DAME_BULLET_ROCKMAN*3
#define BLOOD_ENEMY_ROBOT			DAME_BULLET_ROCKMAN*20
#define BLOOD_ENEMY_WALL_SHOOTER	DAME_BULLET_ROCKMAN*1
#define BLOOD_ENEMY_WORKER			DAME_BULLET_ROCKMAN*5

#pragma endregion

enum class DIRECTIONACTION {
	RUNLEFT,
	RUNRIGHT,
	JUMPLEFT,
	JUMPRIGHT,
	STARTJUMP,
	DOWNLEFT,
	DOWNRIGHT,
	STANDLEFT,
	STANDRIGHT,
	START,
	STOSP,
	DIE,
};

enum class STTBOOM{
	DROPP,
	EXPLOSIVE,
	FIRE,
	NONE,
	START,
};
//86-c1 
//10108

#define ID_SPRITE_ENEMY_NINJA_STAND       1312
#define ID_SPRITE_ENEMY_NINJA_JUMP    1313
#define ID_SPRITE_ENEMY_NINJA_FIRE    1314