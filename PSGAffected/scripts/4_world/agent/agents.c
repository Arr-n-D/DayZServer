//agent register

modded class PluginTransmissionAgents
{
    void PluginTransmissionAgents()
    {
        RegisterAgent(new AffectedAgentBase); 
        Print("Registered "); 
    }
};
//modifier
class AffectedModifier: ModifierBase
{
	static const int AGENT_THRESHOLD_ACTIVATE = 2399;
	
	override void Init()
	{
		m_TrackActivatedTime = true;
		m_IsPersistent = true;
		m_ID 	= PSGModifiers.MDF_AFFECTED;
		m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive = DEFAULT_TICK_TIME_ACTIVE;
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		if(player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= AGENT_THRESHOLD_ACTIVATE) 
		{
			return true;
		}
		return false;
	}

	override void OnReconnect(PlayerBase player)
	{
        ActivateCondition(player);
	}

	override bool DeactivateCondition(PlayerBase player)
	{
	    return false;
	}

  // Assuming 259200 is 72 hours in seconds and 86400 is the tick value we have after 72 hours, we can find the amount of time until we reach a next stage by doing
  // Tick value * 3 / 60 / 60
  // To find the tick value we reverse the operation, 60 * 60 / 3 * 12 = 14400, 12 hours = value of 14400
  void MutationMessageQueue(PlayerBase player)
  {
	if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 9600) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 9602)) //Stage 2 first physical mutation passively regain food and water in the biozone can only eat human meat 9600 = 8 hours passed 
	{
        player.SendMessageToClient(player, "I don't feel so good... Perhaps I should head home and warn my friends about this?");
	}
    if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 9902) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 9904)) //death warning 10 minutes 9900
    {
        player.SendMessageToClient(player, "I should probably lay down when I get home and rest...(10 minutes warning)");
    }
    if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 9994) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 9996)) //death warning 5 minutes 9990
    {
      player.SendMessageToClient(player, "I feel like I have a fever, I should lay down.(5 minutes warning");
    }
    if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 10026) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 10028)) //death warning 60 seconds 10020
    {
      player.SendMessageToClient(player, "I feel like I'm going to pass out, I should lay down and be prepared.(60 seconds warning)");
    }
    if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 10050) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 10052))//kills player 10050
    {
      player.SetHealth(0);
    }
		if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 86400) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 86402)) //Stage 4 you get increased stats including passive healing reduced fall damage and increased jump height during night increased food loss during the day 86400 = 72hours
		{
      player.SendMessageToClient(player, "You feel something irreversibly change inside of you");
		}
    if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 86702) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 86704)) //death warning 10 minutes 9900
    {
      player.SendMessageToClient(player, "you have 10 minutes before the transformation takes place get somewhere safe");
    }
    if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 86854) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 86856)) //death warning 5 minutes 9990
    {
      player.SendMessageToClient(player, "you have 5 minutes before the transformation takes place get somewhere safe");
    }
    if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 86886) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 86888)) //death warning 60 seconds 10020
    {
      player.SendMessageToClient(player, "you have 60 second before the transformation takes place get somewhere safe");
    }
    if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 86890) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 86892))//kills player 10050
    {
      player.SetHealth(0);
    }
  };
  void MutationSymptomQueue(PlayerBase player)
  {
    if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 2400) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 2402)) //Stage 1 skin begins to decay visible smell and flies follow you are immune to the biozone 2400 = 2 hours agents passed start
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(PSGSymptomIDs.SYMPTOM_CRUDESERUM);
		}
		if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 9600) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 9602)) //Stage 2 first physical mutation passively regain food and water in the biozone can only eat human meat 9600 = 8 hours passed 
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(PSGSymptomIDs.SYMPTOM_AFFECTEDFIRST);
      player.GetSymptomManager().RemoveSecondarySymptom(PSGSymptomIDs.SYMPTOM_CRUDESERUM);
		}
		if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 28800) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 28802)) //Stage 3 you gain your second physical mutation you no longer aggro AI and have enchanced vision tbd 28800 = 24hours 
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(PSGSymptomIDs.SYMPTOM_AFFECTEDFIRST);
		}
		if((player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 86400) && (player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 86402)) //Stage 4 you get increased stats including passive healing reduced fall damage and increased jump height during night increased food loss during the day 86400 = 72hours
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(PSGSymptomIDs.SYMPTOM_AFFECTEDSECOND);
			player.GetSymptomManager().RemoveSecondarySymptom(PSGSymptomIDs.SYMPTOM_AFFECTEDFIRST);
		}
    if(player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 86893 && player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 115692) //Stage 4 you get increased stats including passive healing reduced fall damage and increased jump height during night increased food loss during the day 86400 = 72hours
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(PSGSymptomIDs.SYMPTOM_AFFECTEDSECOND);
		}
    if(player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 115693) //Stage 4 you get increased stats including passive healing reduced fall damage and increased jump height during night increased food loss during the day 86400 = 72hours
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(PSGSymptomIDs.SYMPTOM_AFFECTEDSECOND);
		}
  };
  void MutationLevelSyncer(PlayerBase player)
  {
    if(player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 2400 && player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 9599 )
    {
      if(player.GetAffectedLevel() != 1)
      {
        player.SetAffectedLevel(1);
      }
    }
    if(player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 9600 && player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 28799 )
    {
      if(player.GetAffectedLevel() != 2)
      {
        player.SetAffectedLevel(2);
      }
    }
    if(player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 28800 && player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 86399 )
    {
      if(player.GetAffectedLevel() != 3)
      {
        player.SetAffectedLevel(3);
      }
    }
    if(player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) >= 86400 && player.GetSingleAgentCount(AffectedAgent.AFFECTED_AGENT) <= 115692)
    {
      if(player.GetAffectedLevel() != 4)
      {
        player.SetAffectedLevel(4);
      }
    }
  };
	override void OnTick(PlayerBase player, float deltaT)
	{
    if(GetGame().IsMultiplayer())
    {
      player.InsertAgent(MutantAgent.AFFECTED_AGENT, 1);
      player.m_ModifiersManager.DeactivateModifier(eModifiers.MDF_BRAIN);
      MutationMessageQueue(player);
      MutationSymptomQueue(player);
      MutationLevelSyncer(player);
      if(player.GetAffectedLevel() >= 2)
      {
        player.InsertAgent(eAgents.BRAIN,-6000);
        player.RemoveAgent(eAgents.BRAIN);
        player.m_ModifiersManager.DeactivateModifier(eModifiers.MDF_BRAIN);
        player.InsertAgent(eAgents.SALMONELLA,-6000);
        player.RemoveAgent(eAgents.SALMONELLA);
        player.m_ModifiersManager.DeactivateModifier(eModifiers.MDF_SALMONELLA);
        player.InsertAgent(eAgents.FOOD_POISON,-6000);
        player.RemoveAgent(eAgents.FOOD_POISON);
        player.m_ModifiersManager.DeactivateModifier(eModifiers.MDF_POISONING);
      }
      if (GetGame().GetWorld().IsNight() && player.GetAffectedLevel() >= 4)
      {
        player.GetStatEnergy().Add(2);
      }
    }
 
  }
};
class BioHazardHealModifier: ModifierBase
{	
  bool inside_area;
	override void Init()
	{
		m_TrackActivatedTime = true;
    m_ID 					= PSGModifiers.MDF_BioHazardHeal;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE_LONG;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_INACTIVE_LONG;
	}
	
	override string GetDebugText()
	{

	}	
	
	override void OnDeactivate(PlayerBase player)
	{

	}

  override bool DeactivateCondition(PlayerBase player)
  {

    if(!inside_area)
    {
      return true;
    }

    return false;
  }

	override void OnTick(PlayerBase player, float deltaT)
	{
    inside_area = player.GetModifiersManager().IsModifierActive(eModifiers.MDF_AREAEXPOSURE);
		
    player.GetStatEnergy().Add(20);
  }
};

//mdfrregister
modded class ModifiersManager
{
    override void Init()
    {
        super.Init();
        AddModifier(new AffectedModifier);
        Print("Registered AffectedModifier");
        AddModifier(new BioHazardHealModifier);
        Print("Registered BioHazardHealMdfr");
    }
};
//agent=====================================================================================================================================================================================================================
class AffectedAgentBase: AgentBase
{
	override void Init()
	{
		m_Type 					= AffectedAgent.AFFECTED_AGENT;
		m_Invasibility 			= 0;
		m_TransferabilityIn		= 0;
		m_TransferabilityOut	= 0;
		m_AntibioticsResistance = 1;
		m_MaxCount 				= 116000;
		m_Potency 				= EStatLevels.CRITICAL;
		m_DieOffSpeed 			= 0;
	}
};
//symptoms=====================================================================================================================================================================================================================
class AffectedCrudeSerum: SymptomBase //changes skin colour biozone entry
{
    override void OnInit() 
    {
        m_SymptomType = SymptomTypes.SECONDARY;
        m_Priority = 50;
        m_ID = PSGSymptomIDs.SYMPTOM_CRUDESERUM;
        m_DestroyOnAnimFinish = false;
        m_IsPersistent = true;
        m_SyncToClient = true;
        m_MaxCount = 1;
    }

    override bool CanActivate()
    {
      return true;
    }

    //!gets called once on an Symptom which is being activated
    override void OnGetActivatedServer(PlayerBase player)
    {
      string 	m_DecayedTexture;
      m_DecayedTexture = player.ConfigGetString(m_DecayedTexture);
      player.m_CorpseState = PlayerConstants.CORPSE_STATE_DECAYED;
      player.SetFaceTexture(m_DecayedTexture);
      #ifndef SERVER
	    
      #endif
    }

    override void OnGetActivatedClient(PlayerBase player)
    {
      string 	m_DecayedTexture;
      m_DecayedTexture = player.ConfigGetString(m_DecayedTexture);
      player.m_CorpseState = PlayerConstants.CORPSE_STATE_DECAYED;
      player.SetFaceTexture(m_DecayedTexture);
      
    }
};
class AffectedFirst: SymptomBase //
{
	
    //this is just for the Symptom parameters set-up and is called even if the Symptom doesn't execute, don't put any gameplay code in here
    override void OnInit() 
    {
        m_SymptomType = SymptomTypes.SECONDARY;
        m_Priority = 50;
        m_ID = PSGSymptomIDs.SYMPTOM_AFFECTEDFIRST;
        m_DestroyOnAnimFinish = false;
        m_IsPersistent = true;
        m_SyncToClient = true;
        m_MaxCount = 1;
    }

    override bool CanActivate()
    {
      return true;
    }

    //!gets called once on an Symptom which is being activated
    override void OnGetActivatedServer(PlayerBase player)
    {
      if(player.GetAffectedLevel() == 2 || player.GetAffectedLevel() == 3 && GetGame().IsMultiplayer())
      {
        if(player.IsMale())
        {
          GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurMutant_M");
        }
        else
        {
          GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurMutant_F");
        }
      }     
    }

    override void OnGetActivatedClient(PlayerBase player)
    {
      if(player.GetAffectedLevel() == 2 || player.GetAffectedLevel() == 3 && GetGame().IsMultiplayer())
      {
        if(player.IsMale())
        {
          GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurMutant_M");
        }
        else
        {
          GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurMutant_F");
        }
      }   
                  	
    }
};
class AffectedSecond: SymptomBase
{
    override void OnInit() 
    {
      m_SymptomType = SymptomTypes.SECONDARY;
      m_Priority = 50;
      m_ID = PSGSymptomIDs.SYMPTOM_AFFECTEDSECOND;
      m_DestroyOnAnimFinish = false;
      m_IsPersistent = true;
      m_SyncToClient = true;
      m_MaxCount = 1;
    }
    
    override bool CanActivate()
    {
      return true;
    }

    //!gets called once on an Symptom which is being activated
    override void OnGetActivatedServer(PlayerBase player)
    {
      if(player.GetAffectedLevel() >= 4 && GetGame().IsMultiplayer())
      {
        if(player.IsMale())
        {
          GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurMutant_M_2");
        }
        else
        {
          GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurMutant_F_2");
        }
        Print("char reset symptom");
      }     
    }

    override void OnGetActivatedClient(PlayerBase player)
    {
      if(player.GetAffectedLevel() >= 4 && GetGame().IsMultiplayer())
      {
        if(player.IsMale())
        {
          GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurMutant_M_2");
        }
        else
        {
          GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurMutant_F_2");
        }
      } 
    }
};

//symptom register
modded class SymptomManager
{
  void Init()
  {
    super.Init();
    RegisterSymptom(new AffectedCrudeSerum);
    RegisterSymptom(new AffectedFirst);
    RegisterSymptom(new AffectedSecond);
  }
};



