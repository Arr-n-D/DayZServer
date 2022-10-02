const float SOUNDS_HEARING_DISTANCE = 1000;
modded class PlayerSoundManagerClient {


    override void CheckAllowUpdate() {
        
       if( GetGame().GetPlayer() )
		{
			bool is_at_hearing_distance = vector.Distance(GetGame().GetPlayer().GetPosition(), m_Player.GetPosition()) < SOUNDS_HEARING_DISTANCE;
			
			if( m_UpdateTimerRunning && !is_at_hearing_distance )
			{
				SetAllowUpdate(false);
			}
			else if( !m_UpdateTimerRunning && is_at_hearing_distance )
			{
				SetAllowUpdate(true);
			}
			//PrintString("distance:" + vector.Distance(GetGame().GetPlayer().GetPosition(), m_Player.GetPosition()).ToString());
		}
    }
}