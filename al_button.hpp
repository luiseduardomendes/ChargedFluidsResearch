#pragma once

#include "allegro.hpp"
#include "vector.hpp"
#include <string>

class Button{

protected:
    Vec screenPos;
    std::string text;

    ALLEGRO_COLOR bg_color, txt_color;
    
    double w, h;

public:
    Button();
    Button(Vec pos);
    Button(Vec pos, std::string txt);
    bool clicked(Vec mouse_axis);
    void setScreenPos(Vec);
    Vec getScreenPos();
    void setText(std::string text);
    void setTextColor(int r,int g, int b);
    void setBgColor(int r,int g, int b);

    void draw();

};  