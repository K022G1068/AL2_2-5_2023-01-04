#pragma once
#include"Novice.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>

struct f_Vector2
{
	float x, y;
};

struct pcl_Object
{
	f_Vector2 Pos;
	f_Vector2 Speed;
	f_Vector2 Scale;
	float theta;
	int time;
	int radius;
	float speed;
	bool active;

};

class Particle
{
private:
	int active_;
	int mouseX;
	int mouseY;
	int speed_;
	int time_;
	BlendMode blend;
	f_Vector2 Scale_;
	int EmitterMax_;
	f_Vector2 pcl_pos_;
	pcl_Object pcl_object_[100];

public:
	unsigned currTime = time(nullptr);
	Particle(int EmitterMax, float posX, float posY, int times, int radius, float scale, int speed);
	~Particle();
	void Update(char* keys, char* preKeys);
	void Draw(int graph);
};

