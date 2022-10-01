modded class DayZGame
{
	protected ref DUBJSONConfig m_DUBJSONConfig;

	void SetDUBJSON(DUBJSONConfig config)
	{
		m_DUBJSONConfig = config;
		Print("Dressupbox Settings Received From Server");
	}

	void SaveDUBJSON()
	{
		JsonFileLoader<ref DUBJSONConfig>.JsonSaveFile("$profile:\\Dressupbox\\DUBJSON.json", m_DUBJSONConfig);
		Print("Dressupbox Settings Saved");
	}

	DUBJSONConfig GetDUBJSONConfig()
	{
		if (!m_DUBJSONConfig)
		{
			if (!FileExist("$profile:\\Dressupbox"))
			{
				MakeDirectory("$profile:\\Dressupbox");
			}
			if (!FileExist("$profile:\\Dressupbox\\DUBJSON.json")) 
			{
				m_DUBJSONConfig = new DUBJSONConfig();

				m_DUBJSONConfig.m_DUBJSONInfo = new ref array<ref DUBJSONInfo>;

				m_DUBJSONConfig.m_DUBJSONInfo.Insert(new DUBJSONInfo("test",0,0,0,0));

				JsonFileLoader<ref DUBJSONConfig>.JsonSaveFile("$profile:\\Dressupbox\\DUBJSON.json", m_DUBJSONConfig);
			} 
			else
			{
				JsonFileLoader<ref DUBJSONConfig>.JsonLoadFile("$profile:\\Dressupbox\\DUBJSON.json", m_DUBJSONConfig);			
			}		
		}
		return m_DUBJSONConfig;
	}

	void ~DayZGame()
	{
		delete m_DUBJSONConfig;
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
				DUBJSONConfig config = GetDayZGame().GetDUBJSONConfig();
				config.UpdateJSON(SteamID,0,0,0,0);
			}
		}
		return super.CreateRandomPlayer();
	}
}