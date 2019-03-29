#pragma once

#include "imgui/imgui.h"

#define FILEPATH_MAX_SIZE 255


static void imguiSpacing()
  {
  ImGui::Spacing();
  ImGui::Spacing();
  ImGui::Spacing();
  }

static void imguiSeperator()
  {
  imguiSpacing();
  ImGui::Separator();
  imguiSpacing();
  }

static void imguiIndent(int n = 1)
  {
  for (int i = 0; i < n; ++i)
    ImGui::Indent();
  }

static void imguiUnindent(int n = 1)
  {
  for (int i = 0; i < n; ++i)
    ImGui::Unindent();
  }

static void imguiText(string text)
  {
  ImGui::Text(text.c_str(), text.size());
  }

static void imguiWrappedText(string text)
  {
  ImGui::TextWrapped(text.c_str(), text.size());
  }

static bool imguiButton(string text)
  {
  return ImGui::Button(text.c_str());
  }

static auto vector_getter = [](void* vec, int idx, const char** out_text)
  {
  auto& vector = *static_cast<std::vector<std::string>*>(vec);
  if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
  *out_text = vector.at(idx).c_str();
  return true;
  };

static bool imguiCombo(const char* label, int* currIndex, std::vector<std::string>& values)
  {
  if (values.empty()) { return false; }
    return ImGui::Combo(label, currIndex, vector_getter,
        static_cast<void*>(&values), values.size());
  }

static bool imguiListBox(const char* label, int* currIndex, std::vector<std::string>& values)
  {
  if (values.empty()) { return false; }
  return ImGui::ListBox(label, currIndex, vector_getter,
      static_cast<void*>(&values), values.size());
  }


enum class SandboxItemType
  {
  polygonalModel,
  voxelModel,
  };


static const std::map<SandboxItemType, string> sandboxItemTypesList
  {
    { SandboxItemType::polygonalModel,    "Polygonal Model"  },
    { SandboxItemType::voxelModel,        "Voxel Model"  },
  };
  

static string sandboxItemTypeName(SandboxItemType type)
  {
  auto iter = sandboxItemTypesList.find(type);
  if (iter != sandboxItemTypesList.end())
    return iter->second;
  ASSERT(false, "");
  return "";
  }