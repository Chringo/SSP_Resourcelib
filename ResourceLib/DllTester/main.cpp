#include <cstdlib>
#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#include <d3d11sdklayers.h>
#include "..\ResourceLib\Resource.h"

//#pragma comment (lib,"../x64/Debug/ResourceLib")
int main()
{
	ID3D11Device *gDevice;
	ID3D11DeviceContext *gContext;
	HRESULT hr;
	// Create the device and device context objects
	 hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&gDevice,
		nullptr,
		&gContext);

	 if (FAILED(hr))
		 MessageBox(GetConsoleWindow(), TEXT("ERROR"), TEXT("ERROR"), MB_OK);

	
	 ID3D11Buffer* m_indexBuffer = nullptr;

	 unsigned int indices[3] = { 1,2,3 };

	 D3D11_BUFFER_DESC ibd;

	 ibd.Usage = D3D11_USAGE_DEFAULT;
	 ibd.ByteWidth = sizeof(UINT) * 3;
	 ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	 ibd.CPUAccessFlags = 0;
	 ibd.MiscFlags = 0;
	 ibd.StructureByteStride = 0;

	 D3D11_SUBRESOURCE_DATA ibdData;
	 ibdData.pSysMem = indices;

	
	 hr = gDevice->CreateBuffer(&ibd, &ibdData, &m_indexBuffer);

	 if (FAILED(hr))
		 MessageBox(NULL, L"Error creating indexbuffer", L"Error in mesh class", MB_ICONERROR | MB_OK);
	 

	 std::cout << " buffer created" << std::endl;
	
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	hr = gContext->Map(m_indexBuffer, 0, D3D11_MAP_READ , 0, &mappedResource);
	if (FAILED(hr))
		return(0);
	unsigned int* bufferData = (unsigned int*)mappedResource.pData;

	std::cout << "Data from D3D11Buffer" << std::endl;
	for (size_t i = 0; i < 3; i++)
	{
		std::cout << bufferData[i] << ",";
	}
	std::cout << std::endl;

	
	getchar();
	return 0;
}