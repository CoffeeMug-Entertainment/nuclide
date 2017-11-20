/*
FreeCS Project
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

.int iMag_M3;

#ifdef SSQC
.int iMode_M3;
#else
int iWeaponMode_M3;
#endif

// Weapon Info
weaponinfo_t wptM3 = { 
	WEAPON_M3, 			// Identifier
	SLOT_PRIMARY,		// Slot
	1700, 				// Price
	CALIBER_BUCKSHOT, 	// Caliber ID
	0.92, 				// Max Player Speed
	9, 					// Bullets Per Shot
	8, 					// Clip/MagSize
	26, 				// Damage Per Bullet
	1, 					// Penetration Multiplier
	3000, 				// Bullet Range
	0.7, 				// Range Modifier
	TYPE_SEMI,			// Firing Type
	1.0, 				// Attack-Delay
	3.0, 				// Reload-Delay
	iAmmo_BUCKSHOT, 	// Caliber Pointer
	iMag_M3, 			// Clip Pointer
	200,				// Accuracy Divisor
	0.35,				// Accuracy Offset
	1.25,				// Max Inaccuracy
	8,					// Minimum Crosshair Distance
	6,					// Crosshair Movement Delta
	1.0,				// Armor penetration ratio
	ATYPE_SHOTGUN,		// Animation Type
	SHELL_SHOTGUN
};

// Anim Table
enum {
	ANIM_M3_IDLE,
	ANIM_M3_SHOOT1,
	ANIM_M3_SHOOT2,
	ANIM_M3_INSERT,
	ANIM_M3_RELOAD_END,
	ANIM_M3_RELOAD_START,
	ANIM_M3_DRAW
};

void WeaponM3_Draw( void ) {
	#ifdef SSQC
	BaseGun_Draw();
	#else
	View_PlayAnimation( ANIM_M3_DRAW );
	#endif
}

void WeaponM3_ReloadNULL( void ) { }

void WeaponM3_PrimaryFire( void ) {
#ifdef SSQC
	if ( self.iMode_M3 == TRUE ) {
		self.iMode_M3 = 0;
		Client_SendEvent( self, EV_WEAPON_RELOAD );
		self.think = WeaponM3_ReloadNULL;
		self.fAttackFinished = time + 1.0;
		return;
	}
	
	if ( BaseGun_PrimaryFire() == TRUE ) {
		sound( self, CHAN_WEAPON, "weapons/m3-1.wav", 1, ATTN_NORM );
	}
#else
	if ( random() <= 0.5 ) {
		View_PlayAnimation( ANIM_M3_SHOOT1 );
	} else {
		View_PlayAnimation( ANIM_M3_SHOOT2 );
	}
	BaseGun_ShotMultiplierHandle( 1 );
#endif
}

// The gun has no real secondary mode, but part of the reloading uses this function
// mainly for client-side cosmetics. The server doesn't have a function telling
// the client to switch animations (we save 1 byte in networking by reusing this)
void WeaponM3_Reload( void);
void WeaponM3_Secondary( void ) {
#ifdef SSQC
	// If it's full or no ammo is left...
	if ( (self.(wptM3.iMagfld) == wptM3.iMagSize) || ( self.(wptM3.iCaliberfld) <= 0 ) ) {
		self.iMode_M3 = 0;
		Client_SendEvent( self, EV_WEAPON_RELOAD );
		self.think = WeaponM3_ReloadNULL;
		self.fAttackFinished = time + 1.0;
		return;
	}
	
	self.(wptM3.iMagfld) += 1;
	self.(wptM3.iCaliberfld) -= 1;
	
	Client_SendEvent( self, EV_WEAPON_SECONDARYATTACK );
	
	self.think = WeaponM3_Secondary;
	self.nextthink = time + 0.5;
#else
	View_PlayAnimation( ANIM_M3_INSERT );
#endif
}

void WeaponM3_Reload( void ) {
#ifdef SSQC
	// Can we reload the gun even if we wanted to?
	if ( ( self.(wptM3.iMagfld) != wptM3.iMagSize ) && ( self.(wptM3.iCaliberfld) > 0 ) ) {
		self.iMode_M3 = 1 - self.iMode_M3;
			
		if ( self.iMode_M3 == TRUE ) {
			self.think = WeaponM3_Secondary;
			self.nextthink = time + 0.8;
		} else {
			self.think = WeaponM3_ReloadNULL;
		}
			
		Client_SendEvent( self, EV_WEAPON_RELOAD );
		self.fAttackFinished = time + 1.0;
	}
#else
	iWeaponMode_M3 = 1 - iWeaponMode_M3;
	
	if ( iWeaponMode_M3 == TRUE ) {
		View_PlayAnimation( ANIM_M3_RELOAD_START );
	} else {
		View_PlayAnimation( ANIM_M3_RELOAD_END );
	}
#endif
}
