#pragma once
#include "Player.h"
class Bullet :  public Body

{
public:
	float livingTime = 0;
	bool shouldDestroy = false;
	void update(bool tp) override;

};

