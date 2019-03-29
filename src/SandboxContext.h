#pragma once

#include "GameSystem/GameContextImpl.h"
#include "imgui/imgui.h"
#include "CameraHandler.h"
#include "SandboxUtils.h"
#include "SandboxItem.h"


typedef std::string string;

class SandboxContext : public GameContextImpl
  {
private:
  std::shared_ptr<CameraHandler> cameraHandler;
  mathernogl::MappedList<SandboxItem*> items;
  std::vector<uint> listItems;
  uint selectedItemID = 0;
  int selectedItemIndex = -1;
  string refreshErrorMsg; 
  char resFilePath[FILEPATH_MAX_SIZE] = "resources/"; 
  std::vector<string> itemNames;
  
public:
  SandboxContext(RenderContextPtr renderContext);

  virtual bool initialise() override;
  virtual void processUpdateStage() override;
  virtual void doIMGui() override;
  virtual void cleanUp() override;

protected:
  void onRefreshModelPressed();
  SandboxItemPtr createSandboxItem(SandboxItemType type);
  void deleteSandboxItem(uint id);
  void doIMGuiCreateItemPopup();
  };