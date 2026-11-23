#include "FirmwareUpdate.h"
#include <cassert>
using namespace lord_sumi;
int main(){
 FirmwareUpdate u;const uint8_t b[]={1,2,3};uint32_t h=2166136261u;
 for(unsigned i=0;i<3;++i){h^=b[i];h*=16777619u;}
 assert(u.begin(3));assert(u.append(b,2));assert(u.append(b+2,1));assert(u.finish(h));
 assert(u.state()==UpdateStatus::Verified);
 u.reset();assert(u.begin(3));assert(!u.append(b,4));assert(u.state()==UpdateStatus::Fault);
 assert(!u.begin(3));u.reset();assert(!u.begin(0));u.reset();
 assert(u.begin(3));assert(u.append(b,2));assert(!u.finish(h));assert(u.state()==UpdateStatus::Fault);
}
