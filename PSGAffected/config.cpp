class CfgPatches
{
	class PSGAffected
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts"};
	};
};
class CfgMods
{
	class PSGAffected
	{
		type = "mod";
		author = "R&D";
		name = "PSGAffected";
		dir = "PSGAffected";
		dependencies[] = {"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"PSGAffected\scripts\4_world"};
			};

		};
	};
};