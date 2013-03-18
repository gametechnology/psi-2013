#include "net.h"
#include <irrlicht.h>
#include <process.h>
#include <sstream>
#include <SFML/Network.hpp>
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int MainSceneStart();