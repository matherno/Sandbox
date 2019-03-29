#include "SandboxItem.h"


void SandboxItem::onAttached(GameContext* gameContext)
  {
  
  }

void SandboxItem::onUpdate(GameContext* gameContext)
  {
  
  }

void SandboxItem::onDetached(GameContext* gameContext)
  {
  
  }

void SandboxItem::doItemProperties(GameContext* gameContext)
  {
  imguiText("Translation");
  if(ImGui::InputDouble("X", &translation.x, 1, 10))
    onTransformChanged();
  if(ImGui::InputDouble("Y", &translation.y, 1, 10))
    onTransformChanged();
  if(ImGui::InputDouble("Z", &translation.z, 1, 10))
    onTransformChanged();
  imguiSpacing();
  }

void SandboxItem::setupTransform(Transform* transform)
  {
  transform->setIdentityMatrix();
  transform->translate(translation);
  }

/*static*/ void SandboxItem::getFilesInResourceDir(const string& resDir, std::vector<string>& files, int& currSel, string ext)
  {
  getFilesInResourceDir(resDir, files, currSel, std::vector<string>({ext}));
  }

/*static*/ void SandboxItem::getFilesInResourceDir(const string& resDir, std::vector<string>& files, int& currSel, const std::vector<string>& exts)
  {
  string prevSelection;
  if (currSel >= 0 && currSel < files.size())
    prevSelection = files[currSel];

  files.clear();
  std::list<string> filesSet;
  for (const string& ext : exts)
    mathernogl::getFilesInDirectory(resDir, &filesSet, ext);
  for (string& file : filesSet)
    files.push_back(file);

  currSel = -1;
  if (!prevSelection.empty())
    {
    for (int idx = 0; idx < files.size(); ++idx)
      {
      if (files[idx] == prevSelection)
        currSel = idx;
      }
    }
  }
