#include "IOSystem.h"

IOSystem::IOSystem()
{

}

IOSystem::~IOSystem()
{

}

char IOSystem::onCreate()
{
#if defined(WIN32)
    return _window.init();
#endif
    return 1;
}

char IOSystem::onUpdate()
{
#if defined(WIN32)
    return _window.broadcast();
#endif
    return 1;
}
