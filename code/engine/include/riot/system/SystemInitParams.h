#pragma once

struct SystemInitParams
{
    void*   hWnd;
    char    systemCmdLine[2048];


    SystemInitParams()
        :   hWnd(nullptr),
            systemCmdLine{}
    {}
};