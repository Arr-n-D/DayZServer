const float hearing_distance_sound = 1000;
modded class PlayerSoundManagerClient {


    override void CheckAllowUpdate() {
        
       if( GetGame().GetPlayer() )
		{
			bool is_at_hearing_distance = vector.Distance(GetGame().GetPlayer().GetPosition(), m_Player.GetPosition()) < hearing_distance_sound;
			
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