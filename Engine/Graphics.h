#pragma once
#include "def.h"
#include "pch.h"

#include "Exception.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API Graphics final
			{
				friend class Bindable;
			public:
				Graphics() = default;
				Graphics(const Graphics&) = delete;
				Graphics& operator=(const Graphics&) = delete;
				~Graphics() = default;
			public:
				//Initializes DirectX 11
				void Initialize(HWND hwnd, bool Fullscreen = false, bool Vsync = false, float O_Width = 0.0f, float O_Height = 0.0f);
				//Receives GraphicCardDescription, GraphicCardMemorySize, Numerator and Denominator and their value is available to use after this function
				void ReceiveHardwareInformation();
				//Creating DirectX::SpriteBatch class
				void CreateSpriteBatch();
				//Creating DirectX::CommonStates class
				void CreateCommonStates();
				//Creating a new RenderTarget, Be aware of that It doesn't bind it to the pipeline.
				void CreateRenderTarget();
			public:
				//Get D3D11 Device Object
				ID3D11Device* GetDevice() const;
				//Get DXGI SwapChain Object
				IDXGISwapChain* GetSwap() const;
				//Get D3D11 Context Object
				ID3D11DeviceContext* GetContext() const;
				//Get D3D11 RenderTarget Object
				ID3D11RenderTargetView* GetRenderTarget() const;
				//Get D3D11 Pointer-To-Pointer RenderTarget Object
				ID3D11RenderTargetView* const * GetRenderTargetPP() const;
				//Get D3D11 DepthStencilState Object
				ID3D11DepthStencilState* GetDepthStencilState() const;
				//Get D3D11 DepthStencilView Object
				ID3D11DepthStencilView* GetDepthStencilView() const;
				//Get Width of the Window
				float GetWidth() const;
				//Get Height of the Window
				float GetHeight() const;
				//Get Sprite Batch
				DirectX::SpriteBatch* GetSpriteBatch() const;
				//Get Common States
				DirectX::CommonStates* GetCommonStates() const;
				//Get VideoCard memory size in MBs
				const unsigned long GetGraphicCardMemorySize() const;
				//Get VideoCard description
				const char* GetGraphicCardDescription() const;
				//Get Vsync Boolean
				const bool GetVsyncBoolean() const;
				//Get GraphicCard informations with a pair, first element is description and the second one is the size of its memory
				constexpr std::pair<const char*, unsigned long> GetGraphicCardInfo() const;
			private:
				struct ReportLiveObjectGuard
				{
					~ReportLiveObjectGuard()
					{
					#ifdef _DEBUG
						Microsoft::WRL::ComPtr<IDXGIDebug1> Debug;
						if(SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&Debug))))
						{
							Debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_DETAIL);
						}
					#endif
					}
				} MemoryGuard;
			private:
				Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr;
				Microsoft::WRL::ComPtr<IDXGISwapChain> m_Swap = nullptr;
				Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context = nullptr;
				Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTarget = nullptr;
				Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState = nullptr;
				Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
				Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_RasterizerState = nullptr;
				Microsoft::WRL::ComPtr<ID3D11BlendState> m_BlendState = nullptr;
				std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch = nullptr;
				std::unique_ptr<DirectX::CommonStates> m_CommonStates = nullptr;
				float Width = 0.0f, Height = 0.0f;
				bool m_Vsync = false;
				char m_GraphicCardDescription[MAX_PATH]{};
				unsigned long m_GraphicCardMemorySize = 0;
				unsigned int Numerator = 0;
				unsigned int Denominator = 0;
			};
		}
	}
}

template<UINT TNameLength>
inline void SetDebugCOMObjectName(_In_ ID3D11DeviceChild* resource, _In_z_ const char(&name)[TNameLength])
{
#if defined(_DEBUG) || defined(PROFILE)
	resource->SetPrivateData(WKPDID_D3DDebugObjectName, TNameLength - 1, name);
#endif
}
