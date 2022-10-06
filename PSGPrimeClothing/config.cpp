class CfgPatches
{
	class PSGPrimeClothing
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgMods
{
	class PSGPrimeClothing
	{
		type = "mod";
		author = "R&D";
		name = "PSGPrimeClothing";
		dir = "PSGPrimeClothing";
	
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"PSGPrimeClothing\scripts\4_World"};
			};
		};
	};
};