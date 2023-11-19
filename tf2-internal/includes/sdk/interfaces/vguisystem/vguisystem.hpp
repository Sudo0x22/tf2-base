#pragma once
#include"../../features/overlay/overlay.hpp"

template< class T >
T Min(T const& val1, T const& val2)
{
	return val1 < val2 ? val1 : val2;
}

template< class T >
T Max(T const& val1, T const& val2)
{
	return val1 > val2 ? val1 : val2;
}

typedef struct RGBA {
	unsigned long R;
	unsigned long G;
	unsigned long B;
	unsigned long A;
};

class Colors {
public:
	RGBA white = { 255,255,255,255 };
	RGBA black = { 0,0,0,255 };
	RGBA blue = { 0,0,255,255 };
	RGBA red = { 255,0,0,255 };
public:

	__declspec(dllexport) Colors GetTeamColor(const int nTeamIndex)
	{
		if (nTeamIndex == 2)
			return (Colors)red;
		else if (nTeamIndex == 3)
			return (Colors)blue;
		else
			return (Colors)white;
	}

	__declspec(dllexport) Colors GetHealthColor(const int nHealth, const int nMaxHealth) {
		if (nHealth < nMaxHealth)
			return (Colors)blue;

		const int nHP = Max(0, Min(nHealth, nMaxHealth));
		const uint32_t nR = static_cast<uint32_t>(Min((520 * (nMaxHealth - nHP)) / nMaxHealth, 200));
		const uint32_t nG = static_cast<uint32_t>(Min((520 * nHP) / nMaxHealth, 200));

		return { static_cast<byte>(nR), static_cast<byte>(nG), 0u, 255u };
	}
};

class VGuiSystem {
public:
	__declspec(dllexport) void draw_line(const ImVec2& aPoint1,
		const ImVec2& aPoint2, ImU32 aColor, float aThickness) {
		auto vList = ImGui::GetOverlayDrawList();
		vList->AddLine(aPoint1, aPoint2, aColor, aThickness);
	}

	__declspec(dllexport) void health_bar(float x, float y, float w, float h, int pHealth)
	{
		auto vList = ImGui::GetOverlayDrawList();
		int healthValue = max(0, min(pHealth, 100));
		int barColor = ImColor(
			min(510 * (100 - healthValue) / 100, 255), min(510 * healthValue / 100, 255), 25, 255
		);

		vList->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0));
		vList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + (((float)h / 100.0f) * (float)pHealth)), barColor, 0.0f, 0);

	}
};