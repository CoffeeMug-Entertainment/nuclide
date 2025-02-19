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

enumflags
{
	TRAIN_WAIT,
	TRAIN_NOPITCH,
	TRAIN_UNUSED2,
	TRAIN_NOTSOLID
};

/*!QUAKED func_tracktrain (0 .5 .8) ? TRAIN_WAIT TRAIN_NOPITCH x TRAIN_NOTSOLID
# OVERVIEW
An interactive train that moves along a path akin to func_train.

# KEYS
- "targetname" : Name
- "target" : First node.
- "killtarget" : Target to kill when triggered.
- "dmg" : Damage to inflict upon a person blocking the way.
- "snd_move" : Path to sound sample which plays when it's moving.
- "snd_stop" : Path to sound sample which plays when it stops moving.

# SPAWNFLAGS
- TRAIN_WAIT (1) : Stop at each path_corner until we're triggered again.
- TRAIN_NOPITCH (2) : Train does not pivot up/down at all.
- TRAIN_NOTSOLID (8) : Don't do collision testing against this entity.

# NOTES
Upon level entry, the func_tracktrain will spawn right where its first path_corner
node is. This is so you can light the func_tracktrain somewhere else - like a lonely
box somewhere outside the playable area.

If no targetname is specified, the train will move on its own at map-launch.

# TRIVIA
This entity was introduced in Half-Life (1998).
*/
class
func_tracktrain:NSRenderableEntity
{
	float m_flWait;
	float m_flSpeed;
	float m_flDamage;
	float m_flHeight;
	float m_flStartSpeed;
	float m_flBank;
	string m_strMoveSnd;
	string m_strStopSnd;

public:
	void func_tracktrain(void);

	virtual void Save(float);
	virtual void Restore(string,string);
	virtual void SpawnKey(string,string);
	virtual void Spawned(void);
	virtual void Respawn(void);
	virtual void Trigger(entity, triggermode_t);

	nonvirtual void SoundMove(void);
	nonvirtual void SoundStop(void);
	nonvirtual void AfterSpawn(void);
	nonvirtual void PathNext(void);
	nonvirtual void PathMove(void);
	nonvirtual void PathDone(void);
	virtual void Blocked(entity);

};

void
func_tracktrain::func_tracktrain(void)
{
	m_flWait = 0.0f;
	m_flSpeed = 100; /* FIXME: This is all decided by the first path_corner pretty much */
	m_flDamage = 0.0f;
	m_flHeight = 0.0f;
	m_flStartSpeed = 0.0f;
	m_flBank = 0.0f;
	m_strMoveSnd = __NULL__;
	m_strStopSnd = __NULL__;
}

void
func_tracktrain::Save(float handle)
{
	super::Save(handle);
	SaveFloat(handle, "m_flWait", m_flWait);
	SaveFloat(handle, "m_flSpeed", m_flSpeed);
	SaveFloat(handle, "m_flDamage", m_flDamage);
	SaveFloat(handle, "m_flHeight", m_flHeight);
	SaveFloat(handle, "m_flStartSpeed", m_flStartSpeed);
	SaveString(handle, "m_strMoveSnd", m_strMoveSnd);
	SaveString(handle, "m_strStopSnd", m_strStopSnd);
}

void
func_tracktrain::Restore(string strKey, string strValue)
{
	switch (strKey) {
	case "m_flWait":
		m_flWait = ReadFloat(strValue);
		break;
	case "m_flSpeed":
		m_flSpeed = ReadFloat(strValue);
		break;
	case "m_flDamage":
		m_flDamage = ReadFloat(strValue);
		break;
	case "m_flHeight":
		m_flHeight = ReadFloat(strValue);
		break;
	case "m_flStartSpeed":
		m_flStartSpeed = ReadFloat(strValue);
		break;
	case "m_strMoveSnd":
		m_strMoveSnd = ReadString(strValue);
		break;
	case "m_strStopSnd":
		m_strStopSnd = ReadString(strValue);
		break;
	default:
		super::Restore(strKey, strValue);
	}
}

void
func_tracktrain::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "startspeed":
		m_flStartSpeed = stof(strValue);
		break;
	case "height":
		m_flHeight = stof(strValue);
		break;
	case "dmg":
		m_flDamage = stof(strValue);
		break;
	case "snd_move":
		m_strMoveSnd = strValue;
		break;
	case "snd_stop":
		m_strStopSnd = strValue;
		break;
	/* compatibility */
	case "movesnd":
		m_strMoveSnd = sprintf("func_tracktrain.move_%i", stoi(strValue) + 1i);
		break;
	case "stopsnd":
		m_strStopSnd = sprintf("func_tracktrain.stop_%i", stoi(strValue) + 1i);
		break;
	default:
		super::SpawnKey(strKey, strValue);
	}
}

void
func_tracktrain::Spawned(void)
{
	super::Spawned();

	if (m_strMoveSnd)
		Sound_Precache(m_strMoveSnd);
	if (m_strStopSnd)
		Sound_Precache(m_strStopSnd);
}

void
func_tracktrain::Respawn(void)
{
	SetSolid(HasSpawnFlags(TRAIN_NOTSOLID) ? SOLID_NOT : SOLID_BSP);
	SetMovetype(MOVETYPE_PUSH);
	SetModel(GetSpawnModel());
	SetOrigin(GetSpawnOrigin());
	m_flSpeed = m_flStartSpeed;

	/* let's wait 1/4 a second to give the path_corner entities a chance to
	 * spawn in case they're after us in the ent lump */
	ScheduleThink(AfterSpawn, 0.25f);
	SetTriggerTarget(m_oldstrTarget);
}

void
func_tracktrain::Blocked(entity eBlocker)
{
	/* HACK: Make corpses gib instantly */
	if (eBlocker.solid == SOLID_CORPSE) {
		Damage_Apply(eBlocker, this, 500, 0, DMG_EXPLODE);
		return;
	}

	if (eBlocker.takedamage != DAMAGE_NO) {
		Damage_Apply(eBlocker, this, m_flDamage, 0, DMG_CRUSH);
	} else {
		remove(eBlocker);
	}
}

void
func_tracktrain::SoundMove(void)
{
	if (m_strMoveSnd) {
		Sound_Play(this, CHAN_VOICE, m_strMoveSnd);
	}
}

void
func_tracktrain::SoundStop(void)
{
	if (m_strStopSnd) {
		Sound_Play(this, CHAN_BODY, m_strStopSnd);
	}

	if (m_strMoveSnd) {
		sound(this, CHAN_VOICE, "common/null.wav", 1.0, ATTN_NORM);
	}
}

void
func_tracktrain::PathMove(void)
{
	entity eNode;
	float flTravelTime;
	vector vecVelocity;
	vector vecWorldPos;

	eNode = find(world, ::targetname, target);

	if (!eNode) {
		return;
	}

	vecWorldPos = origin;

	vecVelocity = (eNode.origin + [0,0,m_flHeight]) - vecWorldPos;
	flTravelTime = (vlen(vecVelocity) / m_flSpeed);

	if (!flTravelTime) {
		print("^1func_tracktrain::^3PathMove^7: Distance short, going next\n");
		ScheduleThink(PathNext, 0.0f);
		return;
	}

	SoundMove();

	SetVelocity(vecVelocity * (1 / flTravelTime));

	vector vecAngleDest;
	vector vecDiff;
	vector vecAngleDiff;

	vecDiff = eNode.origin - origin;

	/* the direction we're aiming for */
	vecAngleDest = vectoangles(vecDiff);

	vecAngleDest[1] += 180.0f; /* this is an evil hack */

	/* we only care about YAW */
	if (HasSpawnFlags(TRAIN_NOPITCH))
		vecAngleDest[0] = 0;
	else
		vecAngleDest[0] = -Math_FixDelta(vecAngleDest[0]);
	vecAngleDest[1] = Math_FixDelta(vecAngleDest[1]);
	vecAngleDest[2] = 0;

	vecAngleDiff = vecAngleDest - angles;
	vecAngleDiff[2] = 0;

	//print(sprintf("vecAngleDiff: %v\n", vecAngleDiff));

	if (vecAngleDiff[1] == 0)
		SetAngles(vecAngleDest);
	else
		SetAngularVelocity(vecAngleDiff * (1 / flTravelTime));

	if (!eNode)
		SetAngularVelocity([0,0,0]);

	ScheduleThink(PathNext, flTravelTime);
}

void
func_tracktrain::PathDone(void)
{
	path_corner eNode;
	eNode = (path_corner)find(world, ::targetname, target);

	/* stop */
	ClearVelocity();

	if (!eNode) {
		return;
	}

	NSLog("func_tracktrain (%s): Touched base with path_corner %S", targetname, target);

	/* fire the path_corners' target */
	if (eNode.m_strMessage) {
		eNode.Trigger(this, TRIG_TOGGLE);
	}
	SoundStop();
}

void
func_tracktrain::PathNext(void)
{
	path_corner eNode;
	eNode = (path_corner)find(world, ::targetname, target);

	if (!eNode) {
		return;
	}

	SetOrigin((eNode.origin) + [0,0,m_flHeight]);
	PathDone();

	/* if speed is 0, retain current speed */
	if (eNode.m_flSpeed > 0)
		m_flSpeed = eNode.m_flSpeed;

	m_flWait = eNode.m_flWait;
	target = eNode.target;
	ClearVelocity();

	/* warp */
	if (eNode.HasSpawnFlags(PC_TELEPORT)) {
		SetOrigin((eNode.origin) + [0,0,m_flHeight]);
	}

	/* stop until triggered again */
	if (eNode.HasSpawnFlags(PC_WAIT)) {
		SoundStop();
		return;
	}

	PathMove();
}

/* TODO: Handle state? */
void
func_tracktrain::Trigger(entity act, triggermode_t state)
{
	PathMove();
}

void
func_tracktrain::AfterSpawn(void)
{
	PathNext();

	if (!targetname) {
		PathMove();
	}
}
