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

/*
=================
HUD_DrawCrosshair

Draws the cursor every frame, unless spectator
=================
*/
void HUD_DrawCrosshair( void ) {	
	int iCrosshairDistance;
	int iLineLength;
	
	// Weapon Info Tables have got Mins and Deltas they are willing to share
	float fDistance = wptTable[ getstatf( STAT_ACTIVEWEAPON ) ].iCrosshairMinDistance; 
	float fDeltaDistance = wptTable[ getstatf( STAT_ACTIVEWEAPON ) ].iCrosshairDeltaDistance;
	
	if ( iNightVision == FALSE ) {
		vCrossColor = autocvar_cross_color * ( 1 / 255 );
	} else {
		vCrossColor = '1 0 0';
	}
	
	if ( !( getstatf( STAT_FLAGS ) & FL_ONGROUND) ) { // If we are in the air...
		fDistance = fDistance * 2;
	} else if ( getstatf( STAT_FLAGS ) & FL_CROUCHING ) { // Crouching...
		fDistance = fDistance * 0.5;
	} else if ( vlen( pSeat->ePlayer.velocity ) > 120 ) { // Running, not walking
		fDistance = fDistance * 1.5;
	}
	
	// The amount of shots that we've shot totally does affect our accuracy!
	if ( pSeat->iShotMultiplier > pSeat->iOldShotMultiplier ) {
		pSeat->fCrosshairDistance = min( 15, pSeat->fCrosshairDistance + fDeltaDistance );
	} else if ( pSeat->fCrosshairDistance > fDistance ) {
		// Slowly decrease the distance again
		pSeat->fCrosshairDistance -= ( pSeat->fCrosshairDistance * frametime );
		
		if ( ( pSeat->iShotMultiplier > 0 ) && ( pSeat->fDecreaseShotTime < time ) ) {
			pSeat->fDecreaseShotTime = time + 0.2;
			pSeat->iShotMultiplier--;
		}
	}
	
	pSeat->iOldShotMultiplier = pSeat->iShotMultiplier;
	
	if ( pSeat->fCrosshairDistance < fDistance ) {
		 pSeat->fCrosshairDistance = fDistance;
	}

	iCrosshairDistance = ceil( pSeat->fCrosshairDistance );
	iLineLength = ( ( iCrosshairDistance - fDistance ) / 2 ) + 5;

	iLineLength = max( 1, iLineLength );
	
	// Line positions
	vector vVer1, vVer2, vHor1, vHor2;
	vVer1 = vVer2 = vHor1 = vHor2 = vVideoMins;
	
	// Vertical Lines
	vVer1_x += ( vVideoResolution_x / 2 );
	vVer1_y += ( vVideoResolution_y / 2 ) - ( iCrosshairDistance + iLineLength );
	vVer2_x += ( vVideoResolution_x / 2 );
	vVer2_y += ( vVideoResolution_y / 2 ) + iCrosshairDistance + 1;
	
	// Horizontal Lines
	vHor1_x += ( vVideoResolution_x / 2 ) - ( iCrosshairDistance + iLineLength );
	vHor1_y += ( vVideoResolution_y / 2 );
	vHor2_x += ( vVideoResolution_x / 2 ) + iCrosshairDistance + 1;
	vHor2_y += ( vVideoResolution_y / 2 );

	drawfill( vVer1, [ 1, iLineLength ], vCrossColor, 1, DRAWFLAG_ADDITIVE );
	drawfill( vVer2, [ 1, iLineLength ], vCrossColor, 1, DRAWFLAG_ADDITIVE );
	drawfill( vHor1, [ iLineLength, 1 ], vCrossColor, 1, DRAWFLAG_ADDITIVE );
	drawfill( vHor2, [ iLineLength, 1 ], vCrossColor, 1, DRAWFLAG_ADDITIVE );
}
