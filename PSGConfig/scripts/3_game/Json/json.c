class PSGJsonInfo
{  
    protected string m_SteamID;
    protected int m_AffectedLevel;

    void PSGJsonInfo(string id, int affectedLevel)  
    {
        m_SteamID = id;
        m_AffectedLevel = affectedLevel;
    }

    string GetJSONSteamID()
    {
        return m_SteamID;
    }
    
    void SetJSONSteamID(string steamid)
    {
        m_SteamID = steamid;
    }

    int GetJSONAffectedLevel()
    {
        return m_AffectedLevel;
    }

    void SetJSONAffectedLevel(int affectedLevel)
    {
        m_AffectedLevel = affectedLevel;
    }
};

class PSGJsonConfig
{
    ref array<ref PSGJsonInfo> m_PSGJsonInfo;

    void UpdateJSON(string playerId, int affectedLevel)
    {
        int playerIndex = IsPlayerInJSON(playerId);
        if (playerIndex > -1)
        {
            m_PSGJsonInfo.Get(playerIndex).SetJSONAffectedLevel(affectedLevel);
            GetDayZGame().SavePSGJson();
            Print("Saving JSON");
        }    
    }

    int GetJSONAffectedLevel(string playerId)
    {
        int affectedLevel;
        int playerIndex = IsPlayerInJSON(playerId);
        if (playerIndex > -1)
        {
            affectedLevel = m_PSGJsonInfo.Get(playerIndex).GetJSONAffectedLevel();
        }
        return affectedLevel;   
    }

    void NewJSON(string playerId, int affectedLevel)
    {
        int playerIndex = IsPlayerInJSON(playerId);
        if (playerIndex == -1)
        {
            m_PSGJsonInfo.Insert(new PSGJsonInfo(playerId,affectedLevel));
            GetDayZGame().SavePSGJson();
            Print("New JSON");
        }
    }

    int IsPlayerInJSON(string steamId)
    {  
        for (int i = 0; i < m_PSGJsonInfo.Count(); i++ )
        {
            if (m_PSGJsonInfo.Get(i).GetJSONSteamID() == steamId)
            {
                return i;
            }
        }
        return -1;
    }

};

