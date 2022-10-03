class CfgPatches
{
	class Dressupbox
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts","DZ_Characters","DZ_Characters_Headgear","DZ_Characters_Tops","DZ_Characters_Vests","DZ_Characters_Pants","DZ_Characters_Belts","DZ_Characters_Backpacks","DZ_Characters_Heads","DZ_Gear_Optics","DZ_Gear_Tools","DZ_Radio","DZ_Gear_Food","DZ_Gear_Medical","DZ_Gear_Containers","DZ_Gear_Consumables","DZ_Gear_Cooking","DZ_Gear_Navigation","DZ_Gear_Drinks","DZ_Gear_Camping","DZ_Gear_Crafting","DZ_Animals","DZ_AI","DZ_Weapons_Melee","DZ_Characters_Zombies","DZ_Weapons_Projectiles","DZ_Weapons_Magazines","DZ_Weapons_Firearms","DZ_Weapons_Explosives","DZ_Weapons_Ammunition","DZ_Weapons_Shotguns","DZ_Weapons_Archery","DZ_Weapons_Optics","DZ_Weapons_Supports","DZ_Weapons_Muzzles","DZ_Weapons_Attachments_Data","DZ_Pistols","DZ_Structures","DZ_Vehicles_Parts","DZ_Vehicles_Wheeled","DZ_Sounds_Effects","DZ_Sounds_Weapons"};
	};
};
class CfgMods
{
	class Dressupbox
	{
		type = "mod";
		author = "R&D";
		name = "Dressupbox";
		dir = "Dressupbox";
		dependencies[] = {};
	};
};

class CfgVehicles {
	class Inventory_Base;
	class Head_Default;
	class SurvivorMale_Base;
	class SurvivorFemale_Base;
	class Man;
	class MaleTorso_Base;
	class MaleHands_Base;
	class MaleLegs_Base;
	class MaleFeet_Base;
	class FemaleTorso_Base;
	class FemaleHands_Base;
	class FemaleLegs_Base;
	class FemaleFeet_Base;
	class AntiChemInjector;

	class DUB_SurMutant_M: SurvivorMale_Base
	{
		scope = 2;
		emptyHead = "DUB_Muthead_M";
		emptyBody = "DUB_Mutchest_M";
		emptyLegs = "DUB_Mutlegs_M";
		emptyFeet = "DUB_Mutfeet_M";
		emptyGloves = "DUB_Muthands_M";
		faceType = "DUB_Muthead_M";
		decayedTexture = "";
		class BloodyHands
		{
			mat_normal = "";
			mat_blood = "";
		};
		voiceType = 1;
	};
	class DUB_Muthead_M: Head_Default
	{
		scope = 2;
		displayName = "Mutant face";
		model = "Dressupbox\mutation\male\muthead_m.p3d";
		itemSize[] = {2,2};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{""}},{0.7,{""}},{0.5,{""}},{0.3,{""}},{0.1,{""}}};
				};
			};
		};
	};
	class DUB_Mutchest_M: MaleTorso_Base
	{
		scope = 2;
		displayName = "Mutant chest";
		model = "Dressupbox\mutation\male\mutchest_m.p3d";
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_m_co.paa"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Muthands_M: MaleHands_Base
	{
		scope = 2;
		displayName = "Mutant hands";
		model = "Dressupbox\mutation\male\muthands_m.p3d";
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_m_co.paa"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Mutlegs_M: MaleLegs_Base
	{
		scope = 2;
		displayName = "Mutant legs";
		model = "Dressupbox\mutation\male\mutlegs_m.p3d";
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_m_co.paa"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Mutfeet_M: MaleFeet_Base
	{
		scope = 2;
		displayName = "mutant feet";
		model = "Dressupbox\mutation\male\mutfeet_m.p3d";
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_m_co.paa"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_SurMutant_F: SurvivorFemale_Base
	{
		scope = 2;
		emptyHead = "DUB_Muthead_F";
		emptyBody = "DUB_Mutchest_F";
		emptyLegs = "DUB_Mutlegs_F";
		emptyFeet = "DUB_Mutfeet_F";
		emptyGloves = "DUB_Muthands_F";
		faceType = "DUB_Muthead_F";
		decayedTexture = "";
		class BloodyHands
		{
			mat_normal = "";
			mat_blood = "";
		};
		voiceType = 1;
	};
	class DUB_Muthead_F: Head_Default
	{
		scope = 2;
		displayName = "Mutant face";
		model = "Dressupbox\mutation\female\muthead_f.p3d";
		itemSize[] = {2,2};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{""}},{0.7,{""}},{0.5,{""}},{0.3,{""}},{0.1,{""}}};
				};
			};
		};
	};
	class DUB_Mutchest_F: FemaleTorso_Base
	{
		scope = 2;
		displayName = "Mutant chest";
		model = "Dressupbox\mutation\female\mutchest_f.p3d";
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_f_co.paa"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Muthands_F: FemaleHands_Base
	{
		scope = 2;
		displayName = "Mutant hands";
		model = "Dressupbox\mutation\female\muthands_f.p3d";
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_f_co.paa"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Mutlegs_F: FemaleLegs_Base
	{
		scope = 2;
		displayName = "Mutant legs";
		model = "Dressupbox\mutation\female\mutlegs_f.p3d";
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_f_co.paa"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Mutfeet_F: FemaleFeet_Base
	{
		scope = 2;
		displayName = "mutant feet";
		model = "Dressupbox\mutation\female\mutfeet_f.p3d";
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_f_co.paa"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_SurMutant_M_2: SurvivorMale_Base
	{
		scope = 2;
		emptyHead = "DUB_Muthead_M_2";
		emptyBody = "DUB_Mutchest_M_2";
		emptyLegs = "DUB_Mutlegs_M_2";
		emptyFeet = "DUB_Mutfeet_M_2";
		emptyGloves = "DUB_Muthands_M_2";
		faceType = "DUB_Muthead_M_2";
		decayedTexture = "";
		class BloodyHands
		{
			mat_normal = "";
			mat_blood = "";
		};
		voiceType = 1;
	};
	class DUB_Muthead_M_2: Head_Default
	{
		scope = 2;
		displayName = "Mutant face";
		model = "Dressupbox\mutation\male\muthead_m_2.p3d";
		itemSize[] = {2,2};
		hiddenSelections[] = {"personality","mutation"};
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_m_2_co.paa","Dressupbox\mutation\data\mutant_2_co"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat","Dressupbox\mutation\data\mutantpersonality.rvmat"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{""}},{0.7,{""}},{0.5,{""}},{0.3,{""}},{0.1,{""}}};
				};
			};
		};
	};
	class DUB_Mutchest_M_2: MaleTorso_Base
	{
		scope = 2;
		displayName = "Mutant chest";
		model = "Dressupbox\mutation\male\mutchest_m_2.p3d";
		hiddenSelections[] = {"personality","mutation"};
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_m_2_co.paa","Dressupbox\mutation\data\mutant_2_co"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat","Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Muthands_M_2: MaleHands_Base
	{
		scope = 2;
		displayName = "Mutant hands";
		model = "Dressupbox\mutation\male\muthands_m_2.p3d";
		hiddenSelections[] = {"personality","mutation"};
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_m_2_co.paa","Dressupbox\mutation\data\mutant_2_co"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat","Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Mutlegs_M_2: MaleLegs_Base
	{
		scope = 2;
		displayName = "Mutant legs";
		model = "Dressupbox\mutation\male\mutlegs_m_2.p3d";
		hiddenSelections[] = {"personality","mutation"};
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_m_2_co.paa","Dressupbox\mutation\data\mutant_2_co"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat","Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Mutfeet_M_2: MaleFeet_Base
	{
		scope = 2;
		displayName = "mutant feet";
		model = "Dressupbox\mutation\male\mutfeet_m_2.p3d";
		hiddenSelections[] = {"personality","mutation"};
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_m_2_co.paa","Dressupbox\mutation\data\mutant_2_co"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat","Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_SurMutant_F_2: SurvivorFemale_Base
	{
		scope = 2;
		emptyHead = "DUB_Muthead_F_2";
		emptyBody = "DUB_Mutchest_F_2";
		emptyLegs = "DUB_Mutlegs_F_2";
		emptyFeet = "DUB_Mutfeet_F_2";
		emptyGloves = "DUB_Muthands_F_2";
		faceType = "DUB_Muthead_F_2";
		decayedTexture = "";
		class BloodyHands
		{
			mat_normal = "";
			mat_blood = "";
		};
		voiceType = 1;
	};
	class DUB_Muthead_F_2: Head_Default
	{
		scope = 2;
		displayName = "Mutant face";
		model = "Dressupbox\mutation\female\muthead_f_2.p3d";
		itemSize[] = {2,2};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{""}},{0.7,{""}},{0.5,{""}},{0.3,{""}},{0.1,{""}}};
				};
			};
		};
	};
	class DUB_Mutchest_F_2: FemaleTorso_Base
	{
		scope = 2;
		displayName = "Mutant chest";
		model = "Dressupbox\mutation\female\mutchest_f_2.p3d";
		hiddenSelections[] = {"personality","mutation"};
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_f_2_co.paa","Dressupbox\mutation\data\mutant_2_co"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat","Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Muthands_F_2: FemaleHands_Base
	{
		scope = 2;
		displayName = "Mutant hands";
		model = "Dressupbox\mutation\female\muthands_f_2.p3d";
		hiddenSelections[] = {"personality","mutation"};
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_f_2_co.paa","Dressupbox\mutation\data\mutant_2_co"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat","Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Mutlegs_F_2: FemaleLegs_Base
	{
		scope = 2;
		displayName = "Mutant legs";
		model = "Dressupbox\mutation\female\mutlegs_f_2.p3d";
		hiddenSelections[] = {"personality","mutation"};
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_f_2_co.paa","Dressupbox\mutation\data\mutant_2_co"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat","Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};
	class DUB_Mutfeet_F_2: FemaleFeet_Base
	{
		scope = 2;
		displayName = "mutant feet";
		model = "Dressupbox\mutation\female\mutfeet_f_2.p3d";
		hiddenSelections[] = {"personality","mutation"};
		hiddenSelectionsTextures[] = {"Dressupbox\mutation\data\mutant_f_2_co.paa","Dressupbox\mutation\data\mutant_2_co"};
		hiddenSelectionsMaterials[] = {"Dressupbox\mutation\data\mutantpersonality.rvmat","Dressupbox\mutation\data\mutantpersonality.rvmat"};
	};

	class AffectedSyringe_Pure: AntiChemInjector
	{
		scope = 2;
		displayName = "Pure Affected strain";
		descriptionShort = "Contains a pure strain of the Affected virus. Use with caution.";
		debug_ItemCategory = 7;
		model = "Dressupbox\object\injector\injector.p3d";
		rotationFlags = 17;
		itemSize[] = {1,2};
		weight = 60;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
				};
			};
		};
	};

	class AffectedAdminLevel1: AntiChemInjector
	{
		scope = 2;
		displayName = "Affected strain - Stage Level 1";
		descriptionShort = "Admin use only";
		debug_ItemCategory = 7;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"\dz\gear\medical\data\antidote_co.paa"};
		rotationFlags = 17;
		itemSize[] = {1,2};
		weight = 60;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] = {{1,{"DZ\gear\medical\data\epipen.rvmat"}},{0.7,{"DZ\gear\medical\data\epipen.rvmat"}},{0.5,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0.3,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0,{"DZ\gear\medical\data\epipen_destruct.rvmat"}}};
				};
			};
		};
	};
	class AffectedAdminLevel2: AntiChemInjector
	{
		scope = 2;
		displayName = "Affected strain - Stage Level 2";
		descriptionShort = "Admin use only";
		debug_ItemCategory = 7;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"\dz\gear\medical\data\antidote_co.paa"};
		rotationFlags = 17;
		itemSize[] = {1,2};
		weight = 60;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] = {{1,{"DZ\gear\medical\data\epipen.rvmat"}},{0.7,{"DZ\gear\medical\data\epipen.rvmat"}},{0.5,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0.3,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0,{"DZ\gear\medical\data\epipen_destruct.rvmat"}}};
				};
			};
		};
	};
	class AffectedAdminLevel3: AntiChemInjector
	{
		scope = 2;
		displayName = "Affected strain - Stage Level 3";
		descriptionShort = "Admin use only";
		debug_ItemCategory = 7;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"\dz\gear\medical\data\antidote_co.paa"};
		rotationFlags = 17;
		itemSize[] = {1,2};
		weight = 60;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] = {{1,{"DZ\gear\medical\data\epipen.rvmat"}},{0.7,{"DZ\gear\medical\data\epipen.rvmat"}},{0.5,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0.3,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0,{"DZ\gear\medical\data\epipen_destruct.rvmat"}}};
				};
			};
		};
	};
	class AffectedAdminLevel4: AntiChemInjector
	{
		scope = 2;
		displayName = "Affected strain - Stage Level 4";
		descriptionShort = "Admin use only";
		debug_ItemCategory = 7;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"\dz\gear\medical\data\antidote_co.paa"};
		rotationFlags = 17;
		itemSize[] = {1,2};
		weight = 60;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] = {{1,{"DZ\gear\medical\data\epipen.rvmat"}},{0.7,{"DZ\gear\medical\data\epipen.rvmat"}},{0.5,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0.3,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0,{"DZ\gear\medical\data\epipen_destruct.rvmat"}}};
				};
			};
		};
	};
	class AffectedAdminLevel5: AntiChemInjector
	{
		scope = 2;
		displayName = "Affected strain - Stage Level 5|DO NOT USE|";
		descriptionShort = "Admin use only";
		debug_ItemCategory = 7;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"\dz\gear\medical\data\antidote_co.paa"};
		rotationFlags = 17;
		itemSize[] = {1,2};
		weight = 60;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] = {{1,{"DZ\gear\medical\data\epipen.rvmat"}},{0.7,{"DZ\gear\medical\data\epipen.rvmat"}},{0.5,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0.3,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0,{"DZ\gear\medical\data\epipen_destruct.rvmat"}}};
				};
			};
		};
	};
};