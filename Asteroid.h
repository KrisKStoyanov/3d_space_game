#include "GameObject.h"

class Asteroid : public GameObject
{
private:
	int base;
public:
	Asteroid(glm::vec3 pos, Color _asteroidColor, float size); 
	~Asteroid();
	void drawScene();
	void Asteroid::start();
	void Asteroid::update(int deltaTime);
	unsigned int setupDrawing(unsigned int baseList);
	void collides(GameObject * other);
	float mass = 1.5f;
	float speedX = 0.0f;
	float speedY = 0.0f;
	float speedZ = 0.0f;
};


