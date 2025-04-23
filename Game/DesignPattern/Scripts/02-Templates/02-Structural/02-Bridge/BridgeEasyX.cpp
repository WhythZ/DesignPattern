#include "Bridge.h"

#include <codecvt>
#include <graphics.h>

using namespace _BridgePattern;

void EasyXImpl::InitTheWindow(int _width, int _height)
{
    initgraph(_width, _height, EW_NOCLOSE);
    SetWindowText(GetHWnd(), _T("Window Created By EasyX (Press Esc Quit)"));
}

void* EasyXImpl::LoadTheImage(const std::string& _path)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;

    IMAGE* _image = new IMAGE();
    loadimage(_image, convert.from_bytes(_path).c_str());

    return _image;
}

void EasyXImpl::ShowTheImage(void* _image, int _x, int _y)
{
    IMAGE* _img = static_cast<IMAGE*>(_image);

    putimage(_x, _y, _img);
}

bool EasyXImpl::NeedQuit()
{
    ExMessage _message;
    while (peekmessage(&_message))
    {
        if (_message.message == WM_KEYDOWN && _message.vkcode == VK_ESCAPE)
            return true;
    }

    return false;
}

void EasyXImpl::QuitTheWindow()
{
    closegraph();
}