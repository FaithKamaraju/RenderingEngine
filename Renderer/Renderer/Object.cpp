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

void RE::Object::translate(float x, float y, float z)
{
	transform.translation += glm::vec3(x, y, z);
}

void RE::Object::translate(glm::vec3 translateBy)
{
	transform.translation += translateBy;
}

void RE::Object::rotate(float pitch, float yaw, float roll)
{
	transform.rotation += glm::vec3(pitch, yaw, roll);
}

void RE::Object::rotate(glm::vec3 rotateBy)
{
	transform.rotation += rotateBy;
}

void RE::Object::scale(float x, float y, float z)
{
	transform.scale += glm::vec3(x, y, z);
}

void RE::Object::scale(glm::vec3 scaleBy)
{
	transform.scale += scaleBy;
}
