#pragma once

#include "core/core.h"
#include "core/Constants.h"
#include <array>
#include <mutex>

#include <glm/glm.hpp>



namespace RE {

	struct RE_API PointLightStruct {
		glm::vec4 position{ 0.0f };				//16 0  
		glm::vec4 ambient{ 0.0f };				//16 16 
		glm::vec4 diffuse{ 0.0f };				//16 32 
		glm::vec4 specular{ 0.0f };				//16 48
		float constant = 0.f;					//4  64
		float linear = 0.f;						//4  68
		float quadratic = 0.f;					//4  72
		float padding = 0.f;					//4  76
	};
	struct RE_API SpotLightStruct {
		glm::vec4 position{ 0.0f };				//16 0
		glm::vec4 direction{ 0.0f };			//16 16
		glm::vec4 ambient{ 0.0f };				//16 32
		glm::vec4 diffuse{ 0.0f };				//16 48
		glm::vec4 specular{ 0.0f };				//16 64
		float innerCutoff = 0.f;				// 4 80
		float outerCutoff = 0.f;				// 4 84
		float constant = 0.f;					// 4 88
		float linear = 0.f;						// 4 92
		float quadratic = 0.f;					// 4 96
		float padding1 = 0.f;					// 4 100
		float padding2 = 0.f;					// 4 104
		float padding3 = 0.f;					// 4 108
	};

	class RE_API LightUBOManager
	{
	private:
		static LightUBOManager* _instance;
		static std::mutex _mutex;

		unsigned int LightsUBO;
		int numPointLights;
		int numSpotLights;

		int _PointLightOffset;
		int _SpotLightOffset;
		int _numPointLightsOffset;
		int _numSpotLightsOffset;

	private:

		LightUBOManager();
		

		/*std::array<PointLight, MAXLIGHTS> pointLightsArr;
		std::array<SpotLight, MAXLIGHTS> spotLightsArr;*/

	public:
		LightUBOManager(LightUBOManager& other) = delete;
		void operator=(const LightUBOManager&) = delete;

		static LightUBOManager* GetInstance();

		void addPointLightToMemory(const PointLightStruct& pointLightInfo);
		void addSpotLightToMemory(const SpotLightStruct& spotLightInfo);
	};
}


