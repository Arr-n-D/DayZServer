
modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        PSGJsonConfig config = GetDayZGame().GetPSGJsonConfig();
        GetDayZGame().SetPSGJson(config);
    }
	
};
