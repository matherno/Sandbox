#include "ItemParticleSystem.h"
#include "ParticleSystem/ParticleSystem.h"



void ItemParticleSystem::doItemProperties(GameContext* gameContext)
  {
  SandboxItem::doItemProperties(gameContext);
  
  ImGui::Text("Paticle System Parameters");
  ImGui::ColorEdit3("Colour", particleCol);
  if(ImGui::InputDouble("Particle Size", &particleSize, 1, 5))
    particleSize = std::max(particleSize, 0.000001);
  ImGui::InputDouble("Gravity", &gravity, 0.0001, 0.001);
  ImGui::InputDouble("Initial Velocity", &initVelocity, 0.1, 1);
  if(ImGui::InputInt("Time Alive (ms)", &timeAlive, 250, 1000))
    timeAlive = std::max(timeAlive, 1);
  if(ImGui::InputInt("Time Between Spawns (ms)", &timeBetweenSpawns, 50, 250))
    timeBetweenSpawns = std::max(timeBetweenSpawns, 1);

  imguiSpacing();

  imguiRadioGroup("Spawn Direction", 
    {
      { "Random", &isDirectionRandom },
      { "Uniform", &isDirectionSingle },
      { "Hemisphere", &isDirectionHemisphere },
    });
  if (isDirectionHemisphere || isDirectionSingle)
    imguiVector3D("Direction", &spawnDirection);
  if(isDirectionHemisphere)
    ImGui::InputDouble("Exponent", &hemisphereExp, 10, 100);

  imguiSpacing();

  imguiRadioGroup("Spawn Offset", 
    {
      { "Point", &isSpawnPoint },
      { "Line", &isSpawnLine },
      { "Circle", &isSpawnCircle },
      { "Sphere", &isSpawnSphere },
    });
  if (isSpawnSphere || isSpawnCircle)
    ImGui::InputDouble("Radius", &spawnRadius, 0.5, 5);
  if (isSpawnCircle)
    {
    imguiVector3D("Normal", &spawnCircleNormal);
    }
  if (isSpawnLine)
    {
    imguiVector3D("Point 1", &spawnLinePt1);
    imguiVector3D("Point 2", &spawnLinePt2);
    }

  imguiSpacing();

  if(particleSystem && ImGui::Checkbox("Emitting", &emitting))
    {
    if (emitting)
      particleSystem->startEmitters();
    else
      particleSystem->stopEmitters();
    }
  }
  
void ItemParticleSystem::refreshItem(GameContext* gameContext, string resourceDir, string* errMsg)
  {
  if (particleSystem)
    {
    gameContext->removeActor(particleSystem->getID());
    particleSystem.reset();
    }
    
  particleSystem.reset(new ParticleSystem(gameContext->getNextActorID(), true));
  particleSystem->setParticleSize(particleSize);
  particleSystem->setGravityAccel(gravity / 1000);
  particleSystem->setInitVelocity(initVelocity / 1000);
  particleSystem->setTimeAlive(timeAlive);
  particleSystem->setTimeBetweenSpawns(timeBetweenSpawns);

  if (isDirectionRandom)
    particleSystem->setParticleDirectionRandom();
  else if (isDirectionHemisphere)
    particleSystem->setParticleDirectionHemisphere(spawnDirection, hemisphereExp);
  else if (isDirectionSingle)
    particleSystem->setParticleDirection(spawnDirection);

  if (isSpawnPoint)
    particleSystem->setParticleSpawnPoint();
  else if (isSpawnSphere)
    particleSystem->setParticleSpawnSphere(spawnRadius);
  else if (isSpawnCircle)
    particleSystem->setParticleSpawnCircle(spawnRadius, spawnCircleNormal);
  else if (isSpawnLine)
    particleSystem->setParticleSpawnLine(spawnLinePt1, spawnLinePt2);

  particleSystem->addEmitter(Vector3D(0,0,0), 999999, Vector3D(particleCol[0], particleCol[1], particleCol[2]));

  gameContext->addActor(particleSystem);

  emitting = true;
  }

void ItemParticleSystem::onDetached(GameContext* gameContext)
  {
  if (particleSystem)
    {
    gameContext->removeActor(particleSystem->getID());
    particleSystem.reset();
    }
  }

void ItemParticleSystem::onResourceDirChanged(string resourceDir)
  {
  }

void ItemParticleSystem::onTransformChanged()
  {
  if (particleSystem)
    particleSystem->setTranslation(translation);
  }
