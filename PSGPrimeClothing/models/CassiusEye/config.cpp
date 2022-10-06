class CfgPatches
{
	class CassiusEye
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};

class CfgVehicles
{
	class Clothing;
	class CassiusEye: Clothing
	{
		scope = 2;
		displayName = "Cassius' Eye";
		descriptionShort = "The eye of Cassius, an Affected Prime. It is said the wearer will be granted abilities that humans can only dream of.";
		model = "\PSGPrimeClothing\models\CassiusEye\cassius_eye_g.p3d";
		inventorySlot[] = {"Eyewear"};
		simulation = "clothing";
		itemInfo[] = {"Clothing","Eyewear"};
		weight = 100;
		rotationFlags = 1;
		itemSize[] = {2,1};
		varWetMax = 1;
		repairableWithKits[] = {5,2};
		repairCosts[] = {30,25};
		hiddenSelectionsTextures[] = {"PSGPrimeClothing\models\CassiusEye\data\cassius_eye_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 60;
					healthLevels[] = {{1,{""}},{0.7,{""}},{0.5,{""}},{0.3,{""}},{0,{""}}};
				};
			};
		};
		class ClothingTypes
		{
			male = "\PSGPrimeClothing\models\CassiusEye\cassius_eye_m.p3d";
			female = "\PSGPrimeClothing\models\CassiusEye\cassius_eye_f.p3d";
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet = "WorkingGloves_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "WorkingGloves_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
};
