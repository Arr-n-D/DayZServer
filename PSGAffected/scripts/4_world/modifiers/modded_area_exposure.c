modded class AreaExposureMdfr
{
  float buffInterval = 0;
	override void OnActivate(PlayerBase player)
	{
    player.SetBioZoneStatus(true);
    super.OnActivate(player);
	}

  override void OnDeactivate(PlayerBase player)
	{
    player.SetBioZoneStatus(false);
    super.OnDeactivate(player);
  }

  override void OnTick(PlayerBase player, float deltaT)
	{
    if (player && player.IgnoreContaminatedArea())
    {
        player.GetStatEnergy().Add(20);
        player.GetStatWater().Add(20);
    }
    else
    {
      super.OnTick(player, deltaT);
    }  
  }
}