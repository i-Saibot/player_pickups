# Player Pickups
This library for SAMP helps you create a pickup that will be visible only to a specific player.

>Dependencies: Pawn.RakNet, streamer, and foreach.

**Callback: Triggered when a player picks up a player pickup.**
```pawn
forward OnPlayerPickUpPlayerPickup(playerid, pickupid);
```

**Functions: I think the names are self-explanatory.**
```pawn
CreatePlayerPickup(playerid, modelid, type, Float:x, Float:y, Float:z, worldid = -1, Float:streamdistance);
DestroyPlayerPickup(playerid, pickupid);

IsValidPlayerPickup(playerid, pickupid);

SetPlayerPickupVirtualWorld(playerid, pickupid, worldid);
SetPlayerPickupPos(playerid, pickupid, Float:x, Float:y, Float:z);
SetPlayerPickupModel(playerid, pickupid, modelid);
SetPlayerPickupType(playerid, pickupid, typeid);

GetPlayerPickupVirtualWorld(playerid, pickupid);
GetPlayerPickupPos(playerid, pickupid, &Float:x, &Float:y, &Float:z);
GetPlayerPickupModel(playerid, pickupid);
GetPlayerPickupType(playerid, pickupid);
```

>The pickups are automatically removed after the player exits.
