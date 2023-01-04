#include "Particle.h"

Particle::Particle(int EmitterMax, float posX, float posY, int times, int radius, float scale, int speed)
{
	this->EmitterMax_ = EmitterMax;
	this->pcl_pos_.x = posX;
	this->pcl_pos_.y = posY;
	this->Scale_.x = scale;
	this->Scale_.y = scale;
	this->speed_ = speed;
	this->time_ = times;
	this->blend = BlendMode::kBlendModeNone;
	srand(currTime);

	
	for (int i = 0; i < EmitterMax; i++)
	{
		pcl_object_[i].time = rand() % times/2 + times;
		pcl_object_[i].Pos.x = posX;
		pcl_object_[i].Pos.y = posY;
		pcl_object_[i].radius = radius;
		pcl_object_[i].theta = (rand() % 720 - 360) / 100.0f;
		pcl_object_[i].speed = speed;
		pcl_object_[i].Scale.x = scale;
		pcl_object_[i].Scale.y = scale;
		pcl_object_[i].active = false;
	}
	active_ = rand() % EmitterMax;
	pcl_object_[active_].active = true;
}

Particle::~Particle()
{
}

void Particle::Update(char* keys, char* preKeys)
{
	active_ = rand() % EmitterMax_;
	pcl_object_[active_].active = true;
	//Mouse
	Novice::GetMousePosition(&mouseX, &mouseY);
	if (Novice::IsPressMouse(0))
	{
		pcl_pos_.x = mouseX;
		pcl_pos_.y = mouseY;
	}
	blend = blend = BlendMode::kBlendModeAdd;
	Novice::ScreenPrintf(10, 10, "Mode : 1.Screen2.Multiply3.Add4.Substract5.CountOfBlend6.Normal7.none");
	//Input
	if (keys[DIK_1])
	{
		blend = BlendMode::kBlendModeScreen;
		Novice::ScreenPrintf(10, 40, "Mode : Screen");
	}
	else if (keys[DIK_2])
	{
		blend = BlendMode::kBlendModeMultily;
		Novice::ScreenPrintf(10, 40, "Mode : Multiply");
	}
	else if (keys[DIK_3] )
	{
		blend = BlendMode::kBlendModeAdd;
		Novice::ScreenPrintf(10, 40, "Mode : Add");
	}
	else if (keys[DIK_4] )
	{
		blend = BlendMode::kBlendModeSubtract;
		Novice::ScreenPrintf(10, 40, "Mode : Substract");
	}
	else if (keys[DIK_5] )
	{
		blend = BlendMode::kCountOfBlendMode;
		Novice::ScreenPrintf(10, 40, "Mode : CountOfBlendMode");
	}
	else if (keys[DIK_6] )
	{
		blend = BlendMode::kBlendModeNormal;
		Novice::ScreenPrintf(10, 40, "Mode : Normal");
	}
	else if (keys[DIK_0] )
	{
		blend = BlendMode::kBlendModeNone;
		Novice::ScreenPrintf(10, 40, "Mode : None");
	}

	for (size_t i = 0; i < EmitterMax_; i++)
	{
		if (pcl_object_[i].active)
		{
			pcl_object_[i].Scale.x += 0.001f;
			pcl_object_[i].Scale.y += 0.001f;
			pcl_object_[i].Pos.x += sinf(pcl_object_[i].theta) * pcl_object_[i].speed;
			pcl_object_[i].Pos.y += cosf(pcl_object_[i].theta) * pcl_object_[i].speed;
			pcl_object_[i].time--;
			if (pcl_object_[i].time <= 0)
			{
				pcl_object_[i].Pos = pcl_pos_;
				pcl_object_[i].theta = (rand() % 720 - 360)/ 100.0f;
				pcl_object_[i].speed = speed_;
				pcl_object_[i].time = rand() % time_/2 + time_;
				pcl_object_[i].Scale.x = Scale_.x;
				pcl_object_[i].Scale.y = Scale_.y;
			}
		}
	}
}

void Particle::Draw(int graph)
{
	
	Novice::SetBlendMode(blend);
	for (int i = 0; i < EmitterMax_; i++)
	{
		if (pcl_object_[i].active)
		{
			//Novice::DrawEllipse(pcl_object_[i].Pos.x, pcl_object_[i].Pos.y, pcl_object_[i].radius, pcl_object_[i].radius, 0, WHITE, kFillModeSolid);
			Novice::DrawSprite(pcl_object_[i].Pos.x - pcl_object_[i].radius / 2, pcl_object_[i].Pos.y - pcl_object_[i].radius / 2, graph, pcl_object_[i].Scale.x, pcl_object_[i].Scale.x, 0, WHITE);
		}
	}
}
