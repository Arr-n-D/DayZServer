//syringes
class AffectedSyringe_Pure: AntiChemInjector
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionInjectSelf);
	}
	
	override void OnApply(PlayerBase player)
	{
		int random = Math.RandomIntInclusive(0, 20);
		if (random >= 5)
		{
			player.SetAffectedLevel(1);
			player.InsertAgent(AffectedAgent.AFFECTED_AGENT, 2400);
		}
		else
		{
			player.SetHealth(0)
		}
	}
};

class AffectedAdminLevel1: AntiChemInjector
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInjectSelf);
	}
	
	override void OnApply(PlayerBase player)
	{
		player.SetAffectedLevel(1);
		player.m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 2400);
		
	}
};
class AffectedAdminLevel2: AntiChemInjector
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInjectSelf);
	}
	
	override void OnApply(PlayerBase player)
	{
		player.SetAffectedLevel(2);
		player.m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 10053);
		
	}
};
class AffectedAdminLevel3: AntiChemInjector
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInjectSelf);
	}
	
	override void OnApply(PlayerBase player)
	{
		player.SetAffectedLevel(3);
		player.m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 28800);
		
	}
};
class AffectedAdminLevel4: AntiChemInjector
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInjectSelf);
	}
	
	override void OnApply(PlayerBase player)
	{
		player.SetAffectedLevel(4);
		player.m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 86893);
		
	}
};
class AffectedAdminLevel5: AntiChemInjector
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInjectSelf);
	}
	
	override void OnApply(PlayerBase player)
	{
		player.SetAffectedLevel(5);
		player.m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 115693);	
	}
};

class IsPrimeAdminInjector: AntiChemInjector
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInjectSelf);
	}
	
	override void OnApply(PlayerBase player)
	{
		player.SetIsPrime(1);
		player.m_AgentPool.SetAgentCount(AffectedAgent.AFFECTED_AGENT, 115693);	
	}
};