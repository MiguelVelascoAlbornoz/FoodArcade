#pragma once
#include "Body.h"
class Player :
    public Body
{

public:
    void draw(VAO* squrae) override;
    float coolDownTimer = 0.0f;
    bool onCoolDown = false;
    int lifes = 5;

};

