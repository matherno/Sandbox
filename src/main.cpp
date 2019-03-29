#include <iostream>
#include <RenderSystem/RenderSystem.h>
#include <RenderSystem/RenderContextImpl.h>
#include "SandboxContext.h"


//  essentially an exception type that will never be thrown (to make a try-catch block not catch anything)
class null_exception : public std::exception
  {};

void attemptCrashCleanup(RenderContext* renderContext)
  {
  std::vector<RenderablePtr> renderables;
  renderContext->getRenderableSet()->forEachChild([&renderables](RenderablePtr renderable)
    {
    renderables.push_back(renderable);
    });
  for (RenderablePtr renderable : renderables)
    {
    renderable->cleanUp(renderContext);
    renderContext->getRenderableSet()->removeRenderable(renderable->getID());
    }
  }

void runGame()
  {
  RenderInitConfig renderConfig;
  renderConfig.windowName = "OpenGL Sandbox";
  renderConfig.windowWidth = 1800;
  renderConfig.windowHeight = 900;
  renderConfig.antiAliasing = true;
  renderConfig.fullscreen = false;

  RenderContextPtr renderContext(new RenderContextImpl());
  if (!renderContext->initialise(&renderConfig))
    {
    mathernogl::logError("Failed to initialise render system!");
    return;
    }

  mathernogl::logInfo("Starting... ");

  try
    {
    SandboxContext gameContext(renderContext);
    if(gameContext.initialise())
      {
      while (!gameContext.isContextEnded() && renderContext->isWindowOpen())
        {
        gameContext.startFrame();
        gameContext.processInputStage();
        gameContext.processUpdateStage();
        gameContext.processDrawStage();
        gameContext.endFrame(60);
        }
      }
    gameContext.cleanUp();
    }
#ifdef NDEBUG
  catch (const std::exception& err)
#else
  catch (const null_exception& err)   //  no exceptions will be caught (so they can be captured in debug)
#endif
    {
    mathernogl::logError("Crashed: " + string(err.what()));
    attemptCrashCleanup(renderContext.get());
    }

  renderContext->cleanUp();
  mathernogl::logInfo("Quiting...");
  }

int main()
  {
  try
    {
    runGame();
    }
#ifdef NDEBUG
    catch (const std::exception& err)
#else
  catch (const null_exception& err)   //  no exceptions will be caught (so they can be captured in debug)
#endif
    {
    mathernogl::logError("Completely crashed: " + string(err.what()));
    }
  }