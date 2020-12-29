#pragma once

#include "Graphics2D.h"
#include "Car.h"

#include <vector>

class Track {
private:
	std::vector<std::vector<std::vector<float>>> coords;

public:
	Track();
	void render(Graphics2D* engine);
	bool isColliding(Car* car);
	~Track();
};