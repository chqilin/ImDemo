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


bool open_file_dialog(std::string& select_file_path) {
	IFileDialog* pfd = NULL;
	auto hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
	DWORD flags;
	hr = pfd->GetOptions(&flags);
	hr = pfd->SetOptions(flags | FOS_FORCEFILESYSTEM | FOS_ALLOWMULTISELECT);
	COMDLG_FILTERSPEC file_types[] = {
		{ L"NGR Niagara Performance File", L"*.niagaraperf" },
	};
	hr = pfd->SetFileTypes(ARRAYSIZE(file_types), file_types);
	hr = pfd->SetFileTypeIndex(1);

	hr = pfd->Show(NULL);

	IShellItem* item = nullptr;
	hr = pfd->GetResult(&item);

	if (item == nullptr) {
		return false;
	}

	struct CoTaskMemFreeScope {
		CoTaskMemFreeScope(LPVOID p)
			:ptr(p) {

		}

		~CoTaskMemFreeScope() {
			if (ptr) {
				CoTaskMemFree(ptr);
			}
		}

		LPVOID ptr;
	};

	LPWSTR wpath = NULL;
	CoTaskMemFreeScope _(wpath);
	hr = item->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &wpath);

	if (wpath == NULL) {
		return false;
	}

	DWORD dwMinSize = 0;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, wpath, -1, NULL, 0, NULL, FALSE);
	if (dwMinSize == 0) {
		return false;
	}

	select_file_path.resize(dwMinSize + 1);
	WideCharToMultiByte(CP_OEMCP, NULL, wpath, -1, select_file_path.data(), dwMinSize, NULL, FALSE);

	return true;
}


void ImApp::init() {

}

void ImApp::quit() {

}

void ImApp::tick() {
	this->menu();
	this->content();
}

void ImApp::menu() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open File...")) {
				std::string select_file_path;
				if (open_file_dialog(select_file_path)) {
					// allocate_visualization_page(select_file_path);
				}

			}

			if (ImGui::MenuItem("Open Folder...")) {

			}

			if (ImGui::BeginMenu("Open Recent")) {
				ImGui::MenuItem("fish_hat.c");
				ImGui::MenuItem("fish_hat.inl");
				ImGui::MenuItem("fish_hat.h");
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Tools")) {

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window")) {

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("About")) {

			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void ImApp::content()
{
	ImGuiIO& io = ImGui::GetIO();
	static const char* content_window_name = "##niagara_perf_viewer_main_window";
	static const ImGuiWindowFlags content_window_flags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus;
	ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight()));
	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y - ImGui::GetFrameHeight()));
	if (ImGui::Begin(content_window_name, nullptr, content_window_flags))
	{


		ImGui::End();
	}
}

