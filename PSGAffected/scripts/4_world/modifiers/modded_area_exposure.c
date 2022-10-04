modded class AreaExposureMdfr
{
  float buffInterval = 0;
	override void OnActivate(PlayerBase player)
	{
    Print("AreaExposureMdfr::OnActivate::Start");
    player.SetBioZoneStatus(true);
    super.OnActivate(player);
	}

  override void OnDeactivate(PlayerBase player)
	{
    Print("AreaExposureMdfr::OnDeactivate::Start");
    player.SetBioZoneStatus(false);
    super.OnDeactivate(player);
  }

  override void OnTick(PlayerBase player, float deltaT)
	{
    Print("AreaExposureMdfr::OnTick::Start");
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