#include "Object.h"


RE::Object::Object()
	: transform(), m_modelMatrix(1.f)
{
}


RE::ObjectTransform RE::Object::getTransform()
{
	return this->transform;
}

glm::mat4 RE::Object::getModelMT() const
{
	return this->m_modelMatrix;
}

void RE::Object::setTransform(const ObjectTransform& otherTransform)
{
	this->transform = otherTransform;
	
	_updateModelMatrix();
}

void RE::Object::setPositionLocal(float x, float y, float z)
{
	transform.position = { x,y,z };
	_updateModelMatrix();
}

void RE::Object::setPositionGlobal(float x, float y, float z)
{
	transform.globalPosition = { x,y,z };
	_updateModelMatrix();
}

void RE::Object::setRotationLocal(float pitch, float yaw, float roll)
{
	this->transform.rotation = { pitch, yaw, roll };
	if (transform.rotation.x >= 360.f)
		transform.rotation.x = (int)transform.rotation.x % 360;
	if (transform.rotation.y >= 360.f)
		transform.rotation.y = (int)transform.rotation.y % 360;
	if (transform.rotation.z >= 360.f)
		transform.rotation.z = (int)transform.rotation.z % 360;

	_updateModelMatrix();

}

void RE::Object::setRotationGlobal(float pitch, float yaw, float roll)
{
	this->transform.globalRotation = { pitch, yaw, roll };
	if (transform.globalRotation.x >= 360.f)
		transform.globalRotation.x = (int)transform.globalRotation.x % 360;
	if (transform.globalRotation.y >= 360.f)
		transform.globalRotation.y = (int)transform.globalRotation.y % 360;
	if (transform.globalRotation.z >= 360.f)
		transform.globalRotation.z = (int)transform.globalRotation.z % 360;
	_updateModelMatrix();
}

void RE::Object::setScale(float x, float y, float z)
{
	this->transform.scale = { x, y, z };

	_updateModelMatrix();
}

void RE::Object::translateLocal(float x, float y, float z)
{
	transform.position += glm::vec3(x, y, z);
	_updateModelMatrix();
}

void RE::Object::translateLocal(glm::vec3 translateBy)
{
	transform.position += translateBy;
	_updateModelMatrix();
}
void RE::Object::translateGlobal(float x, float y, float z)
{
	transform.globalPosition += glm::vec3(x, y, z);
	_updateModelMatrix();
}

void RE::Object::translateGlobal(glm::vec3 translateBy)
{
	transform.globalPosition += translateBy;
	_updateModelMatrix();
}

void RE::Object::rotateLocal(float pitch, float yaw, float roll)
{
	transform.rotation += glm::vec3(pitch, yaw, roll);
	if (transform.rotation.x >= 360.f)
		transform.rotation.x = (int)transform.rotation.x % 360;
	if (transform.rotation.y >= 360.f)
		transform.rotation.y = (int)transform.rotation.y % 360;
	if (transform.rotation.z >= 360.f)
		transform.rotation.z = (int)transform.rotation.z % 360;
		
	_updateModelMatrix();
}

void RE::Object::rotateLocal(glm::vec3 rotateBy)
{
	transform.rotation += rotateBy;
	if (transform.rotation.x >= 360.f)
		transform.rotation.x = (int)transform.rotation.x % 360;
	if (transform.rotation.y >= 360.f)
		transform.rotation.y = (int)transform.rotation.y % 360;
	if (transform.rotation.z >= 360.f)
		transform.rotation.z = (int)transform.rotation.z % 360;
	_updateModelMatrix();
}

void RE::Object::rotateGlobal(float pitch, float yaw, float roll)
{
	transform.globalRotation += glm::vec3(pitch, yaw, roll);
	if (transform.globalRotation.x >= 360.f)
		transform.globalRotation.x = (int)transform.globalRotation.x % 360;
	if (transform.globalRotation.y >= 360.f)
		transform.globalRotation.y = (int)transform.globalRotation.y % 360;
	if (transform.globalRotation.z >= 360.f)
		transform.globalRotation.z = (int)transform.globalRotation.z % 360;
	_updateModelMatrix();
}

void RE::Object::rotateGlobal(glm::vec3 rotateBy)
{
	transform.globalRotation += rotateBy;
	if (transform.globalRotation.x >= 360.f)
		transform.globalRotation.x = (int)transform.globalRotation.x % 360;
	if (transform.globalRotation.y >= 360.f)
		transform.globalRotation.y = (int)transform.globalRotation.y % 360;
	if (transform.globalRotation.z >= 360.f)
		transform.globalRotation.z = (int)transform.globalRotation.z % 360;
	_updateModelMatrix();
}

void RE::Object::_updateModelMatrix()
{
	m_modelMatrix = glm::mat4(1.f);
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(transform.globalRotation.x), glm::vec3(1.f, 0.f, 0.f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(transform.globalRotation.y), glm::vec3(0.f, 1.f, 0.f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(transform.globalRotation.z), glm::vec3(0.f, 0.f, 1.f));
	transform.globalPosition = m_modelMatrix * glm::vec4(transform.globalPosition, 1.f);
	m_modelMatrix = glm::translate(m_modelMatrix, transform.globalPosition);
	m_modelMatrix = glm::translate(m_modelMatrix, transform.position);
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(transform.rotation.x), glm::vec3(1.f, 0.f, 0.f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(transform.rotation.y), glm::vec3(0.f, 1.f, 0.f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(transform.rotation.z), glm::vec3(0.f, 0.f, 1.f));
	m_modelMatrix = glm::scale(m_modelMatrix, transform.scale);

	
}

