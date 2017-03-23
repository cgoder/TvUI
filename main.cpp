#include "AppDelegate.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int lorewalker_launcher()
{
    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
