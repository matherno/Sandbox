#include "ItemVoxelModel.h"
#include "RenderSystem/RenderableVoxels.h"



void ItemVoxelModel::doItemProperties(GameContext* gameContext)
  {
  SandboxItem::doItemProperties(gameContext);
  imguiCombo("Voxel Model", &currModelFileSel, listModelFiles);
  if(ImGui::InputDouble("Voxel Size", &voxelSize, 0.1, 1))
    voxelSize = std::max(voxelSize, 0.000001);
  }
  
void ItemVoxelModel::refreshItem(GameContext* gameContext, string resourceDir, string* errMsg)
  {
  RenderContext* renderContext = gameContext->getRenderContext();
  if (model)
    renderContext->removeAndCleanUpRenderable(model);

  if (currModelFileSel < 0)
    {
    *errMsg = "No model selected";
    return;
    }

  try
    {
    RenderableVoxels* voxelModel = new RenderableVoxels(renderContext->getNextRenderableID());
    voxelModel->setVoxelStorage(renderContext->getSharedVoxelStorage(resourceDir + listModelFiles[currModelFileSel]));
    voxelModel->setVoxelSize(voxelSize);
    model.reset(voxelModel);
    renderContext->addAndInitialiseRenderable(model);
    }
  catch(std::runtime_error& err)
    {
    *errMsg = err.what();
    }
  }

void ItemVoxelModel::onDetached(GameContext* gameContext)
  {
  if (model)
    {
    gameContext->getRenderContext()->removeAndCleanUpRenderable(model);
    model.reset();
    }
  }

void ItemVoxelModel::onResourceDirChanged(string resourceDir)
  {
  getFilesInResourceDir(resourceDir, listModelFiles, currModelFileSel, "mgv");
  }

void ItemVoxelModel::onTransformChanged()
  {
  if (model)
    setupTransform(model->getTransform());
  }
