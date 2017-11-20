/*
OpenCS Project
Copyright (C) 2016, 2017 Marco "eukara" Hladik

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#pragma target FTE
//#pragma flag enable lo	//enable short-circuiting

#define VEC_HULL_MIN '-16 -16 -36'
#define VEC_HULL_MAX '16 16 36'

#define VEC_CHULL_MIN '-16 -16 -18'
#define VEC_CHULL_MAX '16 16 18'

#define PLAYER_SENDFLAG_UPDATE 1
#define PLAYER_SENDFLAG_INGAME 2

string sCSPlayers[ 9 ] = {
	"",
	"models/player/terror/terror.mdl",
	"models/player/leet/leet.mdl",
	"models/player/arctic/arctic.mdl",
	"models/player/guerilla/guerilla.mdl",
	"models/player/urban/urban.mdl",
	"models/player/gsg9/gsg9.mdl",
	"models/player/sas/sas.mdl",
	"models/player/gign/gign.mdl"
};

// Stuff that applies to all codebases
enum {
	TEAM_SPECTATOR,
	TEAM_T,
	TEAM_CT,
	TEAM_VIP
};

enum { 
	STAT_BUYZONE = 34,
	STAT_HOSTAGEZONE,
	STAT_BOMBZONE,
	STAT_MONEY,
	STAT_FLAGS,
	STAT_SLOT_MELEE,
	STAT_SLOT_PRIMARY,
	STAT_SLOT_SECONDARY,
	STAT_SLOT_GRENADE,
	STAT_EQUIPMENT,
	STAT_ITEM_FLASHBANG,
	STAT_ITEM_HEGRENADE,
	STAT_ITEM_SMOKEGRENADE,
	STAT_CURRENT_MAG,
	STAT_CURRENT_CALIBER,
	STAT_PROGRESS,
	STAT_TEAM,
	STAT_GAMETIME,
	STAT_GAMESTATE,
	STAT_WON_T,
	STAT_WON_CT
};

enum {
	ENT_PLAYER = 1,
	ENT_AMBIENTSOUND,
	ENT_SPRITE
};

enum {
	GAME_INACTIVE,
	GAME_COMMENCING,
	GAME_FREEZE,
	GAME_ACTIVE,
	GAME_END
};

#define CS_WEAPON_COUNT 28
enum {
	WEAPON_NONE = 0,
	WEAPON_KNIFE,
	WEAPON_USP45,
	WEAPON_GLOCK18,
	WEAPON_DEAGLE,
	WEAPON_P228,
	WEAPON_ELITES,
	WEAPON_FIVESEVEN,
	WEAPON_M3,
	WEAPON_XM1014,
	WEAPON_MP5,
	WEAPON_P90,
	WEAPON_UMP45,
	WEAPON_MAC10,
	WEAPON_TMP,
	WEAPON_AK47,
	WEAPON_SG552,
	WEAPON_M4A1,
	WEAPON_AUG,
	WEAPON_SCOUT,
	WEAPON_AWP,
	WEAPON_G3SG1,
	WEAPON_SG550,
	WEAPON_PARA,
	WEAPON_C4BOMB,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE
};

#define CS_EQUIPMENT_COUNT 		7
#define EQUIPMENT_KEVLAR 		1
#define EQUIPMENT_HELMET 		2
#define EQUIPMENT_DEFUSALKIT 	4
#define EQUIPMENT_NIGHTVISION 	8

enum {
	CALIBER_50AE = 1,
	CALIBER_762MM,
	CALIBER_556MM,
	CALIBER_556MMBOX,
	CALIBER_338MAG,
	CALIBER_9MM,
	CALIBER_BUCKSHOT,
	CALIBER_45ACP,
	CALIBER_357SIG,
	CALIBER_57MM,
	EXPLOSIVE_C4,
	EXPLOSIVE_SMOKE,
	EXPLOSIVE_HE,
	EXPLOSIVE_FLASH,
};

.int iAmmo_50AE;
.int iAmmo_762MM;
.int iAmmo_556MM;
.int iAmmo_556MMBOX;
.int iAmmo_338MAG;
.int iAmmo_9MM;
.int iAmmo_BUCKSHOT;
.int iAmmo_45ACP;
.int iAmmo_357SIG;
.int iAmmo_57MM;

// Weapon types
enum {
	TYPE_SEMI,
	TYPE_AUTO
};

// Slot types
enum { 
	SLOT_PRIMARY,
	SLOT_SECONDARY,
	SLOT_MELEE,
	SLOT_GRENADE
};

// These variables are taken from CS:S' .ctx script files, usually and interpreted as I go along...
typedef struct {
	int iWeaponID; 	// Identifier
	int iSlot;
	int iPrice;		
	int iCaliber;
	float fSpeedM;
	
	int iBullets;	// How many bullets does it shoot?
	int iMagSize;	// How big is the clip/magazine?
	
	int iDamage;	// How much damage is done by a single bullet?
	int iPenetration;	// Penetration multiplier
	
	float fRange;	// Max distance of the bullet trace
	float fRangeModifier;	// ???
	
	float fWeaponType;
	float fAttackFinished; 
	float fReloadFinished;
	
	.int iCaliberfld;	// Pointer towards the caliberfield of the gun
	.int iMagfld;		// Pointer towards the clip of the gun
	
	float fAccuracyDivisor;
	float fAccuracyOffset;
	float fMaxInaccuracy;
	
	int iCrosshairMinDistance;	// Some weapons just are inaccurate by design... 
	int iCrosshairDeltaDistance;	// Scale factor of sorts
	float fWeaponArmorRatio; // Some weapons seem to do more damage to the kevlar than others I guess
	float fAnimType;
	int iShellType;	// Type of shell the weapon ejects
} weaponinfo_t;

enum {
	SHELL_PISTOL,
	SHELL_RIFLE,
	SHELL_RIFLEBIG,
	SHELL_SHOTGUN
};

typedef struct {
	int iID;
	int iPrice;
} equipmentinfo_t;

typedef struct {
	int iSize;
	int iMaxAmount;
	int iPrice;
} ammoinfo_t;

typedef struct {
	void() vDraw;
	void() vPrimary;
	void() vSecondary;
	void() vReload;
} weaponfunc_t;

// Network Events
enum {
	EV_WEAPON_DRAW,
	EV_WEAPON_PRIMARYATTACK,
	EV_WEAPON_SECONDARYATTACK,
	EV_WEAPON_RELOAD,
	EV_IMPACT,
	EV_EXPLOSION,
	EV_SPARK,
	EV_SMOKE,
	EV_FLASH,
	EV_MODELGIB,
	EV_CAMERATRIGGER,
	EV_RADIOMSG,
	EV_RADIOMSG2,
	EV_ORBITUARY,
	EV_CHAT,
	EV_CHAT_TEAM,
	EV_CHAT_VOX
};

// Submodel materials
enum { 
	MATERIAL_GLASS = 0, 
	MATERIAL_WOOD, 
	MATERIAL_METAL, 
	MATERIAL_FLESH, 
	MATERIAL_CINDER, 
	MATERIAL_TILE, 
	MATERIAL_COMPUTER, 
	MATERIAL_GLASS_UNBREAKABLE, 
	MATERIAL_ROCK, 
	MATERIAL_NONE	
};

// Impact types
enum { 
	IMPACT_MELEE = 0, 
	IMPACT_EXPLOSION, 
	IMPACT_DEFAULT, 
	IMPACT_GLASS, 
	IMPACT_WOOD, 
	IMPACT_METAL, 
	IMPACT_FLESH,
	IMPACT_ROCK,
};

// Animation types
enum {
	ATYPE_ONEHAND,
	ATYPE_DUALPISTOLS,
	ATYPE_CARBINE,
	ATYPE_RIFLE,
	ATYPE_MP5,
	ATYPE_SHOTGUN,
	ATYPE_PARA,
	ATYPE_GRENADE,
	ATYPE_C4,
	ATYPE_KNIFE,
	ATYPE_AK47
};

// Actually used by input_button etc.
#define INPUT_BUTTON0 1
#define INPUT_BUTTON2 2
#define INPUT_BUTTON3 4
#define INPUT_BUTTON4 8
#define INPUT_BUTTON5 16
#define INPUT_BUTTON6 32

#define FL_USERELEASED 	(1<<13)
#define FL_CROUCHING 	(1<<19)
#define FL_SEMI_TOGGLED (1<<15)
#define FL_FROZEN 	(1<<17)
#define FL_REMOVEME	(1<<18)

#define clamp(d,min,max) bound(min,d,max)

void Empty( void ) { }
void BaseGun_ShotMultiplierHandle( float fShots );
