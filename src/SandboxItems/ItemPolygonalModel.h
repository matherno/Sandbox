#pragma once

#include "SandboxItem.h"



class ItemPolygonalModel : public SandboxItem
  {
private:
  RenderablePtr model;
  bool isModelColoured = true;
  bool isModelTextured = false;
  bool isModelVertColoured = false;
  float modelColour[3];

  int currModelFileSel = -1;
  std::vector<string> listModelFiles;

  int currTextureFileSel = -1;
  std::vector<string> listTextureFiles;


public:
  ItemPolygonalModel(uint id) : SandboxItem(id, SandboxItemType::polygonalModel) {}

  virtual void doItemProperties(GameContext* gameContext) override;
  virtual void refreshItem(GameContext* gameContext, string resourceDir, string* errMsg) override; 
  virtual void onDetached(GameContext* gameContext) override; 
  virtual void onResourceDirChanged(string resourceDir) override;
  virtual void onTransformChanged() override;
  };