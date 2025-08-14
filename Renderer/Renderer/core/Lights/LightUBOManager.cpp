#include "LightUBOManager.h"
#include "glad/glad.h"
#include <algorithm>
#include <iostream>
#include "PointLight.h"
#include "SpotLight.h"

RE::LightUBOManager* RE::LightUBOManager::_instance{ nullptr };
std::mutex RE::LightUBOManager::_mutex;

RE::LightUBOManager::LightUBOManager()
{	

	pointLightsArr.reserve(MAXLIGHTS * sizeof(PointLightStruct));
	spotLightsArr.reserve(MAXLIGHTS * sizeof(SpotLightStruct));

	constexpr unsigned int total_memory = _PointLightOffset + _SpotLightOffset + _numPointLightsOffset + _numSpotLightsOffset;
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
	GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offset,		4, (const void*)pointLightsArr.size()));
	GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offset + 4,	4, (const void*)spotLightsArr.size()));
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

int RE::LightUBOManager::addPointLightToMemory(std::shared_ptr<PointLight> pointLightPtr)
{
	if (pointLightsArr.size() < MAXLIGHTS) {

		if (std::find_if(pointLightsArr.begin(), pointLightsArr.end(),
			[&pointLightPtr](const std::weak_ptr<PointLight>& x) {return x.lock() == pointLightPtr; }) == pointLightsArr.end()) {
			int index = pointLightsArr.size();
			int offset = (index) * sizeof(PointLightStruct);
			pointLightPtr->UBO_index = index;
			pointLightsArr.emplace_back(std::weak_ptr(pointLightPtr));

			PointLightStruct info;
			info.position = glm::vec4(pointLightPtr->transform.globalPosition, 1.f);
			info.ambient = glm::vec4(pointLightPtr->ambient, 1.f);
			info.diffuse = glm::vec4(pointLightPtr->diffuse, 1.f);
			info.specular = glm::vec4(pointLightPtr->specular, 1.f);
			info.constant = pointLightPtr->constant;
			info.linear = pointLightPtr->linear;
			info.quadratic = pointLightPtr->quadratic;
			int size = pointLightsArr.size();
			GLCall(glNamedBufferSubData(LightsUBO, offset, sizeof(PointLightStruct), &info));
			GLCall(glNamedBufferSubData(LightsUBO, _numPointLightsOffset, 4, &size));
			return index;
		}
		else {
			std::cout << "Point Light data already present!";
			return -1;
		}
		
	}
	else {
		std::cout << "Maximum point lights reached!, cannot add any further!";
		return -1;
	}

}

int RE::LightUBOManager::addSpotLightToMemory(std::shared_ptr<SpotLight> spotLightPtr)
{
	if (spotLightsArr.size() < MAXLIGHTS) {

		if (std::find_if(spotLightsArr.begin(), spotLightsArr.end(),
			[&spotLightPtr](const std::weak_ptr<SpotLight>& x) {return x.lock() == spotLightPtr; }) == spotLightsArr.end())
		{
			int index = spotLightsArr.size();
			int offset = (index) * sizeof(SpotLightStruct) + _SpotLightOffset;
			spotLightPtr->UBO_index = index;
			spotLightsArr.emplace_back(std::weak_ptr(spotLightPtr));

			SpotLightStruct info;

			float innerCutoff = glm::cos(spotLightPtr->innerangle);
			float outerCutoff = glm::cos(spotLightPtr->outerangle);
			info.position = glm::vec4(spotLightPtr->transform.globalPosition, 1.f);
			info.direction = glm::vec4(spotLightPtr->direction, 1.f);
			info.ambient = glm::vec4(spotLightPtr->ambient, 1.f);
			info.diffuse = glm::vec4(spotLightPtr->diffuse, 1.f);
			info.specular = glm::vec4(spotLightPtr->specular, 1.f);
			info.innerCutoff = innerCutoff;
			info.outerCutoff = outerCutoff;
			info.constant = spotLightPtr->constant;
			info.linear = spotLightPtr->linear;
			info.quadratic = spotLightPtr->quadratic;
			int size = spotLightsArr.size();
			GLCall(glNamedBufferSubData(LightsUBO, offset, sizeof(SpotLightStruct), &info));
			GLCall(glNamedBufferSubData(LightsUBO, _numSpotLightsOffset, 4, &size));

			return index;
		}
		else {
			std::cout << "Spot Light data already present!";
			return -1;
		}
		
	}
	else {
		std::cout << "Maximum spot lights reached!, cannot add any further!";
		return -1;
	}

}

void RE::LightUBOManager::updateUBO(std::weak_ptr<PointLight> pointLightPtr)
{
	
	if (std::find_if(pointLightsArr.begin(), pointLightsArr.end(),
		[&pointLightPtr](const std::weak_ptr<PointLight>& x) {return x.lock() == pointLightPtr.lock(); }) != pointLightsArr.end())
	{

		int offset = (pointLightPtr.lock()->UBO_index) * sizeof(PointLightStruct);
		PointLightStruct info;
		info.position = glm::vec4(pointLightPtr.lock()->transform.globalPosition, 1.f);
		info.ambient = glm::vec4(pointLightPtr.lock()->ambient, 1.f);
		info.diffuse = glm::vec4(pointLightPtr.lock()->diffuse, 1.f);
		info.specular = glm::vec4(pointLightPtr.lock()->specular, 1.f);
		info.constant = pointLightPtr.lock()->constant;
		info.linear = pointLightPtr.lock()->linear;
		info.quadratic = pointLightPtr.lock()->quadratic;

		GLCall(glNamedBufferSubData(LightsUBO, offset, sizeof(PointLightStruct), &info));
		//GLCall(glNamedBufferSubData(LightsUBO, _numPointLightsOffset, 4, (const void*)pointLightsArr.size()));
	}
	

}

void RE::LightUBOManager::updateUBO(std::weak_ptr<SpotLight> spotLightPtr)
{
	if (std::find_if(spotLightsArr.begin(), spotLightsArr.end(), 
		[&spotLightPtr](const std::weak_ptr<SpotLight>& x) {return x.lock() == spotLightPtr.lock(); }) != spotLightsArr.end())
	{
		int offset = (spotLightPtr.lock()->UBO_index) * sizeof(SpotLightStruct) + _SpotLightOffset;

		SpotLightStruct info;

		float innerCutoff = glm::cos(spotLightPtr.lock()->innerangle);
		float outerCutoff = glm::cos(spotLightPtr.lock()->outerangle);
		info.position = glm::vec4(spotLightPtr.lock()->transform.globalPosition, 1.f);
		info.direction = glm::vec4(spotLightPtr.lock()->direction, 1.f);
		info.ambient = glm::vec4(spotLightPtr.lock()->ambient, 1.f);
		info.diffuse = glm::vec4(spotLightPtr.lock()->diffuse, 1.f);
		info.specular = glm::vec4(spotLightPtr.lock()->specular, 1.f);
		info.innerCutoff = innerCutoff;
		info.outerCutoff = outerCutoff;
		info.constant = spotLightPtr.lock()->constant;
		info.linear = spotLightPtr.lock()->linear;
		info.quadratic = spotLightPtr.lock()->quadratic;

		GLCall(glNamedBufferSubData(LightsUBO, offset, sizeof(SpotLightStruct), &info));
		//GLCall(glNamedBufferSubData(LightsUBO, _numSpotLightsOffset, 4, (const void*)spotLightsArr.size()));
	}
	
}

void RE::LightUBOManager::deleteLight(std::weak_ptr<PointLight> pointLightPtr)
{
	auto it = std::find_if(pointLightsArr.begin(), pointLightsArr.end(),
		[&pointLightPtr](const std::weak_ptr<PointLight>& x) {return x.lock() == pointLightPtr.lock(); });
	size_t index = std::distance(pointLightsArr.begin(), it);
	if ( it != pointLightsArr.end()) 
	{
		pointLightsArr.erase(it);
		resetPointLightMemory(index);
	}
	int size = pointLightsArr.size();
	GLCall(glNamedBufferSubData(LightsUBO, _numPointLightsOffset, 4, &size));
}
void RE::LightUBOManager::deleteLight(std::weak_ptr<SpotLight> spotLightPtr)
{
	auto it = std::find_if(spotLightsArr.begin(), spotLightsArr.end(), 
		[&spotLightPtr](const std::weak_ptr<SpotLight>& x) {return x.lock() == spotLightPtr.lock(); });
	size_t index = std::distance(spotLightsArr.begin(), it);
	if (it != spotLightsArr.end())
	{
		spotLightsArr.erase(it);
		resetSpotLightMemory(index);
	}
	int size = spotLightsArr.size();
	GLCall(glNamedBufferSubData(LightsUBO, _numSpotLightsOffset, 4, &size));

}

void RE::LightUBOManager::resetPointLightMemory(size_t index)
{
	
	for (auto i = index; i < pointLightsArr.size(); i++) {

		int offset = (i) * sizeof(PointLightStruct);
		pointLightsArr[i].lock()->UBO_index = i;
		PointLightStruct info;
		info.position = glm::vec4(pointLightsArr[i].lock()->transform.globalPosition, 1.f);
		info.ambient = glm::vec4(pointLightsArr[i].lock()->ambient, 1.f);
		info.diffuse = glm::vec4(pointLightsArr[i].lock()->diffuse, 1.f);
		info.specular = glm::vec4(pointLightsArr[i].lock()->specular, 1.f);
		info.constant = pointLightsArr[i].lock()->constant;
		info.linear = pointLightsArr[i].lock()->linear;
		info.quadratic = pointLightsArr[i].lock()->quadratic;

		GLCall(glNamedBufferSubData(LightsUBO, offset, sizeof(PointLightStruct), &info));
	}
}

void RE::LightUBOManager::resetSpotLightMemory(size_t index)
{
	for (auto i = index; i < spotLightsArr.size(); i++) {

		int offset = (i) * sizeof(SpotLightStruct) + _SpotLightOffset;
		spotLightsArr[i].lock()->UBO_index = i;
		SpotLightStruct info;

		float innerCutoff = glm::cos(spotLightsArr[i].lock()->innerangle);
		float outerCutoff = glm::cos(spotLightsArr[i].lock()->outerangle);
		info.position = glm::vec4(spotLightsArr[i].lock()->transform.globalPosition, 1.f);
		info.direction = glm::vec4(spotLightsArr[i].lock()->direction, 1.f);
		info.ambient = glm::vec4(spotLightsArr[i].lock()->ambient, 1.f);
		info.diffuse = glm::vec4(spotLightsArr[i].lock()->diffuse, 1.f);
		info.specular = glm::vec4(spotLightsArr[i].lock()->specular, 1.f);
		info.innerCutoff = innerCutoff;
		info.outerCutoff = outerCutoff;
		info.constant = spotLightsArr[i].lock()->constant;
		info.linear = spotLightsArr[i].lock()->linear;
		info.quadratic = spotLightsArr[i].lock()->quadratic;

		GLCall(glNamedBufferSubData(LightsUBO, offset, sizeof(SpotLightStruct), &info));
	}
}
