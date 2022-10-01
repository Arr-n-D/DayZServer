class PSGJSon
{  
    protected string m_SteamID;
    protected int m_MutantLvl;
    protected int m_FirstMutation;
    protected int m_SecondMutation;
    protected int m_Amputee;

    void PSGJSon(string id, int affectedLevel)  
    {
        m_SteamID = id;
        m_MutantLvl = mutlvl;
        m_FirstMutation = fstmut;
        m_SecondMutation = secmut;
        m_Amputee = amp;
    }

    string GetJSONSteamID()
    {
        return m_SteamID;
    }
    
    void SetJSONSteamID(string steamid)
    {
        m_SteamID = steamid;
    }

    int GetJSONMutantLevel()
    {
        return m_MutantLvl;
    }

    void SetJSONMutantLevel(int mutantlevel)
    {
        m_MutantLvl = mutantlevel;
    }

    int GetJSONFirstMutation()
    {
        return m_FirstMutation;
    }

    void SetJSONFirstMutation(int firstmutation)
    {
        m_FirstMutation = firstmutation;
    }

    int GetJSONSecondMutation()
    {
        return m_SecondMutation;
    }

    void SetJSONSecondMutation(int secondmutation)
    {
        m_SecondMutation = secondmutation;
    }

    int GetJSONAmputation()
    {
        return m_Amputee;
    }

    void SetJSONAmputation(int amputation)
    {
        m_Amputee = amputation;
    }


};

class DUBJSONConfig
{
    ref array<ref DUBJSONInfo> m_DUBJSONInfo;

    void UpdateJSON(string pid, int mutantlvl, int firsttmut, int secondmut, int amputation)
    {
        int playerIndex = IsPlayerInJSON(pid);
        if (playerIndex > -1)
        {
            m_DUBJSONInfo.Get(playerIndex).SetJSONMutantLevel(mutantlvl);
            m_DUBJSONInfo.Get(playerIndex).SetJSONFirstMutation(firsttmut);
            m_DUBJSONInfo.Get(playerIndex).SetJSONSecondMutation(secondmut);
            m_DUBJSONInfo.Get(playerIndex).SetJSONAmputation(amputation);

            GetDayZGame().SaveDUBJSON();
            Print("UpdatingDressupboxJson");
        }    
    }

    int GetJSONMutant(string pid)
    {
        int mutantlvl;
        int playerIndex = IsPlayerInJSON(pid);
        if (playerIndex > -1)
        {
            mutantlvl = m_DUBJSONInfo.Get(playerIndex).GetJSONMutantLevel();
        }
        return mutantlvl;   
    }

    int GetJSONFirstMutation(string pid)
    {
        int firsttmut;
        int playerIndex = IsPlayerInJSON(pid);
        if (playerIndex > -1)
        {
            firsttmut = m_DUBJSONInfo.Get(playerIndex).GetJSONFirstMutation();
        }
        return firsttmut;  
    }

    int GetJSONSecondMutation(string pid)
    {
        int secondmut;
        int playerIndex = IsPlayerInJSON(pid);
        if (playerIndex > -1)
        {
            secondmut = m_DUBJSONInfo.Get(playerIndex).GetJSONSecondMutation();
        }
        return secondmut;  
    }

    int GetJSONAmputation(string pid)
    {
        int amputation;
        int playerIndex = IsPlayerInJSON(pid);
        if (playerIndex > -1)
        {
            amputation = m_DUBJSONInfo.Get(playerIndex).GetJSONAmputation();
        }
        return amputation;  
    }

    void NewJSON(string pid, int mutantlvl, int firsttmut, int secondmut, int amputation)
    {
        int playerIndex = IsPlayerInJSON(pid);
        if (playerIndex == -1)
        {
            m_DUBJSONInfo.Insert(new DUBJSONInfo(pid,mutantlvl,firsttmut,secondmut,amputation));
            GetDayZGame().SaveDUBJSON();
            Print("NewDressupboxJson");
        }
    }

    int IsPlayerInJSON(string steamId)
    {  
        for (int i = 0; i < m_DUBJSONInfo.Count(); i++ )
        {
            if (m_DUBJSONInfo.Get(i).GetJSONSteamID() == steamId)
            {
                return i;
            }
        }
        return -1;
    }

};

