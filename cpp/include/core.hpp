#pragma once
#include <cstddef>
#include <cstdint>
namespace lord_sumi {
class UpdateVerifier {
 uint32_t hash_=2166136261u; uint32_t received_=0; uint32_t expectedLength_=0; uint32_t expectedHash_=0; bool active_=false; bool failed_=false;
public:
 bool begin(uint32_t length,uint32_t hash) { reset(); if(!length || length>1048576u) return false; expectedLength_=length;expectedHash_=hash;active_=true;return true; }
 bool append(const uint8_t* data,size_t size) {
  if(!active_||failed_||(!data&&size)||size>expectedLength_-received_){failed_=true;return false;}
  for(size_t i=0;i<size;++i){hash_^=data[i];hash_*=16777619u;} received_+=static_cast<uint32_t>(size);return true;
 }
 bool verified() const {return active_&&!failed_&&received_==expectedLength_&&hash_==expectedHash_;}
 void reset(){hash_=2166136261u;received_=expectedLength_=expectedHash_=0;active_=failed_=false;}
 uint32_t received() const {return received_;}
};
}