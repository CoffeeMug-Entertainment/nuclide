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

string sViewModels[ CS_WEAPON_COUNT - 1 ] = {
	"models/v_knife.mdl",
	"models/v_usp.mdl",
	"models/v_glock18.mdl",
	"models/v_deagle.mdl",
	"models/v_p228.mdl",
	"models/v_elite.mdl",
	"models/v_fiveseven.mdl",
	"models/v_m3.mdl",
	"models/v_xm1014.mdl",
	"models/v_mp5.mdl",
	"models/v_p90.mdl",
	"models/v_ump45.mdl",
	"models/v_mac10.mdl",
	"models/v_tmp.mdl",
	"models/v_ak47.mdl",
	"models/v_sg552.mdl",
	"models/v_m4a1.mdl",
	"models/v_aug.mdl",
	"models/v_scout.mdl",
	"models/v_awp.mdl",
	"models/v_g3sg1.mdl",
	"models/v_sg550.mdl",
	"models/v_m249.mdl",
	"models/v_c4.mdl",
	"models/v_flashbang.mdl",
	"models/v_hegrenade.mdl",
	"models/v_smokegrenade.mdl"
};

/*
====================
View_CalcBob
====================
*/
void View_CalcBob( void ) {
	float fCycle;

	vector vVelocity;
	
	if ( self.flags & FL_ONGROUND == -1 ) {
		return;	
	}

	pSeat->fBobTime += frametime;
	fCycle = pSeat->fBobTime - (int)( pSeat->fBobTime / autocvar_v_bobcycle ) * autocvar_v_bobcycle;
	fCycle /= autocvar_v_bobcycle;
	
	if ( fCycle < autocvar_v_bobup ) {
		fCycle = MATH_PI * fCycle / autocvar_v_bobup;
	} else {
		fCycle = MATH_PI + MATH_PI * ( fCycle - autocvar_v_bobup )/( 1.0 - autocvar_v_bobup );
	}

	vVelocity = pSeat->vPlayerVelocity;
	vVelocity_z = 0;

	float fBob = sqrt( vVelocity_x * vVelocity_x + vVelocity_y * vVelocity_y ) * autocvar_v_bob;
	fBob = fBob * 0.3 + fBob * 0.7 * sin( fCycle );
	pSeat->fBob = bound( -7, fBob, 4 );
}

/*
====================
View_DropPunchAngle

Quickly lerp to the original viewposition
====================
*/
void View_DropPunchAngle( void ) {
	float fLerp;
	fLerp = 1.0f - ( frametime * 4 );
	pSeat->vPunchAngle *= fLerp;
}

/*
====================
View_AddPunchAngle

Gives the angle a bit of an offset/punch/kick
====================
*/
void View_AddPunchAngle( vector vAdd ) {
	pSeat->vPunchAngle += vAdd;
}

/*
====================
View_ShellEject

Spawns a shell tempentity. Looking fancy
====================
*/
void View_ShellEject( void ) {
	static void View_ShellEject_Death( void ) {
		remove( self );	
	}
	vector vOrigin = pSeat->vPlayerOrigin;
	vector vEndPos = gettaginfo( pSeat->eViewModel, pSeat->fEjectBone );
	makevectors( view_angles );
	
	vOrigin += ( v_forward * vEndPos_x ) + ( v_right * -vEndPos_y ) + ( v_up * vEndPos_z ) + [ 0, 0, getstatf( STAT_VIEWHEIGHT ) ];
	
	entity eShell = spawn();
	setorigin( eShell, vOrigin );
	setmodel( eShell, sShellModel[ wptTable[ getstati( STAT_ACTIVEWEAPON ) ].iShellType ] );
	eShell.movetype = MOVETYPE_BOUNCE;
	eShell.drawmask = MASK_ENGINE;
	eShell.angles = [ 0, view_angles_y, 0 ];
	eShell.velocity = pSeat->vPlayerVelocity + ( v_up * random( 70, 120 ) ) + ( v_right * -random( 50, 70 ) );
	eShell.think = View_ShellEject_Death;
	eShell.nextthink = time + 2.5f; 
}

/*
====================
View_ProcessEvent

Called by the engine whenever a model
tries to play an event.
====================
*/
void View_ProcessEvent( float fTimeStamp, int iCode, string sData ) {
	if ( iCode == 5004 ) {
		localsound( sData, CHAN_AUTO, 1.0 );
	} else if ( iCode == 5001 ) {
		pSeat->eMuzzleflash.alpha = 1.0f;
		pSeat->eMuzzleflash.scale = 0.5;
		pSeat->eMuzzleflash.skin = pSeat->fNumBones;
		setmodel( pSeat->eMuzzleflash, sprintf( "sprites/muzzleflash%s.spr", substring( sData, 1, 1 ) ) );
		View_ShellEject();
	} else if( iCode == 5011 ) {
		pSeat->eMuzzleflash.alpha = 1.0f;
		pSeat->eMuzzleflash.scale = 0.5;
		pSeat->eMuzzleflash.skin = pSeat->fNumBones + 1;
		setmodel( pSeat->eMuzzleflash, sprintf( "sprites/muzzleflash%s.spr", substring( sData, 1, 1 ) ) );
		View_ShellEject();
	} else if ( iCode == 5021 ) {
		pSeat->eMuzzleflash.alpha = 1.0f;
		pSeat->eMuzzleflash.scale = 0.5;
		pSeat->eMuzzleflash.skin = pSeat->fNumBones + 2;
		setmodel( pSeat->eMuzzleflash, sprintf( "sprites/muzzleflash%s.spr", substring( sData, 1, 1 ) ) );
		View_ShellEject();
	} else if ( iCode == 5031 ) {
		pSeat->eMuzzleflash.alpha = 1.0f;
		pSeat->eMuzzleflash.scale = 0.5;
		pSeat->eMuzzleflash.skin = pSeat->fNumBones + 3;
		setmodel( pSeat->eMuzzleflash, sprintf( "sprites/muzzleflash%s.spr", substring( sData, 1, 1 ) ) );
		View_ShellEject();
	}
}

/*
====================
View_DrawViewModel

Really convoluted function that makes the gun,
muzzleflash, dynamic lights and so on appear
====================
*/
void View_DrawViewModel( void ) {
	if( !pSeat->eViewModel ) {
		pSeat->eViewModel = spawn();
		pSeat->eViewModel.classname = "view model";
		pSeat->eViewModel.renderflags = RF_VIEWMODEL | RF_DEPTHHACK;
		
		pSeat->eMuzzleflash = spawn();
		pSeat->eMuzzleflash.classname = "view muzzleflash";
		pSeat->eMuzzleflash.renderflags = RF_VIEWMODEL | RF_DEPTHHACK | RF_ADDITIVE;
	}
	entity eViewModel = pSeat->eViewModel;
	entity eMuzzleflash = pSeat->eMuzzleflash;

	if ( getstatf( STAT_HEALTH ) <= 0 ) {
		return;
	}

	// Don't update when paused
	if ( serverkey( "pausestate" ) == "0" ) {
		View_CalcBob();

		int aw = getstati( STAT_ACTIVEWEAPON );
		if( aw < CS_WEAPON_COUNT ) {
			if ( pSeat->fLastWeapon != aw ) {
				pSeat->fLastWeapon = aw;
				if ( aw >= 1 ) {
					setmodel( eViewModel, sViewModels[ aw - 1 ] );
					skel_delete( eMuzzleflash.skeletonindex );
					eMuzzleflash.skeletonindex = skel_create( eViewModel.modelindex );
					pSeat->fNumBones = skel_get_numbones( eMuzzleflash.skeletonindex ) + 1;
					pSeat->fEjectBone = pSeat->fNumBones + 1;
				}
			}
		}

		// Take away alpha once it has drawn fully at least once
		if ( eMuzzleflash.alpha > 0.0f ) {
			eMuzzleflash.alpha -= ( frametime * 45 );			
		}

		float fBaseTime = eViewModel.frame1time;
		eViewModel.frame1time += frametime;
		eViewModel.frame2time += frametime;
		processmodelevents( eViewModel.modelindex, eViewModel.frame, fBaseTime, eViewModel.frame1time, View_ProcessEvent );
	}
	
	makevectors( '0 0 0');
	eViewModel.origin = '0 0 -1' + ( v_forward * ( pSeat->fBob * 0.4 ) );
	
	// Left-handed weapons
	if ( autocvar_v_lefthanded ) {
		v_right *= -1;
		eViewModel.renderflags |= RF_USEAXIS;
		eViewModel.forceshader = SHADER_CULLED;
	} else {
		if ( eViewModel.forceshader ) {
			eViewModel.forceshader = 0;
			eViewModel.renderflags -= RF_USEAXIS;
		}
	}
	
	// Give the gun a tilt effect like in old HL/CS versions
	if ( autocvar_v_bobclassic == 1 ) {
		eViewModel.angles_z = -pSeat->fBob;
	}

	// Only bother when zoomed out
	if ( getstatf( STAT_VIEWZOOM ) == 255 ) {
		// Update muzzleflash position and draw it
		if ( eMuzzleflash.alpha > 0.0f ) {
			eMuzzleflash.origin = gettaginfo( eViewModel, eMuzzleflash.skin );
			dynamiclight_add( pSeat->vPlayerOrigin, 400 * eMuzzleflash.alpha, '1 0.45 0');
			addentity( eMuzzleflash );
		}
		addentity( eViewModel );
	}
}

/*
====================
View_PlayAnimation

Resets the timeline and plays a new sequence
onto the view model
====================
*/
void View_PlayAnimation( int iSequence ) {
	pSeat->eViewModel.frame = (float)iSequence;
	pSeat->eViewModel.frame1time = 0.0f;
}
