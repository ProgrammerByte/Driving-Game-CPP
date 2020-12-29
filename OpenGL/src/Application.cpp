//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "Graphics2D.h"
#include "Car.h"
#include "Track.h"

#include <vector>
#include <iostream>

using namespace std;

Graphics2D engine = Graphics2D(1920, 1080, "Driving", true);
Track track = Track();
Car car = Car();

void input() {
	if (engine.keyPress(GLFW_KEY_W)) {
		car.setAcc(0.0001f);
	}
	if (engine.keyPress(GLFW_KEY_S)) {
		car.setAcc(-0.0001f);
	}
	if (engine.keyPress(GLFW_KEY_A)) {
		car.turn(1);
	}
	if (engine.keyPress(GLFW_KEY_D)) {
		car.turn(-1);
	}
}

//for now the coordinates system goes from (-aspectRatio, -1) to (aspectRatio, 1)
int main() {
	while (engine.shouldClose() == false) {
		input();
		car.update();
		car.render(&engine);
		track.render(&engine);
		engine.clear();

		if (track.isColliding(&car)) {
			engine.setFillColour(1, 0, 0, 1);
		}
		else {
			engine.setFillColour(1, 1, 1, 1);
		}

		if (engine.keyPress(GLFW_KEY_ESCAPE)) {
			engine.closeWindow();
		}
	}
}