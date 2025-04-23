#include "Bridge.h"

#include <raylib.h>

using namespace _BridgePattern;

void RaylibImpl::InitTheWindow(int _width, int _height)
{
    InitWindow(_width, _height, "Window Created By Raylib");
}

void* RaylibImpl::LoadTheImage(const std::string& _path)
{
    Texture2D* _texture = new Texture2D(LoadTexture(_path.c_str()));

    return _texture;
}

void RaylibImpl::ShowTheImage(void* _image, int _x, int _y)
{
    BeginDrawing();
    DrawTexture(*(Texture2D*)_image, _x, _y, { 255, 255, 255, 255 });
    EndDrawing();
}

bool RaylibImpl::NeedQuit()
{
    return WindowShouldClose();
}

void RaylibImpl::QuitTheWindow()
{
    CloseWindow();
}