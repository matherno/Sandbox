#include "ItemPolygonalModel.h"
#include "RenderSystem/RenderableMesh.h"



void ItemPolygonalModel::doItemProperties(GameContext* gameContext)
  {
  SandboxItem::doItemProperties(gameContext);
  imguiCombo("3D Model", &currModelFileSel, listModelFiles);

  imguiSpacing();

  if(ImGui::RadioButton("Single Coloured", isModelColoured))
    {
    isModelColoured = true;
    isModelVertColoured = false;
    isModelTextured = false;
    }
  ImGui::SameLine();  
  if(ImGui::RadioButton("Vertex Coloured", isModelVertColoured))
    {
    isModelColoured = false;
    isModelVertColoured = true;
    isModelTextured = false;
    }
  ImGui::SameLine();  
  if(ImGui::RadioButton("Textured", isModelTextured))
    {
    isModelColoured = false;
    isModelVertColoured = false;
    isModelTextured = true;
    }
  imguiSpacing();

  if (isModelTextured)
    imguiCombo("Texture", &currTextureFileSel, listTextureFiles);
  if (isModelColoured)
    ImGui::ColorEdit3("Colour", modelColour);
  }
  
void ItemPolygonalModel::refreshItem(GameContext* gameContext, string resourceDir, string* errMsg)
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
    RenderableMesh* meshModel = new RenderableMesh(renderContext->getNextRenderableID());
    meshModel->setMeshStorage(renderContext->getSharedMeshStorage(resourceDir + listModelFiles[currModelFileSel]));

    if (isModelColoured)
      meshModel->setDrawStyleSingleColour(Vector3D(modelColour[0], modelColour[1], modelColour[2]));
    else if (isModelVertColoured)
      meshModel->setDrawStyleVertColours();
    else if (isModelTextured && currTextureFileSel >= 0)
      meshModel->setDrawStyleTexture(renderContext->getSharedTexture(resourceDir + listTextureFiles[currTextureFileSel]));
    
    model.reset(meshModel);
    renderContext->addAndInitialiseRenderable(model);
    }
  catch(std::runtime_error& err)
    {
    *errMsg = err.what();
    }
  }

void ItemPolygonalModel::onDetached(GameContext* gameContext)
  {
  if (model)
    {
    gameContext->getRenderContext()->removeAndCleanUpRenderable(model);
    model.reset();
    }
  }

void ItemPolygonalModel::onResourceDirChanged(string resourceDir)
  {
  getFilesInResourceDir(resourceDir, listModelFiles, currModelFileSel, "obj");
  getFilesInResourceDir(resourceDir, listTextureFiles, currTextureFileSel, std::vector<string>({"png", "jpg"}));
  }

void ItemPolygonalModel::onTransformChanged()
  {
  if (model)
    setupTransform(model->getTransform());
  }
