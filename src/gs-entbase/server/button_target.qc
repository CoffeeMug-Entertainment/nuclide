/*
 * Copyright (c) 2016-2022 Vera Visions LLC.
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

/** Spawnflags that button_target supports. */
typedef enumflags
{
	BUTTA_USE,	/**< Button has to be used by a player to trigger, instead of being shot. */
	BUTTA_TEXON	/**< Button texture starts in the **ON** state. */
} sf_button_target_t;

/*!QUAKED button_target (0 .5 .8) ? BUTTA_USE BUTTA_TEXON
# OVERVIEW
Non-moving button that can either be used by hand, or shot.

# KEYS
- "targetname" : Name
- "target" : Target when triggered.
- "delay" : Time in seconds until target is triggered.

# SPAWNFLAGS
- BUTTA_USE (1) : Button becomes 'use' only, clients have to interact with it manually instead of shooting it.
- BUTTA_TEXON (2) : Texture choices will be inverted in case multiple frames exist.

# TRIVIA
This entity was introduced in Half-Life (1998).
*/
class
button_target:NSSurfacePropEntity
{
public:
	void button_target(void);
	
	virtual void Respawn(void);
	virtual void Trigger(entity,triggermode_t);
	virtual void Damage(void);
};

void
button_target::button_target(void)
{
}

void
button_target::Respawn(void)
{
	/* yuck */
	static void PUseWrapper(void) {
		Trigger(eActivator, TRIG_TOGGLE);
	}

	SetMovetype(MOVETYPE_PUSH);
	SetSolid(SOLID_BSP);
	SetModel(GetSpawnModel());
	SetOrigin(GetSpawnOrigin());

	/* it's either one or the other */
	if (HasSpawnFlags(BUTTA_USE)) {
		PlayerUse = PUseWrapper;
	} else {
		SetHealth(1);
		SetTakedamage(DAMAGE_YES);
		Pain = Death = Damage;
	}

	/* purely cosmetic */
	SetFrame(HasSpawnFlags(BUTTA_TEXON) ? 1 : 0);
}

void
button_target::Trigger(entity act, triggermode_t status)
{
	/* make unusable */
	PlayerUse = __NULL__;
	SetTakedamage(DAMAGE_NO);

	/* toggle texture frame */
	float new_frame = (GetFrame() >= 1) ? 0 : 1;
	SetFrame(new_frame);

	UseTargets(act, status, m_flDelay);
}

void
button_target::Damage(void)
{
	Trigger(g_dmg_eAttacker, TRIG_TOGGLE);
}
