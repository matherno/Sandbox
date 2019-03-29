#pragma once

#include <GameSystem/GameSystem.h>

/*
*   
*/

class CameraHandler : public InputHandler
  {
private:
  Vector3D focalPosition;
  float panSpeed = 70;
  float yawSpeed = 120;
  float zoomSpeed = 3;
  float mousePanSpeed = 40;
  float mouseYawSpeed = 30;
  float minZoom = 20;
  float maxZoom = 100;
  float rotation;
  float pitch;
  Matrix4 rotationMatrix;
  float zoomOffset;
  bool cameraNeedsRefresh = true;
  double aspectRatio = 1;

public:
  CameraHandler(uint id, const Vector3D& focalPosition, float zoomOffset = 0, float rotation = 0, float pitch = -45);

  void setCameraNeedsRefresh() { cameraNeedsRefresh = true; }
  Vector3D getFocalPosition() const { return focalPosition; }
  float getPitch() const { return pitch; };
  float getRotation() const { return rotation; };
  float getZoomOffset() { return zoomOffset; }
  void setFocalPosition(Vector3D pos) { focalPosition = pos; }
  void setPanSpeed(float speed) { panSpeed = speed; }
  void setYawSpeed(float speed) { yawSpeed = speed; }
  void setZoomOffset(float zoomOffset) { this->zoomOffset = zoomOffset; }
  void setZoomSpeed(float speed) { zoomSpeed = speed; }
  void setZoomLimits(float min, float max) { minZoom = min; maxZoom = max; }
  void setRotation(float rot) { rotation = rot; }
  void setPitch(float pitch) { this->pitch = pitch; }
  void refreshCamera(Camera* camera);

  virtual void onAttached(GameContext* gameContext) override;
  virtual void onUpdate(GameContext* gameContext) override;
  virtual bool onMousePressed(GameContext* gameContext, uint button, uint mouseX, uint mouseY) override;
  virtual bool onKeyPressed(GameContext* gameContext, uint key) override;
  virtual void onDetached(GameContext* gameContext) override;
  virtual bool onKeyHeld(GameContext* gameContext, uint key) override;
  virtual bool onMouseScroll(GameContext* gameContext, double scrollOffset, uint mouseX, uint mouseY) override;
  virtual bool onMouseHeld(GameContext* gameContext, uint button, uint mouseX, uint mouseY) override;
  virtual bool onMouseReleased(GameContext* gameContext, uint button, uint mouseX, uint mouseY) override;
  virtual bool onMouseMove(GameContext* gameContext, uint mouseX, uint mouseY, uint prevMouseX, uint prevMouseY) override;

protected:
  void refreshRotationMatrix();
  };
