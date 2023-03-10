
/*
Projec --> AI --> Common

AI -> right clic --> properties --> C/C++ --> General --> aditial includd directories "$(ProjectDir)Inc"

AI -> right clic --> properties --> C/C++ -->PrecompiledHeaders --> PrecompiledHeader "Use(Yu)" --> PrecompiledHeadersFile "Precompiled.h"

Click on pricompiled.cpp

C/C++ -->PrecompiledHeaders --> PrecompiledHeader "Create(Yu)"

Every cpp file in AI project must include precompiled.h

*/
#pragma once
#include "Common.h"
#include "GridBasedGraph.h"
#include "BFS.h"
#include "DFS.h"

#include "Dijkstra.h"
#include "AStar.h"

//Week 06
#include "Agent.h"
#include "AIWorld.h"
#include "StateMachine.h"

//Week 08
#include "ArriveBehavior.h"
#include "EvadeBehavior.h"
#include "FleeBehavior.h"
#include "PursuitBehavior.h"
#include "SteeringBehavior.h"
#include "SteeringModule.h"
#include "SeekBehavior.h"
//Week 09
#include "WanderBehavior.h"
#include "SeparationBehavior.h"
#include "AlignmentBehavior.h"
