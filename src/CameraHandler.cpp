//
// Created by matt on 3/12/17.
//

#include <GameSystem/InputCodes.h>
#include "CameraHandler.h"

CameraHandler::CameraHandler(uint id, const Vector3D& focalPosition, float zoomOffset, float rotation, float pitch)
  : InputHandler(id), focalPosition(focalPosition), zoomOffset(zoomOffset), rotation(rotation), pitch(pitch)
  {
  }

void CameraHandler::refreshCamera(Camera* camera)
  {
  *camera->getWorldToCamera() = mathernogl::matrixTranslate(focalPosition * -1) * rotationMatrix * mathernogl::matrixTranslate(0, 0, -zoomOffset);
  // *camera->getCameraToClip() = mathernogl::matrixOrthogonal(zoomOffset, aspectRatio, -300);
  *camera->getCameraToClip() = mathernogl::matrixPerspective(1, aspectRatio, -1, -300);
  camera->setValid(false);
  cameraNeedsRefresh = false;
  }

void CameraHandler::onAttached(GameContext* gameContext)
  {
  Camera* camera = gameContext->getCamera();
  aspectRatio = gameContext->getRenderContext()->getWindow()->getAspectRatio();
  refreshRotationMatrix();
  refreshCamera(camera);
  camera->setValid(false);
  }

void CameraHandler::onDetached(GameContext* gameContext)
  {

  }

void CameraHandler::onUpdate(GameContext* gameContext)
  {
  if (cameraNeedsRefresh)
    {
    Camera* camera = gameContext->getCamera();
    refreshRotationMatrix();
    refreshCamera(camera);
    camera->setValid(false);
    }
  }

bool CameraHandler::onKeyHeld(GameContext* gameContext, uint key)
  {
  char character = getCharFromKeyCode(key);
  Vector3D translation(0);
  float rotationDelta = 0;
  float speed = panSpeed * gameContext->getDeltaTime() * 0.001f;
  float rotateSpeed = yawSpeed * gameContext->getDeltaTime() * 0.001f;
  speed *= zoomOffset / maxZoom;

  switch(character)
    {
    case 'W':
      translation.set(0, 0, -speed);
      break;
    case 'A':
      translation.set(-speed, 0, 0);
      break;
    case 'S':
      translation.set(0, 0, speed);
      break;
    case 'D':
      translation.set(speed, 0, 0);
      break;
    case 'Q':
      rotationDelta = -rotateSpeed;
      break;
    case 'E':
      rotationDelta = rotateSpeed;
      break;
    }

  if (translation.magnitude() > 0 || rotationDelta != 0)
    {
    if (rotationDelta != 0)
      {
      rotation += rotationDelta;
      refreshRotationMatrix();
      }
    translation *= mathernogl::matrixYaw(rotation);
    Vector3D newFocalPosition = focalPosition + translation;
    focalPosition = newFocalPosition;
    setCameraNeedsRefresh();
    return true;
    }
  return false;
  }

void CameraHandler::refreshRotationMatrix()
  {
  rotationMatrix = mathernogl::matrixYaw(-rotation) * mathernogl::matrixPitch(-pitch);
  }

bool CameraHandler::onKeyPressed(GameContext* gameContext, uint key)
  {
  return false;
  }

bool CameraHandler::onMousePressed(GameContext* gameContext, uint button, uint mouseX, uint mouseY)
  {
  return false;
  }

bool CameraHandler::onMouseHeld(GameContext* gameContext, uint button, uint mouseX, uint mouseY)
  {
  return false;
  }

bool CameraHandler::onMouseReleased(GameContext* gameContext, uint button, uint mouseX, uint mouseY)
  {
  return false;
  }

bool CameraHandler::onMouseScroll(GameContext* gameContext, double scrollOffset, uint mouseX, uint mouseY)
  {
  zoomOffset -= scrollOffset * zoomSpeed;
  zoomOffset = mathernogl::clampf(zoomOffset, minZoom, maxZoom);
  setCameraNeedsRefresh();
  return true;
  }

bool CameraHandler::onMouseMove(GameContext* gameContext, uint mouseX, uint mouseY, uint prevMouseX, uint prevMouseY)
  {
  if (gameContext->getInputManager()->isMouseDown(MOUSE_MIDDLE))
    {
    float rotateSpeed = mouseYawSpeed * gameContext->getDeltaTime() * 0.001f;
    rotation += ((float) prevMouseX - (float) mouseX) * rotateSpeed;
    refreshRotationMatrix();
    setCameraNeedsRefresh();
    return true;
    }
  else if (gameContext->getInputManager()->isMouseDown(MOUSE_RIGHT))
    {
    float speed = panSpeed * gameContext->getDeltaTime() * 0.00005f;
    speed *= zoomOffset / maxZoom;
    Vector3D translation;
    translation.x += ((float) prevMouseX - (float) mouseX) * speed;
    translation.z += ((float) prevMouseY - (float) mouseY) * speed;
    translation *= mathernogl::matrixYaw(rotation);
    focalPosition += translation;
    setCameraNeedsRefresh();
    return true;
    }
  return false;
  }

