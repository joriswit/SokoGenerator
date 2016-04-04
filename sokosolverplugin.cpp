#include <QApplication>
#include <QMessageBox>

#include "solvercpp/solver.h"
#include "solvercpp/level.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma pack(push, 1)
#include "sokobanpluginsdll.h"
#pragma pack(pop)

extern "C" {

int __declspec(dllexport) __stdcall SolveEx(unsigned int width,
                                                 unsigned int height,
                                                 char* board,
                                                 char* pcSolution,
                                                 unsigned int uiSolutionBufferSize,
                                                 struct PluginStatus *psStatus,
                                                 PLUGINCALLBACK *pc) {


    level newLevel;

    for(unsigned int y = 0; y < height; y++){
        for(unsigned int x = 0; x < width; x++){
            newLevel.f[y][x] = board[y * width + x];
            if(newLevel.f[y][x] == '@'){
                newLevel.sx = x;
                newLevel.sy = y;
            }
            else if(newLevel.f[y][x] == '+'){
                newLevel.sx = x;
                newLevel.sy = y;
            }
        }
    }

    newLevel.width = width;
    newLevel.height = height;
    newLevel.next_level = NULL;

    struct solution sol;

    Solver s;
    bool solved = s.solve(newLevel, 0, sol);
    if(solved){
        psStatus->uiFlags = SOKOBAN_PLUGIN_FLAG_SOLUTION;
        if((int)uiSolutionBufferSize > sol.length) {
            strncpy(pcSolution, sol.move, sol.length);
            pcSolution[sol.length] = '\0';
            return SOKOBAN_PLUGIN_RESULT_SUCCESS;
        } else {
            return SOKOBAN_PLUGIN_RESULT_GAMETOOLONG;
        }
    } else {
        return SOKOBAN_PLUGIN_RESULT_GIVEUP;
    }
}

void __declspec(dllexport) __stdcall GetConstraints(unsigned int* puiMaxWidth, unsigned int* puiMaxHeight, unsigned int* puiMaxBoxes) {
    *puiMaxWidth = 0;
    *puiMaxHeight = 0;
    *puiMaxBoxes = 0;
}

void __declspec(dllexport) __stdcall GetPluginName(char* pcString, unsigned int uiStringBufferSize) {
    strcpy_s(pcString, uiStringBufferSize, "RBrNx SokoGenerator");
}

void __declspec(dllexport) __stdcall Configure(HWND hwndParent) {
    MessageBox(hwndParent, L"No configuration options", L"RBrNx SokoGenerator", MB_OK);
}

void __declspec(dllexport) __stdcall ShowAbout(HWND hwndParent) {
    int argc = 0; char** argv = NULL;
    QApplication a(argc, argv);
    QMessageBox::about(NULL, "About SokoGenrator", "<img src=':/tileset/textures/logo.png' align = 'left'></img>"
                                                   "<p align = 'center'>"
                                                   "<h2>Version 1.0.1</h2>"
                                                   "<h4>Developed by <a href='https://github.com/RBrNx'> Conor Watson </a></h4>"
                                                   "<h4>Special Thanks to <a href='http://pavel.klavik.cz/'> Pavel Klavik </a></h4>"
                                                   "<h4>Developed using C++ and QT</h4>"
                                                   "<h4>SokoGenerator Licensed under MIT 2016</h4>"
                                                   "<h4><a href='https://github.com/RBrNx/SokoGenerator#help'>Needing Help?</a></h4>"
                                                   "</p>");
}

}
