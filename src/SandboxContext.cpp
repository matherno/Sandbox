#include "SandboxContext.h"
#include "SandboxItems/ItemPolygonalModel.h"
#include "SandboxItems/ItemVoxelModel.h"
#include "SandboxItems/ItemParticleSystem.h"


#define POPUP_CREATE_ITEM "Create Item"


SandboxContext::SandboxContext(RenderContextPtr renderContext) : GameContextImpl(renderContext) 
  {
  
  }

bool SandboxContext::initialise()
  {
  if(!GameContextImpl::initialise())
    return false;

  cameraHandler.reset(new CameraHandler(getInputManager()->getNextHandlerID(), Vector3D(0, 0, 0), 10, 0, -30));
  addInputHandler(cameraHandler);

  return true;
  }

void SandboxContext::processUpdateStage()
  {
  GameContextImpl::processUpdateStage();
  }


void SandboxContext::doIMGui()
  {
  ImGui::Begin("Sandbox Controls");
  imguiSpacing();

  bool refreshResources = false;
  if(ImGui::InputText("Resources File Path", resFilePath, FILEPATH_MAX_SIZE))
    refreshResources = true;
  if(ImGui::Button("Refesh Resources Lists"))
    refreshResources = true;
  if (refreshResources)
    {
    for (SandboxItem* item : *items.getList())
      item->onResourceDirChanged(resFilePath);
    }

  imguiSeperator();

  doIMGuiCreateItemPopup();
  if(ImGui::Button("Create Item"))
    ImGui::OpenPopup(POPUP_CREATE_ITEM);

  imguiSpacing();

  itemNames.clear();
  for (uint id : listItems)
    itemNames.push_back(items.get(id)->getUniqueName());

  if(imguiListBox("", &selectedItemIndex, itemNames))
    refreshErrorMsg.clear();

  if (selectedItemIndex >= 0 && selectedItemIndex < listItems.size())
    {
    SandboxItem* selectedItem = items.get(listItems[selectedItemIndex]);
    imguiSeperator();
    imguiIndent(5);
    imguiText(selectedItem->getUniqueName());
    imguiUnindent(4);
    imguiSpacing();

    selectedItem->doItemProperties(this);

    imguiSpacing();

    if(ImGui::Button("Refresh"))
      {
      refreshErrorMsg.clear();
      selectedItem->refreshItem(this, resFilePath, &refreshErrorMsg);
      selectedItem->onTransformChanged();
      }
    ImGui::SameLine();
    if(ImGui::Button("Delete"))
      {
      refreshErrorMsg.clear();
      deleteSandboxItem(selectedItem->getID());
      }
    ImGui::NewLine();
    if (!refreshErrorMsg.empty())
      imguiWrappedText("Failed to refresh item: " + refreshErrorMsg);
    imguiUnindent();
    }

  imguiSeperator();
  imguiSpacing();
  ImGui::Text("FPS %.1f, ms per frame %.3f", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
  ImGui::End();

  GameContextImpl::doIMGui();
  }

void SandboxContext::cleanUp()
  {
  GameContextImpl::cleanUp();
  }

void SandboxContext::onRefreshModelPressed()
  {

  }

SandboxItemPtr SandboxContext::createSandboxItem(SandboxItemType type)
  {
  SandboxItemPtr item;

  const uint id = getNextActorID();

  switch (type)
    {
    case SandboxItemType::polygonalModel:
      item.reset(new ItemPolygonalModel(id));
      break;
    case SandboxItemType::voxelModel:
      item.reset(new ItemVoxelModel(id));
      break;
    case SandboxItemType::particleSystem:
      item.reset(new ItemParticleSystem(id));
      break;
    default:
      ASSERT(false, "");
      break;
    }

  if (item)
    {
    items.add(item.get(), item->getID());
    addActor(item);
    item->onResourceDirChanged(resFilePath);
    item->onTransformChanged();
    listItems.push_back(item->getID());
    }

  return item;
  }

void SandboxContext::deleteSandboxItem(uint id)
  {
  auto iter = std::find(listItems.begin(), listItems.end(), id);
  if (iter != listItems.end())
    listItems.erase(iter);
  items.remove(id);
  removeActor(id);
  }

void SandboxContext::doIMGuiCreateItemPopup()
  {
  if (!ImGui::BeginPopup(POPUP_CREATE_ITEM))
    return;

  for (const std::pair<SandboxItemType, string>& typeAndName : sandboxItemTypesList)
    {
    if(imguiButton(typeAndName.second))
      {
      if(createSandboxItem(typeAndName.first) != nullptr)
        {
        selectedItemIndex = listItems.size() - 1;
        refreshErrorMsg.clear();
        }
      ImGui::CloseCurrentPopup();
      }
    }
  ImGui::EndPopup();
  }