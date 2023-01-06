#include "al_button.hpp"

Button::Button(){
    screenPos = Vec(0,0,0);
    text = "";
    setBgColor(0x80,0x80,0x80);
    setTextColor(0x40,0x40,0x40);
}

Button::Button(Vec pos){
    
}

Button::Button(Vec pos, std::string txt){
    
}

void Button::setScreenPos(Vec pos){
    screenPos = pos;
}

Vec Button::getScreenPos(){
    return screenPos;
}

bool Button::clicked(Vec mouse_axis){
    if (
        mouse_axis.x > screenPos.x - (w/2.0) &&
        mouse_axis.x < screenPos.x + (w/2.0) &&
        mouse_axis.y > screenPos.y - (h/2.0) &&
        mouse_axis.y < screenPos.y + (h/2.0)
    )
        return true;
    return false;

}

void Button::setText(std::string text){
    this->text = text;
}

void Button::setBgColor(int r,int g, int b){
    bg_color = al_map_rgb(r, g, b);
}

void Button::setTextColor(int r,int g, int b){
    txt_color = al_map_rgb(r, g, b);
}

void Button::draw(){
    
}

