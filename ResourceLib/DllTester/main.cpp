#include <cstdlib>
#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#include <d3d11sdklayers.h>
#include "..\ResourceLib\Resource.h"
#include <DirectXMath.h>
#include "../ResourceLib/ResourceHandler.h"
#pragma comment (lib,"../x64/Debug/ResourceLib")
int main()
{
	Resources::ResourceHandler resHandle;

	Resources::Model* model;
	
	
#pragma region
//	ID3D11Device *gDevice;
//	ID3D11DeviceContext *gContext;
//	IDXGISwapChain *gSwapChain;
//
//	DXGI_SWAP_CHAIN_DESC scd;
//
//	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
//
//	scd.BufferDesc.Width = (UINT)800;
//	scd.BufferDesc.Height = (UINT)600;
//	scd.BufferCount = 1;
//	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
//	scd.SampleDesc.Count = 1;
//	scd.Windowed = 1;
//	scd.BufferDesc.RefreshRate.Numerator = 60; //fps cap
//	scd.BufferDesc.RefreshRate.Denominator = 1;
//	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
//	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//	scd.OutputWindow = GetConsoleWindow();
//	HRESULT hr;
//	// Create the device and device context objects
//	 hr = D3D11CreateDeviceAndSwapChain(
//		NULL,
//		D3D_DRIVER_TYPE_HARDWARE,
//		NULL,
//		0,
//		NULL,
//		NULL,
//		D3D11_SDK_VERSION,
//		&scd,
//		&gSwapChain,
//		&gDevice,
//		NULL,
//		&gContext);
//
//	 if (FAILED(hr))
//		 MessageBox(GetConsoleWindow(), TEXT("ERROR"), TEXT("ERROR"), MB_OK);
//
//	
//	 ID3D11Buffer* m_indexBuffer = nullptr;
//
//	 unsigned int indices[3] = { 1,2,3 };
//
//	 D3D11_BUFFER_DESC ibd;
//
//	 ibd.Usage = D3D11_USAGE_DEFAULT;
//	 ibd.ByteWidth = sizeof(UINT) * 3;
//	 ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	 ibd.CPUAccessFlags = 0;
//	 ibd.MiscFlags = 0;
//	 ibd.StructureByteStride = 0;
//
//	 D3D11_SUBRESOURCE_DATA ibdData;
//	 ibdData.pSysMem = indices;
//
//	
//	 hr = gDevice->CreateBuffer(&ibd, &ibdData, &m_indexBuffer);
//	 gContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
//	 if (FAILED(hr))
//		 MessageBox(NULL, L"Error creating indexbuffer", L"Error in mesh class", MB_ICONERROR | MB_OK);
//	 
//
//	 std::cout << " buffer created" << std::endl;
//	
//	
////D3D11_MAPPED_SUBRESOURCE mappedResource;
////ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
////
////hr = gContext->Map(m_indexBuffer, 0, D3D11_MAP_READ , 0, &mappedResource);
////if (FAILED(hr))
////	return(0);
////unsigned int* bufferData = (unsigned int*)mappedResource.pData;
//
//	
//#pragma endregion
//	
//		
//
//	 getchar();
//
//	 gContext->Draw(0, 0);
//	 gSwapChain->Present(0, 0);
//	 gContext->Draw(0, 0);
//	 getchar();
//	 gContext->Release();
//	 gDevice->Release();
	
	getchar();

	//Resources::Status st = resHandle.LoadLevel(UINT(1337));
	
		
	getchar();
	return 0;
}