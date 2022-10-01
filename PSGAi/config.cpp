class CfgPatches
{
	class PSGAi
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts"};
	};
};
class CfgMods
{
	class PSGAi
	{
		type = "mod";
		author = "R&D";
		name = "PSGAI";
		dir = "PSGAI";
		dependencies[] = {"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"PSGAi\scripts\4_world"};
			};

		};
	};
};