#include "../D3D11Hooker/D3D11Hooker.h"
#include "../Includes.h"
#include <Windows.h>
HRESULT __stdcall D3D11Hooker::InitD3D11() 
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView); //C6387 is False Positive Warning D3D11 Device
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			init = true;
		}
	}
	else {
		return oPresent(pSwapChain, SyncInterval, Flags);
	}
}
void D3D11Hooker::Shutdown() {
	kiero::shutdown();
	pDevice->Release();
	pContext->Release();
	oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)(oWndProc));
	fclose(stdout);
	FreeConsole();
}