#include "FirmwareUpdate.h"
#include <cstdlib>
#include <iostream>
using namespace firmware;
void check(bool x){if(!x){std::cerr<<"FAIL\n";std::exit(1);}}
int main(){
 const uint8_t data[]={1,2,3,4,5};const auto hash=fnv1a(data,5);
 Receiver r(3,10);
 check(!r.begin({3,5,hash})&&r.state()==State::Failed);
 check(!r.begin({4,11,hash}));
 check(r.begin({4,5,hash}));
 check(r.append(data,2,0));check(r.append(data+2,3,2));check(r.finish());
 check(r.state()==State::Verified&&r.received()==5);
 check(!r.append(data,1,5)&&r.state()==State::Failed);
 check(r.begin({4,5,hash}));check(!r.append(data,2,1));
 check(r.begin({4,5,hash}));check(r.append(data,4,0));check(!r.finish());
 check(r.begin({4,5,hash+1}));check(r.append(data,5,0));check(!r.finish());
 check(r.begin({4,5,hash}));check(!r.append(nullptr,1,0));
 check(r.begin({4,5,hash}));check(!r.append(data,6,0));
 std::cout<<"firmware tests passed\n";
}
