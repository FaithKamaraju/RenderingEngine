#pragma once

#include "EngineCore/EngineCore.h"
#include "Renderer/Constants.h"
#include <vector>
#include <memory>
#include <mutex>
#include <glm/glm.hpp>



namespace FE {

	struct FE_API PointLightStruct {
		glm::vec4 position{ 0.0f };				//16 0  
		glm::vec4 ambient{ 0.0f };				//16 16 
		glm::vec4 diffuse{ 0.0f };				//16 32 
		glm::vec4 specular{ 0.0f };				//16 48
		float constant = 0.f;					//4  64
		float linear = 0.f;						//4  68
		float quadratic = 0.f;					//4  72
		int id = -1;							//4  76
	};
	struct FE_API SpotLightStruct {
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
		int id = -1;							// 4 100
		float padding2 = 0.f;					// 4 104
		float padding3 = 0.f;					// 4 108
	};

	constexpr int _PointLightOffset = 0;
	constexpr int _SpotLightOffset = MAXLIGHTS * sizeof(PointLightStruct);
	constexpr int _numPointLightsOffset = (MAXLIGHTS * sizeof(SpotLightStruct)) + _SpotLightOffset;
	constexpr int _numSpotLightsOffset = _numPointLightsOffset + 4;

	class PointLight;
	class SpotLight;

	class FE_API LightUBOManager
	{

	private:
		static LightUBOManager* _instance;
		static std::mutex _mutex;

		unsigned int LightsUBO;
		std::vector<std::weak_ptr<PointLight>> pointLightsArr{};
		std::vector<std::weak_ptr<SpotLight>> spotLightsArr{};

	private:

		LightUBOManager();

		void resetPointLightMemory(size_t index);
		void resetSpotLightMemory(size_t index);

	public:
		LightUBOManager(LightUBOManager& other) = delete;
		void operator=(const LightUBOManager&) = delete;

		static LightUBOManager* GetInstance();

		int addPointLightToMemory(std::shared_ptr<PointLight> pointLightPtr);
		int addSpotLightToMemory(std::shared_ptr<SpotLight> spotLightPtr);

		void updateUBO(std::weak_ptr<PointLight> pointLightPtr);
		void updateUBO(std::weak_ptr<SpotLight> spotLightPtr);

		void deleteLight(std::weak_ptr<PointLight> pointLightPtr);
		void deleteLight(std::weak_ptr<SpotLight> spotLightPtr);

	};
}


