// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <intrin.h>
#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "adjustments.h"
#include "parent.h"
#include "wall.h"
#include "cell.h"
#include "nest.h"
#include "splitmix64.h"
#include "xorshiro.h"
#include "mongo.h"
#include "rules.h"
