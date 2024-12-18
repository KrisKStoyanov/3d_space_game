#include "SphereCollider.h"
#include <iostream>

#define PI 3.14159265358979324

SphereCollider::SphereCollider(glm::vec3 * centre, int points, float circleWidth, float circleHeight, float circleLength)
{
	this->colliderCentre = centre;
	this->points = points;
	this->radius = radius;
	this->width = circleWidth;
	this->height = circleHeight;
	this->length = circleLength;
	radius = sqrt(abs((this->colliderCentre->x - this->maxX()) * (this->colliderCentre->x - this->maxX()) + 
		(this->colliderCentre->y - this->maxY()) * (this->colliderCentre->y - this->maxY())));
}

SphereCollider::~SphereCollider()
{

}

float SphereCollider::minX() {
	return this->colliderCentre->x - this->width / 2;
}

float SphereCollider::maxX()
{
	return this->colliderCentre->x + this->width / 2;
}

float SphereCollider::minY()
{
	return this->colliderCentre->y - this->height / 2;
}

float SphereCollider::maxY()
{
	return this->colliderCentre->y + this->height / 2;
}

float SphereCollider::minZ()
{
	return this->colliderCentre->z - this->length / 2;
}

float SphereCollider::maxZ()
{
	return this->colliderCentre->z + this->length / 2;
}

bool SphereCollider::collidesWith(Collider * other)
{
	if (other == NULL) {
		return false;
	}
	// distance = a.centre - b.centre		if a.radius + b.radius > distance : collision
	// axis aligned: 

	glm::vec3 distVec = *other->colliderCentre - *this->colliderCentre;
	float distance = sqrtf((distVec.x * distVec.x) + (distVec.y * distVec.y) + (distVec.z * distVec.z));

	if (other->radius > 0.0) {
		return (other->radius + this->radius >= distance);
	}
	else {
		bool overlapX = other->minX() <= this->maxX() && other->maxX() >= this->minX();
		bool overlapY = other->minY() <= this->maxY() && other->maxY() >= this->minY();
		bool overlapZ = other->minZ() <= this->maxZ() && other->maxZ() >= this->minZ();
		return overlapX && overlapY && overlapZ;
	}

	//bool overlapRadius = this->radius + other->radius >= (other->colliderCentre->x - this->colliderCentre->x )
	//	* (other->colliderCentre->x - this->colliderCentre->x) + (other->colliderCentre->y - this->colliderCentre->y)
	//		* (other->colliderCentre->y - this->colliderCentre->y) + (other->colliderCentre->z - this->colliderCentre->z)
	//			* (other->colliderCentre->z - this->colliderCentre->z);

	//return overlapRadius;

	//bool overlapX = other->minX() <= this->maxX() && other->maxX() >= this->minX();
	//bool overlapY = other->minY() <= this->maxY() && other->maxY() >= this->minY();
	//bool overlapZ = other->minZ() <= this->maxZ() && other->maxZ() >= this->minZ();
	//
	//if (overlapX && overlapY && overlapZ) {
	//	if (this->radius + other->radius < this->colliderCentre->x - other->colliderCentre->x ||
	//		this->radius + other->radius < this->colliderCentre->y - other->colliderCentre->y ||
	//		this->radius + other->radius < this->colliderCentre->z - other->colliderCentre->z) {
	//		return true;
	//	}
	//}
	//	if (this->maxX() > other->maxX() && this->maxY() > other->maxY() &&	this->maxZ() < other->maxZ());

	//	float piercePoint[] = { this->maxX() - other->minX(), this->maxY() - other->minY(), this->maxZ() - other->minZ() };

	//	if (piercePoint[0] > radius && piercePoint[1] > radius && piercePoint[2] > radius) {
	//		overlapRadius = true;
	//	}
	//	else {
	//		overlapRadius = false;
	//	}
	//}
}

void SphereCollider::Draw()
{
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(colliderCentre->x, colliderCentre->y, colliderCentre->z);
	glutWireSphere(this->radius, points, points);
	glPopMatrix();
}

