modded class PlayerBase
{
	bool isPrime;
    bool isAffected;
    bool isZombieClose;
	protected bool m_IsInBioZone = false;
	int affectedLevel;

	string SteamID;
	
	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableInt("affectedLevel",0,5);
		isPrime = false;
		isAffected = false;
		isZombieClose = false;
		affectedLevel = 0;
		
		
	};
	void ~PlayerBase()
	{
		if ( GetGame() && ( !GetGame().IsDedicatedServer() ) )
		{
			ClientData.RemovePlayerBase( this );
			SetContaminatedEffectEx(false);
		}
		
		SEffectManager.DestroyEffect(m_FliesEff);
		StopSoundSet(m_SoundFliesEffect);
		isPrime = false;
	}
	override void OnPlayerLoaded()
	{
		super.OnPlayerLoaded();

		PlayerJSONSave();
		JSONSynchDirty();
		// AgentUpdater();
	}
	override void OnConnect()//serverside only
	{
		super.OnConnect();
		if (GetIdentity())
		{
			SteamID = GetIdentity().GetPlainId();
		}
	}

//JSON
	void PlayerJSONUpdate()
	{
		if(GetGame().IsDedicatedServer())
		{	
			PSGJsonConfig config = GetDayZGame().GetPSGJsonConfig();
			config.UpdateJSON(GetSteamID(),GetAffectedLevel());
		}
	}
	void PlayerJSONSave()
	{
		if(GetGame().IsDedicatedServer())
		{
			PSGJsonConfig config = GetDayZGame().GetPSGJsonConfig();
			config.NewJSON(GetSteamID(),GetAffectedLevel());
		}
	}
	void JSONSynchDirty()
	{
		if(GetGame().IsDedicatedServer())
		{
			PSGJsonConfig config = GetDayZGame().GetPSGJsonConfig();
			affectedLevel = config.GetJSONAffectedLevel(GetSteamID());
			SetSynchDirty();
		}
		
	}

	string GetSteamID()
	{
		return SteamID;
	};
	

//Mutation
	int GetAffectedLevel()
	{
		return affectedLevel;
	};
	void SetAffectedLevel(int level)
	{
		affectedLevel = level;
		SetSynchDirty();
	};
	
	// void AgentUpdater()
	// {
	// 	if(GetGame().IsDedicatedServer())
	// 	{
	// 		int mutelevel = GetAffectedLevel();
	// 		if(mutelevel == 1)
	// 		{
	// 			if(GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 2400)
	// 			{
	// 				m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 2400);
	// 			}
	// 		}

	// 		if(mutelevel == 2)
	// 		{
	// 			if(GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 10053)
	// 			{
	// 				m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 10053);
	// 			}
	// 		}

	// 		if(mutelevel == 3)
	// 		{
	// 			if(GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 28800)
	// 			{
	// 				m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 28800);
	// 			}
	// 		}

	// 		if(mutelevel == 4)
	// 		{
	// 			if(GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 86893)
	// 			{
	// 				m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 86893);
	// 			}
	// 		}

	// 		if(mutelevel == 5)
	// 		{
	// 			if(GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 115692)
	// 			{
	// 				m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 115693);
	// 			}
	// 		}
	// 	}
	// }
	bool ZombieClose()
	{
		return isZombieClose;
	}

//Alphas
	bool IsPrime()
	{
		return isPrime;
	};
	void SetIsPrime(bool prime)
	{
		isPrime = prime;
		SetSynchDirty();
	};

	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);

		if(!GetGame().IsDedicatedServer())
		{
			if(GetAffectedLevel() >= 3)
			{
				ItemBase eyewear = GetItemOnSlot("Eyewear");
				if (eyewear)
				{
					PPEffects.SetEVValuePP(2.1); 
				}
				else
				{
					PPEffects.SetEVValuePP(5.5);
				}   
			}
		}
	};
	
	override bool CanBeTargetedByAI(EntityAI ai)
	{
		
		if(ai.IsZombie() && ai.IsAlive())
		{
			float zombie = vector.Distance(ai.GetPosition(), GetPosition());
			if(zombie <= 20)
			{
				isZombieClose = true;
			}
			else
			{
				isZombieClose = false;
			}
		}

		if(IsPrime())
		{
			if(ai.IsZombie())
			{
				return false;
			}
		}

		if(GetAffectedLevel() >= 3)
		{
			if(ai.IsZombie())
			{
				if(isZombieClose)
				{
					return false;
				}
			}
		}

		return super.CanBeTargetedByAI( ai ) && !IsUnconscious();
	};
	override void EEKilled( Object killer )
	{

		PlayerJSONUpdate();

		super.EEKilled( killer );
	};
	override void OnDisconnect()
	{
		PlayerJSONUpdate();
		super.OnDisconnect();
	}
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if(IsPrime())
		{
			GiveShock(100);
		}


	};
	
	override void SetDecayEffects(int effect = -1)
	{

		super.SetDecayEffects(effect);
		
		if (effect)
		{
			SEffectManager.DestroyEffect( m_FliesEff );
			SEffectManager.DestroyEffect( m_SoundFliesEffect );
		}
	};

void SetBioZoneStatus(bool isInZone)
{
	m_IsInBioZone = isInZone;
}

  bool IsInBioZone()
  {
    return m_IsInBioZone;
  }

  bool IgnoreContaminatedArea()
  {
    return IsPlayerAffected()
  }

  bool IsPlayerAffected()
  {
    int slot_id = InventorySlots.GetSlotIdFromString("Head");
    Head_Default tempHead = Head_Default.Cast(GetInventory().FindPlaceholderForSlot( slot_id ));
    if (tempHead && (tempHead.GetType() == "DUB_Muthead_M" || tempHead.GetType() == "DUB_Muthead_F" || tempHead.GetType() == "DUB_Muthead_M_2" || tempHead.GetType() == "DUB_Muthead_F_2"))
    {
      return true;
    }
    return false;
  }

  bool IsPlayerPreMutant()
  {
    if (IsAlive() && m_FliesEff)
    {
      return true;
    }
    return false;
  }

  void SendMessageToClient( Object reciever, string message ) //sends given string to client, don't use if not nescessary
	{
		PlayerBase man;
    	Param1<string> m_MessageParam = new Param1<string>(message);
		if( GetGame().IsServer() && Class.CastTo(man, reciever) && m_MessageParam && reciever.IsAlive() && message != "" )
		{
			GetGame().RPCSingleParam(man, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, man.GetIdentity());
		}
	}
};