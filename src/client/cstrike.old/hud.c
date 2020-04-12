/*
 * Copyright (c) 2016-2019 Marco Hladik <marco@icculus.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define HUD_NUMFILE "sprites/640hud7.spr" // We'll precache this
#define HUD_NUMFILE_LAYER "sprites/640hud7.spr_0.tga" // And only use the first frame for drawing (needs precache)

// Sigh
#define NUMSIZE_X 0.09375
#define NUMSIZE_Y 0.09765625

#define HUD_ALPHA 0.5

// Instead of calculating them on demand, just read the offsets here
float vHUDNumPos[10] = {
	0,
	0.09375,
	0.1875,
	0.28125,
	0.375,
	0.46875,
	0.5625,
	0.65625,
	0.75,
	0.84375
};

// Ditto
vector vHUDCalPos[15] = {
	[0, 0],
	[0.09375, 0.28125],		// 50AE
	[0.28125, 0.28125],		// 762MM
	[0, 0.375],				// 556MM
	[0, 0.375],				// 556MM
	[0.09375, 0.375],		// 338MAG
	[0.1875, 0.28125],		// 9MM
	[0, 0.28125],			// BUCKSHOT
	[0.375, 0.28125],		// 45ACP
	[0.46875, 0.28125],		// 357SIG
	[0.46875, 0.375],		// 57MM
	[0.375, 0.375],			// C4
	[0.5625, 0.375],		// SMOKE
	[0.28125, 0.375],		// HE
	[0.1875, 0.375]			// FLASH
};

void HUD_Init(void)
{
	precache_model(HUD_NUMFILE);
	precache_model("sprites/top_left.spr");
	precache_model("sprites/top.spr");
	precache_model("sprites/top_right.spr");
	precache_model("sprites/left.spr");
	precache_model("sprites/right.spr");
	precache_model("sprites/bottom_left.spr");
	precache_model("sprites/bottom.spr");
	precache_model("sprites/bottom_right.spr");
	precache_model("sprites/sniper_scope.spr");
	precache_model("sprites/radar640.spr");
	precache_model("sprites/640hud1.spr");
	precache_model("sprites/640hud16.spr");
	precache_model("sprites/640hud2.spr");
	precache_model("sprites/640hud10.spr");
	precache_model("sprites/640hud12.spr");
	precache_model("sprites/640hud14.spr");
	precache_model("sprites/640hud3.spr");
	precache_model("sprites/640hud5.spr");
}

/*
=================
HUD_DrawRedNumber

Draws a normal number
=================
*/
void HUD_DrawNumber(int iNumber, vector vecPos, float fAlpha, vector vColor) {
	drawsubpic(vecPos, [24,25], HUD_NUMFILE_LAYER, [vHUDNumPos[iNumber], 0], [NUMSIZE_X, NUMSIZE_Y], vColor, fAlpha, DRAWFLAG_ADDITIVE);
}

/*
=================
HUD_DrawNums

Draws numerals quickly for health, armor etc.
=================
*/
void HUD_DrawNums(float fNumber, vector vecPos, float fAlpha, vector vColor) {
	int iNumber = fNumber;
	if (iNumber > 0) {
		while (iNumber > 0) {
			HUD_DrawNumber((float)iNumber % 10, vecPos, fAlpha, vColor);
			iNumber = iNumber / 10;
			vecPos[0] -= 20;
		} 
	} else {
		HUD_DrawNumber(0, vecPos, fAlpha, vColor);
	}
}

/*
=================
HUD_DrawHealth

Draw the current amount of health
=================
*/
void HUD_DrawHealth(void) {
	static float fOldHealth;
	static float fHealthAlpha;
	if (getstatf(STAT_HEALTH) != fOldHealth) {
		fHealthAlpha = 1.0;
	}
	
	if (fHealthAlpha >= HUD_ALPHA) {
		fHealthAlpha -= frametime * 0.5;
	} else {
		fHealthAlpha = HUD_ALPHA;
	}
	
	vector vHealthPos = video_mins + [16, video_res[1] - 42];
	if (getstatf(STAT_HEALTH) > 25) {
		drawsubpic(vHealthPos, [24, 24], HUD_NUMFILE_LAYER, [NUMSIZE_X * 2, NUMSIZE_Y], [NUMSIZE_X, NUMSIZE_X], vHUDColor, HUD_ALPHA, DRAWFLAG_ADDITIVE);
		HUD_DrawNums(getstatf(STAT_HEALTH), vHealthPos + [72, 0], HUD_ALPHA, vHUDColor);
	} else {
		drawsubpic(vHealthPos, [24, 24], HUD_NUMFILE_LAYER, [NUMSIZE_X * 2, NUMSIZE_Y], [NUMSIZE_X, NUMSIZE_X], [1,0,0], HUD_ALPHA, DRAWFLAG_ADDITIVE);
		HUD_DrawNums(getstatf(STAT_HEALTH), vHealthPos + [72, 0], HUD_ALPHA, [1,0,0]);
	}
	fOldHealth = getstatf(STAT_HEALTH);
}

/*
=================
HUD_DrawArmor

Draw the current amount of Kevlar
=================
*/
void HUD_DrawArmor(void) {
	static float fOldArmor;
	static float fArmorAlpha;
	if (getstatf(STAT_ARMOR) != fOldArmor) {
		fArmorAlpha = 1.0;
	}
	
	if (fArmorAlpha >= HUD_ALPHA) {
		fArmorAlpha -= frametime * 0.5;
	} else {
		fArmorAlpha = HUD_ALPHA;
	}
	
	vector vArmorPos = video_mins + [128, video_res[1] - 42];
	
	if (getstatf(STAT_EQUIPMENT) & EQUIPMENT_HELMET) {
		drawsubpic(vArmorPos, [24,24], HUD_NUMFILE_LAYER, [0, 0.4862745098], [NUMSIZE_X, NUMSIZE_X], vHUDColor, fArmorAlpha, DRAWFLAG_ADDITIVE);
	} else {
		drawsubpic(vArmorPos, [24,24], HUD_NUMFILE_LAYER, [0, NUMSIZE_Y], [NUMSIZE_X, NUMSIZE_X], vHUDColor, fArmorAlpha, DRAWFLAG_ADDITIVE);
	}

	HUD_DrawNums(getstatf(STAT_ARMOR), vArmorPos + [72,0], fArmorAlpha, vHUDColor);
	fOldArmor = getstatf(STAT_ARMOR);
}

/*
=================
HUD_DrawIcons

Draw icons such as hostage, bomb and buyzones
=================
*/
void HUD_DrawIcons(void) {
	vector iconpos;
	
	iconpos = video_mins + [16, (video_res[1] / 2) - 24];

	// Defusal Kit Icon (64, 148)
	if (getstatf(STAT_EQUIPMENT) & EQUIPMENT_DEFUSALKIT) {
		drawsubpic(iconpos, [32,32], HUD_NUMFILE_LAYER, [0.125, 0.578125], [0.125, 0.125], [0,1,0], 1, DRAWFLAG_ADDITIVE);
		iconpos[1] += 32;
	}

	// BuyZone Icon
	if (getstatf(STAT_BUYZONE) == TRUE) {
		drawsubpic(iconpos, [32,32], HUD_NUMFILE_LAYER, [0.125 * 3, 0.125 * 5 - 0.046875], [0.125, 0.125], [0,1,0], 1, DRAWFLAG_ADDITIVE);
		iconpos[1] += 32;
	}

	// Hostage-Rescue Area Icon
	if (getstatf(STAT_HOSTAGEZONE) == TRUE) {
		drawsubpic(iconpos, [32,32], HUD_NUMFILE_LAYER, [0.125 * 2, 0.125 * 5 - 0.046875], [0.125, 0.125], [0,1,0], 1, DRAWFLAG_ADDITIVE);
		iconpos[1] += 32;
	}

	// Escape Zone Icon (128, 148)
	if (getstatf(STAT_ESCAPEZONE) == TRUE) {
		drawsubpic(iconpos, [32,32], HUD_NUMFILE_LAYER, [0.5, 0.578125], [0.125, 0.125], [0,1,0], 1, DRAWFLAG_ADDITIVE);
		iconpos[1] += 32;
	}

	// VIP Zone Icon (160, 148)
	if (getstatf(STAT_VIPZONE) == TRUE) {
		drawsubpic(iconpos, [32,32], HUD_NUMFILE_LAYER, [0.625, 0.578125], [0.125, 0.125], [0,1,0], 1, DRAWFLAG_ADDITIVE);
		iconpos[1] += 32;
	}

	// Bomb-Area
	if (getstatf(STAT_SLOT_C4BOMB) == WEAPON_C4BOMB) {
		if (getstatf(STAT_BOMBZONE) == TRUE) {
			float fAlpha = fabs(sin(time * 20));
			drawsubpic(iconpos, [32,32], HUD_NUMFILE_LAYER, [0, 0.125 * 5 - 0.046875], [0.125, 0.125], [1,0,0], fAlpha, DRAWFLAG_ADDITIVE);
			drawsubpic(iconpos, [32,32], HUD_NUMFILE_LAYER, [0, 0.125 * 5 - 0.046875], [0.125, 0.125], [0,1,0], 1 - fAlpha, DRAWFLAG_ADDITIVE);
		} else {
			drawsubpic(iconpos, [32,32], HUD_NUMFILE_LAYER, [0, 0.125 * 5 - 0.046875], [0.125, 0.125], [0,1,0], 1, DRAWFLAG_ADDITIVE);
		}
		iconpos[1] += 32;
	}
}

/*
=================
HUD_DrawTimer

Draws the roundtime at the bottom of the screen (always visible)
=================
*/
void HUD_DrawTimer(void) {
	static int iOldUnits;
	static float fTimerAlpha;
	int iMinutes, iSeconds, iTens, iUnits;
	vector vTimePos = video_mins+[(video_res[0] / 2) - 62, video_res[1] - 42];

	if (getstatf(STAT_GAMETIME) == -1) {
		return;
	}

	iMinutes = getstatf(STAT_GAMETIME) / 60;
	iSeconds = getstatf(STAT_GAMETIME) - 60 * iMinutes;
	iTens = iSeconds / 10;
	iUnits = iSeconds - 10 * iTens;

	// Flashing red numbers
	if ((iMinutes == 0) &&  (iTens <= 1)) {
		float fAlpha;
		
		// 0:00 is fully red
		if ((iTens == 0) && (iUnits == 0)) {
			fAlpha = 1;
		} else {
			fAlpha = fabs(sin(time * 20));
		}
		
		HUD_DrawNumber(iMinutes, vTimePos + [48,0], fAlpha, [1,0,0]);
		HUD_DrawNumber(iTens, vTimePos + [75,0], fAlpha, [1,0,0]);
		HUD_DrawNumber(iUnits, vTimePos + [99,0],fAlpha, [1,0,0]);
		HUD_DrawNumber(iMinutes, vTimePos + [48,0], 1 - fAlpha, vHUDColor);
		HUD_DrawNumber(iTens, vTimePos + [75,0], 1 - fAlpha, vHUDColor);
		HUD_DrawNumber(iUnits, vTimePos + [99,0],1 - fAlpha, vHUDColor);
		
		// : symbol
		drawsubpic(vTimePos + [70,6], [3,3], HUD_NUMFILE_LAYER, [0.9375, 0], [0.01171875, 0.01171875], [1,0,0], fAlpha, DRAWFLAG_ADDITIVE);
		drawsubpic(vTimePos + [70,16], [3,3], HUD_NUMFILE_LAYER, [0.9375, 0], [0.01171875, 0.01171875], [1,0,0], fAlpha, DRAWFLAG_ADDITIVE);
		drawsubpic(vTimePos + [70,6], [3,3], HUD_NUMFILE_LAYER, [0.9375, 0], [0.01171875, 0.01171875], vHUDColor, 1 - fAlpha, DRAWFLAG_ADDITIVE);
		drawsubpic(vTimePos + [70,16], [3,3], HUD_NUMFILE_LAYER, [0.9375, 0], [0.01171875, 0.01171875], vHUDColor, 1 - fAlpha, DRAWFLAG_ADDITIVE);
		
		drawsubpic(vTimePos, [24,25], HUD_NUMFILE_LAYER, [NUMSIZE_X * 6, NUMSIZE_Y * 3], [NUMSIZE_X, NUMSIZE_Y], [1,0,0], fAlpha, DRAWFLAG_ADDITIVE);
		drawsubpic(vTimePos, [24,25], HUD_NUMFILE_LAYER, [NUMSIZE_X * 6, NUMSIZE_Y * 3], [NUMSIZE_X, NUMSIZE_Y], vHUDColor, 1 - fAlpha, DRAWFLAG_ADDITIVE);
	} else {
		if (iUnits != iOldUnits) {
			fTimerAlpha = 1.0;
		}
	
		if (fTimerAlpha >= HUD_ALPHA) {
			fTimerAlpha -= frametime * 0.5;
		} else {
			fTimerAlpha = HUD_ALPHA;
		}
		HUD_DrawNumber(iMinutes, vTimePos + [48,0], fTimerAlpha, vHUDColor);
		HUD_DrawNumber(iTens, vTimePos + [75,0], fTimerAlpha, vHUDColor);
		HUD_DrawNumber(iUnits, vTimePos + [95,0], fTimerAlpha, vHUDColor);
		
		drawsubpic(vTimePos + [70,6], [3,3], HUD_NUMFILE_LAYER, [0.9375, 0], [0.01171875, 0.01171875], vHUDColor, fTimerAlpha, DRAWFLAG_ADDITIVE);
		drawsubpic(vTimePos + [70,16], [3,3], HUD_NUMFILE_LAYER, [0.9375, 0], [0.01171875, 0.01171875], vHUDColor, fTimerAlpha, DRAWFLAG_ADDITIVE);
		
		drawsubpic(vTimePos, [24,25], HUD_NUMFILE_LAYER, [NUMSIZE_X * 6, NUMSIZE_Y * 3], [NUMSIZE_X, NUMSIZE_Y], vHUDColor, fTimerAlpha, DRAWFLAG_ADDITIVE);
		iOldUnits = iUnits;
	}
}

/*
=================
HUD_DrawMoney

Draws the amount of money (0-16000) with an icon to the screen
=================
*/
void HUD_DrawMoney(void) {
	static float fOldMoneyValue;
	static float fMoneyAlphaEffect;
	static vector vMoneyColorEffect;
	static float fMoneyDifference;

	// If the money differs from last frame, paint it appropriately
	if (getstatf(STAT_MONEY) > fOldMoneyValue) {
		// Effect already in progress from something else, go add on top of it!
		if (fMoneyAlphaEffect > 0) {
			fMoneyDifference += (fOldMoneyValue - getstatf(STAT_MONEY));
		} else {
			fMoneyDifference = fOldMoneyValue - getstatf(STAT_MONEY);
		}
		// Make it green for a short time
		vMoneyColorEffect = [0,1,0];
		fMoneyAlphaEffect = 1.0;
	} else if (getstatf(STAT_MONEY) < fOldMoneyValue) {
		// Same one as above
		if (fMoneyAlphaEffect > 0) {
			fMoneyDifference += (fOldMoneyValue - getstatf(STAT_MONEY));
		} else {
			fMoneyDifference = fOldMoneyValue - getstatf(STAT_MONEY);
		}
		// Make it red
		vMoneyColorEffect = [1,0,0];
		fMoneyAlphaEffect = 1.0;
		fMoneyDifference = fOldMoneyValue - getstatf(STAT_MONEY);
	}
	
	vector vMoneyPos = video_mins+[video_res[0] - 160, video_res[1] - 72];
	
	// If the alpha/color effect is active, draw the money twice in their varying alphas/colors
	if (fMoneyAlphaEffect > 0) {
		fMoneyAlphaEffect -= frametime * 0.5;
		drawsubpic(vMoneyPos, [18,25], HUD_NUMFILE_LAYER, [NUMSIZE_X * 8, NUMSIZE_Y * 1], [NUMSIZE_X * 0.75, NUMSIZE_Y], vMoneyColorEffect, fMoneyAlphaEffect, DRAWFLAG_ADDITIVE);
		drawsubpic(vMoneyPos, [18,25], HUD_NUMFILE_LAYER, [NUMSIZE_X * 8, NUMSIZE_Y * 1], [NUMSIZE_X * 0.75, NUMSIZE_Y], vHUDColor, HUD_ALPHA - (fMoneyAlphaEffect * 0.5), DRAWFLAG_ADDITIVE);
		
		// Draw the +/- symbols depending on whether or not we made or lost money
		if (fMoneyDifference < 0) {
			drawsubpic(vMoneyPos + [0,-32], [18,23], HUD_NUMFILE_LAYER, [0.8671875, 0.09765625], [0.0703125, 0.08984375], vMoneyColorEffect, fMoneyAlphaEffect, DRAWFLAG_ADDITIVE);
		} else {
			drawsubpic(vMoneyPos + [0,-32], [13,23], HUD_NUMFILE_LAYER, [0.8203125, 0.09765625], [0.05078125, 0.08984375], vMoneyColorEffect, fMoneyAlphaEffect, DRAWFLAG_ADDITIVE);
		}
		
		// Shift the numbers for reverse drawing
		vMoneyPos[0] += (24 * 5);
		
		// Draw the regular numbers at their normal positions
		HUD_DrawNums(getstatf(STAT_MONEY), vMoneyPos, fMoneyAlphaEffect, vMoneyColorEffect);
		HUD_DrawNums(getstatf(STAT_MONEY), vMoneyPos, HUD_ALPHA - (fMoneyAlphaEffect * 0.5), vHUDColor);
		
		// Draw above how much money we've gotten from all this
		HUD_DrawNums(fabs(fMoneyDifference), vMoneyPos + [0,-32], fMoneyAlphaEffect, vMoneyColorEffect);
	} else {
		drawsubpic(vMoneyPos, [18,25], HUD_NUMFILE_LAYER, [NUMSIZE_X * 8, NUMSIZE_Y * 1], [NUMSIZE_X * 0.75, NUMSIZE_Y], vHUDColor, HUD_ALPHA, DRAWFLAG_ADDITIVE);
		vMoneyPos[0] += (24 * 5);
		HUD_DrawNums(getstatf(STAT_MONEY), vMoneyPos, HUD_ALPHA, vHUDColor);
	}
	
	fOldMoneyValue = getstatf(STAT_MONEY);
}

/*
=================
HUD_DrawAmmo

Draws the current clip, the amount of ammo for the caliber and a matching caliber icon
=================
*/
void HUD_DrawAmmo(void) {
	static float fOldMag, fOldCal;
	static float fAmmoAlpha;
	static vector vAmmoMagPos;
	static vector vAmmoCalPos;
	
	if (getstatf(STAT_ACTIVEWEAPON) == 0) {
		return;
	}
	if (getstatf(STAT_ACTIVEWEAPON) == WEAPON_KNIFE || getstatf(STAT_ACTIVEWEAPON) == WEAPON_C4BOMB) {
		return;
	}
	
	if (getstatf(STAT_CURRENT_MAG) != fOldMag || getstatf(STAT_CURRENT_CALIBER) != fOldCal) {
		fAmmoAlpha = 1.0;
	}
	
	if (fAmmoAlpha >= HUD_ALPHA) {
		fAmmoAlpha -= frametime * 0.5;
	} else {
		fAmmoAlpha = HUD_ALPHA;
	}
	
	if (wptTable[getstatf(STAT_ACTIVEWEAPON)].iCaliber < 11) {
		vAmmoMagPos = video_mins+[video_res[0] - 142, video_res[1] - 42];
		HUD_DrawNums(getstatf(STAT_CURRENT_MAG), vAmmoMagPos, fAmmoAlpha, vHUDColor);
		
		drawsubpic(video_mins+[video_res[0] - 118, video_res[1] - 42], '3 25', HUD_NUMFILE_LAYER, [0.9375, 0], [0.01171875, 0.09765625], vHUDColor, fAmmoAlpha, DRAWFLAG_ADDITIVE);
		
		vAmmoCalPos = video_mins+[video_res[0] - 64, video_res[1] - 42];
		HUD_DrawNums(getstatf(STAT_CURRENT_CALIBER), vAmmoCalPos, fAmmoAlpha, vHUDColor);
	} else {
		vAmmoMagPos = video_mins+[video_res[0] - 64, video_res[1] - 42];
		HUD_DrawNums(getstatf(STAT_CURRENT_MAG), vAmmoMagPos, fAmmoAlpha, vHUDColor);
	}
	
	// Caliber icon
	drawsubpic(video_mins+video_res - [42,42], [24,24], HUD_NUMFILE_LAYER, vHUDCalPos[wptTable[getstatf(STAT_ACTIVEWEAPON)].iCaliber], [NUMSIZE_X, NUMSIZE_X], vHUDColor, fAmmoAlpha, DRAWFLAG_ADDITIVE);
	fOldMag = getstatf(STAT_CURRENT_MAG);
	fOldCal = getstatf(STAT_CURRENT_CALIBER);
}

void HUD_DrawProgressBar(void) {
	vector vSize = [540,16];
	vector vMainPos;

	if (getstatf(STAT_PROGRESS) > 0) {
		vMainPos = video_mins;
		vMainPos[0] += (video_res[0] / 2) - (vSize[0] / 2);
		vMainPos[1] += (video_res[1] / 2) - (vSize[1] / 2);
	
		// Draw the background
		vector vBar = vSize;
		vBar[0] = 538 * getstatf(STAT_PROGRESS);
		vBar[1] = 14;
		drawfill(vMainPos + [1,1], vBar, vHUDColor, 1, DRAWFLAG_ADDITIVE);

		drawfill(vMainPos, [vSize[0], 1], vHUDColor, 1.0f); // Top
		drawfill([vMainPos[0], vMainPos[1] + vSize[1]], [vSize[0], 1], vHUDColor, 1.0f); // Bottom
	
		drawfill(vMainPos, [1, vSize[1]], vHUDColor, 1.0f); // Left
		drawfill([vMainPos[0] + vSize[0], vMainPos[1]], [1, vSize[1] + 1], vHUDColor, 1.0f); // Right
	}
}

void HUD_DrawRadar(void) {
	if (autocvar_cl_radar == 1) {
		drawpic(video_mins, "sprites/radar640.spr_0.tga", [128,128], [1,1,1], 0.25, DRAWFLAG_ADDITIVE);
	} else if (autocvar_cl_radar == 2) {
		static int iLastMode = 0;
		static vector vMapSize;
		static float fZoom;
		
		if (iLastMode != pSeat.iMapExpand) {
			iLastMode = pSeat.iMapExpand;
		}
		
		if (pSeat.iMapExpand == 1) {
			if (pSeat.fMapLerp < 1.0f) {
				vMapSize[0] = rint(Math_Lerp(128, video_res[0] - 32, pSeat.fMapLerp));
				vMapSize[1] = rint(Math_Lerp(128, video_res[1] - 32, pSeat.fMapLerp));
				fZoom = Math_Lerp((ovMap.fCameraHeight * (128 / (video_res[1] - 32))), ovMap.fCameraHeight - 32, pSeat.fMapLerp);
				pSeat.fMapLerp += frametime * 2;
			} else {
				pSeat.fMapLerp = 1.0f;
				fZoom = ovMap.fCameraHeight;
				vMapSize = video_res + [-32,-32];
			}
		} else {
			if (pSeat.fMapLerp > 0.0f) {
				vMapSize[0] = rint(Math_Lerp(128, video_res[0] - 32, pSeat.fMapLerp));
				vMapSize[1] = rint(Math_Lerp(128, video_res[1] - 32, pSeat.fMapLerp));
				fZoom = Math_Lerp((ovMap.fCameraHeight * (128 / (video_res[1] - 32))), ovMap.fCameraHeight - 32, pSeat.fMapLerp);
				pSeat.fMapLerp -= frametime * 2;
			} else {
				pSeat.fMapLerp = 0.0f;
				fZoom = (ovMap.fCameraHeight * (128 / (video_res[1] - 32)));
				vMapSize = [128,128];
			}
		}

		clearscene();
		drawfill(video_mins + [15,15], vMapSize + [2,2], vHUDColor, 1.0f, DRAWFLAG_ADDITIVE);
		drawfill(video_mins + [16,16], vMapSize, [0,0,0], 1.0f, 0);
		setproperty(VF_MIN, video_mins + [16,16]);
		setproperty(VF_SIZE, vMapSize);
	
		Overview_DrawLayer();
		
		makevectors(view_angles);
		setproperty(VF_ORIGIN, [pSeat->m_vecPredictedOrigin[0], pSeat->m_vecPredictedOrigin[1], fZoom]);
		setproperty(VF_ANGLES, [Math_Lerp(90, 60, pSeat.fMapLerp), view_angles[1], 0]);
		setproperty(VF_DRAWWORLD, 0);
		renderscene();
	}
}

void HUD_DrawFlash(void) {
	if (pSeat->fFlashTime > 0.0f) {
		pSeat->fFlashTime -= frametime;
	} else {
		if (pSeat->fFlashAlpha > 0.0f) {
			pSeat->fFlashAlpha -= (frametime * 0.5);
		} else {
			return;
		}
	}
	
	drawfill(video_mins, video_res, [1,1,1], pSeat->fFlashAlpha, 0/*pSeat->fFlashTime*/);
}

/*
=================
HUD_Draw

Called every frame in Draw.c
=================
*/
void HUD_Draw(void) {
	vHUDColor = autocvar_con_color * (1 / 255);
	
	// I guess viewzoom turns from 0.0-1.0 float into a 0-255 byte
	if (getstatf(STAT_VIEWZOOM) < 1.0f) {
		if (getstatf(STAT_ACTIVEWEAPON) == WEAPON_SG552 || getstatf(STAT_ACTIVEWEAPON) == WEAPON_AUG) {
			HUD_DrawSimpleCrosshair();
		} else {
			HUD_DrawScope();
		}
	} else {
		HUD_DrawCrosshair();
	}

	HUD_DrawFlash();
	Damage_Draw();
	HUD_DrawTimer();
	HUD_DrawHealth();
	HUD_DrawArmor();
	HUD_DrawIcons();
	HUD_DrawMoney();
	HUD_DrawAmmo();
	HUD_DrawRadar();
	HUD_DrawProgressBar();
	HUD_DrawWeaponSelect();
}
