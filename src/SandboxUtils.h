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

static bool imguiVector3D(string text, Vector3D* vector)
  {
  float v[] = { (float)vector->x, (float)vector->y, (float)vector->z };
  ImGui::InputFloat3(text.c_str(), v);
  vector->x = v[0];
  vector->y = v[1];
  vector->z = v[2];
  }

static void imguiRadioGroup(string title, const std::list<std::pair<string, bool*>>& options)
  {
  if(!title.empty())
    imguiText(title);
  for (auto pair : options)
    {
    if(ImGui::RadioButton(pair.first.c_str(), *pair.second))
      {
      for (auto pair2 : options)
        *pair2.second = (pair.first == pair2.first);
      }
    ImGui::SameLine();  
    }
  ImGui::NewLine();  
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
  particleSystem,
  };


static const std::map<SandboxItemType, string> sandboxItemTypesList
  {
    { SandboxItemType::polygonalModel,    "Polygonal Model"  },
    { SandboxItemType::voxelModel,        "Voxel Model"  },
    { SandboxItemType::particleSystem,    "Particle System"  },
  };
  

static string sandboxItemTypeName(SandboxItemType type)
  {
  auto iter = sandboxItemTypesList.find(type);
  if (iter != sandboxItemTypesList.end())
    return iter->second;
  ASSERT(false, "");
  return "";
  }