#ifndef _BRIDGE_H_
#define _BRIDGE_H_

#include <string>

#include "Example.h"

namespace _BridgePattern
{
    class GraphicsImpl 
    {
    public:
        //注意InitWinodw会与raylib.h中的同名函数冲突
        virtual void InitTheWindow(int, int) = 0;
		//注意LoadImage也会冲突
        virtual void* LoadTheImage(const std::string&) = 0;
        virtual void ShowTheImage(void*, int, int) = 0;
        virtual bool NeedQuit() = 0;
        virtual void QuitTheWindow() = 0;
    };

    class RaylibImpl : public GraphicsImpl 
    {
    public:
        void InitTheWindow(int, int) override;
        void* LoadTheImage(const std::string&) override;
        void ShowTheImage(void*, int, int) override;
        bool NeedQuit() override;
        void QuitTheWindow() override;

    };

    class EasyXImpl : public GraphicsImpl
    {
    public:
        void InitTheWindow(int, int) override;
        void* LoadTheImage(const std::string&) override;
        void ShowTheImage(void*, int, int) override;
        bool NeedQuit() override;
        void QuitTheWindow() override;
    };

    class Window 
    {
    private:
        void* image = nullptr;
        GraphicsImpl* impl = nullptr;

    public:
        Window(GraphicsImpl* _impl) : impl(_impl) {}
        ~Window() = default;

        void create(int _w, int _h) 
        {
            impl->InitTheWindow(_w, _h);
        }

        void LoadTheImage(const std::string& _path)
        {
            image = impl->LoadTheImage(_path);
        }

        void run()
        {
            while (!impl->NeedQuit())
            {
                impl->ShowTheImage(image, 0, 0);
                SDL_Delay(10);
            }

            impl->QuitTheWindow();
        }
    };
}

class BridgePattern : public Example
{
public:
	BridgePattern() = default;
	~BridgePattern() = default;

    void OnUpdate(float) override;
};

#endif
