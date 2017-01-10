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

/*
=================
CSQC_ConsoleCommand_Init

Init all the cmds in one place
=================
*/
void CSQC_ConsoleCommand_Init( void ) {
	registercommand( "buy" );
	registercommand( "chooseteam" );
	registercommand( "invnext" );
	registercommand( "invprev" );
	registercommand( "+showscores" );
	registercommand( "-showscores" );
	registercommand( "nightvision" );
	
	registercommand( "radio1" );
	registercommand( "radio2" );
	registercommand( "radio3" );
	
	registercommand( "glock" );
	registercommand( "usp" );
	registercommand( "p228" );
	registercommand( "deagle" );
	registercommand( "fn57" );
	registercommand( "elites" );
	registercommand( "m3" );
	registercommand( "xm1014" );
	registercommand( "tmp" );
	registercommand( "mac10" );
	registercommand( "mp5" );
	registercommand( "ump45" );
	registercommand( "p90" );
	registercommand( "ak47" );
	registercommand( "m4a1" );
	registercommand( "sg552" );
	registercommand( "aug" );
	registercommand( "scout" );
	registercommand( "sg550" );
	registercommand( "awp" );
	registercommand( "g3sg1" );
	registercommand( "m249" );
	
	registercommand( "primammo" );
	registercommand( "secammo" );
	
	registercommand( "vest" );
	registercommand( "vesthelm" );
	registercommand( "flash" );
	registercommand( "hegren" );
	registercommand( "vsgren" );
	registercommand( "defuser" );
	registercommand( "nvg" );
	
	registercommand( "coverme" );
	registercommand( "takepoint" );
	registercommand( "holdpos" );
	registercommand( "regroup" );
	registercommand( "followme" );
	registercommand( "takingfire" );
	
	registercommand( "go" );
	registercommand( "fallback" );
	registercommand( "sticktog" );
	registercommand( "getinpos" );
	registercommand( "stormfront" );
	registercommand( "report" );
	
	registercommand( "roger" );
	registercommand( "enemyspot" );
	registercommand( "needbackup" );
	registercommand( "sectorclear" );
	registercommand( "inposition" );
	registercommand( "reportingin" );
	registercommand( "getout" );
	registercommand( "negative" );
	registercommand( "enemydown" );
}

/*
=================
CSQC_ConsoleCommand

Can interject cmds and create new ones
=================
*/
float CSQC_ConsoleCommand( string sCMD ) {
	tokenize( sCMD );
	switch ( argv(0) ) {
	case "buy":
		if( getstatf( STAT_BUYZONE ) == TRUE ) {
			fVGUI_Display = VGUI_BM_MAIN;
		}
		return TRUE;
		break;
    case "chooseteam":
		fVGUI_Display = VGUI_TEAMSELECT;
		return TRUE;
		break;
	case "invnext":
		HUD_DrawWeaponSelect_Back();
		return TRUE;
		break;
	case "invprev":
		HUD_DrawWeaponSelect_Forward();
		return TRUE;
		break;
	case "+showscores":
		iShowScores = TRUE;
		return TRUE;
		break;
	case "-showscores":
		iShowScores = FALSE;
		return TRUE;
		break;
	case "nightvision":
		Nightvision_Toggle();
		return TRUE;
		break;
	case "glock":
		return TRUE;
		break;
	case "usp":
		return TRUE;
		break;
	case "p228":
		return TRUE;
		break;
	case "deagle":
		return TRUE;
		break;
	case "fn57":
		return TRUE;
		break;
	case "elites":
		return TRUE;
		break;
	case "m3":
		return TRUE;
		break;
	case "xm1014":
		return TRUE;
		break;
	case "tmp":
		return TRUE;
		break;
	case "mac10":
		return TRUE;
		break;
	case "mp5":
		return TRUE;
		break;
	case "ump45":
		return TRUE;
		break;
	case "p90":
		return TRUE;
		break;
	case "ak47":
		return TRUE;
		break;
	case "m4a1":
		return TRUE;
		break;
	case "sg552":
		return TRUE;
		break;
	case "aug":
		return TRUE;
		break;
	case "scout":
		return TRUE;
		break;
	case "sg550":
		return TRUE;
		break;
	case "awp":
		return TRUE;
		break;
	case "g3sg1":
		return TRUE;
		break;
	case "m249":
		return TRUE;
		break;
	case "primammo":
		return TRUE;
		break;
	case "secammo":
		return TRUE;
		break;
	case "vest":
		return TRUE;
		break;
	case "vesthelm":
		return TRUE;
		break;
	case "flash":
		return TRUE;
		break;
	case "hegren":
		return TRUE;
		break;
	case "vsgren":
		return TRUE;
		break;
	case "defuser":
		return TRUE;
		break;
	case "nvg":
		return TRUE;
		break;
	case "coverme":
		sendevent( "RadioMessage", "f", RADIO_CT_COVERME );
		return TRUE;
		break;
	case "takepoint":
		sendevent( "RadioMessage", "f", RADIO_CT_POINT );
		return TRUE;
		break;
	case "takepoint":
		sendevent( "RadioMessage", "f", RADIO_POSITION );
		return TRUE;
		break;
	case "regroup":
		sendevent( "RadioMessage", "f", RADIO_REGROUP );
		return TRUE;
		break;
	case "followme":
		sendevent( "RadioMessage", "f", RADIO_FOLLOWME );
		return TRUE;
		break;
	case "takingfire":
		sendevent( "RadioMessage", "f", RADIO_FIREASSIS );
		return TRUE;
		break;
	case "go":
		sendevent( "RadioMessage", "f", RADIO_GO );
		return TRUE;
		break;
	case "fallback":
		sendevent( "RadioMessage", "f", RADIO_FALLBACK );
		return TRUE;
		break;
	case "sticktog":
		sendevent( "RadioMessage", "f", RADIO_STICKTOG );
		return TRUE;
		break;
	case "getinpos":
		sendevent( "RadioMessage", "f", RADIO_COM_GETINPOS );
		return TRUE;
		break;
	case "stormfront":
		sendevent( "RadioMessage", "f", RADIO_STORMFRONT );
		return TRUE;
		break;
	case "report":
		sendevent( "RadioMessage", "f", RADIO_COM_REPORTIN );
		return TRUE;
		break;
	case "roger":
		sendevent( "RadioMessage", "f", RADIO_ROGER );
		return TRUE;
		break;
	case "enemyspot":
		sendevent( "RadioMessage", "f", RADIO_CT_ENEMYS );
		return TRUE;
		break;
	case "needbackup":
		sendevent( "RadioMessage", "f", RADIO_CT_BACKUP );
		return TRUE;
		break;
	case "sectorclear":
		sendevent( "RadioMessage", "f", RADIO_CLEAR );
		return TRUE;
		break;
	case "inposition":
		sendevent( "RadioMessage", "f", RADIO_CT_INPOS );
		return TRUE;
		break;
	case "reportingin":
		sendevent( "RadioMessage", "f", RADIO_CT_REPORTINGIN );
		return TRUE;
		break;
	case "getout":
		sendevent( "RadioMessage", "f", RADIO_GETOUT );
		return TRUE;
		break;
	case "negative":
		sendevent( "RadioMessage", "f", RADIO_NEGATIVE );
		return TRUE;
		break;
	case "enemydown":
		sendevent( "RadioMessage", "f", RADIO_ENEMYDOWN );
		return TRUE;
		break;
	case "radio1":
		VGUI_Radio_Toggle( VGUI_RADIO1 );
		return TRUE;
		break;
	case "radio2":
		VGUI_Radio_Toggle( VGUI_RADIO2 );
		return TRUE;
		break;
	case "radio3":
		VGUI_Radio_Toggle( VGUI_RADIO3 );
		return TRUE;
		break;
	}
	return FALSE;
}

/*
=================
CSQC_Parse_Event

Whenever we call a SVC_CGAMEPACKET on the SSQC, this is being run
=================
*/
void CSQC_Parse_Event( void ) {
	float fHeader = readbyte();
	
	if ( fHeader == EV_WEAPON_DRAW ) {
		Weapon_Draw( getstatf( STAT_ACTIVEWEAPON ) );
	} else if ( fHeader == EV_WEAPON_PRIMARYATTACK ) {
		Weapon_PrimaryAttack( getstatf( STAT_ACTIVEWEAPON ) );
	} else if ( fHeader == EV_WEAPON_SECONDARYATTACK ) {
		Weapon_SecondaryAttack( getstatf( STAT_ACTIVEWEAPON ) );
	} else if ( fHeader == EV_WEAPON_RELOAD ) {
		Weapon_Reload( getstatf( STAT_ACTIVEWEAPON ) );
	} else if ( fHeader == EV_MODELGIB ) {
		vector vPos;
		vPos_x = readcoord();
		vPos_y = readcoord();
		vPos_z = readcoord();
		
		vector vSize;
		vSize_x = readcoord();
		vSize_y = readcoord();
		vSize_z = readcoord();

		float fStyle = readbyte();
		Effect_BreakModel( vPos, vSize, '0 0 0', fStyle );
	} else if ( fHeader == EV_CAMERATRIGGER ) {
		vCameraPos_x = readcoord();
		vCameraPos_y = readcoord();
		vCameraPos_z = readcoord();

		vCameraAngle_x = readcoord();
		vCameraAngle_y = readcoord();
		vCameraAngle_z = readcoord();
		
		fCameraTime = time + readfloat();
	} else if ( fHeader == EV_RADIOMSG ) {
		Radio_PlayMessage( readbyte() );
	} else if ( fHeader == EV_RADIOMSG2 ) {
		Radio_PlayPlayerMessage( readbyte(), readbyte() );
	} else if ( fHeader == EV_ORBITUARY ) {
		HUD_AddOrbituaries( readbyte(), readbyte(), readbyte(), readbyte(), readbyte(), readbyte());
	} else if ( fHeader == EV_IMPACT ) {
		int iType;
		vector vOrigin, vNormal;
		
		iType = (int)readbyte();
		vOrigin_x = readcoord();
		vOrigin_y = readcoord();
		vOrigin_z = readcoord();

		vNormal_x = readcoord();
		vNormal_y = readcoord();
		vNormal_z = readcoord();
		
		Effect_Impact( iType, vOrigin, vNormal );
	}
}

/*
=================
CSQC_InputEvent

Updates all our input related globals for use in other functions
=================
*/
float CSQC_InputEvent( float fEventType, float fKey, float fCharacter, float fDeviceID ) {
	if ( fEventType == IE_KEYDOWN ) {
		if ( fKey == K_MOUSE1 ) {
			fMouseClick = 1;
		} else {
			fInputKeyDown = 1;
		}

		fInputKeyCode = fKey;
		fInputKeyASCII = fCharacter;
	} else if ( fEventType == IE_KEYUP ) {
		if ( fKey == K_MOUSE1 ) {
			fMouseClick = 0;
		} else {
			fInputKeyDown = 0;
		}
		fInputKeyCode = 0;
		fInputKeyASCII = 0;
	} else if ( fEventType == IE_MOUSEABS ) {
		vMousePos_x = fKey;
		vMousePos_y = fCharacter;
	} 
	
	return FALSE;
}

/*
=================
CSQC_Input_Frame

Hijacks and controls what input globals are being sent to the server
=================
*/
void CSQC_Input_Frame( void ) {
	// If we are inside a VGUI, don't let the client do stuff outside
	if ( ( fVGUI_Display != VGUI_NONE ) ) {
		input_angles = '0 0 0';
		input_movevalues = '0 0 0';
		input_buttons = 0;
		input_impulse = 0;
	}
	
	if ( ( fHUDWeaponSelected ) && ( input_buttons & INPUT_BUTTON0 ) ) {
		HUD_DrawWeaponSelect_Trigger();
		input_buttons = 0;
	}
}
