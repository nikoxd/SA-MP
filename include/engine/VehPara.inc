/****************************************************************************************************
 *                                                                                                  *
 *                                        Vehicle Parachute                                         *
 *                                                                                                  *
 * Copyright � 2017 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                        *
 * Publication: http://forum.sa-mp.com/showthread.php?p=3848232                                     *
 *                                                                                                  *
 * Plugins: Streamer, ColAndreas                                                                    *
 * Modules: 3DTryg                                                                                  *
 * Attributes: None                                                                                 *
 *                                                                                                  *
 * File Version: 1.0.1                                                                              *
 * SA:MP Version: 0.3.7 (REQUIRE)                                                                   *
 * Streamer Version: 2.8.2                                                                          *
 * ColAndreas Version: 1.4.0                                                                        *
 * 3DTryg Version: 4.0.2                                                                            *
 *                                                                                                  *
 * Functions:                                                                                       *
 * bool:IsPlayerUsingVehPara(playerid);                                                             *
 * bool:IsToggleVehicleParachute(vehicleid);                                                        *
 * ToggleVehicleParachute(vehicleid,bool:toggle);                                                   *
 *                                                                                                  *
 ****************************************************************************************************/
 
#if defined _vehicle_parachute
	#endinput
#endif
#define _vehicle_parachute

#if (!defined GetPlayerPoolSize)
	#error [ADM] This include requires SA:MP version 0.3.7
#endif

#if ((!defined Streamer_AppendArrayData) || (!defined INVALID_STREAMER_ID))
	#error [ADM] Unknown Streamer Version
#endif

#if !defined COLANDREAS
	#error [ADM] Unknown ColAndreas Version
#endif

//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v4.0.2
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v4.0.2
#elseif (Tryg3D_Version < 40002)
	#error [ADM] Update you 3DTryg.inc to v4.0.2
#endif

new VehicleConfigParachute[64],
	VehicleParachuteObject[MAX_VEHICLES][3],
	PlayerUsingVehPara[32];

//Get Compress Adress
#define GetVehicleParaConfAddress(%0)				(floatround((%0)/32))
#define GetVehicleParaConfBit(%0)					((%0) % 32)

//BitFunctions.inc
#define VP_GetValueBit(%0,%1)						((%0) >>> (%1) & 0x01)
#define VP_SetValueBit(%0,%1,%2)					((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

#define IsPlayerUsingVehPara(%0)					VP_GetValueBit(PlayerUsingVehPara[GetVehicleParaConfAddress(%0)],GetVehicleParaConfBit(%0))
#define TogglePlayerUsingVehPara(%0,%1)				VP_SetValueBit(PlayerUsingVehPara[GetVehicleParaConfAddress(%0)],GetVehicleParaConfBit(%0),(%1))

#define IsToggleVehicleParachute(%0)				VP_GetValueBit(VehicleConfigParachute[GetVehicleParaConfAddress(%0)],GetVehicleParaConfBit(%0))

stock ToggleVehicleParachute(vehicleid,bool:toggle){
	if(IsValidDynamicObject(VehicleParachuteObject[vehicleid][0])) DestroyDynamicObject(VehicleParachuteObject[vehicleid][0]);
	VehicleParachuteObject[vehicleid][0] = INVALID_STREAMER_ID;
	
	if(IsValidDynamicObject(VehicleParachuteObject[vehicleid][1])) DestroyDynamicObject(VehicleParachuteObject[vehicleid][1]);
	VehicleParachuteObject[vehicleid][1] = INVALID_STREAMER_ID;
	
	if(IsValidDynamicObject(VehicleParachuteObject[vehicleid][2])) DestroyDynamicObject(VehicleParachuteObject[vehicleid][2]);
	VehicleParachuteObject[vehicleid][2] = INVALID_STREAMER_ID;
	
	if(toggle){
		if(!IsToggleVehicleParachute(vehicleid)){
			new T3D:vw = GetVehicleVirtualWorld(vehicleid);
			VehicleParachuteObject[vehicleid][1] = CreateDynamicObject(1310,0.0,0.0,-6000.0,0.0,0.0,0.0,T3D:vw,-1);
			VehicleParachuteObject[vehicleid][2] = CreateDynamicObject(1310,0.0,0.0,-6000.0,0.0,0.0,0.0,T3D:vw,-1);
			
			new Float:T3D:x,Float:T3D:y,Float:T3D:z;
			GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_SIZE,T3D:x,T3D:y,T3D:z);
			T3D:z /= 2.0;
		
			AttachDynamicObjectToVehicle(VehicleParachuteObject[vehicleid][1],vehicleid,0.5,0.0,T3D:z+0.1,270.0,0.0,35.0);
			AttachDynamicObjectToVehicle(VehicleParachuteObject[vehicleid][2],vehicleid,-0.5,0.0,T3D:z+0.1,270.0,0.0,325.0);
		}
	}
	VP_SetValueBit(VehicleConfigParachute[GetVehicleParaConfAddress(vehicleid)],GetVehicleParaConfBit(vehicleid),(_:toggle));
}

stock StartVehicleParachuteAction(playerid){
	TogglePlayerUsingVehPara(playerid,1);
	
	new vid = GetPlayerVehicleID(playerid);
	if(IsValidDynamicObject(VehicleParachuteObject[vid][1])) DestroyDynamicObject(VehicleParachuteObject[vid][1]);
	VehicleParachuteObject[vid][1] = INVALID_STREAMER_ID;
	
	if(IsValidDynamicObject(VehicleParachuteObject[vid][2])) DestroyDynamicObject(VehicleParachuteObject[vid][2]);
	VehicleParachuteObject[vid][2] = INVALID_STREAMER_ID;
	
	if(IsValidDynamicObject(VehicleParachuteObject[vid][0])) DestroyDynamicObject(VehicleParachuteObject[vid][0]);
	VehicleParachuteObject[vid][0] = CreateDynamicObject(18849,0.0,0.0,-6000.0,0.0,0.0,0.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid));
	
	switch(random(5)){
		case 0: {
			SetDynamicObjectMaterial(VehicleParachuteObject[vid][0],0,18841,"MickyTextures","Smileyface2",0x00000000);
			SetDynamicObjectMaterial(VehicleParachuteObject[vid][0],2,10412,"hotel1","carpet_red_256",0x00FFFFFF);
		}
		case 1: {
			SetDynamicObjectMaterial(VehicleParachuteObject[vid][0],0,18841,"MickyTextures","red032",0x00000000);
			SetDynamicObjectMaterial(VehicleParachuteObject[vid][0],2,10412,"hotel1","carpet_red_256",0x00FFFFFF);
		}
		case 2: {
			SetDynamicObjectMaterial(VehicleParachuteObject[vid][0],0,18841,"MickyTextures","ws_gayflag1",0x00000000);
			SetDynamicObjectMaterial(VehicleParachuteObject[vid][0],2,10412,"hotel1","carpet_red_256",0x00FFFFFF);
		}
		case 3: {
			SetDynamicObjectMaterial(VehicleParachuteObject[vid][0],0,18841,"MickyTextures","waterclear256",0x00000000);
			SetDynamicObjectMaterial(VehicleParachuteObject[vid][0],2,10412,"hotel1","carpet_red_256",0x00FFFFFF);
		}
		case 4: {
			SetDynamicObjectMaterial(VehicleParachuteObject[vid][0],2,10412,"hotel1","carpet_red_256",0x00FFFFFF);
		}
	}
	new Float:T3D:x,Float:T3D:y,Float:T3D:z;
	GetVehicleModelInfo(GetVehicleModel(vid),VEHICLE_MODEL_INFO_SIZE,T3D:x,T3D:y,T3D:z);
	T3D:z /= 2.0;
	AttachDynamicObjectToVehicle(VehicleParachuteObject[vid][0],vid,0.0,0.0,T3D:z+6.0,0.0,0.0,90.0);
}

stock StopVehicleParachuteAction(playerid,vehicleid=INVALID_VEHICLE_ID){
	TogglePlayerUsingVehPara(playerid,0);
	if(vehicleid == INVALID_VEHICLE_ID) vehicleid = GetPlayerVehicleID(playerid);
	ToggleVehicleParachute(vehicleid,false);
}

//Hook: OnPlayerUpdate
public OnPlayerUpdate(playerid){
	if(IsPlayerUsingVehPara(playerid)){
		if(IsCollisionFlag(GetElementCollisionFlags(GetPlayerVehicleID(playerid),item_vehicle),POSITION_FLAG_GROUND)){
			StopVehicleParachuteAction(playerid);
			GameTextForPlayer(playerid,"~g~Parachute has been thrown",2500,3);
		} else {
			static vid, Float:T3D:x, Float:T3D:y, Float:T3D:z;
			vid = GetPlayerVehicleID(playerid);
			GetVehicleVelocity(vid,T3D:x,T3D:y,T3D:z);
			SetVehicleVelocity(vid,T3D:x,T3D:y,-0.2);
		}
	}
	#if defined VP_OnPlayerUpdate
		VP_OnPlayerUpdate(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate VP_OnPlayerUpdate
#if defined VP_OnPlayerUpdate
	forward VP_OnPlayerUpdate(playerid);
#endif

//Hook: OnVehicleSpawn
public OnVehicleSpawn(vehicleid){
	ToggleVehicleParachute(vehicleid,false);
	#if defined VP_OnVehicleSpawn
		VP_OnVehicleSpawn(vehicleid);
	#endif
	return 1;
}

#if defined _ALS_OnVehicleSpawn
	#undef OnVehicleSpawn
#else
	#define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn VP_OnVehicleSpawn
#if defined VP_OnVehicleSpawn
	forward VP_OnVehicleSpawn(vehicleid);
#endif

//Hook: OnPlayerEnterVehicle
public OnPlayerEnterVehicle(playerid,vehicleid,ispassenger){
	if(IsValidDynamicObject(VehicleParachuteObject[vehicleid][0])){
		ToggleVehicleParachute(vehicleid,false);
		GameTextForPlayer(playerid,"~g~Parachute has been thrown",2500,3);
	}
	#if defined VP_OnPlayerEnterVehicle
		VP_OnPlayerEnterVehicle(playerid,vehicleid,ispassenger);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif
#define OnPlayerEnterVehicle VP_OnPlayerEnterVehicle
#if defined VP_OnPlayerEnterVehicle
	forward VP_OnPlayerEnterVehicle(playerid,vehicleid,ispassenger);
#endif

//Hook: OnPlayerExitVehicle
public OnPlayerExitVehicle(playerid,vehicleid){
	if(IsPlayerUsingVehPara(playerid)){
		StopVehicleParachuteAction(playerid);
		GameTextForPlayer(playerid,"~g~Parachute has been thrown",2500,3);
	}
	#if defined VP_OnPlayerExitVehicle
		VP_OnPlayerExitVehicle(playerid,vehicleid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerExitVehicle
	#undef OnPlayerExitVehicle
#else
	#define _ALS_OnPlayerExitVehicle
#endif
#define OnPlayerExitVehicle VP_OnPlayerExitVehicle
#if defined VP_OnPlayerExitVehicle
	forward VP_OnPlayerExitVehicle(playerid,vehicleid);
#endif

//Hook: OnPlayerStateChange
public OnPlayerStateChange(playerid,newstate,oldstate){
	if(oldstate == PLAYER_STATE_DRIVER && IsPlayerUsingVehPara(playerid)){
		StopVehicleParachuteAction(playerid,GetPlayerVehicleID(playerid));
	}
	#if defined VP_OnPlayerStateChange
		VP_OnPlayerStateChange(playerid,newstate,oldstate);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange VP_OnPlayerStateChange
#if defined VP_OnPlayerStateChange
	forward VP_OnPlayerStateChange(playerid,newstate,oldstate);
#endif

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0){
		new vid = GetPlayerVehicleID(playerid);
		if(Tryg3D_KeyPressed(KEY_CROUCH)){
			if(IsToggleVehicleParachute(vid)){
				if(IsPlayerUsingVehPara(playerid)){
					StopVehicleParachuteAction(playerid);
					GameTextForPlayer(playerid,"~g~Parachute has been thrown",2500,3);
				} else {
					if(IsCollisionFlag(GetElementCollisionFlags(vid,item_vehicle),POSITION_FLAG_AIR)){
						StartVehicleParachuteAction(playerid);
						GameTextForPlayer(playerid,"~g~Parachute has been opened",2500,3);
					} else {
						GameTextForPlayer(playerid,"~g~Cannot use parachute",2500,3);
					}
				}
			}
		}
	}
	#if defined VP_OnPlayerKeyStateChange
		VP_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange VP_OnPlayerKeyStateChange
#if defined VP_OnPlayerKeyStateChange
	forward VP_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

//Hook: PutPlayerInVehicle
stock VP_PutPlayerInVehicle(playerid,vehicleid,seatid){
	if(IsValidDynamicObject(VehicleParachuteObject[vehicleid][0])){
		ToggleVehicleParachute(vehicleid,false);
	}
	return PutPlayerInVehicle(playerid,vehicleid,seatid);
}

#if defined _ALS_PutPlayerInVehicle
    #undef PutPlayerInVehicle
#else
    #define _ALS_PutPlayerInVehicle
#endif
#define PutPlayerInVehicle VP_PutPlayerInVehicle

//Hook: CreateVehicle
stock VP_CreateVehicle(modelid,Float:x,Float:y,Float:z,Float:angle,color1,color2,respawn_delay,addsiren=0){
	new vehicleid = CreateVehicle(modelid,x,y,z,angle,color1,color2,respawn_delay,addsiren);
	ToggleVehicleParachute(vehicleid,false);
	return vehicleid;
}
 
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
#define CreateVehicle VP_CreateVehicle
 
//Hook: AddStaticVehicle
stock VP_AddStaticVehicle(modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:angle,color1,color2){
	new vehicleid = AddStaticVehicle(modelid,spawn_x,spawn_y,spawn_z,angle,color1,color2);
	ToggleVehicleParachute(vehicleid,false);
	return vehicleid;
}
 
#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif
#define AddStaticVehicle VP_AddStaticVehicle
 
//Hook: AddStaticVehicleEx
stock VP_AddStaticVehicleEx(modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:angle,color1,color2,respawn_delay,addsiren=0){
	new vehicleid = AddStaticVehicleEx(modelid,spawn_x,spawn_y,spawn_z,angle,color1,color2,respawn_delay,addsiren);
	ToggleVehicleParachute(vehicleid,false);
	return vehicleid;
}
 
#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx VP_AddStaticVehicleEx
 
//Hook: DestroyVehicle
stock VP_DestroyVehicle(vehicleid){
	ToggleVehicleParachute(vehicleid,false);
	return DestroyVehicle(vehicleid);
}
 
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
#define DestroyVehicle VP_DestroyVehicle

//EOF