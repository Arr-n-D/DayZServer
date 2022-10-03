class PSGJsonInfo
{  
    protected string m_SteamID;
    protected int m_AffectedLevel;
    protected int m_IsPrime;

    void PSGJsonInfo(string id, int affectedLevel, int isPrime)  
    {
        m_SteamID = id;
        m_AffectedLevel = affectedLevel;
        m_IsPrime = isPrime;
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

    int GetJSONIsPrime()
    {
        return m_IsPrime;
    }

    void SetJSONIsPrime(int isPrime)
    {
        m_IsPrime = isPrime;
    }
};

class PSGJsonConfig
{
    ref array<ref PSGJsonInfo> m_PSGJsonInfo;

    void UpdateJSON(string playerId, int affectedLevel, int isPrime)
    {
        int playerIndex = IsPlayerInJSON(playerId);
        if (playerIndex > -1)
        {
            m_PSGJsonInfo.Get(playerIndex).SetJSONAffectedLevel(affectedLevel);
            m_PSGJsonInfo.Get(playerIndex).SetJSONIsPrime(isPrime);
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

    int GetJSONIsPrime(string playerId)
    {
        int isPrime;
        int playerIndex = IsPlayerInJSON(playerId);
        if (playerIndex > -1)
        {
            isPrime = m_PSGJsonInfo.Get(playerIndex).GetJSONIsPrime();
        }
        return isPrime;   
    }

    void NewJSON(string playerId, int affectedLevel, int isPrime)
    {
        int playerIndex = IsPlayerInJSON(playerId);
        if (playerIndex == -1)
        {
            m_PSGJsonInfo.Insert(new PSGJsonInfo(playerId,affectedLevel, isPrime));
            GetDayZGame().SavePSGJson();
            Print("New JSON entry");
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

