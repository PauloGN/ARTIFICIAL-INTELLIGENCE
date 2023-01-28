
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
//2:16:37
#include "Dijkstra.h"
#include "AStar.h"
