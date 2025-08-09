#include "LightUBOManager.h"
#include "glad/glad.h"

#include <iostream>

RE::LightUBOManager* RE::LightUBOManager::_instance{ nullptr };
std::mutex RE::LightUBOManager::_mutex;

RE::LightUBOManager::LightUBOManager()
	:numPointLights(0), numSpotLights(0)
{
	_PointLightOffset = 0;
	_SpotLightOffset = MAXLIGHTS * sizeof(PointLightStruct);
	_numPointLightsOffset = (MAXLIGHTS * sizeof(SpotLightStruct)) + _SpotLightOffset;
	_numSpotLightsOffset = _numPointLightsOffset + 4;

	unsigned int total_memory = _PointLightOffset + _SpotLightOffset + _numPointLightsOffset + _numSpotLightsOffset;
	GLCall(glGenBuffers(1, &LightsUBO));
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, LightsUBO));
	GLCall(glBufferData(GL_UNIFORM_BUFFER, total_memory, nullptr, GL_DYNAMIC_DRAW));
    GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, BPI_Lights, LightsUBO, 0, total_memory));
	unsigned int offset = 0;
    for (int i = 0; i < MAXLIGHTS; i++) {
		PointLightStruct temp{};
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(PointLightStruct), &temp);
		offset += sizeof(PointLightStruct);
    }
    for (int i = 0; i < MAXLIGHTS; i++) {
		SpotLightStruct temp{};
		glBufferSubData(GL_UNIFORM_BUFFER, i, sizeof(SpotLightStruct), &temp);
		offset += sizeof(SpotLightStruct);
    }
	glBufferSubData(GL_UNIFORM_BUFFER, offset,		4, &numPointLights);
	glBufferSubData(GL_UNIFORM_BUFFER, offset + 4,	4, &numSpotLights);
    GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

RE::LightUBOManager* RE::LightUBOManager::GetInstance()
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_instance == nullptr) {
		_instance = new LightUBOManager();
	}
	return _instance;
}

void RE::LightUBOManager::addPointLightToMemory(const PointLightStruct& pointLightInfo)
{
	if (numPointLights < MAXLIGHTS) {
		numPointLights += 1;
		/*pointLightsArr[m_numPointLights - 1] = pointLightInfo;*/
		int offset = (numPointLights - 1) * sizeof(PointLightStruct);

		GLCall(glNamedBufferSubData(LightsUBO, offset, sizeof(PointLightStruct), &pointLightInfo));
		GLCall(glNamedBufferSubData(LightsUBO, _numPointLightsOffset, 4, &numPointLights));
	}
	else {
		std::cout << "Maximum point lights reached!, cannot add any further!";
	}

}

void RE::LightUBOManager::addSpotLightToMemory(const SpotLightStruct& spotLightInfo)
{
	if (numSpotLights < MAXLIGHTS) {
		numSpotLights += 1;
		//spotLightsArr[m_numSpotLights - 1] = spotLightInfo;
		int offset = (numSpotLights - 1) * sizeof(SpotLightStruct) + _SpotLightOffset;

		GLCall(glNamedBufferSubData(LightsUBO, offset, sizeof(SpotLightStruct), &spotLightInfo));
		GLCall(glNamedBufferSubData(LightsUBO, _numSpotLightsOffset, 4, &numSpotLights));
	}
	else {
		std::cout << "Maximum spot lights reached!, cannot add any further!";
	}



}