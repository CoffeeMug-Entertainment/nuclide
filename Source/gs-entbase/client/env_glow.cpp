/***
*
*	Copyright (c) 2016-2019 Marco 'eukara' Hladik. All rights reserved.
*
*	See the file LICENSE attached with the sources for usage details.
*
****/

class env_glow:CBaseEntity
{
	vector m_vecColor;
	float m_flAlpha;
	float m_flMaxAlpha;
	string m_strSprite;
	vector m_vecSize;
	void() env_glow;
	virtual void() customphysics;
	virtual float() predraw;
	virtual void(string, string) SpawnKey;
};

float env_glow::predraw(void)
{
	m_flAlpha = bound(0, m_flAlpha, 1.0f);

	if (m_flAlpha > 0) {
		vector forg;
		vector fsize;
		float falpha;
		int s = (float)getproperty(VF_ACTIVESEAT);
		pSeat = &seats[s];
		
		/* Scale the glow somewhat with the players distance */
		fsize = m_vecSize;
		fsize *= vlen(pSeat->vPlayerOrigin - origin) / 256;
		
		/* Fade out when the player is starting to move away */
		falpha = 1 - bound(0, vlen(pSeat->vPlayerOrigin - origin) / 1024, 1);
		falpha *= m_flAlpha;
		
		/* Clamp the alpha by the glows' renderamt value */
		falpha = bound(0, falpha, m_flMaxAlpha);
		makevectors(view_angles);
		
		/* Nudge this slightly towards the camera */
		makevectors(vectoangles(origin - pSeat->vPlayerOrigin));
		forg = origin + (v_forward * -16);

		/* Project it, always facing the player */
		makevectors(view_angles);
		R_BeginPolygon(m_strSprite, 1, 0);
		R_PolygonVertex(forg + v_right * fsize[0] - v_up * fsize[1], [1,1], m_vecColor, falpha);
		R_PolygonVertex(forg - v_right * fsize[0] - v_up * fsize[1], [0,1], m_vecColor, falpha);
		R_PolygonVertex(forg - v_right * fsize[0] + v_up * fsize[1], [0,0], m_vecColor, falpha);
		R_PolygonVertex(forg + v_right * fsize[0] + v_up * fsize[1], [1,0], m_vecColor, falpha);
		R_EndPolygon();
		addentity(this);
	}

	return PREDRAW_NEXT;
}

void env_glow::customphysics(void)
{
	int s = (float)getproperty(VF_ACTIVESEAT);
	pSeat = &seats[s];

	if (checkpvs(pSeat->vPlayerOrigin, this) == FALSE) {
		m_flAlpha -= frametime;
		return;
	}

	other = world;
	traceline(this.origin, pSeat->vPlayerOrigin, MOVE_OTHERONLY, this);

	/* If we can't trace against the player, or are two close, fade out */
	if (trace_fraction < 1.0f || vlen(origin - pSeat->vPlayerOrigin) < 128) {
		m_flAlpha -= frametime; 
		return;
	}

	m_flAlpha += frametime; 
}

void env_glow::env_glow(void)
{
	m_flMaxAlpha = 1.0f;
	m_vecColor = [1,1,1];
	drawmask = MASK_ENGINE;
	Init();
}

void env_glow::SpawnKey(string strField, string strKey)
{
	switch (strField) {
		case "shader":
			m_strSprite = strKey;
			m_vecSize = drawgetimagesize(m_strSprite) / 2;
			break;
		case "model":
			m_strSprite = sprintf("%s_0.tga", strKey);
			m_vecSize = drawgetimagesize(m_strSprite) / 2;
			break;
		case "rendercolour":
			m_vecColor = stov(strKey) / 255;
		case "renderamt":
			m_flMaxAlpha = stof(strKey) / 255;
		default:
			CBaseEntity::SpawnKey(strField, strKey);
	}
}
