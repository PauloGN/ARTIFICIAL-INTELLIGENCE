
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