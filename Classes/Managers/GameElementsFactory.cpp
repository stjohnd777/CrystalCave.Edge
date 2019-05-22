//
//  GameElementFactory.cpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 5/18/19.
//

#include "GameElementsFactory.h"


const char* GameElementsFactory::MINE = "Mine";
const char* GameElementsFactory::VER_ELECTRIC_FENCE = "VEF";
const char* GameElementsFactory::HOR_ELECTRIC_FENCE = "HEF";
const char* GameElementsFactory::LIGHTNING = "Linghtning";
const char* GameElementsFactory::SCAN_BEAM = "ScanBeam";
const char* GameElementsFactory::HUNTER_SEEKER = "Seeker";

const char* GameElementsFactory::TRANS = "TRANS";

GameElementsFactory* GameElementsFactory::INSTANCE = nullptr;
