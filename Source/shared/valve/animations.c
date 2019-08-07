/***
*
*	Copyright (c) 2016-2019 Marco 'eukara' Hladik. All rights reserved.
*
*	See the file LICENSE attached with the sources for usage details.
*
****/

.float frame_time;
.float frame_old;
.float fWasCrouching;

// For lerping, sigh
#ifdef CSQC
.float frame_last;
.float baseframe_last;
#else
.float subblend2frac;
#endif

void Animation_Print( string sWow ) {
#ifdef CSQC
	print( sprintf( "[DEBUG] %s", sWow ) );
#else 
	bprint(PRINT_HIGH, sprintf( "SSQC: %s", sWow )  );
#endif	
}

/*
=================
Animation_PlayerUpdate

Called every frame to update the animation sequences
depending on what the player is doing
=================
*/
void Animation_PlayerUpdate( void ) {
	self.basebone = 16;
#ifdef SSQC
	// TODO: Make this faster
	if ( self.frame_time < time ) {
		player pl = (player)self;
		self.frame = Weapons_GetAim(pl.activeweapon);
		self.frame_old = self.frame;
	}
	
	if ( !( self.flags & FL_ONGROUND ) ) {
		self.baseframe = ANIM_JUMP;
	} else if ( vlen( self.velocity ) == 0 ) {
		if ( self.flags & FL_CROUCHING ) {
			self.baseframe = ANIM_CROUCHIDLE;
		} else {
			self.baseframe = ANIM_IDLE;
		}
	} else if ( vlen( self.velocity ) < 150 ) {
		if ( self.flags & FL_CROUCHING ) {
			self.baseframe = ANIM_CRAWL;
		} else {
			self.baseframe = ANIM_WALK;
		}
	} else if ( vlen( self.velocity ) > 150 ) {
		if ( self.flags & FL_CROUCHING ) {
			self.baseframe = ANIM_CRAWL;
		} else {
			self.baseframe = ANIM_RUN;
		}
	}
#endif

#ifdef CSQC
	// Lerp it down!
	if ( self.lerpfrac > 0 ) {
		self.lerpfrac -= frametime * 5;
		if ( self.lerpfrac < 0 ) {
			self.lerpfrac = 0;
		}
	}

	if ( self.baselerpfrac > 0 ) {
		self.baselerpfrac -= frametime * 5;
		if ( self.baselerpfrac < 0 ) {
			self.baselerpfrac = 0;
		}
	}

	if ( self.frame != self.frame_last ) {
		//Animation_Print( sprintf( "New Frame: %d, Last Frame: %d\n", self.frame, self.frame_last ));
		
		// Move everything over to frame 2
		self.frame2time = self.frame1time;
		self.frame2 = self.frame_last;
		
		// Set frame_last to avoid this being called again
		self.frame_last = self.frame;
		
		self.lerpfrac = 1.0f;
		self.frame1time = 0.0f;
	}
	
	if ( self.baseframe != self.baseframe_last ) {
		//Animation_Print( sprintf( "New Baseframe: %d, Last Baseframe: %d\n", self.baseframe, self.baseframe_last ) );
		
		// Move everything over to frame 2
		self.baseframe2time = self.baseframe1time;
		self.baseframe2 = self.baseframe_last;
		
		// Set frame_last to avoid this being called again
		self.baseframe_last = self.baseframe;
		
		self.baselerpfrac = 1.0f;
		self.baseframe1time = 0.0f;
	}
	
	self.bonecontrol1 = self.angles[0];
#endif
	self.angles[0] = self.angles[2] = 0;
	
	if ( !( self.flags & FL_ONGROUND ) ) {
		/*self.frame = ANIM_JUMP;*/
	}
	
	// Force the code above to update if we switched positions
	if ( self.fWasCrouching != ( self.flags & FL_CROUCHING ) ) {
		self.frame_old = 0;
		self.frame_time = 0;
		self.fWasCrouching = ( self.flags & FL_CROUCHING );
	}

#ifdef SSQC
	// On the CSQC it's done in Player.c
	self.subblend2frac = self.v_angle[0] / 90;
#endif
}

/*
=================
Animation_PlayerTop

Changes the animation sequence for the upper body part
=================
*/
void Animation_PlayerTop( float fFrame ) {
	self.frame = fFrame;
	self.frame_old = fFrame;
}

void Animation_PlayerTopTemp( float fFrame, float fTime ) {
	self.frame = fFrame;
	self.frame_time = time + fTime;
}