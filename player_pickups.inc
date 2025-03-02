/*
	Author: Saibot
*/

#if defined _s_player_pickups_inc
	#endinput
#endif
#define _s_player_pickups_inc


#if !defined PAWNRAKNET_INC_
	#error "Please include Pawn.RakNet before player_pickups"
#endif

#if !defined _streamer_included
	#error "Please include streamer before player_pickups"
#endif

#if !defined _FOREACH_LOCAL_VERSION
	#error "Please include foreach before player_pickups"
#endif

static const ORPC_CREATE_PL_PICKUP = 95;

static bool:gPlayerPickupsIsStreamPickup[MAX_PICKUPS];


forward OnPlayerPickUpPlayerPickup(playerid, pickupid);


public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	if (IsPlayerPickup(pickupid))
	{
		if (IsPlayerPickupForPlayer(playerid, pickupid))
		{
			CallRemoteFunction(
				"OnPlayerPickUpPlayerPickup",
				"dd",
				playerid,
				pickupid
			);
			return 1;
		}
	}
#if defined sppick_OnPlayerPickUpDynPickup
	return sppick_OnPlayerPickUpDynPickup(playerid, pickupid);
#else
	return 1;
#endif
}
#if defined _ALS_OnPlayerPickUpDynPickup
	#undef OnPlayerPickUpDynamicPickup
#else
	#define _ALS_OnPlayerPickUpDynPickup
#endif
#define OnPlayerPickUpDynamicPickup sppick_OnPlayerPickUpDynPickup
#if defined    sppick_OnPlayerPickUpDynPickup
	forward sppick_OnPlayerPickUpDynPickup(playerid, pickupid);
#endif

ORPC:ORPC_CREATE_PL_PICKUP(playerid, BitStream:bs)
{
	static iPickupID;

	BS_ReadValue(bs, PR_INT16, iPickupID);

	new streamer_pickupid = Streamer_GetItemStreamerID(playerid, STREAMER_TYPE_PICKUP, iPickupID);

	if (IsPlayerPickup(streamer_pickupid))
	{
		new targetid = Streamer_GetIntData(STREAMER_TYPE_PICKUP, streamer_pickupid, E_STREAMER_PLAYER_ID);

		if (targetid != playerid)
		{
			return 0;
		}
	}
	return 1;
}


/*

	functions

*/

stock CreatePlayerPickup(playerid, modelid, type, Float:x, Float:y, Float:z, worldid = -1, Float:streamdistance)
{
	new pickupid = CreateDynamicPickup(
		modelid,
		type,
		x,
		y,
		z,
		.worldid = worldid,
		.playerid = playerid,
		.streamdistance = streamdistance
	);
	if (pickupid == -1)
	{
		return -1;
	}
	Iter_Add(PlayerPickupsId[playerid], pickupid);
	SetPlayerPickupValue(pickupid, true);
	return pickupid;
}

stock DestroyPlayerPickup(playerid, pickupid)
{
	if (!IsPlayerPickupForPlayer(playerid, pickupid))
	{
		return 0;
	}
	Iter_Remove(PlayerPickupsId[playerid], pickupid);
	SetPlayerPickupValue(pickupid, false);
	return DestroyDynamicPickup(pickupid);
}

stock IsValidPlayerPickup(playerid, pickupid)
{
	if (!IsPlayerPickupForPlayer(playerid, pickupid))
	{
		return 0;
	}
	return IsValidDynamicPickup(pickupid);
}

stock SetPlayerPickupVirtualWorld(playerid, pickupid, worldid)
{
	if (!IsPlayerPickupForPlayer(playerid, pickupid))
	{
		return 0;
	}
	return Streamer_SetIntData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_WORLD_ID, worldid);
}

stock SetPlayerPickupPos(playerid, pickupid, Float:x, Float:y, Float:z)
{
	if (!IsPlayerPickupForPlayer(playerid, pickupid))
	{
		return 0;
	}
	Streamer_SetFloatData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_X, x);
	Streamer_SetFloatData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_Y, y);
	Streamer_SetFloatData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_Z, z);
	return 1;
}

stock SetPlayerPickupModel(playerid, pickupid, modelid)
{
	if (!IsPlayerPickupForPlayer(playerid, pickupid))
	{
		return 0;
	}
	return Streamer_SetIntData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_MODEL_ID, modelid);
}

stock SetPlayerPickupType(playerid, pickupid, typeid)
{
	if (!IsPlayerPickupForPlayer(playerid, pickupid))
	{
		return 0;
	}
	return Streamer_SetIntData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_TYPE, typeid);
}

stock GetPlayerPickupVirtualWorld(playerid, pickupid)
{
	if (!IsPlayerPickupForPlayer(playerid, pickupid))
	{
		return 0;
	}
	return Streamer_GetIntData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_WORLD_ID);
}

stock GetPlayerPickupPos(playerid, pickupid, &Float:x, &Float:y, &Float:z)
{
	if (!IsPlayerPickupForPlayer(playerid, pickupid))
	{
		return 0;
	}
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_X, x);
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_Y, y);
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_Z, z);
	return 1;
}

stock GetPlayerPickupModel(playerid, pickupid)
{
	if (!IsPlayerPickupForPlayer(playerid, pickupid))
	{
		return 0;
	}
	return Streamer_GetIntData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_MODEL_ID, modelid);
}

stock GetPlayerPickupType(playerid, pickupid)
{
	if (!IsPlayerPickupForPlayer(playerid, pickupid))
	{
		return 0;
	}
	return Streamer_GetIntData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_TYPE, modelid);
}


/*

	static functions

*/

static stock SetPlayerPickupValue(pickupid, bool:value)
{
	gPlayerPickupsIsStreamPickup[pickupid] = value;
	return 1;
}

static stock IsPlayerPickupForPlayer(playerid, pickupid)
{
	return Streamer_GetIntData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_PLAYER_ID) == playerid;
}

static stock IsPlayerPickup(pickupid)
{
	return gPlayerPickupsIsStreamPickup[pickupid];
}