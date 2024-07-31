#include "app.h"

#include <windows.h>
// file dialog
#include <Shlobj.h>

// std
#include <functional>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>
#include <memory>
#include <cstdint>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cctype>

// imgui
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
// implot
#include "implot/implot.h"
#include "implot/implot_internal.h"
// fmt
#include "fmt/format.h"


ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
{
	return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

ImVec2 operator*(const ImVec2& lhs, const ImVec2& rhs)
{
	return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y);
}

bool operator==(const ImVec4& lhs, const ImVec4& rhs)
{
	return memcmp(&lhs, &rhs, sizeof(ImVec4)) == 0;
}

bool operator!=(const ImVec4& lhs, const ImVec4& rhs)
{
	return memcmp(&lhs, &rhs, sizeof(ImVec4)) != 0;
}


namespace string_utils
{
	bool contains(const std::string& src, const char* target)
	{
		return src.find(target) != std::string::npos;
	}
}


bool open_file_dialog(std::string& select_file_path)
{
	IFileDialog* pfd = NULL;
	auto hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
	DWORD flags;
	hr = pfd->GetOptions(&flags);
	hr = pfd->SetOptions(flags | FOS_FORCEFILESYSTEM | FOS_ALLOWMULTISELECT);
	COMDLG_FILTERSPEC file_types[] =
	{
		{ L"NGR Niagara Performance File", L"*.niagaraperf" },
	};
	hr = pfd->SetFileTypes(ARRAYSIZE(file_types), file_types);
	hr = pfd->SetFileTypeIndex(1);

	hr = pfd->Show(NULL);

	IShellItem* item = nullptr;
	hr = pfd->GetResult(&item);

	if (item == nullptr)
	{
		return false;
	}

	struct CoTaskMemFreeScope
	{
		CoTaskMemFreeScope(LPVOID p)
			:ptr(p)
		{

		}

		~CoTaskMemFreeScope()
		{
			if (ptr)
			{
				CoTaskMemFree(ptr);
			}
		}

		LPVOID ptr;
	};

	LPWSTR wpath = NULL;
	CoTaskMemFreeScope _(wpath);
	hr = item->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &wpath);

	if (wpath == NULL)
	{
		return false;
	}

	DWORD dwMinSize = 0;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, wpath, -1, NULL, 0, NULL, FALSE);
	if (dwMinSize == 0)
	{
		return false;
	}

	select_file_path.resize(dwMinSize + 1);
	WideCharToMultiByte(CP_OEMCP, NULL, wpath, -1, select_file_path.data(), dwMinSize, NULL, FALSE);

	return true;
}

void app_init()
{

}

void app_quit()
{}

void app_tick()
{}
