#pragma once
#include <cstdint>
#include <cstddef>
namespace firmware {
enum class State { Idle, Receiving, Verified, Failed };
enum class Error { None, InvalidManifest, InvalidChunk, OutOfOrder, Overflow, BadChecksum, WrongState };
struct Manifest { uint32_t version, size, checksum; };
class Receiver {
 public:
 explicit Receiver(uint32_t installed, uint32_t maxBytes=1048576) : installed_(installed), limit_(maxBytes) {}
 bool begin(Manifest m) {
  reset(); if(m.version<=installed_||m.size==0||m.size>limit_)return fail(Error::InvalidManifest);
  manifest_=m; state_=State::Receiving; return true;
 }
 bool append(const uint8_t* bytes,size_t length,uint32_t offset) {
  if(state_!=State::Receiving)return fail(Error::WrongState);
  if(!bytes||length==0||offset!=received_||length>manifest_.size-received_)return fail(Error::InvalidChunk);
  for(size_t i=0;i<length;++i){hash_^=bytes[i];hash_*=16777619u;}
  received_+=static_cast<uint32_t>(length);return true;
 }
 bool finish(){
  if(state_!=State::Receiving)return fail(Error::WrongState);
  if(received_!=manifest_.size||hash_!=manifest_.checksum)return fail(Error::BadChecksum);
  state_=State::Verified;return true;
 }
 void reset(){state_=State::Idle;error_=Error::None;received_=0;hash_=2166136261u;manifest_={0,0,0};}
 State state()const{return state_;} Error error()const{return error_;}
 uint32_t received()const{return received_;}
 uint32_t candidateVersion()const{return manifest_.version;}
 private:
 bool fail(Error e){state_=State::Failed;error_=e;return false;}
 uint32_t installed_,limit_,received_=0,hash_=2166136261u;
 Manifest manifest_={0,0,0}; State state_=State::Idle;Error error_=Error::None;
};
inline uint32_t fnv1a(const uint8_t* bytes,size_t n){uint32_t h=2166136261u;for(size_t i=0;i<n;++i){h^=bytes[i];h*=16777619u;}return h;}
}
