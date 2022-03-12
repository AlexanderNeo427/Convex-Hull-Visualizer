#ifndef _ANIM_FRAME_
#define _ANIM_FRAME_

#include <glm/vec2.hpp>
#include <vector>

#include "SceneContext.h"

struct IAnimFrame
{
	virtual void OnRender(const SceneContext& sceneCtx) = 0;
};

#endif
