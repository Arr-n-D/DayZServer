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

class CfgSoundShaders {

	class Cassius_Teleport_SoundShader {
		samples[] = {{"PSGAffected\sounds\cassius_teleport",1}};
		volume = 1;
		range = 1000;
	};
	
};

class CfgSoundSets {

	class Cassius_Teleport_SoundSet {
		soundShaders[] = {"Cassius_Teleport_SoundShader"};
	};

};