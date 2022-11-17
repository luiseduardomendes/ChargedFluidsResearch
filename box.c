#include "box.h"

Box BoxInit(Vector inf, Vector sup){
    Box box;
    if (inf.x <= sup.x && inf.y <= sup.y && inf.z <= sup.z){
        box.inf = inf;
        box.sup = sup;
    }
    return box;
}