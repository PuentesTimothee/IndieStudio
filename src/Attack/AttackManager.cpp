//
// Created by mymy on 01/06/17.
//

#include "Systems/Attack/AttackManager.hpp"

void					Gauntlet::AttackManager::takeEvent(Gauntlet::Event const &evt)
{
  if (evt._type == Gauntlet::EventType::ATTACK
      && evt._entities.size() > 0)
    this->generateAttack(evt._entities[0]);
  else if (evt._type == Gauntlet::EventType::DESTROY
	   && evt._entities.size() > 0)
      this->destroyEnt(evt._entities[0].get());
}

void					Gauntlet::AttackManager::destroyEnt(Gauntlet::Entity* ent)
{
  auto attack = std::remove_if(this->_attacks.begin(), this->_attacks.end(),
			       [ent](Gauntlet::AttackData const &obj)
			       { return (ent == obj.attack.get()); });

  if (attack != this->_attacks.end())
    {
      this->_attacks.erase(attack, this->_attacks.end());
    }

  //Check if attacker die
  for (auto & attackIt : this->_attacks)
    {
      if (attackIt.attacker.get() == ent)
    	attackIt.attacker = nullptr;
    }
}

void					Gauntlet::AttackManager::updateTrajectorys()
{
  for (auto & attack : this->_attacks)
    {
      Gauntlet::Weapon			*weapon = attack.attack->getPtr<Gauntlet::Weapon>();
      Gauntlet::Model			*model = attack.attack->getPtr<Gauntlet::Model>();

      Ogre::Vector3			pos;

      pos = (weapon->rangeStart * (1 - attack.perc)) +
	      (weapon->rangeEnd * attack.perc);
      attack.perc += weapon->attackSpeed * Gauntlet::CoreGame::core->frameRate;
      model->body->setPosition(pos);
      if (attack.perc >= 1)
	{
	  Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::DESTROY,
					     attack.attack);
	  if (attack.attacker)
	    Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::ATTACK_END,
					       attack.attacker);
	}
    }
}


void					Gauntlet::AttackManager::generateAttack(std::shared_ptr<Gauntlet::Entity> const& entity)
{
  Gauntlet::Model			*model = entity->getPtr<Gauntlet::Model>();
  Gauntlet::Weapon			*weapon = entity->getPtr<Gauntlet::Weapon>();
  int                                   i = 0;

  if (model == nullptr || weapon == nullptr)
    return ;

  std::vector<std::shared_ptr<Gauntlet::Entity>>	attacks;

  if (weapon->type == Gauntlet::Weapon::Type::CAC)
    attacks.push_back(EntityFactory::create<CaCAttack>());
  else if (weapon->type == Gauntlet::Weapon::Type::DIST)
      attacks.push_back(EntityFactory::create<DistAttack>());
    else if (weapon->type == Gauntlet::Weapon::Type::HEAL)
	attacks.push_back(EntityFactory::create<HealAttack>());
      else if (weapon->type == Gauntlet::Weapon::Type::ZONE_DIST)
	  {
	    attacks.push_back(EntityFactory::create<ZoneDistAttack>());
	    attacks.push_back(EntityFactory::create<ZoneDistAttack>());
	    attacks.push_back(EntityFactory::create<ZoneDistAttack>());
	    attacks.push_back(EntityFactory::create<ZoneDistAttack>());
	  }
      else
	std::cerr << "No weapon Linked" << std::endl;

  for (auto &attack : attacks)
    {
      Gauntlet::Model			*attackModel = attack->getPtr<Gauntlet::Model>();
      Gauntlet::Stats			*attackStats = attack->getPtr<Gauntlet::Stats>();
      Gauntlet::Weapon			*attackWeapon = new Gauntlet::Weapon(*weapon);

      Ogre::Radian				rot(Ogre::Math::ATan2(model->dirVec.crossProduct(Ogre::Vector3::UNIT_X).normalise(),
									model->dirVec.dotProduct(Ogre::Vector3::UNIT_X)));
      if (model->dirVec.z >= 0)
	rot *= -1;

      if (i == 1)
	{
	  weapon->rangeStart.x *= -1;
	  weapon->rangeEnd.x *= -1;
	}
      else if (i == 2)
	  {
	    weapon->rangeStart.z *= -1;
	    weapon->rangeEnd.z *= -1;
	  }
      else if (i == 3)
	    {
	      weapon->rangeStart.x *= -1;
	      weapon->rangeEnd.x *= -1;
	    }
      attackWeapon->rangeStart = Gauntlet::CustomMath::rotateVectorOnY(weapon->rangeStart, rot)
				 + model->body->getPosition();
      attackWeapon->rangeEnd = Gauntlet::CustomMath::rotateVectorOnY(weapon->rangeEnd, rot)
			       + model->body->getPosition();

      if (weapon->type == Weapon::Type::HEAL)
	attack->type = Entity::Type::HEAL_ATTACK;
      else if (entity->type == Entity::Type::HERO)
	  attack->type = Entity::Type::HERO_ATTACK;
	else if (entity->type == Entity::Type::EVIL)
	    attack->type = Entity::Type::EVIL_ATTACK;
	  else
	    attack->type = entity->type;

      attackModel->dirVec = model->dirVec;
      attackModel->body->setOrientation(attackModel->getDiretion());
      attackModel->body->setPosition(weapon->rangeStart + model->node->getPosition());
      attackStats->moveSpeed = weapon->attackSpeed;

      attack->attach<Gauntlet::Weapon>(attackWeapon);

      Gauntlet::CoreGame::core->addEntity(attack);
      this->_attacks.emplace_back(attack, attackWeapon, entity);
      i += 1;
    }
}

void		Gauntlet::AttackManager::destroyAllEntity()
{
  this->_attacks.clear();
}


Gauntlet::AttackData::AttackData(std::shared_ptr<Gauntlet::Entity> const &paramAttack,
				 Gauntlet::Weapon *paramAttackWeapon,
				 std::shared_ptr<Gauntlet::Entity> const& paramAttacker)
	: attack(paramAttack),
	  attackWeapon(paramAttackWeapon),
	  attacker(paramAttacker),
	  perc(0)
{
}
