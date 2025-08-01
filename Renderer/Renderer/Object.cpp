#include "Object.h"


RE::Object::Object()
	: transform()
{
}

RE::ObjectTransform RE::Object::getTransform() const
{
	return this->transform;
}

void RE::Object::setTransform(const ObjectTransform& otherTransform)
{
	this->transform = otherTransform;
}

void RE::Object::setPosition(float x, float y, float z)
{
	this->transform.position = { x,y,z };
}

void RE::Object::setRotation(float pitch, float yaw, float roll)
{
	this->transform.rotation = { pitch, yaw, roll };
}

void RE::Object::setScale(float x, float y, float z)
{
	this->transform.scale = { x,y,z };
}

void RE::Object::translate(float x, float y, float z)
{
	transform.position += glm::vec3(x, y, z);
}

void RE::Object::translate(glm::vec3 translateBy)
{
	transform.position += translateBy;
}

void RE::Object::rotate(float pitch, float yaw, float roll)
{
	transform.rotation += glm::vec3(pitch, yaw, roll);
}

void RE::Object::rotate(glm::vec3 rotateBy)
{
	transform.rotation += rotateBy;
}

