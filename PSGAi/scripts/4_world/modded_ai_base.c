//zombie base
modded class ZombieBase
{

	protected ref Timer 	Movetimer;
	override void EOnInit(IEntity other, int extra)
	{
		super.EOnInit(other, extra);
		ForceCrawl();
	}
	bool IsBoss()
	{
		return false;
	}
	
 	override bool ResistContaminatedEffect() {
		return true;
	}

	bool CannotRunInDayLight()
	{
		return true;
	}
	bool ChanceToCrawl()
	{
		return true;
	}
	void ForceCrawl()
	{
		if (ChanceToCrawl())
		{
			float crawlchance = Math.RandomIntInclusive(0, 20);
			if (crawlchance == 1)
			{
				m_IsCrawling = true;
				StartCommand_Crawl(0);
			}	
		}
	}
	override void HandleMove(int pCurrentCommandID)
	{
		private float movementSpeedApply;
		DayZInfectedInputController ic = GetInputController();
		if(CannotRunInDayLight() && !IsZombieMilitary())
		{
			
			if(!GetGame().GetWorld().IsNight())
			{
				GetInputController().OverrideMovementSpeed(true,1.5);
			}
			else
			{
				GetInputController().OverrideMovementSpeed(false,1.0);
			}
		}

		super.HandleMove(pCurrentCommandID);	
	}
};