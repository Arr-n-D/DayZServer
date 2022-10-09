modded class PlayerBase
{
    bool isZombieClose;
	protected bool m_IsInBioZone = false;
	int affectedLevel;
	int isPrime;

	string SteamID;
	
	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableInt("affectedLevel",0,5);
		RegisterNetSyncVariableInt("isPrime", 0, 1);
		isZombieClose = false;
		affectedLevel = 0;
		isPrime = 0;
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

	bool HasCassiusEye() {
		ItemBase eyewear = GetItemOnSlot("Eyewear");
		if (eyewear && eyewear.GetType() == "CassiusEye") {
			return true;
		}
		return false 
	}

	bool HasCaspianHelmet () {
		return GetItemOnSlot("Headgear").GetType() == "PCGNML_Space_Helmet_Black";
	}

//JSON
	void PlayerJSONUpdate()
	{
		if(GetGame().IsDedicatedServer())
		{	
			PSGJsonConfig config = GetDayZGame().GetPSGJsonConfig();
			config.UpdateJSON(GetSteamID(),GetAffectedLevel(), IsPrime());
		}
	}

	void PlayerJSONSave()
	{
		if(GetGame().IsDedicatedServer())
		{
			PSGJsonConfig config = GetDayZGame().GetPSGJsonConfig();
			config.NewJSON(GetSteamID(),GetAffectedLevel(), IsPrime());
		}
	}

	void JSONSynchDirty()
	{
		if(GetGame().IsDedicatedServer())
		{
			PSGJsonConfig config = GetDayZGame().GetPSGJsonConfig();
			affectedLevel = config.GetJSONAffectedLevel(GetSteamID());
			isPrime = config.GetJSONIsPrime(GetSteamID());
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

	int IsPrime()
	{
		return isPrime;
	};

	void SetIsPrime(int isP)
	{
		isPrime = isP;
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
	
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);
		if(!GetGame().IsDedicatedServer())	{
			vector pos_player = GetPosition();
			if(GetAffectedLevel() >= 3 && GetAffectedLevel() < 5) {
				ItemBase eyewear = GetItemOnSlot("Eyewear");
				if (eyewear) {
					PPEffects.SetEVValuePP(2.1); 
				} else {
					PPEffects.SetEVValuePP(5.5);
				}   
			}

			if( ( GetAffectedLevel() >= 5) && GetGame().GetWorld().IsNight() ) {
				PPEffects.SetEVValuePP(5.5);
			} else {
				PPEffects.SetEVValuePP(1.0);
			}

			if (HasCassiusEye()) { 
				if ( KeyState(KeyCode.KC_LCONTROL) == 1 && GetMouseState(MouseState.LEFT) & MB_PRESSED_MASK) {
					vector rayStart = GetGame().GetCurrentCameraPosition();
					vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * 1000;		
					vector hitPos;
					vector hitNormal;
					int hitComponentIndex;		
					DayZPhysics.RaycastRV(rayStart, rayEnd, hitPos, hitNormal, hitComponentIndex, NULL, NULL, this);
					
					float distance = vector.Distance( pos_player, hitPos );
					
					if ( distance < 150 ) {
						GetRPCManager().SendRPC("PSGRpc", "TeleportPlayer", new Param1<vector>(hitPos));
						ClearKey(KeyCode.KC_LCONTROL);	
					} else {
						GetRPCManager().SendRPC("PSGRpc", "FailTeleportPlayer", new Param1<string>("I don't have the energy to reach that distance")); 
					}

				}
			}
		}
		

		// if (GetGame().IsDedicatedServer()) {
		// 	if (shouldUpdatePos) {
		// 		Print("Should Update");
		// 		SetPosition(pos);
		// 	} else {
		// 		SendMessageToClient(this, message);
		// 	}
		// }
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

		switch (damageType)
		{
			case DT_CLOSE_COMBAT:
			{
				if(source.IsPlayer()) { // fists
					PlayerBase m_Source = PlayerBase.Cast(source);
					if (m_Source.IsPrime()) {
						SetHealth("", "Shock", 0);
						GetModifiersManager().ActivateModifier(eModifiers.MDF_UNCONSCIOUSNESS);
					}
				}
			}
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
    return IsPlayerAffected() || IsPrime()
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

  	float GetJumpHeight() {
		float height = 2.6; // default

		if(IsPrime())
		{
			height = 15;
		}
		return height;
	};

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

modded class DayZPlayerImplementJumpClimb
{
	const vector CAPTURE_VELOCITY = { 10, 10, 10 };
	override void Jump()
	{
		m_bIsJumpInProgress = true;
		m_Player.SetFallYDiff(m_Player.GetPosition()[1]);

		m_Player.OnJumpStart();

    PlayerBase pb = PlayerBase.Cast(m_Player);
    float jumpHeight = 2.6;
    if (pb)
    {
      jumpHeight = pb.GetJumpHeight();
    }
    
    m_Player.StartCommand_Fall(jumpHeight);
		m_Player.StopHandEvent();
	}
};