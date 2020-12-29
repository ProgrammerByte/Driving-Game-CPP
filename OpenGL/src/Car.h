#pragma once

#include "Graphics2D.h"

#include <vector>

class Car {
private:
	float vel;
	float acc;
	std::vector<std::vector<float>> coords;
	std::vector<float> center;
	std::vector<std::vector<float>> boundingBox;
	std::vector<float> dir;

	void findBoundingBox();

public:
	Car();
	void render(Graphics2D* engine);
	void turn(int dir);
	//void findBoundingBoxkkk();
	void translate(float x, float y);
	void rotate(double angle);
	void update();
	std::vector<std::vector<float>> getCoords();
	std::vector<std::vector<float>> getBoundingBox();
	void setAcc(float val);
	~Car();
};