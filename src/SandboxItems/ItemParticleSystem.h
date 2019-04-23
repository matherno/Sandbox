#pragma once

#include "SandboxItem.h"



class ParticleSystem;

class ItemParticleSystem : public SandboxItem
  {
private:
  std::shared_ptr<ParticleSystem> particleSystem;
  double particleSize = 3;
  float particleCol[3] = {1, 0, 0};
  double gravity = 0.001;
  double initVelocity = 0.8;
  int timeAlive = 1000;
  int timeBetweenSpawns = 50;
  bool isDirectionRandom = true;
  bool isDirectionHemisphere = false;
  bool isDirectionSingle = false;
  double hemisphereExp = 20;
  Vector3D spawnDirection = Vector3D(0, 1, 0);
  bool isSpawnPoint = true;
  bool isSpawnSphere = false;
  bool isSpawnCircle = false;
  bool isSpawnLine = false;
  double spawnRadius = 1;
  Vector3D spawnCircleNormal = Vector3D(0, 1, 0);
  Vector3D spawnLinePt1 = Vector3D(0, 0, 0);
  Vector3D spawnLinePt2 = Vector3D(1, 0, 0);
  bool emitting = true;

public:
  ItemParticleSystem(uint id) : SandboxItem(id, SandboxItemType::particleSystem) {}

  virtual void doItemProperties(GameContext* gameContext) override;
  virtual void refreshItem(GameContext* gameContext, string resourceDir, string* errMsg) override; 
  virtual void onDetached(GameContext* gameContext) override; 
  virtual void onResourceDirChanged(string resourceDir) override;
  virtual void onTransformChanged() override;
  };