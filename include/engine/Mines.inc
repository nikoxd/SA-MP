/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                 Military Dynamic Mines System                                                  *
 *                                                                                                                                *
 * Copyright � 2017 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                                                      *
 * Publication: http://forum.sa-mp.com/showthread.php?t=600369                                                                    *
 *                                                                                                                                *
 * Plugins: Streamer                                                                                                              *
 * Modules: 3DTryg                                                                                                                *
 * Attributes: None                                                                                                               *
 *                                                                                                                                *
 * File Version: 2.0.0                                                                                                            *
 * SA:MP Version: 0.3.7                                                                                                           *
 * Streamer Version: 2.8.2                                                                                                        *
 * 3DTryg Version: 4.0.2                                                                                                          *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * CreateDynamicMine(type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z,            *
 *                   worldid,interiorid,playerid,Float:streamdistance,mine_object = MINE_OBJECT_STANDARD,teamid = ANY_TEAM,       *
 *                   detect_type = MINE_DETECT_TYPE_ALL,byplayerid = INVALID_PLAYER_ID);                                          *
 * CreateDynamicMineEx(objectid,type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z, *
 *                     Float:rx,Float:ry,Float:rz,worldid,interiorid,playerid,Float:streamdistance,teamid = ANY_TEAM,             *
 *                     detect_type = MINE_DETECT_TYPE_ALL,byplayerid = INVALID_PLAYER_ID);                                        *
 * DestroyDynamicMine(mobid);                                                                                                     *
 * Float:GetMineExplodeVisibility();                                                                                              *
 * SetMineExplodeVisibility(Float:explode_stream);                                                                                *
 *                                                                                                                                *
 * Extended Functions:                                                                                                            *
 * ForceRespawnDynamicMine(mobid);                                                                                                *
 * CountDynamicMines();                                                                                                           *
 * GetMineObjectID(mobid);                                                                                                        *
 * GetMineAreaID(mobid);                                                                                                          *
 * GetDynamicMinePos(mobid,&Float:x,&Float:y,&Float:z);                                                                           *
 * SetDynamicMinePos(mobid,Float:x,Float:y,Float:z);                                                                              *
 * GetDynamicMineRot(mobid,&Float:rx,&Float:ry,&Float:rz);                                                                        *
 * SetDynamicMineRot(mobid,Float:rx,Float:ry,Float:rz);                                                                           *
 * GetDynamicMineDetectionRange(mobid,&Float:detection_range);                                                                    *
 * SetDynamicMineDetectionRange(mobid,Float:detection_range);                                                                     *
 * GetDynamicMineExplodeRadius(mobid,&Float:explode_radius);                                                                      *
 * SetDynamicMineExplodeRadius(mobid,Float:explode_radius);                                                                       *
 * GetDynamicMineHealth(mobid,&Float:health);                                                                                     *
 * SetDynamicMineHealth(mobid,Float:health);                                                                                      *
 * GetDynamicMineMaxHealth(mobid,&Float:health);                                                                                  *
 * SetDynamicMineMaxHealth(mobid,Float:health);                                                                                   *
 * GetDynamicMineVW(mobid);                                                                                                       *
 * SetDynamicMineVW(mobid,worldid);                                                                                               *
 * GetDynamicMineINT(mobid);                                                                                                      *
 * SetDynamicMineINT(mobid,interiorid);                                                                                           *
 * GetDynamicMineSD(mobid,&Float:streamdistance);                                                                                 *
 * SetDynamicMineSD(mobid,Float:streamdistance);                                                                                  *
 * GetDynamicMineTeam(mobid);                                                                                                     *
 * SetDynamicMineTeam(mobid,teamid);                                                                                              *
 * GetDynamicMineType(mobid);                                                                                                     *
 * SetDynamicMineType(mobid,type);                                                                                                *
 * GetDynamicMineRespawntime(mobid);                                                                                              *
 * SetDynamicMineRespawntime(mobid,respawntime);                                                                                  *
 *                                                                                                                                *
 * Callbacks:                                                                                                                     *
 * OnMineDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,Float:radius,damagerid);                                             *
 *                                                                                                                                *
 **********************************************************************************************************************************/

#if ((!defined Streamer_AppendArrayData) || (!defined INVALID_STREAMER_ID))
	#error [ADM] Unknown Streamer Version
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v4.0.2
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v4.0.2
#elseif (Tryg3D_Version < 40002)
	#error [ADM] Update you 3DTryg.inc to v4.0.2
#endif

#if defined _dynamic_mine_system
	#endinput
#endif
#define _dynamic_mine_system

#define MINE_OBJECT_STANDARD					(0)
#define MINE_OBJECT_UNDERWATER					(1)
#define MINE_OBJECT_LASER						(3)
#define MINE_OBJECT_PIZZA						(4)

#define MAX_MINES								(2048)
#define MINE_EXTRA_ID_OFFSET					(200001)
#define MINE_INFINITY_HEALTH					(1000000.0)

#define MINE_STATUS_UNACTIVE					(0)
#define MINE_STATUS_ACTIVE						(1)
#define MINE_STATUS_DAMAGED						(2)

#define MINE_TYPE_EXPLODE_SMALL					(12)
#define MINE_TYPE_EXPLODE_NORMAL				(2)
#define MINE_TYPE_EXPLODE_LARGE					(6)
#define MINE_TYPE_EXPLODE_HUGE					(7)

#define INVALID_MINE_ID							(0)

#define MINE_DESTROY_TYPE_DETECT				(0)	//When mine has been destroyed by detection range
#define MINE_DESTROY_TYPE_KILL					(1)	//When mine has been destroyed by player shoot

#define MINE_DETECT_TYPE_ALL					(0)
#define MINE_DETECT_TYPE_PLAYER					(1)
#define MINE_DETECT_TYPE_VEHICLE				(2)

#if !defined ANY_TEAM
	#define ANY_TEAM							(0xFFFF)
#endif

enum e_mine {
	mine_status,
	mine_objectid,
	mine_areaid,
	mine_tickcount,
	mine_type,
	mine_respawntime,
	Float:mine_health,
	Float:mine_maxhealth,
	Float:mine_explode,
	mine_teamid,
	mine_dtype,
	mine_playerid
}

new MineComponent[MAX_MINES][e_mine],
	MineUpperBound = 0,
	MineTimer,
	Float:MineExplosionVisibility = 200.0;

#define GetMineObjectID(%0)						MineComponent[(%0)][mine_objectid]
#define GetMineAreaID(%0)						MineComponent[(%0)][mine_areaid]

#define GetMineExplodeVisibility()				MineExplosionVisibility
#define SetMineExplodeVisibility(%0)			MineExplosionVisibility = (%0)

#define GetDynamicMinePos(%0,%1,%2,%3)			GetDynamicObjectPos(MineComponent[(%0)][mine_objectid],%1,%2,%3)
#define SetDynamicMinePos(%0,%1,%2,%3)			SetDynamicObjectPos(MineComponent[(%0)][mine_objectid],%1,%2,%3)

#define GetDynamicMineRot(%0,%1,%2,%3)			GetDynamicObjectRot(MineComponent[(%0)][mine_objectid],%1,%2,%3)
#define SetDynamicMineRot(%0,%1,%2,%3)			SetDynamicObjectRot(MineComponent[(%0)][mine_objectid],%1,%2,%3)

#define GetDynamicMineDetectionRange(%0,%1)		Streamer_GetFloatData(STREAMER_TYPE_AREA,MineComponent[(%0)][mine_areaid],E_STREAMER_SIZE,(%1))
#define SetDynamicMineDetectionRange(%0,%1)		Streamer_SetFloatData(STREAMER_TYPE_AREA,MineComponent[(%0)][mine_areaid],E_STREAMER_SIZE,(%1))

#define GetDynamicMineExplodeRadius(%0,%1)		(%1) = MineComponent[(%0)][mine_explode]
#define SetDynamicMineExplodeRadius(%0,%1)		MineComponent[(%0)][mine_explode] = (%1)

#define GetDynamicMineHealth(%0,%1)				(%1) = MineComponent[(%0)][mine_health]
#define SetDynamicMineHealth(%0,%1)				MineComponent[(%0)][mine_health] = (%1)

#define GetDynamicMineMaxHealth(%0,%1)			(%1) = MineComponent[(%0)][mine_maxhealth]
#define SetDynamicMineMaxHealth(%0,%1)			MineComponent[(%0)][mine_maxhealth] = (%1)

#define GetDynamicMineTeam(%0)					MineComponent[(%0)][mine_teamid]
#define SetDynamicMineTeam(%0,%1)				MineComponent[(%0)][mine_teamid] = (%1)

#define GetDynamicMineVW(%0)					Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[(%0)][mine_objectid],E_STREAMER_WORLD_ID,(%1))
#define GetDynamicMineINT(%0)					Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[(%0)][mine_objectid],E_STREAMER_INTERIOR_ID,(%1))

#define GetDynamicMineType(%0)					MineComponent[(%0)][mine_type]
#define SetDynamicMineType(%0,%1)				MineComponent[(%0)][mine_type] = (%1)

#define GetDynamicMineRespawntime(%0)			MineComponent[(%0)][mine_respawntime]
#define SetDynamicMineRespawntime(%0,%1)		MineComponent[(%0)][mine_respawntime] = (%1)

#define GetDynamicMineSD(%0,%1)					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,MineComponent[(%0)][mine_objectid],E_STREAMER_STREAM_DISTANCE,(%1))

stock SetDynamicMineVW(mobid,worldid){
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_WORLD_ID,worldid);
	Streamer_SetIntData(STREAMER_TYPE_AREA,MineComponent[mobid][mine_areaid],E_STREAMER_WORLD_ID,worldid);
}

stock SetDynamicMineINT(mobid,interiorid){
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_INTERIOR_ID,interiorid);
	Streamer_SetIntData(STREAMER_TYPE_AREA,MineComponent[mobid][mine_areaid],E_STREAMER_INTERIOR_ID,interiorid);
}

stock SetDynamicMineSD(mobid,Float:streamdistance){
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_STREAM_DISTANCE,streamdistance);
	Streamer_SetFloatData(STREAMER_TYPE_AREA,MineComponent[mobid][mine_areaid],E_STREAMER_STREAM_DISTANCE,streamdistance);
}

stock CountDynamicMines(){
	new cnt = 0;
	for(new mobid = 1; mobid <= MineUpperBound; mobid++){
		if(MineComponent[mobid][mine_objectid] != 0) cnt++;
	}
	return cnt;
}

stock FindFreeMineID(){
	for(new mobid = 1; mobid < MAX_MINES; mobid++){
		if(MineComponent[mobid][mine_objectid] == 0) return mobid;
	}
	return INVALID_MINE_ID;
}

forward OnDynamicMineUpdate(tec);
forward ForceRespawnDynamicMine(mobid);
forward DestroyDynamicMine(mobid);
forward ExplodeDynamicMine(mobid,type,playerid);
forward RespawnDynamicMine(mobid);
forward OnMineDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,Float:radius,damagerid);

new bool:CRC_MinesInit = true,
	bool:CRC_MinesExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_MinesInit){
		CRC_MinesInit = false;
		MineTimer = SetTimerEx("OnDynamicMineUpdate", 1000, true, "d", 1);
	}
	#if defined MDM_OnFilterScriptInit
		MDM_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit MDM_OnFilterScriptInit
#if defined MDM_OnFilterScriptInit
	forward MDM_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_MinesInit){
		CRC_MinesInit = false;
		MineTimer = SetTimerEx("OnDynamicMineUpdate", 1000, true, "d", 1);
	}
	#if defined MDM_OnGameModeInit
		MDM_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit MDM_OnGameModeInit
#if defined MDM_OnGameModeInit
	forward MDM_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_MinesExit){
		CRC_MinesExit = false;
		KillTimer(MineTimer);
	}
	#if defined MDM_OnFilterScriptExit
		MDM_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit MDM_OnFilterScriptExit
#if defined MDM_OnFilterScriptExit
	forward MDM_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_MinesExit){
		CRC_MinesExit = false;
		KillTimer(MineTimer);
	}
	#if defined MDM_OnGameModeExit
		MDM_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit MDM_OnGameModeExit
#if defined MDM_OnGameModeExit
	forward MDM_OnGameModeExit();
#endif

public OnDynamicMineUpdate(tec){
	#pragma unused tec
	new tick = GetTickCount();
	for(new mobid = 1; mobid <= MineUpperBound; mobid++){
		if(MineComponent[mobid][mine_status] == MINE_STATUS_DAMAGED){
			if((tick >= MineComponent[mobid][mine_tickcount]) && (MineComponent[mobid][mine_tickcount] != 0)){
				MineComponent[mobid][mine_tickcount] = 0;
				RespawnDynamicMine(mobid);
			}
		}
	}
	return 1;
}

public ForceRespawnDynamicMine(mobid){
	if(mobid <= 0 || mobid >= MAX_MINES) return 0;
	if(MineComponent[mobid][mine_status] == MINE_STATUS_UNACTIVE) return 0;
	if(MineComponent[mobid][mine_status] == MINE_STATUS_DAMAGED && MineComponent[mobid][mine_tickcount] != 0){
		MineComponent[mobid][mine_tickcount] = 0;
		RespawnDynamicMine(mobid);
	}
	return 1;
}

stock CreateDynamicMine(type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z,worldid,interiorid,playerid,Float:streamdistance,mine_object=MINE_OBJECT_STANDARD,teamid=ANY_TEAM,detect_type=MINE_DETECT_TYPE_ALL,byplayerid=INVALID_PLAYER_ID){
	new mobid = FindFreeMineID();
	if(mobid == INVALID_MINE_ID){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Failed to CreateDynamicMine limit %d exceeded, edit Mines.inc and change MAX_MINES",MAX_MINES);
		}
		return INVALID_MINE_ID;
	}
	
	MineComponent[mobid][mine_health] = health;
	MineComponent[mobid][mine_maxhealth] = health;
	MineComponent[mobid][mine_explode] = explode_radius;
	MineComponent[mobid][mine_tickcount] = 0;
	MineComponent[mobid][mine_type] = type;
	MineComponent[mobid][mine_respawntime] = respawntime;
	MineComponent[mobid][mine_teamid] = teamid;
	MineComponent[mobid][mine_dtype] = detect_type;
	MineComponent[mobid][mine_playerid] = byplayerid;
	
	switch(mine_object){
		case MINE_OBJECT_STANDARD:		MineComponent[mobid][mine_objectid] = CreateDynamicObject(19602,x,y,z-0.93,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
		case MINE_OBJECT_UNDERWATER:	MineComponent[mobid][mine_objectid] = CreateDynamicObject(2918,x,y,z-0.10,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
		case MINE_OBJECT_LASER:			MineComponent[mobid][mine_objectid] = CreateDynamicObject(18643,x,y,z-0.09,180.0,90.0,0.0,worldid,interiorid,playerid,streamdistance);
		case MINE_OBJECT_PIZZA:			MineComponent[mobid][mine_objectid] = CreateDynamicObject(19580,x,y,z+0.05,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
		
		default:						MineComponent[mobid][mine_objectid] = CreateDynamicObject(19602,x,y,z-0.93,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
	}
	MineComponent[mobid][mine_areaid] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	AttachDynamicAreaToObject(MineComponent[mobid][mine_areaid],MineComponent[mobid][mine_objectid]);
	
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	Streamer_SetIntData(STREAMER_TYPE_AREA,MineComponent[mobid][mine_areaid],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	MineComponent[mobid][mine_status] = MINE_STATUS_ACTIVE;
	if(mobid > MineUpperBound) MineUpperBound = mobid;
	return mobid;
}

stock CreateDynamicMineEx(objectid,type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,worldid,interiorid,playerid,Float:streamdistance,teamid=ANY_TEAM,detect_type=MINE_DETECT_TYPE_ALL,byplayerid=INVALID_PLAYER_ID){
	new mobid = FindFreeMineID();
	if(mobid == INVALID_MINE_ID){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Failed to CreateDynamicMine limit %d exceeded, edit Mines.inc and change MAX_MINES",MAX_MINES);
		}
		return INVALID_MINE_ID;
	}
	MineComponent[mobid][mine_health] = health;
	MineComponent[mobid][mine_maxhealth] = health;
	MineComponent[mobid][mine_explode] = explode_radius;
	MineComponent[mobid][mine_tickcount] = 0;
	MineComponent[mobid][mine_type] = type;
	MineComponent[mobid][mine_respawntime] = respawntime;
	MineComponent[mobid][mine_teamid] = teamid;
	MineComponent[mobid][mine_dtype] = detect_type;
	MineComponent[mobid][mine_playerid] = byplayerid;

	MineComponent[mobid][mine_objectid] = CreateDynamicObject(objectid,x,y,z,rx,ry,rz,worldid,interiorid,playerid,streamdistance);
	MineComponent[mobid][mine_areaid] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	AttachDynamicAreaToObject(MineComponent[mobid][mine_areaid],MineComponent[mobid][mine_objectid]);
	
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	Streamer_SetIntData(STREAMER_TYPE_AREA,MineComponent[mobid][mine_areaid],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	MineComponent[mobid][mine_status] = MINE_STATUS_ACTIVE;
	if(mobid > MineUpperBound) MineUpperBound = mobid;
	return mobid;
}

public DestroyDynamicMine(mobid){
	if(mobid <= 0 || mobid >= MAX_MINES) return 0;
	if(MineComponent[mobid][mine_status] == MINE_STATUS_UNACTIVE) return 0;
	DestroyDynamicObject(MineComponent[mobid][mine_objectid]);
	DestroyDynamicArea(MineComponent[mobid][mine_areaid]);
	MineComponent[mobid][mine_objectid] = INVALID_STREAMER_ID;
	MineComponent[mobid][mine_areaid] = INVALID_STREAMER_ID;
	MineComponent[mobid][mine_health] = 0.0;
	MineComponent[mobid][mine_maxhealth] = 0.0;
	MineComponent[mobid][mine_explode] = 0.0;
	MineComponent[mobid][mine_tickcount] = 0;
	MineComponent[mobid][mine_type] = 0;
	MineComponent[mobid][mine_status] = MINE_STATUS_UNACTIVE;
	MineComponent[mobid][mine_respawntime] = 0;
	MineComponent[mobid][mine_teamid] = ANY_TEAM;
	MineComponent[mobid][mine_dtype] = MINE_DETECT_TYPE_ALL;
	if(mobid == MineUpperBound) MineUpperBound = (mobid-1);
	return 1;
}

public ExplodeDynamicMine(mobid,type,playerid){
	if(mobid <= 0 || mobid >= MAX_MINES) return 0;
	new Float:minex, Float:miney, Float:minez,
		worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_WORLD_ID),
		interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_INTERIOR_ID),
		Float:radius;
	
	Streamer_GetFloatData(STREAMER_TYPE_AREA,MineComponent[mobid][mine_areaid],E_STREAMER_SIZE,radius);
	GetDynamicObjectPos(MineComponent[mobid][mine_objectid],minex,miney,minez);
	CreateDynamicExplosion(minex,miney,minez,MineComponent[mobid][mine_type],MineComponent[mobid][mine_explode],worldid,interiorid,-1,GetMineExplodeVisibility());
	
	MineComponent[mobid][mine_tickcount] = GetTickCount()+(MineComponent[mobid][mine_respawntime]*1000);
	MineComponent[mobid][mine_status] = MINE_STATUS_DAMAGED;
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_WORLD_ID,worldid+10000); //hide mine
	CallLocalFunction("OnMineDestroy","dfffddfd",mobid,minex,miney,minez,type,playerid,radius,MineComponent[mobid][mine_playerid]);
	return 1;
}

public RespawnDynamicMine(mobid){
	if(mobid <= 0 || mobid >= MAX_MINES) return 0;
	if(MineComponent[mobid][mine_status] == MINE_STATUS_ACTIVE) return 0;
	new worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_WORLD_ID);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,MineComponent[mobid][mine_objectid],E_STREAMER_WORLD_ID,worldid-10000); //show mine
	MineComponent[mobid][mine_tickcount] = 0;
	MineComponent[mobid][mine_health] = MineComponent[mobid][mine_maxhealth];
	MineComponent[mobid][mine_status] = MINE_STATUS_ACTIVE;
	return 1;
}

//Hook: OnPlayerShootDynamicObject
public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z){
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-MINE_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_MINES){
		if(MineComponent[mobid][mine_status] == MINE_STATUS_ACTIVE && MineComponent[mobid][mine_objectid] == objectid && MineComponent[mobid][mine_playerid] != playerid){
			if((MineComponent[mobid][mine_teamid] != GetPlayerTeam(playerid)) || (MineComponent[mobid][mine_teamid] == ANY_TEAM)){
				if(MineComponent[mobid][mine_health] != MINE_INFINITY_HEALTH){
					MineComponent[mobid][mine_health] -= Tryg3D_GetWeaponDamage(weaponid);
					new buffer[128];
					if(MineComponent[mobid][mine_health] > 0){
						format(buffer,sizeof buffer,"Mine~n~~w~%.0f HP~n~~r~~h~~h~-%.0f HP",MineComponent[mobid][mine_health],Tryg3D_GetWeaponDamage(weaponid));
					} else {
						format(buffer,sizeof buffer,"Mine~n~~w~0 HP~n~~r~~h~~h~-%.0f HP",Tryg3D_GetWeaponDamage(weaponid));
					}
					GameTextForPlayer(playerid,buffer,500,4);
					if(MineComponent[mobid][mine_health] <= 0.0){
						ExplodeDynamicMine(mobid,MINE_DESTROY_TYPE_KILL,playerid);
					}
				}
			}
		}
	}
	#if defined MDM_OnPlayerShootDynamicObject
		MDM_OnPlayerShootDynamicObject(playerid, weaponid, objectid, x, y, z);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject MDM_OnPlayerShootDynamicObject
#if defined MDM_OnPlayerShootDynamicObject
	forward MDM_OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid, areaid){
	new mobid = (Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-MINE_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_MINES){
		if(MineComponent[mobid][mine_status] == MINE_STATUS_ACTIVE && MineComponent[mobid][mine_areaid] == areaid && MineComponent[mobid][mine_playerid] != playerid){
			new bool:tmp_det = false;
			switch(MineComponent[mobid][mine_dtype]){
				case MINE_DETECT_TYPE_ALL:		tmp_det = true;
				case MINE_DETECT_TYPE_PLAYER: 	if(!IsPlayerInAnyVehicle(playerid)) tmp_det = true;
				case MINE_DETECT_TYPE_VEHICLE:	if(IsPlayerInAnyVehicle(playerid)) tmp_det = true;
			}
			if((MineComponent[mobid][mine_teamid] != GetPlayerTeam(playerid)) || (MineComponent[mobid][mine_teamid] == ANY_TEAM) && tmp_det){
				MineComponent[mobid][mine_health] = 0.0;
				ExplodeDynamicMine(mobid,MINE_DESTROY_TYPE_DETECT,playerid);
			}
		}
	}	
	#if defined MDM_OnPlayerEnterDynamicArea
		MDM_OnPlayerEnterDynamicArea(playerid, areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea MDM_OnPlayerEnterDynamicArea
#if defined MDM_OnPlayerEnterDynamicArea
	forward MDM_OnPlayerEnterDynamicArea(playerid, areaid);
#endif

//EOF