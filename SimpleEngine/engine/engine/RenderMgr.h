#pragma once

#include "Object.h"
#include "SceneMgr.h"
#include "Window.h"
#include "Application.h"
#include "Renderer.h"
#include "Camera.h"

namespace yk
{
	class RenderMgr : public Object
	{
	public:
		static void init();
		static void rendering();
		static SharedPtr<Window> window() { return s_window; }
	private:
		static SharedPtr<Window> s_window;
		static SharedPtr<Shader> s_shadowShader;
		static unsigned int s_matricesBlock;
		static unsigned int s_pointLightsBlock;
		static unsigned int s_directLightsBlock;
		static unsigned int s_lightSpaceMatrixBlock;
		static void setCameraMatrices(SharedPtr<Camera> camera);
		static void setPointLightsBuffer();
		static void setDirectionalLightsBuffer();
		static void setLightSpaceMatrix(mat4 mat);
		static void renderShadowMap();
		static void renderPointShadow();

	};
}