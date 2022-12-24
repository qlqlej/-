#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <array>
#include <unordered_set>
#include <random>

#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <queue>
#include "protocol.h"

extern "C" {
#include "include/lua.h"
#include "include/lauxlib.h"
#include "include/lualib.h"
}

#pragma comment (lib, "lua54.lib")
#pragma comment (lib, "WS2_32.lib")
#pragma comment (lib, "MSWSock.lib")

using namespace std;
using namespace chrono;