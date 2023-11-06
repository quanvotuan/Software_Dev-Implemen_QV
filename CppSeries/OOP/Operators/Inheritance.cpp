//
// Created by tuanq on 11/4/2023.
//

#include <iostream>

class Entity
{
public:
    float X, Y;
    void Move(float xa, float ya)
    {
        X += xa;
        Y += ya;
    }
};

class Player : public Entity
{
public:
    const char* Name;
    void PrintName()
    {
        std::cout << Name << std::endl;
    }
};
