#pragma once
#include "../Includes.h"
bool init = false;
class D3D11Hooker
{
public:
	HRESULT __stdcall InitD3D11(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	void Shutdown();

};

