modded class DayZGame
{
	protected ref PSGJsonConfig m_PSGJsonConfig;

	void SetPSGJson(PSGJsonConfig config)
	{
		m_PSGJsonConfig = config;
		Print("PSG JSON Config loaded from server");
	}

	void SavePSGJson()
	{
		JsonFileLoader<ref PSGJsonConfig>.JsonSaveFile("$profile:\\PSGConfig\\PSGJson.json", m_PSGJsonConfig);
		Print("PSGJson Settings Saved");
	}

	PSGJsonConfig GetPSGJsonConfig()
	{
		if (!m_PSGJsonConfig)
		{
			if (!FileExist("$profile:\\PSGConfig"))
			{
				MakeDirectory("$profile:\\PSGConfig");
			}
			if (!FileExist("$profile:\\PSGConfig\\PSGJson.json")) 
			{
				m_PSGJsonConfig = new PSGJsonConfig();

				m_PSGJsonConfig.m_PSGJsonInfo = new ref array<ref PSGJsonInfo>;

				m_PSGJsonConfig.m_PSGJsonInfo.Insert(new PSGJsonInfo("test", 0, 0));

				JsonFileLoader<ref PSGJsonConfig>.JsonSaveFile("$profile:\\PSGConfig\\PSGJson.json", m_PSGJsonConfig);
			} 
			else
			{
				JsonFileLoader<ref PSGJsonConfig>.JsonLoadFile("$profile:\\PSGConfig\\PSGJson.json", m_PSGJsonConfig);			
			}		
		}
		return m_PSGJsonConfig;
	}

	void ~DayZGame()
	{
		delete m_PSGJsonConfig;
	}

	override string CreateRandomPlayer()
    {
		
		if(GetGame().IsDedicatedServer())
		{
			Man player = GetGame().GetPlayer();
			if(player)
			{
				PlayerIdentity p_identity = player.GetIdentity();
				string SteamID = p_identity.GetPlainId();
				PSGJsonConfig config = GetDayZGame().GetPSGJsonConfig();
				config.UpdateJSON(SteamID,0, 0);
			}
		}
		return super.CreateRandomPlayer();
	}
}