#ifndef _STATE_ENUMS_
#define _STATE_ENUMS_

enum class APP_STATE 
{ 
	MODE_2D,
	MODE_3D 
};
enum class MODE_STATE 
{ 
	IDLE, 
	GEN_PTS, 
	COMPUTE_CH 
};
enum class CH2D
{
	JARVIS_MARCH = 0,
	GRAHAM_SCAN,
	MONOTONE_CHAIN,
	CHANS_ALGORITHM,
	QUICK_HULL,
};
enum class JM_STATE
{
	FIND_LEFTMOST_POINT,
};

#endif
