#pragma once
#pragma comment(lib,"..\\Debug\\KPI-2016L.lib")
#undef IN

#include <iostream>
#include <cwchar>
#include <Windows.h>
#include <time.h>
#include <string>
#include <fstream>
#include <iomanip>
#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <stack>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

#include "../KPI-2016L/Log.h"
#include "../KPI-2016L/Error.h"
#include "../KPI-2016L/Parm.h"
#include "../KPI-2016L/LT.h"
#include "../KPI-2016L/In.h"
#include "../KPI-2016L/Divide.h"
#include "../KPI-2016L/File.h"
#include "../KPI-2016L/IT.h"
#include "FST.h"
#include "LexicalAnalyzer.h"
#include "Semantics.h"
#include "GRB.h"
#include "MFST.h"
#include "PolishNotation.h"
#include "SyntacticAnalyzer.h"
#include "NT.h"
#include "Generator.h"