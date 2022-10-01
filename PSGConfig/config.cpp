class CfgPatches
{
	class PSGConfig
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts"};
	};
};
class CfgMods
{
	class PSGConfig
	{
		type = "mod";
		author = "R&D";
		name = "PSGConfig";
		dir = "PSGConfig";
		dependencies[] = {"Game"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"PSGConfig\scripts\3_game"};
			};

		};
	};
};