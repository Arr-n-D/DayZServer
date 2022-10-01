modded class PlayerBase
{
	bool isPrime;
    bool isAffected;
    bool isZombieClose;

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
		AgentUpdater();
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
			DUBJSONConfig config = GetDayZGame().GetDUBJSONConfig();
			config.UpdateJSON(GetSteamID(),GetMutantLevel(),GetFirstMutation(),GetSecondMutation(),GetAmputation());
		}
	}
	void PlayerJSONSave()
	{
		if(GetGame().IsDedicatedServer())
		{
			DUBJSONConfig config = GetDayZGame().GetDUBJSONConfig();
			config.NewJSON(GetSteamID(),GetMutantLevel());
		}
	}
	void JSONSynchDirty()
	{
		if(GetGame().IsDedicatedServer())
		{
			DUBJSONConfig config = GetDayZGame().GetDUBJSONConfig();
			MutantLevel = config.GetJSONMutant(GetSteamID());
			FirstMutation = config.GetJSONFirstMutation(GetSteamID());
			SecondMutation = config.GetJSONSecondMutation(GetSteamID());
			Amputation = config.GetJSONAmputation(GetSteamID());
			SetSynchDirty();
		}
		
	}

//NetSync
	void SetPirate(bool pirate)
	{
		isPirate = pirate;
		SetSynchDirty();
	};
	bool IsPirate()
	{
		return isPirate;
	};
	void SetPlayerMadness(bool mad)
	{
		PlayerMadness = mad;
		SetSynchDirty();
	};
	bool IsPlayerMadness()
	{
		return PlayerMadness;
	};
	int GetUnderWater()
	{
		return Underwater;
	}
	void SetUnderWater(int water)
	{
		Underwater = water;
		SetSynchDirty();
	};

//noises
	void Madnessnoise()
	{	
		if(!m_Madness)
		{
			PlaySoundSet(m_Madness,"DUB_Madness_SoundSet", 0, 0);
		}		
	};
	void StopUnderWaternoise()
	{
		StopSoundSet(m_underwater);
	};
	void UnderWaternoise()
	{	
		if(!m_underwater)
		{
			if(GetUnderWater() == 1)
			{
				PlaySoundSetLoop(m_underwater,"DUB_Underwater_SoundSet", 0, 0);
			}
			
			if(GetUnderWater() == 2)
			{
				PlaySoundSetLoop(m_underwater,"DUB_Scuba_SoundSet", 0, 0);
			}
			
		}

		if(m_underwater && (GetUnderWater() == 0))
		{
			StopSoundSet(m_underwater);
		}
	};

//utility
	bool IsInKOSZone()
	{
		if (vector.Distance(GetPosition(), Vector(13399.7, 12.9225, 9843.49)) < 600)
		{
			return true;
		}
		// Paris
		else if (vector.Distance(GetPosition(), Vector(2812.13, 22.4625, 3901.33)) < 750)
		{
			return true;
		}

		return false;
	};
	bool IsInPOI()
	{
		if(vector.Distance(GetPosition(), Vector(422.315, 16.5728, 595.137)) < 850)//arctic
		{
			return true;
		}
		else if (vector.Distance(GetPosition(), Vector(15601.576172, 214.826355, 14739.166992)) < 110)//temple
		{
			return true;
		}
		return false;
	};
	bool IgnoreFallingDamage()
	{
		bool ignoreFalling = false;
		if(IsAlpha())
		{
			ignoreFalling = true;
		}
		else if(IsQueenAlpha())
		{
			ignoreFalling = true;
		}
		//delete on mutation final
		else if (GetGame().GetWaterDepth(GetPosition()) > 0 )
		{
			ignoreFalling = true;
		}

		return ignoreFalling;
	};
	float GetJumpHeight()
	{
		float height = 2.6; // default

		if (IsAlpha() || IsQueenAlpha())
		{
			height = 15;
		}
		return height;
	};
	void SelectionChanger()
	{
		ItemBase Beard = GetItemOnSlot("Mask");
		ItemBase Shield = GetItemOnSlot("LeftHand1");
		ItemBase Gloves = GetItemOnSlot("Gloves");
		ItemBase Hands = GetItemInHands();

		if (Beard)
		{
			SetSimpleHiddenSelectionState(4,0);
		}
		else
		{
			SetSimpleHiddenSelectionState(4,1);
		}

		if (Gloves)
		{
			SetSimpleHiddenSelectionState(10,0);
		}
		else
		{
			SetSimpleHiddenSelectionState(10,1);
		}

		if(Hands && Hands.IsInherited(Weapon_Base) && Shield && Shield.IsShield())
		{
			SetSimpleHiddenSelectionState(5,1);
			SetSimpleHiddenSelectionState(6,0);
			SetSimpleHiddenSelectionState(7,0);
		}
		else if(Hands && Hands.IsInherited(ToolBase) && Shield && Shield.IsShield())
		{
			SetSimpleHiddenSelectionState(5,0);
			SetSimpleHiddenSelectionState(6,1);
			SetSimpleHiddenSelectionState(7,0);

		}
		else
		{
			SetSimpleHiddenSelectionState(5,0);
			SetSimpleHiddenSelectionState(6,0);
			SetSimpleHiddenSelectionState(7,1);
		}	
	};
	string GetSteamID()
	{
		return SteamID;
	};
	void PlayerReset()
	{
		ResetPlayer(false);
		AmputationDeleter();
		SetMutantLevel(0);
		SetFirstMutation(0);
		SetSecondMutation(0);
		SetAmputation(0);
		GetModifiersManager().DeactivateAllModifiers();
		RemoveAllAgents();
		GetSymptomManager().RemoveSecondarySymptom(DUB_SymptomIDs.SYMPTOM_CRUDESERUM);
		GetSymptomManager().RemoveSecondarySymptom(DUB_SymptomIDs.SYMPTOM_MUTANTFIRST);
		GetSymptomManager().RemoveSecondarySymptom(DUB_SymptomIDs.SYMPTOM_MUTANTSECOND);

		if(GetGame().IsDedicatedServer())
		{
			DUBJSONConfig config = GetDayZGame().GetDUBJSONConfig();
			config.UpdateJSON(GetSteamID(),0,0,0,0);
		}

		if(GetGame().IsDedicatedServer())
		{

			if(IsMale())
			{
				GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurvivorM_Mirek");
			}
			else
			{
				GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurvivorF_Eva");
			}
			Print("char reset");
		}
		if(GetGame().IsClient() && GetGame().IsMultiplayer())
		{
			if(IsMale())
			{
				GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurvivorM_Mirek");
			}
			else
			{
				GetGame().GetMenuDefaultCharacterData().SetCharacterType("SurvivorF_Eva");
			}
		}

	}

//amputation
	int GetAmputation()
	{
		return Amputation;
	}
	void SetAmputation(int amp)
	{
		Amputation = amp;
		SetSynchDirty();
	};
	void AmputationDeleter()
	{
		Clothing Feet = Clothing.Cast(GetItemOnSlot("feet"));
		Clothing Body = Clothing.Cast(GetItemOnSlot("body"));
		Clothing Legs = Clothing.Cast(GetItemOnSlot("Legs"));
		Clothing Gloves = Clothing.Cast(GetItemOnSlot("Gloves"));
		
		if(GetAmputation() > 0 && GetGame().IsMultiplayer())
		{
			if(GetAmputation() == 13 && Body && Body.GetType() != "DUB_Leftarmstump" && Feet && Feet.GetType() != "DUB_Rightfootstub")
			{
				Feet.DeleteSafe();
				Body.DeleteSafe();
			}
			else if(GetAmputation() == 14 && Body && Body.GetType() != "DUB_Leftarmstump" && Feet && Feet.GetType() != "DUB_Leftfootstub")
			{
				Body.DeleteSafe();
				Feet.DeleteSafe();
			}
			else if(GetAmputation() == 15 && Body && Body.GetType() != "DUB_Leftarmstump" && Legs && Legs.GetType() != "DUB_Rightlegstub")
			{
				Body.DeleteSafe();
				Legs.DeleteSafe();
				Feet.DeleteSafe();
			}
			else if(GetAmputation() == 16 && Body && Body.GetType() != "DUB_Leftarmstump" && Legs && Legs.GetType() != "DUB_Leftlegstub")
			{
				Body.DeleteSafe();
				Legs.DeleteSafe();
				Feet.DeleteSafe();
			}
			else if(GetAmputation() == 23 && Gloves && Gloves.GetType() != "DUB_Lefthandstub" && Feet && Feet.GetType() != "DUB_Rightfootstub")
			{
				Feet.DeleteSafe();
				Gloves.DeleteSafe();
			}
			else if(GetAmputation() == 24 && Gloves && Gloves.GetType() != "DUB_Lefthandstub" && Feet && Feet.GetType() != "DUB_Leftfootstub")
			{
				Gloves.DeleteSafe();
				Feet.DeleteSafe();
			}
			else if(GetAmputation() == 25 && Gloves && Gloves.GetType() != "DUB_Lefthandstub" && Legs && Legs.GetType() != "DUB_Rightlegstub")
			{
				Feet.DeleteSafe();
				Gloves.DeleteSafe();
				Legs.DeleteSafe();
			}
			else if(GetAmputation() == 26 && Gloves && Gloves.GetType() != "DUB_Lefthandstub" && Legs && Legs.GetType() != "DUB_Leftlegstub")
			{
				Gloves.DeleteSafe();
				Feet.DeleteSafe();
				Legs.DeleteSafe();
			}
			else if(GetAmputation() == 1 && Body && Body.GetType() != "DUB_Leftarmstump")
			{
				Gloves.DeleteSafe();
				Body.DeleteSafe();
			}
			else if(GetAmputation() == 2 && Gloves && Gloves.GetType() != "DUB_Lefthandstub")
			{
				Gloves.DeleteSafe();
			}
			else if(GetAmputation() == 3 && Feet && Feet.GetType() != "DUB_Rightfootstub")
			{
				Feet.DeleteSafe();
			}
			else if(GetAmputation() == 4 && Feet && Feet.GetType() != "DUB_Leftfootstub")
			{
				Feet.DeleteSafe();
			}
			else if(GetAmputation() == 5 && Legs && Legs.GetType() != "DUB_Rightlegstub")
			{
				Feet.DeleteSafe();
				Legs.DeleteSafe();
			}
			else if(GetAmputation() == 6 && Legs && Legs.GetType() != "DUB_Leftlegstub")
			{
				Feet.DeleteSafe();
				Legs.DeleteSafe();
			}
			else
			{
				return;
			}
		}


	}
	void AmputationSpawner()
	{
		Clothing Feet = Clothing.Cast(GetItemOnSlot("feet"));
		int Feet_id = InventorySlots.GetSlotIdFromString("feet");
		Clothing Body = Clothing.Cast(GetItemOnSlot("body"));
		int Body_id = InventorySlots.GetSlotIdFromString("body");
		Clothing Legs = Clothing.Cast(GetItemOnSlot("Legs"));
		int Legs_id = InventorySlots.GetSlotIdFromString("Legs");
		Clothing Gloves = Clothing.Cast(GetItemOnSlot("Gloves"));
		int Gloves_id = InventorySlots.GetSlotIdFromString("Gloves");
		ItemBase fakeleg = ItemBase.Cast(GetItemOnSlot("LPproxy"));
		int fakeleg_id = InventorySlots.GetSlotIdFromString("LPproxy");
		if(GetGame().IsDedicatedServer())
		{
			if(GetAmputation() == 1)//missing left arm
			{
				if(!Body)
				{
					GetInventory().CreateAttachmentEx("DUB_Leftarmstump",Body_id);
				}
				
				if(!Gloves)
				{
					GetInventory().CreateAttachmentEx("DUB_Nolefthand",Gloves_id);
				}
			}
			else if(GetAmputation() == 2)//missing left hand
			{
				if(!Gloves)
				{
					GetInventory().CreateAttachmentEx("DUB_Lefthandstub",Gloves_id);
				}
			}
			else if(GetAmputation() == 3)//missing right foot
			{

				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Rightfootstub",Feet_id);
				}
			}
			else if(GetAmputation() == 4)//missing left foot
			{
				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Leftfootstub",Feet_id);
				}
			}
			else if(GetAmputation() == 5)//missing right leg
			{

				if(!Legs)
				{
					GetInventory().CreateAttachmentEx("DUB_Rightlegstub",Legs_id);
					GetInventory().CreateInInventory("DUB_Woodleg");
				}

				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Norightfoot",Feet_id);
				}
			}
			else if(GetAmputation() == 6)//missing left leg
			{
				if(!Legs)
				{
					GetInventory().CreateAttachmentEx("DUB_Leftlegstub",Legs_id);
					GetInventory().CreateInInventory("DUB_Woodleg");
				}

				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Noleftfoot",Feet_id);
				}
			}
			else if(GetAmputation() == 13)//missing left arm & right foot
			{
				if(!Body)
				{
					GetInventory().CreateAttachmentEx("DUB_Leftarmstump",Body_id);
				}
				if(!Gloves)
				{
					GetInventory().CreateAttachmentEx("DUB_Nolefthand",Gloves_id);
				}
				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Rightfootstub",Feet_id);
				}
			}
			else if(GetAmputation() == 14)//missing left arm & left foot
			{
				if(!Body)
				{
					GetInventory().CreateAttachmentEx("DUB_Leftarmstump",Body_id);
				}
				if(!Gloves)
				{
					GetInventory().CreateAttachmentEx("DUB_Nolefthand",Gloves_id);
				}
				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Leftfootstub",Feet_id);
				}
			}
			else if(GetAmputation() == 15)//missing left arm & right leg
			{
				if(!Body)
				{
					GetInventory().CreateAttachmentEx("DUB_Leftarmstump",Body_id);
				}
				if(!Gloves)
				{
					GetInventory().CreateAttachmentEx("DUB_Nolefthand",Gloves_id);
				}
				if(!Legs)
				{
					GetInventory().CreateAttachmentEx("DUB_Rightlegstub",Legs_id);
					GetInventory().CreateInInventory("DUB_Woodleg");
				}
				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Norightfoot",Feet_id);
				}
			}
			else if(GetAmputation() == 16)//missing left arm & left leg
			{
				if(!Body)
				{
					GetInventory().CreateAttachmentEx("DUB_Leftarmstump",Body_id);
				}
				if(!Gloves)
				{
					GetInventory().CreateAttachmentEx("DUB_Nolefthand",Gloves_id);
				}
				if(!Legs)
				{
					GetInventory().CreateAttachmentEx("DUB_Leftlegstub",Legs_id);
					GetInventory().CreateInInventory("DUB_Woodleg");
				}
				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Noleftfoot",Feet_id);
				}
			}
			else if(GetAmputation() == 23)// missing left hand & right foot
			{
				if(!Gloves)
				{
					GetInventory().CreateAttachmentEx("DUB_Lefthandstub",Gloves_id);
				}
				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Rightfootstub",Feet_id);
				}
			}
			else if(GetAmputation() == 24)// missing left hand & left foot
			{
				if(!Gloves)
				{
					GetInventory().CreateAttachmentEx("DUB_Lefthandstub",Gloves_id);
				}
				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Leftfootstub",Feet_id);
				}
			}
			else if(GetAmputation() == 25)// missing left hand & right leg
			{
				if(!Gloves)
				{
					GetInventory().CreateAttachmentEx("DUB_Lefthandstub",Gloves_id);
				}
				if(!Legs)
				{
					GetInventory().CreateAttachmentEx("DUB_Rightlegstub",Legs_id);
					GetInventory().CreateInInventory("DUB_Woodleg");
				}
				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Norightfoot",Feet_id);
				}
			}
			else if(GetAmputation() == 26)// missing left hand & left leg
			{
				if(!Gloves)
				{
					GetInventory().CreateAttachmentEx("DUB_Lefthandstub",Gloves_id);
				}
				if(!Legs)
				{
					GetInventory().CreateAttachmentEx("DUB_Lefthandstub",Gloves_id);
				}
				if(!Feet)
				{
					GetInventory().CreateAttachmentEx("DUB_Noleftfoot",Feet_id);
				}
			}
			else
			{
				return;
			}
		}

	};
	void AmputationSetter()
	{
		Clothing Feet = Clothing.Cast(GetItemOnSlot("feet"));
		Clothing Body = Clothing.Cast(GetItemOnSlot("body"));
		Clothing Legs = Clothing.Cast(GetItemOnSlot("Legs"));
		Clothing Gloves = Clothing.Cast(GetItemOnSlot("Gloves"));
		if(GetGame().IsDedicatedServer())
		{
			if(Body && Body.GetType() == "DUB_Leftarmstump" && Feet && Feet.GetType() == "DUB_Rightfootstub")
			{
				Amputation = 13;
			}
			else if(Body && Body.GetType() == "DUB_Leftarmstump" && Feet && Feet.GetType() == "DUB_Leftfootstub")
			{
				Amputation = 14;
			}
			else if(Body && Body.GetType() == "DUB_Leftarmstump" && Legs && Legs.GetType() == "DUB_Rightlegstub")
			{
				Amputation = 15;
			}
			else if(Body && Body.GetType() == "DUB_Leftarmstump" && Legs && Legs.GetType() == "DUB_Leftlegstub")
			{
				Amputation = 16;
			}
			else if(Gloves && Gloves.GetType() == "DUB_Lefthandstub" && Feet && Feet.GetType() == "DUB_Rightfootstub")
			{
				Amputation = 23;
			}
			else if(Gloves && Gloves.GetType() == "DUB_Lefthandstub" && Feet && Feet.GetType() == "DUB_Leftfootstub")
			{
				Amputation = 24;
			}
			else if(Gloves && Gloves.GetType() == "DUB_Lefthandstub" && Legs && Legs.GetType() == "DUB_Rightlegstub")
			{
				Amputation = 25;
			}
			else if(Gloves && Gloves.GetType() == "DUB_Lefthandstub" && Legs && Legs.GetType() == "DUB_Leftlegstub")
			{
				Amputation = 26;
			}
			else if(Body && Body.GetType() == "DUB_Leftarmstump")
			{
				Amputation = 1;
			}
			else if(Gloves && Gloves.GetType() == "DUB_Lefthandstub")
			{
				Amputation = 2;
			}
			else if(Feet && Feet.GetType() == "DUB_Rightfootstub")
			{
				Amputation = 3;
			}
			else if(Feet && Feet.GetType() == "DUB_Leftfootstub")
			{
				Amputation = 4;
			}
			else if(Legs && Legs.GetType() == "DUB_Rightlegstub")
			{
				Amputation = 5;
			}
			else if(Legs && Legs.GetType() == "DUB_Leftlegstub")
			{
				Amputation = 6; 
			}
			else
			{
				return;
			}
		}

		SetSynchDirty();
	};

//Mutation
	int GetMutantLevel()
	{
		return MutantLevel;
	};
	void SetMutantLevel(int level)
	{
		MutantLevel = level;
		SetSynchDirty();
	};
	void SetFirstMutation(int first)
	{
		FirstMutation = first;
		SetSynchDirty();
	};
	void SetSecondMutation(int second)
	{
		SecondMutation = second;
		SetSynchDirty();
	};
	int GetFirstMutation()
	{
		return FirstMutation;
	};
	int GetSecondMutation()
	{
		return SecondMutation;
	};
	string GetMutations()
    {
        string first = FirstMutation.ToString();
       	string second = SecondMutation.ToString();

		return first + second;
    };
	void MutationSlots()
	{
		if(GetGame().IsDedicatedServer())
		{
			ItemBase Mutation1 = GetItemOnSlot("Mutation1");
			ItemBase Mutation2 = GetItemOnSlot("Mutation2");
			int Mutation1_id = InventorySlots.GetSlotIdFromString("Mutation1");
			int Mutation2_id = InventorySlots.GetSlotIdFromString("Mutation2");
			if(GetMutantLevel() < 4)
			{
				if(!Mutation1)
				{
					GetInventory().CreateInInventory("DUB_Mutation1_Empty");
				}

				if(!Mutation2)
				{
					GetInventory().CreateInInventory("DUB_Mutation2_Empty");
				}
			}
			if(GetMutantLevel() >= 4)
			{
				
				if(GetFirstMutation() == 0 && Mutation1)
				{
					Mutation1.DeleteSafe();
				}

				if(!Mutation1)
				{
					if(GetFirstMutation() == 1)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation1",Mutation1_id);
					}
					if(GetFirstMutation() == 2)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation2",Mutation1_id);
					}
					if(GetFirstMutation() == 3)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation3",Mutation1_id);
					}
					if(GetFirstMutation() == 4)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation4",Mutation1_id);
					}
					if(GetFirstMutation() == 5)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation5",Mutation1_id);
					}
					if(GetFirstMutation() == 6)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation6",Mutation1_id);
					}
					if(GetFirstMutation() == 7)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation7",Mutation1_id);
					}
					if(GetFirstMutation() == 8)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation8",Mutation1_id);
					}
					if(!Mutation2 && GetMutantLevel() == 4)
					{
						GetInventory().CreateInInventory("DUB_Mutation2_Empty");
					}
				}
			}
			if(GetMutantLevel() == 5)
			{
				
				if(GetSecondMutation() == 0 && Mutation2)
				{
					Mutation2.DeleteSafe();
				}

				if(!Mutation2)
				{
					if(GetSecondMutation() == 1)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation1",Mutation2_id);
					}
					if(GetSecondMutation() == 2)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation2",Mutation2_id);
					}
					if(GetSecondMutation() == 3)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation3",Mutation2_id);
					}
					if(GetSecondMutation() == 4)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation4",Mutation2_id);
					}
					if(GetSecondMutation() == 5)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation5",Mutation2_id);
					}
					if(GetSecondMutation() == 6)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation6",Mutation2_id);
					}
					if(GetSecondMutation() == 7)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation7",Mutation2_id);
					}
					if(GetSecondMutation() == 8)
					{
						GetInventory().CreateAttachmentEx("DUB_Mutation8",Mutation2_id);
					}
				}
			}
		
		}
	};
	void UpdateMutantVisual()
	{
		if(GetFirstMutation() == 3 || GetSecondMutation() == 3)
		{
			EntityAI bodypart;
			ItemBase item;
			
			string path;
			string MutantTexture = "Dressupbox\\Mutation\\Mutations\\data\\mutant_Heat.RVMAT";
			int idx;
			int slot_id;
			array<string> bodyparts = {"Gloves","Body","Legs","Feet","Head"};
			
			for (int i = 0; i < bodyparts.Count(); i++)
			{
				slot_id = InventorySlots.GetSlotIdFromString(bodyparts.Get(i));
				bodypart = GetInventory().FindPlaceholderForSlot( slot_id );
				item = ItemBase.Cast(GetInventory().FindAttachment( slot_id ));
				
				if( bodypart )
				{
					path = "cfgVehicles " + bodypart.GetType();
					idx = bodypart.GetHiddenSelectionIndex("mutation");
					if( idx > -1 )
					{
						bodypart.SetObjectMaterial(idx,MutantTexture);
					}
				}
				if( item )
				{
					path = "cfgVehicles " + item.GetType();
					idx = item.GetHiddenSelectionIndex("personality");
					if( idx > -1 )
					{
						item.SetObjectMaterial(idx,MutantTexture);
					}
				}
			}
			SetFaceTexture(MutantTexture);
		}

		if(GetMutantLevel() == 1)
		{
			string 	m_DecayedTexture;
			m_DecayedTexture = ConfigGetString(m_DecayedTexture);
			m_CorpseState = PlayerConstants.CORPSE_STATE_DECAYED;
			SetFaceTexture(m_DecayedTexture);
			DUB_MiscGameplayFunctions.MutantChecker();
		}
	};
	void AgentUpdater()
	{
		if(GetGame().IsDedicatedServer())
		{
			int mutelevel = GetMutantLevel();
			if(mutelevel == 1)
			{
				if(GetSingleAgentCount(DUB_MutantAgent.MUTANT_AGENT) <= 2400)
				{
					m_AgentPool.SetAgentCount(DUB_MutantAgent.MUTANT_AGENT, 2400);
				}
			}

			if(mutelevel == 2)
			{
				if(GetSingleAgentCount(DUB_MutantAgent.MUTANT_AGENT) <= 10053)
				{
					m_AgentPool.SetAgentCount(DUB_MutantAgent.MUTANT_AGENT, 10053);
				}
			}

			if(mutelevel == 3)
			{
				if(GetSingleAgentCount(DUB_MutantAgent.MUTANT_AGENT) <= 28800)
				{
					m_AgentPool.SetAgentCount(DUB_MutantAgent.MUTANT_AGENT, 28800);
				}
			}

			if(mutelevel == 4)
			{
				if(GetSingleAgentCount(DUB_MutantAgent.MUTANT_AGENT) <= 86893)
				{
					m_AgentPool.SetAgentCount(DUB_MutantAgent.MUTANT_AGENT, 86893);
				}
			}

			if(mutelevel == 5)
			{
				if(GetSingleAgentCount(DUB_MutantAgent.MUTANT_AGENT) <= 115692)
				{
					m_AgentPool.SetAgentCount(DUB_MutantAgent.MUTANT_AGENT, 115693);
				}
			}
		}
	}
	bool ZombieClose()
	{
		return zombieclose;
	}

//Alphas
	bool IsAlpha()
	{
		return isAlpha;
	};
	void SetIsAlpha(bool alpha)
	{
		isAlpha = alpha;
		SetSynchDirty();
	};
	bool IsQueenAlpha()
	{
		return isQueenAlpha;
	}
	void SetIsQueenAlpha(bool alpha)
	{
		isQueenAlpha = alpha;
		SetSynchDirty();
	};

//vanilla
	override void ProcessHandDamage(float delta_time, HumanMovementState pState)
	{
		if(GetFirstMutation() != 2 || GetSecondMutation() != 2)
		{
			super.ProcessHandDamage(delta_time,pState);
		}
	};
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		if (!GetGame().IsDedicatedServer())
		{
			if(IsPlayerMadness())
			{
				Madnessnoise();
			}
			UnderWaternoise();
		}
	};
	// override bool CanSprint()
	// {
	// 	EntityAI attachment;
	// 	Class.CastTo(attachment, GetItemOnSlot("Splint_Right"));

	// 	if ( attachment && attachment.GetType() == "DUB_Legcast_Applied")
	// 	{
	// 		return false;
	// 	}
		
	// 	return super.CanSprint();
	// };
	override void SetActions(out TInputActionMap InputActionMap)
	{
		super.SetActions(InputActionMap);
		//AddAction(ActionEnterNest, InputActionMap);
	};
	override bool IsInVehicle()
	{
		if (isLinked)
		{
			return false;
		}
		return super.IsInVehicle();
	};
	override void EOnContact(IEntity other, Contact extra)
    {
        DUB_Throwingknife knife;
        if (Class.CastTo(knife, other))
        {
            if (GetGame().IsDedicatedServer())
            {
                ProcessDirectDamage(DT_CLOSE_COMBAT, knife, "", knife.GetAmmoType(), "0 0 0", 1);
            }
        }	
    };	
	override void OnCommandSwimStart()
	{
		super.OnCommandSwimStart();
		
		if (GetInventory())
		{
			GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);
		}
	};
	override void OnCommandSwimFinish()
	{
		if (GetInventory()) 
		{ 
			GetInventory().LockInventory(LOCK_FROM_SCRIPT); 
		}
		
		super.OnCommandSwimFinish();
	};
	override void ProcessFeetDamageServer(int pUserInt)
    {
        Clothing shirt		= Clothing.Cast(GetItemOnSlot("body"));
		Clothing shoes		= Clothing.Cast(GetItemOnSlot("feet"));
        if (shirt && shirt.IsDivingSuit() || shoes.NoFootDamage())
        {
            return;
        }
        else
        {
            super.ProcessFeetDamageServer(pUserInt);
        }
	};
	override bool CanReceiveItemIntoHands (EntityAI item_to_hands)
	{

		if(IsSwimming()) 
		{ 
			return true; 
		}

		return super.CanReceiveItemIntoHands(item_to_hands);
	};
	override bool CanReleaseFromHands(EntityAI handheld)
	{

		if(IsSwimming()) 
		{ 
			return true;
		}

		if((GetGame().GetWaterDepth(GetPosition()) > 0))
		{
			return true; 
		}

		return super.CanReleaseFromHands(handheld);
	};
	override bool CanReleaseCargo (EntityAI cargo)
	{
		if(IsSwimming()) 
		{ 
			return true;
		}
		return super.CanReleaseCargo(cargo);
	};	
	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if(IsSwimming()) 
		{ 
			return true;
		}
		return super.CanReceiveItemIntoCargo(item);
	};	
	override bool CanSwapItemInCargo (EntityAI child_entity, EntityAI new_entity)
	{
		if(IsSwimming()) 
		{ 
			return true;
		}
		return super.CanSwapItemInCargo(child_entity, new_entity);
	};
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);
		ParticleSource 		m_ParticleFlame;
		ParticleSource 		m_ParticleFlame1;
		Weapon_Base heldItem = Weapon_Base.Cast(GetItemInHands());
		if ( ((heldItem && heldItem.IsInherited(Rifle_Base)) || (heldItem && heldItem.IsInherited(Pistol_Base))) && IsRaised())
		{
			if(heldItem.GetAttachmentByType(DUB_Bipod))
			{
				DUB_Bipod bipod = DUB_Bipod.Cast(heldItem.GetAttachmentByType(DUB_Bipod));

				vector usti_hlavne_position = heldItem.GetSelectionPositionLS("usti hlavne");
				vector konec_hlavne_position = usti_hlavne_position - "0 0.35 0";
				vector end_point = heldItem.ModelToWorld(usti_hlavne_position);
				vector begin_point = heldItem.ModelToWorld(konec_hlavne_position);
				vector contact_point;
				vector contact_dir;
				int contactComponent;
				bool ishit = DayZPhysics.RaycastRV( end_point, begin_point, contact_point, contact_dir, contactComponent, NULL , NULL, this, false, false, ObjIntersectIFire, 0.0);

				if (ishit && m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_IDLE)
				{
					bipod.Open();
					heldItem.GetPropertyModifierObject().UpdateModifiers();
				}
				else
				{
					bipod.Close();
					heldItem.GetPropertyModifierObject().UpdateModifiers();
				}
			
			}
		}

		if(!GetGame().IsDedicatedServer())
		{
			if(GetFirstMutation() == 5 || GetSecondMutation() == 5 )
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

			if(IsAlpha() || IsQueenAlpha() || IsPirate())
			{
				if(GetGame().GetWorld().IsNight())
				{
					PPEffects.SetEVValuePP(5.5);
				}
				else
				{
					PPEffects.SetEVValuePP(1.2); 
				}
			}
		}
	};
	override void BrokenLegForceProne(bool forceOverride = false)
	{
		if (!IsInWater() && !IsSwimming() && !IsClimbingLadder() && !IsInVehicle() && !IsClimbing() && DayZPlayerUtils.PlayerCanChangeStance(this, DayZPlayerConstants.STANCEIDX_PRONE))
		{
			if (m_MovementState.m_iStanceIdx != DayZPlayerConstants.STANCEIDX_PRONE && m_MovementState.m_iStanceIdx != DayZPlayerConstants.STANCEIDX_RAISEDPRONE)
			{
				EntityAI attachment;
				Class.CastTo(attachment, GetItemOnSlot("Splint_Right"));
				if ( attachment && attachment.GetType() == "DUB_Legcast_Applied" )
				{
					attachment.Delete();
				}
			}
		}

		super.BrokenLegForceProne(forceOverride);
	};
	override bool IsWearingSplint()
	{
		EntityAI attachment;
		Class.CastTo(attachment, GetItemOnSlot("Splint_Right"));
		if ( attachment && attachment.GetType() == "DUB_Legcast_Applied")
		{
			return true;
		}
		return super.IsWearingSplint();		
	};
	override bool CanBeTargetedByAI(EntityAI ai)
	{
		
		DUB_FeralAlpha feral;	
		if(ai.IsZombie() && ai.IsAlive())
		{
			float zombie = vector.Distance(ai.GetPosition(), GetPosition());
			if(zombie <= 20)
			{
				zombieclose = true;
			}
			else
			{
				zombieclose = false;
			}
		}

		if(IsAlpha())
		{
			if(ai.IsZombie() && !IsInKOSZone())
			{
				return false;
			}
		}

		if(IsQueenAlpha())
		{
			
			if(ai.IsZombie())
			{
				return false;
			}

			if(Class.CastTo(feral,ai))
			{
				return false;
			}
		}

		if(GetFirstMutation() == 4 || GetSecondMutation() == 4)
		{
			
			float m_Stamina = GetStaminaHandler().GetStamina();
			if(ai.IsZombie())
			{
				if(zombieclose && m_Stamina >= 10)
				{
					return false;
				}
			}

			if(Class.CastTo(feral,ai))
			{
				float distance = vector.Distance(feral.GetPosition(), GetPosition());
				{
					if(distance > 20)
					{
						return false;
					}
				}
			}
		}

		return super.CanBeTargetedByAI( ai ) && !IsUnconscious();
	};
	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);
		
		SelectionChanger();
		UpdateMutantVisual();
		int isPlayerRespawning = StatGet( "playtime" );
		if(isPlayerRespawning >= 5)
		{
			AmputationSetter();
		}
		
	};
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		
		SelectionChanger();
		UpdateMutantVisual();
	};
	override void EEItemOutOfHands(EntityAI item)
	{
		super.EEItemOutOfHands( item );
		SelectionChanger();
		if(item.GetType() == "DUB_Balshield" || item.GetType() == "DUB_Improvshield")
		{
			GetMeleeFightLogic().SetBlock( false );
		}
	};
	override void EEItemIntoHands(EntityAI item)
	{
		super.EEItemIntoHands( item );
		if(item.GetType() == "DUB_Balshield" || item.GetType() == "DUB_Improvshield")
		{
			GetMeleeFightLogic().SetBlock( true );
		}
		SelectionChanger();
	};
	override void EEKilled( Object killer )
	{

		PlayerJSONUpdate();

		super.EEKilled( killer );
	};
	override void OnDisconnect()
	{
		PlayerJSONUpdate();
		SetPlayerMadness(false);
		super.OnDisconnect();
	}
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if(ammo == "Ammo_Flamethrower")
		{
			if(GetGame().IsDedicatedServer())
			{
				GetModifiersManager().ActivateModifier( DUB_Modifiers.MDF_FLAMETHROWER );
			}
		}

		if(IsAlpha() || IsQueenAlpha())
		{
			GiveShock(100);
		}

		if(GetFirstMutation() == 7 || GetSecondMutation() == 7)
		{
			float damage = damageResult.GetDamage(dmgZone, "Health");
			float shock = damageResult.GetDamage(dmgZone, "Shock");
			damage = damage * 0.5;
			shock = shock * 0.5;
			float Staminaburn = damage + shock;
			float stamina = GetStaminaHandler().GetStamina();
			float health_current = GetHealth("","Health");	
			if(stamina >= 20 && health_current >= 10)
			{
				GetStaminaHandler().SetStamina(stamina - Staminaburn);
				if(GetGame().IsDedicatedServer())
				{
					AddHealth("","Health",damage);
					GiveShock(shock);
				}
			}
		}
	};
	override void OnUnconsciousUpdate(float pDt, int last_command)
	{
		super.OnUnconsciousUpdate(pDt,last_command);
		if( GetGame().IsServer() )
		{
			if( m_UnconsciousTime > PlayerConstants.UNCONSCIOUS_IN_WATER_TIME_LIMIT_TO_DEATH && GetGame().GetWaterDepth(GetPosition()) > 0.1  )
			{
				SetHealth("","",-100);
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
};
modded class DayZPlayerImplementSwimming
{
	bool CheckSwimmingStart(out vector waterLevel)
	{
		vector 	pp = m_pPlayer.GetPosition();
		waterLevel = HumanCommandSwim.WaterLevelCheck(m_pPlayer, pp);

		return false;
	}
};
//Diving====================================================================================================================================================================================================================================================================================================================================================
// *************************************************************************************
// ! Animation Graph Constants Table
// *************************************************************************************
class HumanCommandScript_DivingST
{
	void HumanCommandScript_DivingST(Human pHuman)
	{
		HumanAnimInterface 	hai = pHuman.GetAnimInterface();

		m_CmdStartSwimming 	= hai.BindCommand("CMD_Swim");		
		m_VarSpeed			= hai.BindVariableFloat("MovementSpeed");
		m_VarDirection		= hai.BindVariableFloat("MovementDirection");
		m_TagIsSwimming 	= hai.BindTag("TagSwimming");
	}		
	// TAnimGraphCommand 		m_CmdStartSwimming;		//! command to start swimming
	// TAnimGraphVariable 		m_VarSpeed;				//! float variable - 0,1,2,3 speed
	// TAnimGraphVariable 		m_VarDirection;			//! float variable - angle 
	// TAnimGraphTag			m_TagIsSwimming;		//! 
	int 					m_CmdStartSwimming;		//! command to start swimming
	int 					m_VarSpeed;				//! float variable - 0,1,2,3 speed
	int 					m_VarDirection;			//! float variable - angle 
	int 					m_TagIsSwimming;		//! 
};
class HumanCommandScript_Diving : HumanCommandScript
{
	DayZPlayer 							m_pPlayer;
	HumanCommandScript_DivingST 		m_Table;
	HumanInputController 				m_Input;
	float 								m_fTime;
	SHumanCommandSwimSettings			m_pSettings;			//! swim settings
	protected bool						m_bNeedFinish;
	protected bool						m_bWasDiving = false;


	float 								m_fWaterLevelDepth;		//! water depth
	float 								m_fCharacterDepth;		//! char's depth
	float 								m_fWaterAlignV[1];		//! filter value 

	float 								m_fSpeedX;				//! x speed
	float 								m_fSpeedZ;				//! x speed
	float 								m_fSpeedXV[1];			//! filter value
	float 								m_fSpeedZV[1];			//! filter value
	protected float		WaterLevelSwim = 1.4;					//!< when swimming - entity position depth (1.4 m)
	static float		WaterLevelIn = 1.5;					//!< when entering water - what level cases swimming (1.5m)
	static float		WaterLevelOut = 1.2;					//!< what water level causes to stop swimming (1.2m)
	PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

	void HumanCommandScript_Diving (DayZPlayer pPlayer, HumanCommandScript_DivingST pTable)
	{
		m_pPlayer 	= pPlayer;
		m_Table 	= pTable;
		m_Input		= pPlayer.GetInputController();
		m_pSettings	= pPlayer.GetDayZPlayerType().CommandSwimSettingsW();
	}
	void StartSwimming()
	{
		PreAnim_CallCommand(m_Table.m_CmdStartSwimming, 1, 1);	
	}
	void EndSwimming()
	{
		PreAnim_CallCommand(m_Table.m_CmdStartSwimming, 0, 0);
		WaterLevelSwim = 1.4;
	}
	void UpdateWaterDepth()
	{
		vector 	pp = m_pPlayer.GetPosition();
		vector  wl = HumanCommandSwim.WaterLevelCheck(m_pPlayer, pp);

		m_fWaterLevelDepth = wl[0];		// whats water depth at player's position
		m_fCharacterDepth = wl[1];		// whats character depth  at player's position
	}
	override void OnActivate()
	{
		StartSwimming();
		
		dBodyEnableGravity(m_pPlayer, false);
	}
	override void OnDeactivate()
	{
		dBodyEnableGravity(m_pPlayer, true);
	}
	float GetWaterDepthDive()
	{
		vector 	pp = m_pPlayer.GetPosition();
		vector  wl = HumanCommandSwim.WaterLevelCheck(m_pPlayer, pp);

		return wl[0];
	}
	float GetCharacterDepthDive()
	{
		vector 	pp = m_pPlayer.GetPosition();
		vector  wl = HumanCommandSwim.WaterLevelCheck(m_pPlayer, pp);

		return wl[1];
	}
	bool HandleDiving(int pCurrentCommandID, HumanCommandMove pCMove, HumanMovementState pState)
	{	
		if ( pCurrentCommandID == DayZPlayerConstants.COMMANDID_UNCONSCIOUS || pCurrentCommandID == DayZPlayerConstants.COMMANDID_DAMAGE )
			return false;
		
		m_bWasDiving = false;

		//! get water level 
		if (pCurrentCommandID != DayZPlayerConstants.COMMANDID_SWIM)
		{
			vector wl;
			if ( GetWaterDepthDive() >= WaterLevelSwim)
			{
				m_pPlayer.StartCommand_Swim();
				m_bWasDiving = true;
				return true;
			}
			 
			return false;
		}
		else // if (pCurrentCommandID == DayZPlayerConstants.COMMANDID_SWIM)
		{
			if (GetWaterDepthDive() < WaterLevelOut)
			{
				HumanCommandSwim hcs = m_pPlayer.GetCommand_Swim();
				hcs.StopSwimming();
				m_bWasDiving = false;
				return true;
			}
		
			//! handled !
			m_bWasDiving = true;
			return true;
		}
	}
	override void PreAnimUpdate(float pDt)
	{
	    if (m_bNeedFinish)
		{
			EndSwimming();
			return;
		}

		vector 	localDir;
		float 	speed;
		float 	heading;
		// get int movement 
		m_Input.GetMovement(speed, localDir);
		heading = m_Input.GetHeadingAngle();

		//! if movement moves front - remap 0,1,2,3 to 0,2,3 (in animation graph)
		float 	animSpeed = 0;

		if (speed > 0)
		{
			if (localDir[2] > 0.3)
			{
				if (speed > 2.0)
				{
					animSpeed = 3.0;
				}
				else
				{
					animSpeed = 2.0;
				}
			}
		}

		//! handle animation swimming speed 
		PreAnim_SetFloat(m_Table.m_VarSpeed, animSpeed);		// sets motion variable speed 

		//! rotate character (directly by heading angle - with filtering)
		if (animSpeed <= 0)
		{
			PreAnim_SetFilteredHeading(heading, m_pSettings.m_fAlignIdleTimeout, m_pSettings.m_fAlignIdleMaxChanged);
		}
		else if (animSpeed <= 2)
		{	
			PreAnim_SetFilteredHeading(heading, m_pSettings.m_fAlignSlowTimeout, m_pSettings.m_fAlignSlowMaxChanged);
		}
		else
		{
			PreAnim_SetFilteredHeading(heading, m_pSettings.m_fAlignFastTimeout, m_pSettings.m_fAlignFastMaxChanged);
		}
	
		//! udpate time
		m_fTime += pDt;
	}
	override void PrePhysUpdate(float pDt)
	{
		UpdateWaterDepth();

		float filtCharDepth = Math.SmoothCD(m_fCharacterDepth, WaterLevelSwim, m_fWaterAlignV, 0.3, 1.0, pDt);
			
		//! get filtered part 
		float delta 		= m_fCharacterDepth - filtCharDepth;	
		//! set filtered part as movement 
		vector trans		= vector.Zero;
		//! get local translations 
		PrePhys_GetTranslation(trans);		// in case this returns false ... trans is still zero 
		// waves 
		delta += Math.Sin(m_fTime * 3) * 0.003;
		//! height correction
		trans[1] = trans[1] + delta;

		//! XZ side translation 
		vector 	locDir;
		float 	speed;
		float 	swimSpeedX, swimSpeedZ;
		float 	flipperspeed;
		m_Input.GetMovement(speed, locDir);
		PlayerBase player = PlayerBase.Cast(m_pPlayer);
		if (speed > 0)
		{
			if (locDir[2] < 0)	// backwards ? 
			{
				swimSpeedZ = locDir[2] * m_pSettings.m_fMovementSpeed;
			}

			swimSpeedX = locDir[0] * m_pSettings.m_fMovementSpeed;
		}
		

		UAInterface input_interface = m_pPlayer.GetInputInterface();
		if ((m_pPlayer.GetInstanceType() != DayZPlayerInstanceType.INSTANCETYPE_REMOTE) && input_interface.SyncedHold("UADiveDown", true) && WaterLevelSwim <= 35)
		{
			WaterLevelSwim += 0.05;
		}
		if ( (m_pPlayer.GetInstanceType() != DayZPlayerInstanceType.INSTANCETYPE_REMOTE) && input_interface.SyncedHold("UADiveUp", true) && WaterLevelSwim >= 1.2)
		{
			WaterLevelSwim -= 0.05;
		}
		Clothing feetAttachment = Clothing.Cast(m_pPlayer.FindAttachmentBySlotName("feet"));
		if(feetAttachment && feetAttachment.IsFlippers())
		{
			if (locDir[2] > 0)
			{
				flipperspeed = feetAttachment.ConfigGetFloat("flipper");
				
			}
		}
		if( feetAttachment && feetAttachment.IsFlippers() && m_Input.IsMeleeFastAttackModifier())
		{
			flipperspeed = feetAttachment.ConfigGetFloat("flippersprint");
		}
		if(player.GetFirstMutation() == 6 || player.GetSecondMutation() == 6)
		{
			if (locDir[2] > 0)
			{
				flipperspeed = 0.080;
			}

			if(m_Input.IsMeleeFastAttackModifier())
			{			
				flipperspeed = 0.160;
			}
		}

		m_fSpeedX = Math.SmoothCD(m_fSpeedX, swimSpeedX, m_fSpeedXV, 0.3, 1, pDt);		
		m_fSpeedZ = Math.SmoothCD(m_fSpeedZ, swimSpeedZ, m_fSpeedZV, 0.3, 1, pDt);

		trans[0] = trans[0] + m_fSpeedX * pDt;
		trans[2] = trans[2] + m_fSpeedZ * pDt + flipperspeed;

		PrePhys_SetTranslation(trans);
		//!
	}
	//! called when all animation / pre phys update is handled
	override bool PostPhysUpdate(float pDt)
	{

		//!
		if (m_bNeedFinish)
		{
			return false;
		}

		//! finish if water level is smaller than some value (around 1m of depth)
		if (m_fWaterLevelDepth < WaterLevelOut)
		{
			m_bNeedFinish = true;	// let it run 1 frame more
		}

		return true;	// handled with SetFlagFinished();
	}
	

};
modded class DayZPlayerImplement
{
	ref HumanCommandScript_DivingST	m_DivingST;
	SHumanCommandSwimSettings			m_pSettings;			//! swim settings
	float 								m_fWaterLevelDepth;		//! water depth
	float 								m_fCharacterDepth;		//! char's depth
	void DayZPlayerImplement()
	{	
		m_pSettings	= GetDayZPlayerType().CommandSwimSettingsW();
	}	
	//!
	void 	InitTables()
	{
		if (m_DivingST == null)
		{
			m_DivingST = new HumanCommandScript_DivingST(this);
		}
	}

	override bool ModCommandHandlerInside (float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		//! MUST BE HERE TO NOT DISABLE OTHER MODS
		if (super.ModCommandHandlerInside(pDt, pCurrentCommandID, pCurrentCommandFinished))
		{
			return true;
		}

		//! 
		if (pCurrentCommandID == DayZPlayerConstants.COMMANDID_SCRIPT)
		{
			HumanCommandScript hcs = GetCommand_Script();	
		
			if (HumanCommandScript_Diving.Cast(hcs) != null)
			{
				// we are running  HumanCommandScript_Diving

				return true;		// is handled 
			}
			return false;			// not handled
	
		}
		vector 	pp = this.GetPosition();
		vector  wl = HumanCommandSwim.WaterLevelCheck(this, pp);

		m_fWaterLevelDepth = wl[0];		// whats water depth at player's position
		m_fCharacterDepth = wl[1];		// whats character depth  at player's position

		float		WaterLevelIn = 1.5;					//!< when entering water - what level cases swimming (1.5m)
		float		WaterLevelOut = 1.2;					//!< what water level causes to stop swimming (1.2m)
		Clothing headAttachment = Clothing.Cast(this.FindAttachmentBySlotName("Headgear"));
		Clothing bodyAttachment = Clothing.Cast(this.FindAttachmentBySlotName("body"));
		PlayerBase player = PlayerBase.Cast(this);
		if (m_fCharacterDepth >= WaterLevelIn && m_fCharacterDepth >= WaterLevelIn && !((headAttachment && headAttachment.IsDivingHelmet()) && (bodyAttachment && bodyAttachment.IsDivingSuit()) || player.IsAlpha() || player.IsQueenAlpha()))
		{

			//! init tables - done just once
			InitTables();

			//! allocate / new swim sample
			HumanCommandScript_Diving cmdSSS = new HumanCommandScript_Diving(this, m_DivingST);
		
			// start it now
			StartCommand_Script(cmdSSS);

			return true;

		}
		
		return false;	// not handled
	}

	override bool EvaluateDamageHitAnimation(TotalDamageResult pDamageResult, int pDamageType, EntityAI pSource, string pComponent, string pAmmoType, vector pModelPos, out int pAnimType, out float pAnimHitDir, out bool pAnimHitFullbody)
	{
		PlayerBase player = PlayerBase.Cast(this);
		if(player.IsAlpha() || player.IsQueenAlpha())
		{
			pAnimHitFullbody = false;
		}
		
		return super.EvaluateDamageHitAnimation(pDamageResult,pDamageType,pSource,pComponent,pAmmoType,pModelPos,pAnimType,pAnimHitDir,pAnimHitFullbody);
	}
	
};
modded class DayZPlayerImplementFallDamage
{
	override void HandleFallDamage(float pHeight)
	{
		if (GetGame().IsServer())
		{
			PlayerBase pb = PlayerBase.Cast(m_Player);

			if(pb && pb.IgnoreFallingDamage())
			{
				return;
			}
			//! no dmg height
			if (pHeight <= FD_DMG_FROM_HEIGHT)
			{
				return;
			}
				
			vector posMS = m_Player.WorldToModel(m_Player.GetPosition());
			
			float normalizedHeight = MiscGameplayFunctions.Normalize(pHeight, FD_MAX_HEIGHT_LEG_BREAK); //Normalize the height player fell from
			float dmg; //Damage dealt to leg
			float damagecoef = DamageCoef(pHeight);
			int mutation1 = pb.GetFirstMutation();
			int mutation2 = pb.GetSecondMutation();
			//This uses a quadratic EaseInOut function ro deal damage to legs
			/*if (normalizedHeight < 0.5)
				dmg = 2*Math.Pow(normalizedHeight,2);
			else
				dmg = 1 - Math.Pow(-2*normalizedHeight+2,2)/2;*/
			
			dmg = Easing.EaseInOutQuart(normalizedHeight);
			
			//We multiply by 100 to "un normalize" value and multiply by a random factor to deal extra damage to legs
			dmg = (dmg * 100) * Math.RandomFloatInclusive(0.8, 1.5);
			
			if ( pHeight >= FD_MAX_HEIGHT_LEG_BREAK)
			{
				dmg += 100; //Simply adding 100 should be enough to break legs 100% of time without calling GetHealth method
			}
				
			if(mutation1 != 1 || mutation2 != 1)
			{
				PlayerBase.Cast(m_Player).DamageAllLegs(dmg);
			}
			
			float stamina = pb.GetStaminaHandler().GetStamina();
			if(mutation1 == 1 || mutation2 == 1 && !pb.IsInPOI())
			{
				damagecoef = damagecoef - stamina;
			}
			
			//Deal global damage when falling
			m_Player.ProcessDirectDamage( DT_CUSTOM, m_Player, "", FD_AMMO, posMS, damagecoef);
			
			if(mutation1 == 1 || mutation2 == 1)
			{
				pb.GetStaminaHandler().SetStamina(damagecoef);
			}
			
			//! updates injury state of player immediately
			
			if (pb) pb.ForceUpdateInjuredState();
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
modded class DayZPlayerMeleeFightLogic_LightHeavy
{
	override protected void DamageHands(DayZPlayer DZPlayer, ClothingBase gloves, InventoryItem itemInHands)
	{

		PlayerBase player = PlayerBase.Cast( DZPlayer );
		if(GetGame().IsDedicatedServer())
		{
			if ( player && player.GetFirstMutation() != 2 || player.GetSecondMutation() != 2)
			{
				super.DamageHands(DZPlayer,gloves,itemInHands);
			}
		}

	}
};
modded class StaminaHandler
{
	protected float MaxstaminaAdjustment;
	protected float StamindaDeltaAdjuster;
	float MaxStaminaAdjuster(float adjustment)
	{
		MaxstaminaAdjustment = adjustment;

		return MaxstaminaAdjustment;
	};
	float StaminaDeltaAdjuster(float adjustment)
	{
		StamindaDeltaAdjuster = adjustment;

		return StamindaDeltaAdjuster;
	};
  	void Update(float deltaT, int pCurrentCommandID)
    {
        if( m_Player )
        {
            // Calculates actual max stamina based on player's load
			if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
			{
				//! gets stamina from PlayerStat
				m_Stamina = m_Player.GetStatStamina().Get();                
			}

			if(MaxstaminaAdjustment != 0)
			{
				m_StaminaCap = MaxstaminaAdjustment;
			}
			else
			{
				m_StaminaCap = GameConstants.STAMINA_MAX;
			}
			// Calculates stamina gain/loss based on movement and load
			
			m_Player.GetMovementState(m_State);
			if(StamindaDeltaAdjuster != 0)
			{
				m_StaminaDelta = StamindaDeltaAdjuster;
			}
			else
			{
				m_StaminaDelta = GameConstants.STAMINA_GAIN_IDLE_PER_SEC;
			}

			if(m_Player.GetFirstMutation() == 3 || m_Player.GetSecondMutation() == 3)
			{
				float heat_comfort = m_Player.GetStatHeatComfort().Get();
				if( heat_comfort > PlayerConstants.WATER_LOSS_THRESHOLD_HC_PLUS_HIGH )
				{
					MaxstaminaAdjustment  = 11;
				}

				if( heat_comfort < PlayerConstants.ENERGY_LOSS_THRESHOLD_HC_MINUS_HIGH )
				{
					MaxstaminaAdjustment  = 11;
				}
			}

			if(m_Player.GetFirstMutation() == 4 || m_Player.GetSecondMutation() == 4)
			{
				// Print("pCurrentCommandID" + pCurrentCommandID);
				// Print("ZombieClose" + m_Player.ZombieClose());
				if(m_Player.ZombieClose())
				{
					if(m_State.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT && m_Stamina >= 8)
					{
						StamindaDeltaAdjuster = -20;
					}
					else if(m_State.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_RUN && m_Stamina >= 8)
					{
						StamindaDeltaAdjuster = -15;
					}
					else if(m_State.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_WALK && m_Stamina >= 8)
					{
						StamindaDeltaAdjuster = -10;
					}
					else if(m_State.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_IDLE || m_Player.IsInProne() && m_Stamina >= 8)
					{
						StamindaDeltaAdjuster = -5;
					}
					else
					{
						StamindaDeltaAdjuster = 0;
					}
					
				}
				else
				{
					StamindaDeltaAdjuster = 0;
				}
			}

			if(m_Player.GetFirstMutation() == 6 || m_Player.GetSecondMutation() == 6)
			{
				if(m_State.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT)
				{
					StamindaDeltaAdjuster = -5;
				}
				else
				{
					StamindaDeltaAdjuster = 0;
				}
			}

      //Sets current stamina & stores + syncs data with client
            if (m_Stamina < 0)
            {
                m_Stamina = 0;
            }
            else
            {
                float temp = m_StaminaDelta*deltaT;
                
                m_Stamina = Math.Max(0,Math.Min((m_Stamina + temp),m_StaminaCap));
                m_Stamina = m_Stamina - m_StaminaDepletion;
            }

            if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
            {
                m_Player.GetStatStamina().Set(m_Stamina);
                m_Time += deltaT;
                if ( m_Time >= GameConstants.STAMINA_SYNC_RATE )
                {
                    m_Time = 0;
                    SyncStamina(m_Stamina, m_StaminaCap, m_IsInCooldown);
                }
            }
            else
            {
                m_Player.SetStamina(m_Stamina, m_StaminaCap);
            }

            //! sets exhaustion look of player based on stamina level
            HumanCommandAdditives ad = m_Player.GetCommandModifier_Additives();
            float exhaustion_value = 1-((m_Stamina/(m_StaminaCap*0.01))*0.01);
            exhaustion_value = Math.Min(1,exhaustion_value);
            if ( ad )
            {
                // do not apply exhaustion on local client if player is in ADS/Optics (camera shakes)
                if ( m_Player.GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_CLIENT && (m_Player.IsInOptics() || m_Player.IsInIronsights()) )
                {
                    ad.SetExhaustion(0, true);
                }
                else
                {
                    ad.SetExhaustion(exhaustion_value, true);
                }
            }

            CheckStaminaState();

            m_StaminaDelta = 0;
			// StamindaDeltaAdjuster = 0;
			// MaxstaminaAdjustment = 0;
            m_StaminaDepletion = 0; // resets depletion modifier
			m_StaminaDelta = -GameConstants.STAMINA_DRAIN_STANDING_SPRINT_PER_SEC;
        }
    }
}