#pragma once

#include "GameSystem/GameSystem.h"
#include "SandboxUtils.h"



class SandboxItem : public GameActor
  {
private:
  const SandboxItemType type;

protected:
  string errorMsg;
  Vector3D translation;

public:
  SandboxItem(uint id, SandboxItemType type) : GameActor(id), type(type) {}
  virtual ~SandboxItem() {}

  string getLabel() { return sandboxItemTypeName(type); }
  string getUniqueName() { return getLabel() + " [" + std::to_string(getID()) + "]"; }

  virtual void onAttached(GameContext* gameContext) override;
  virtual void onUpdate(GameContext* gameContext) override;
  virtual void onDetached(GameContext* gameContext) override;
  
  virtual void doItemProperties(GameContext* gameContext);
  virtual void refreshItem(GameContext* gameContext, string resourceDir, string* errMsg) = 0;
  virtual void onResourceDirChanged(string resourceDir) {};
  virtual void onTransformChanged() {};
  void setupTransform(Transform* transform);

  static void getFilesInResourceDir(const string& resDir, std::vector<string>& files, int& currSel, string ext = "");
  static void getFilesInResourceDir(const string& resDir, std::vector<string>& files, int& currSel, const std::vector<string>& exts);
  };

typedef std::shared_ptr<SandboxItem> SandboxItemPtr;