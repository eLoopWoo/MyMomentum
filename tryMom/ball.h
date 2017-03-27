#pragma once
#include <stdlib.h>
#include <SFML\Graphics.hpp>
class ball
{
private:
	sf::CircleShape c;
	sf::RenderWindow* window;
	int mass = 10;
	float x = 250;
	float y = 200;
	float velocity_x = 1;
	float velocity_y = 3;
public:
	int get_mass();
	void set_mass(int m);
	void set_velocity_x(float z);
	void set_velocity_y(float z);
	void collision();
	float get_velocity_x();
	float get_velocity_y(); 
	ball();
	void settings(float x, float y);
	ball(float x, float y,sf::RenderWindow* window);
	void move(float z, float w);
	void set_x(float x);
	void set_y(float y);
	float get_x();
	float get_y();
	void control();
	void play();
	void randomStart();
	void setPos(float x,float y);
	void print();
	sf::CircleShape& ball::getCircle();
};
