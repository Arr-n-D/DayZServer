class CfgPatches
{
	class PSGRpc
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts"};
	};
};
class CfgMods
{
	class PSGRpc
	{
		type = "mod";
		author = "R&D";
		name = "PSGRpc";
		dir = "PSGRpc";
		dependencies[] = {"Mission"};
		class defs
		{
            class missionScriptModule
			{
				value = "";
				files[] = {"PSGRpc\scripts\5_mission"};
			};

		};
	};
};