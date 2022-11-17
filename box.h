#pragma once
#include "vector.h"

typedef struct Box{
    Vector inf, sup;
}Box;

Box BoxInit(Vector inf, Vector sup);