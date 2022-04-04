#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include "CD2DImage.h"
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")

using namespace D2D1;

class CRenderManager
{
	SINGLETON(CRenderManager);

private:
	ID2D1Factory* m_pFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IDWriteFactory* m_pWriteFactory;
	IWICImagingFactory* m_pImageFactory;
	ID2D1Bitmap* m_pBitmap;
	ID2D1SolidColorBrush* m_pBrush;

	IDWriteTextFormat* m_pTextFormat;

	ID2D1PathGeometry* m_pPathGeometry;
	ID2D1PathGeometry* geometry;

public:
	void init();

	void RenderImage(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float alpha = 1.0f, fVec2 pos = fVec2(0, 0), float angle = 0);
	void RenderFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH,
		float srcX, float srcY, float srcW, float srcH, float alpha = 1.0f, fVec2 pos = fVec2(0, 0), float angle = 0);
	void RenderRevFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH,
		float srcX, float srcY, float srcW, float srcH, float alpha = 1.0f, fVec2 pos = fVec2(0, 0), float angle = 0);

	void RenderText(wstring str, float dstX, float dstY, float dstW, float dstH, float fontSize = 12.f, COLORREF color = RGB(0, 0, 0));
	void RenderRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0), fVec2 pos = fVec2(0, 0), float angle = 0);
	void RenderFillRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0), float alpha = 1.0f, fVec2 pos = fVec2(0, 0), float angle = 0);
	void RenderEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color, float strokeWidth, fVec2 pos = fVec2(0, 0), float angle = 0);
	void RenderGeometry(float dstX, float dstY, float dstW, float dstH, COLORREF color, float strokeWidth, bool right = true);
	void RenderFillEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0), fVec2 pos = fVec2(0, 0), float angle = 0);
	void RenderLine(fVec2 startPoint, fVec2 endPoint, COLORREF color = RGB(0, 0, 0), float strokeWidth = 1.f, fVec2 pos = fVec2(0, 0), float angle = 0);

	ID2D1PathGeometry* GenTriangleGeometry(D2D1_POINT_2F pt1, D2D1_POINT_2F pt2, D2D1_POINT_2F pt3);
	ID2D1Bitmap* GetBitmap();
	ID2D1HwndRenderTarget* GetRenderTarget();
	IWICImagingFactory* GetImageFactory();
	IDWriteFactory* GetWriteFactory();
};