#include "core.hpp"
#include <cassert>
int main(){lord_sumi::UpdateVerifier v; const uint8_t b[]={1,2,3};uint32_t h=2166136261u;for(auto x:b){h^=x;h*=16777619u;}assert(v.begin(3,h));assert(v.append(b,2));assert(!v.verified());assert(v.append(b+2,1));assert(v.verified());assert(!v.append(b,1));assert(!v.verified());assert(!v.begin(0,h));}