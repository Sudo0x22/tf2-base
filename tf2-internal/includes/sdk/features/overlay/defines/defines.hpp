#pragma once
#include<d3d9.h>
#include<d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

typedef LRESULT(__stdcall* oEndSceneFn)(LPDIRECT3DDEVICE9);
typedef LRESULT(__stdcall* oWndProcFn)(HWND, UINT, WPARAM, LPARAM);

oEndSceneFn oEndScene = 0;
oWndProcFn oWndProc = 0;