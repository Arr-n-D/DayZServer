//agent register
modded class PluginTransmissionAgents
{
    void PluginTransmissionAgents()
    {
        RegisterAgent(new MutantAgentBase); 
        Print("Registered "); 
    }
};
//modifier
class MutantMdfr: ModifierBase
{
	static const int AGENT_THRESHOLD_ACTIVATE = 2399;
	
	override void Init()
	{
		m_TrackActivatedTime = true;
		m_IsPersistent = true;
		m_ID 	= Modifiers.MDF_MUTANT;
		m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive = DEFAULT_TICK_TIME_ACTIVE;
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		if(player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= AGENT_THRESHOLD_ACTIVATE) 
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
  void MutationMessageQueue(PlayerBase player)
  {
	if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 9600) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 9602)) //Stage 2 first physical mutation passively regain food and water in the biozone can only eat human meat 9600 = 8 hours passed 
	{
        player.SendMessageToClient(player, "You feel something irreversibly change inside of you");
	}
    if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 9902) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 9904)) //death warning 10 minutes 9900
    {
        layer.SendMessageToClient(player, "you have 10 minutes before the transformation takes place get somewhere safe");
    }
    if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 9994) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 9996)) //death warning 5 minutes 9990
    {
      player.SendMessageToClient(player, "you have 5 minutes before the transformation takes place get somewhere safe");
    }
    if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 10026) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 10028)) //death warning 60 seconds 10020
    {
      player.SendMessageToClient(player, "you have 60 second before the transformation takes place get somewhere safe");
    }
    if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 10050) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 10052))//kills player 10050
    {
      player.SetHealth(0);
    }
		if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 86400) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 86402)) //Stage 4 you get increased stats including passive healing reduced fall damage and increased jump height during night increased food loss during the day 86400 = 72hours
		{
      player.SendMessageToClient(player, "You feel something irreversibly change inside of you");
		}
    if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 86702) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 86704)) //death warning 10 minutes 9900
    {
      player.SendMessageToClient(player, "you have 10 minutes before the transformation takes place get somewhere safe");
    }
    if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 86854) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 86856)) //death warning 5 minutes 9990
    {
      player.SendMessageToClient(player, "you have 5 minutes before the transformation takes place get somewhere safe");
    }
    if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 86886) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 86888)) //death warning 60 seconds 10020
    {
      player.SendMessageToClient(player, "you have 60 second before the transformation takes place get somewhere safe");
    }
    if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 86890) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 86892))//kills player 10050
    {
      player.SetHealth(0);
    }
  };
  void MutationSymptomQueue(PlayerBase player)
  {
    if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 2400) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 2402)) //Stage 1 skin begins to decay visible smell and flies follow you are immune to the biozone 2400 = 2 hours agents passed start
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(SymptomIDs.SYMPTOM_CRUDESERUM);
		}
		if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 9600) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 9602)) //Stage 2 first physical mutation passively regain food and water in the biozone can only eat human meat 9600 = 8 hours passed 
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(SymptomIDs.SYMPTOM_MUTANTFIRST);
      player.GetSymptomManager().RemoveSecondarySymptom(SymptomIDs.SYMPTOM_CRUDESERUM);
		}
		if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 28800) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 28802)) //Stage 3 you gain your second physical mutation you no longer aggro AI and have enchanced vision tbd 28800 = 24hours 
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(SymptomIDs.SYMPTOM_MUTANTFIRST);
		}
		if((player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 86400) && (player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 86402)) //Stage 4 you get increased stats including passive healing reduced fall damage and increased jump height during night increased food loss during the day 86400 = 72hours
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(SymptomIDs.SYMPTOM_MUTANTSECOND);
			player.GetSymptomManager().RemoveSecondarySymptom(SymptomIDs.SYMPTOM_MUTANTFIRST);
		}
    if(player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 86893 && player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 115692) //Stage 4 you get increased stats including passive healing reduced fall damage and increased jump height during night increased food loss during the day 86400 = 72hours
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(SymptomIDs.SYMPTOM_MUTANTSECOND);
		}
    if(player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 115693) //Stage 4 you get increased stats including passive healing reduced fall damage and increased jump height during night increased food loss during the day 86400 = 72hours
		{
      player.GetSymptomManager().QueueUpSecondarySymptom(SymptomIDs.SYMPTOM_MUTANTSECOND);
		}
  };
  void MutationLevelSyncer(PlayerBase player)
  {
    if(player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 2400 && player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 9599 )
    {
      if(player.GetAffectedLevel() != 1)
      {
        player.SetMutantLevel(1);
      }
    }
    if(player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 9600 && player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 28799 )
    {
      if(player.GetAffectedLevel() != 2)
      {
        player.SetMutantLevel(2);
      }
    }
    if(player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 28800 && player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 86399 )
    {
      if(player.GetAffectedLevel() != 3)
      {
        player.SetMutantLevel(3);
      }
    }
    if(player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 86400 && player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) <= 115692)
    {
      if(player.GetAffectedLevel() != 4)
      {
        player.SetMutantLevel(4);
      }
    }
    if(player.GetSingleAgentCount(MutantAgent.MUTANT_AGENT) >= 115693)
    {
      if(player.GetAffectedLevel() != 5)
      {
        player.SetMutantLevel(5);
      }
    }
  };
	override void OnTick(PlayerBase player, float deltaT)
	{
    if(GetGame().IsMultiplayer())
    {
      player.InsertAgent(MutantAgent.MUTANT_AGENT, 1);
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
class BioHazardHealMdfr: ModifierBase
{	
  bool inside_area;
	override void Init()
	{
		m_TrackActivatedTime = true;
    m_ID 					= Modifiers.MDF_BioHazardHeal;
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
class FlameThrowerMdfr: ModifierBase
{
	override void Init()
	{
		m_ID 	= Modifiers.MDF_FLAMETHROWER;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
   
	}
  override bool ActivateCondition(PlayerBase player)
  {
    return false;
  }
  override void OnReconnect(PlayerBase player)
	{
		OnDeactivate(player);
	}
  override bool DeactivateCondition(PlayerBase player)
  {
    if (player.IsRolling() || player.IsSwimming() || !player.IsAlive())
    {
      return true;
    }
		else if(player.GetHealth("GlobalHealth", "Health") <= 15)
		{
			return true;
		}
    else if(player.IsQueenAlpha())
    {
      return true;
    }
    else
    {
      return false;
    }

  }
  override void OnActivate(PlayerBase player)
  {
    player.GetSymptomManager().QueueUpSecondarySymptom(SymptomIDs.SYMPTOM_FLAMETHROWER);
    player.DecreaseHealth(40);
		
  }  	  
  override void OnDeactivate(PlayerBase player)
  {
    player.GetSymptomManager().RemoveSecondarySymptom(SymptomIDs.SYMPTOM_FLAMETHROWER);
  }
  override void OnTick(PlayerBase player, float deltaT)
  {
    player.DecreaseHealth(20);  
  }

};
class DrowningMdfr: ModifierBase
{
	override void Init()
	{
		m_ID = Modifiers.MDF_DROWNING;
    m_TrackActivatedTime = true;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE; 
	}
  bool Exclusion(PlayerBase player)
  {
    bool exclusion = true;
    if(player.IsPirate())
    {
      exclusion = false;
    }

    if(player.IsAlpha())
    {
      exclusion = false;
    }

    if(player.IsQueenAlpha())
    {
      exclusion = false;
    }

    return exclusion;
  }
  override bool ActivateCondition(PlayerBase player)
  {
    if ((GetGame().GetWaterDepth(player.GetPosition()) > 0.1) && Exclusion(player))
    {
      return true;
    }

    return false;
  }
  override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}
  override bool DeactivateCondition(PlayerBase player)
  {
    if (GetGame().GetWaterDepth(player.GetPosition()) <= 1.55)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  override void OnActivate(PlayerBase player)
  {
  }	  
  override void OnDeactivate(PlayerBase player)
  {
    player.SetUnderWater(0);
  }
  override void OnTick(PlayerBase player, float deltaT)
  {
    float attached_time = GetAttachedTime();
		ClothingBase bag 		= ClothingBase.Cast(player.GetItemOnSlot("back"));
		ClothingBase headGear	= ClothingBase.Cast(player.GetItemOnSlot("HeadGear"));
		ClothingBase mask		= ClothingBase.Cast(player.GetItemOnSlot("Mask"));
		ClothingBase shirt		= ClothingBase.Cast(player.GetItemOnSlot("body"));
    if ((headGear && headGear.IsDivingHelmet()) && (bag && bag.IsDivingTank()) && (shirt && shirt.IsDivingSuit()))
    {
      
      if (bag.GetQuantity() <= 60)
      {
        player.RequestSoundEventEx(EPlayerSoundEventID.EXHAUSTED_BREATH, false, EPlayerSoundEventParam.HIGHEST_PRIORITY);
      }
      if(bag.GetQuantity() <= 5)
      {
        player.AddHealth("", "Health", -25);
      }
    }
    else if(bag && bag.IsDivingTank())
    {
      if (bag.GetQuantity() <= 60)
      {
        player.RequestSoundEventEx(EPlayerSoundEventID.EXHAUSTED_BREATH, false, EPlayerSoundEventParam.HIGHEST_PRIORITY);
      }
      if(bag.GetQuantity() <= 5)
      {
        player.AddHealth("", "Health", -25);
      }
    }
    else if(player.GetFirstMutation() == 6 || player.GetSecondMutation() == 6)
    {
      if (attached_time >= 600)
      {
        player.RequestSoundEventEx(EPlayerSoundEventID.EXHAUSTED_BREATH, false, EPlayerSoundEventParam.HIGHEST_PRIORITY);
      }
      if(attached_time >= 720)
      {
        player.AddHealth("", "Health", -25);
      }
    }
    else if((mask && mask.IsSnorkel()) && GetGame().GetWaterDepth(player.GetPosition()) <= 1.6)
    {
      return;
    }
    else
    {
      if (attached_time >= 60)
      {
        player.RequestSoundEventEx(EPlayerSoundEventID.EXHAUSTED_BREATH, false, EPlayerSoundEventParam.HIGHEST_PRIORITY);
      }
      if(attached_time >= 120)
      {
        player.AddHealth("", "Health", -25);
      }
    }

    if((bag && bag.IsDivingTank()) && (player.GetUnderWater() != 2))
    {
      player.SetUnderWater(2);
    }
    else
    {
      player.SetUnderWater(1);
    }
  }

};
modded class BrokenLegsMdfr
{
	override void OnDeactivate(PlayerBase player)
	{
    player.UpdateBrokenLegs(eBrokenLegs.NO_BROKEN_LEGS);
		if ( player.IsWearingSplint() )
		{
			Splint_Applied splint;
      if(Class.CastTo(splint, player.GetItemOnSlot("Splint_Right")))
      {
        MiscGameplayFunctions.RemoveSplint(player); //Remove splint when leg is healed
      }
		}
		//SetLegHealed(bool broke)
		player.SetBrokenLegs(eBrokenLegs.NO_BROKEN_LEGS);
		player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_FRACTURE);
  }
};
modded class HeatComfortMdfr
{
	override void OnTick(PlayerBase player, float deltaT)
	{
		float heat_comfort = player.GetStatHeatComfort().Get();
		float health_loss;
		float value_normalized;	
    if(player.GetFirstMutation() == 3 || player.GetSecondMutation() == 3)
    {
      float stamina = player.GetStaminaHandler().GetStamina();
      if( heat_comfort > PlayerConstants.WATER_LOSS_THRESHOLD_HC_PLUS_LOW )
      {
        value_normalized = Math.Lerp(PlayerConstants.WATER_LOSS_THRESHOLD_HC_PLUS_LOW, PlayerConstants.WATER_LOSS_THRESHOLD_HC_PLUS_HIGH, heat_comfort);
        value_normalized = Math.Clamp(value_normalized, 0, 1);
        float water_loss = deltaT * Math.Lerp(PlayerConstants.WATER_LOSS_HC_PLUS_LOW, PlayerConstants.WATER_LOSS_HC_PLUS_HIGH, value_normalized);
        player.GetStatWater().Add(-water_loss/2);

        if( heat_comfort > PlayerConstants.WATER_LOSS_THRESHOLD_HC_PLUS_HIGH )
        {
          player.GetStatWater().Add(-water_loss * 2);
          player.GetStaminaHandler().MaxStaminaAdjuster(10);
        }
      }
      if( heat_comfort < PlayerConstants.ENERGY_LOSS_THRESHOLD_HC_MINUS_LOW )
      {
        value_normalized = Math.InverseLerp(PlayerConstants.ENERGY_LOSS_THRESHOLD_HC_MINUS_LOW, PlayerConstants.ENERGY_LOSS_THRESHOLD_HC_MINUS_HIGH, heat_comfort);
        value_normalized = Math.Clamp(value_normalized, 0, 1);
        float energy_loss = deltaT * Math.Lerp(PlayerConstants.ENERGY_LOSS_HC_MINUS_LOW, PlayerConstants.ENERGY_LOSS_HC_MINUS_HIGH, value_normalized);
        player.GetStatEnergy().Add(-energy_loss/2);

        if( heat_comfort < PlayerConstants.ENERGY_LOSS_THRESHOLD_HC_MINUS_HIGH )
        {
          player.GetStatEnergy().Add(-energy_loss * 2);
          player.GetStaminaHandler().MaxStaminaAdjuster(10);
        }
      }
    }
    else
    {
      super.OnTick(player,deltaT);
    }
	}
};
modded class HealthRegenMdfr
{
	override void OnTick(PlayerBase player, float deltaT)
	{	
    super.OnTick(player,deltaT);

		if (player.IsAlive())
		{
      if(player.IsWearingSplint())
      {
        Splint_Applied splint;
        Legcast_Applied cast;
        if(Class.CastTo(splint, player.GetItemOnSlot("Splint_Right")))
        {
          player.AddHealth("RightLeg","Health", 0.03);
				  player.AddHealth("RightFoot","Health",0.03);
				  player.AddHealth("LeftLeg","Health", 0.03);
				  player.AddHealth("LeftFoot","Health", 0.03);
        }
        else if(Class.CastTo(cast, player.GetItemOnSlot("Splint_Right")))
        {
          player.AddHealth("RightLeg","Health", 0.06);
				  player.AddHealth("RightFoot","Health",0.06);
				  player.AddHealth("LeftLeg","Health", 0.06);
				  player.AddHealth("LeftFoot","Health", 0.06);
        }
        else
        {
          return;
        }
        
      }
		}
	}
};
//mdfrregister
modded class ModifiersManager
{
    override void Init()
    {
        super.Init();
        AddModifier(new MutantMdfr);
        Print("Register MutantMdfr");
        AddModifier(new BioHazardHealMdfr);
        Print("Register BioHazardHealMdfr");
        AddModifier(new FlameThrowerMdfr);
        Print("Register FlameThrowerMdfr");
        AddModifier(new DrowningMdfr);
        Print("Register DrowningMdfr");
    }
};
//agent=====================================================================================================================================================================================================================
class MutantAgentBase: AgentBase
{
	override void Init()
	{
		m_Type 					= MutantAgent.MUTANT_AGENT;
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
class MutantCrudeSerum: SymptomBase //changes skin colour biozone entry
{
    override void OnInit() 
    {
        m_SymptomType = SymptomTypes.SECONDARY;
        m_Priority = 50;
        m_ID = SymptomIDs.SYMPTOM_CRUDESERUM;
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
	    MiscGameplayFunctions.MutantChecker();
      #endif
    }

    override void OnGetActivatedClient(PlayerBase player)
    {
      string 	m_DecayedTexture;
      m_DecayedTexture = player.ConfigGetString(m_DecayedTexture);
      player.m_CorpseState = PlayerConstants.CORPSE_STATE_DECAYED;
      player.SetFaceTexture(m_DecayedTexture);
      MiscGameplayFunctions.MutantChecker();
    }
};
class MutantFirst: SymptomBase //
{
	
    //this is just for the Symptom parameters set-up and is called even if the Symptom doesn't execute, don't put any gameplay code in here
    override void OnInit() 
    {
        m_SymptomType = SymptomTypes.SECONDARY;
        m_Priority = 50;
        m_ID = SymptomIDs.SYMPTOM_MUTANTFIRST;
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
      MiscGameplayFunctions.MutantChecker();            	
    }
};
class MutantSecond: SymptomBase
{
    override void OnInit() 
    {
      m_SymptomType = SymptomTypes.SECONDARY;
      m_Priority = 50;
      m_ID = SymptomIDs.SYMPTOM_MUTANTSECOND;
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
      MiscGameplayFunctions.MutantChecker();    
    }
};

//symptom register
modded class SymptomManager
{
  void Init()
  {
    super.Init();
    RegisterSymptom(new MutantCrudeSerum);
    RegisterSymptom(new MutantFirst);
    RegisterSymptom(new MutantSecond);
  }
};



