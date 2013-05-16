#include "StationStats.h"
#include "../../include/Engine/Composite.h"


StationStats::StationStats(): Component()
{
	health = maxHealth;
	power = 0;
	shield = 0;
}

StationStats::~StationStats()
{
}