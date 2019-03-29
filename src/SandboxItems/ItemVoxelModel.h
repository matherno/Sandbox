#pragma once

#include "SandboxItem.h"



class ItemVoxelModel : public SandboxItem
  {
private:
  RenderablePtr model;
  int currModelFileSel = -1;
  std::vector<string> listModelFiles;
  double voxelSize = 0.25;

public:
  ItemVoxelModel(uint id) : SandboxItem(id, SandboxItemType::voxelModel) {}

  virtual void doItemProperties(GameContext* gameContext) override;
  virtual void refreshItem(GameContext* gameContext, string resourceDir, string* errMsg) override; 
  virtual void onDetached(GameContext* gameContext) override; 
  virtual void onResourceDirChanged(string resourceDir) override;
  virtual void onTransformChanged() override;
  };