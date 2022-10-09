
modded class MissionBase
{
    void MissionBase() {
        GetRPCManager().AddRPC("PSGRpc", "TeleportPlayer", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("PSGRpc", "FailTeleportPlayer", this, SingleplayerExecutionType.Server);

        GetRPCManager().AddRPC("PSGRpc", "PlayTeleportSound", this, SingleplayerExecutionType.Both);
    }

    void TeleportPlayer(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
        Param1<vector> data;
        if (!ctx.Read(data)) return;

       
        PlayerBase player;
        int networkIdLowBits;
        int networkIdHighBits;
        GetGame().GetPlayerNetworkIDByIdentityID(sender.GetPlayerId(), networkIdLowBits, networkIdHighBits);
        Class.CastTo(player, GetGame().GetObjectByNetworkId(networkIdLowBits, networkIdHighBits));

        GetRPCManager().SendRPC("PSGRpc", "PlayTeleportSound", new Param1<vector>(data.param1));


        if (player) {
            player.SetPosition(data.param1);
        }
    }

    void FailTeleportPlayer(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
        Param1<string> data;
        if (!ctx.Read(data)) return;

        
        PlayerBase player;
        int networkIdLowBits;
        int networkIdHighBits;
        GetGame().GetPlayerNetworkIDByIdentityID(sender.GetPlayerId(), networkIdLowBits, networkIdHighBits);
        Class.CastTo(player, GetGame().GetObjectByNetworkId(networkIdLowBits, networkIdHighBits));
        if (player) {
            player.SendMessageToClient(player, data.param1);
        }
    }

    void PlayTeleportSound(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
        if(!GetGame().IsDedicatedServer()) {
             Param1<vector> data;
            if (!ctx.Read(data)) return;

		    vector pos = data.param1;
		    EffectSound sound =	SEffectManager.PlaySound("Cassius_Teleport_SoundSet", pos);
		    sound.SetSoundAutodestroy(true);
        }
	}
    
};
