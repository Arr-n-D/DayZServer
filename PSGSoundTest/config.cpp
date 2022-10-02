class CfgPatches
{
	class PSGSoundTest
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts"};
	};
};
class CfgMods
{
	class PSGSoundTest
	{
		type = "mod";
		author = "R&D";
		name = "PSGSoundTest";
		dir = "PSGSoundTest";
		dependencies[] = {"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"PSGSoundTest\scripts\4_world"};
			};

		};
	};
};