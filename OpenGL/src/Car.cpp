#include "Car.h"
#include "maths.h"
#include "Graphics2D.h"

#include <vector>

//#include <iostream>

using namespace std;

Car::Car() {
	this->vel = 0;
	this->acc = 0;
	this->coords = {{0, 0}, {0.125f / 2, 0}, {0.125f / 2, 0.0625f / 2}, {0, 0.0625f / 2}};
	this->boundingBox = {{0, 0}, {0.125f / 2, 0.0625f / 2}};
	this->center = {0.0625f / 2, 0.03125f / 2};
	this->dir = {1, 0};
	this->translate(0.3, 0.12);
	this->rotate(PI);
}

void Car::render(Graphics2D* engine) {
	engine->triangle(coords[0][0], coords[0][1], coords[1][0], coords[1][1], coords[2][0], coords[2][1]);
	engine->triangle(coords[2][0], coords[2][1], coords[3][0], coords[3][1], coords[0][0], coords[0][1]);
}

void Car::findBoundingBox() {
	float minX = coords[0][0], maxX = coords[0][0], minY = coords[0][1], maxY = coords[0][1];
	for (int i = 1; i < 4; i++) {
		if (coords[i][0] < minX) {
			minX = coords[i][0];
		}
		else if (coords[i][0] > maxX) {
			maxX = coords[i][0];
		}
		if (coords[i][1] < minY) {
			minY = coords[i][1];
		}
		else if (coords[i][1] > maxY) {
			maxY = coords[i][1];
		}
	}
	boundingBox = {{minX, minY}, {maxX, maxY}};
}

void Car::translate(float x, float y) {
	for (int i = 0; i < 4; i++) {
		coords[i][0] += x;
		coords[i][1] += y;
	}
	center[0] += x;
	center[1] += y;
	for (int i = 0; i < 2; i++) {
		boundingBox[i][0] += x;
		boundingBox[i][1] += y;
	}
}

void Car::update() {
	float drag = (float)(4 * vel * vel);
	if (vel < 0) {
		acc += drag;
	}
	else {
		acc -= drag;
	}
	vel += acc; //update velocity
	vel *= 0.99; //apply friction
	acc = 0; //reset acceleration

	this->translate(vel * dir[0], vel * dir[1]);
}

void Car::rotate(double angle) {
	double sinAngle = sin(angle, 50);
	double cosAngle = cos(angle , 50);
	float temp;
	for (int i = 0; i < 4; i++) {
		coords[i][0] -= center[0];
		coords[i][1] -= center[1];
		temp = (cosAngle * coords[i][0]) - (sinAngle * coords[i][1]);
		coords[i][1] = (sinAngle * coords[i][0]) + (cosAngle * coords[i][1]);
		coords[i][0] = temp;
		coords[i][0] += center[0];
		coords[i][1] += center[1];
	}

	temp = (cosAngle * this->dir[0]) - (sinAngle * this->dir[1]);
	this->dir[1] = (sinAngle * this->dir[0]) + (cosAngle * this->dir[1]);
	this->dir[0] = temp;

	this->findBoundingBox();
}

void Car::turn(int dir) {
	//float angle = 0.01 * vel; //some constant x velocity - reduce value to increase turning radius
	rotate(6 * dir * vel);
}

vector<vector<float>> Car::getCoords() {
	return this->coords;
}

vector<vector<float>> Car::getBoundingBox() {
	return this->boundingBox;
}

void Car::setAcc(float val) {
	this->acc = val;
}

Car::~Car() {};