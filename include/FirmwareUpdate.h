#pragma once
#include <stdint.h>
#include <stddef.h>
namespace lord_sumi {
enum class UpdateStatus { Ready, Receiving, Verified, Invalid, Fault };
class FirmwareUpdate {
  uint32_t expected_, checksum_, bytes_; bool failed_; UpdateStatus state_;
public:
  FirmwareUpdate():expected_(0),checksum_(2166136261u),bytes_(0),failed_(false),state_(UpdateStatus::Ready){}
  UpdateStatus state() const{return state_;}
  uint32_t received() const{return bytes_;}
  void reset(){expected_=0;checksum_=2166136261u;bytes_=0;failed_=false;state_=UpdateStatus::Ready;}
  bool begin(uint32_t size){
    if(failed_ || state_!=UpdateStatus::Ready || size==0 || size>1048576u){failed_=true;state_=UpdateStatus::Fault;return false;}
    expected_=size;state_=UpdateStatus::Receiving;return true;
  }
  bool append(const uint8_t* data,size_t n){
    if(failed_ || state_!=UpdateStatus::Receiving || !data || n==0 || n>expected_-bytes_){failed_=true;state_=UpdateStatus::Fault;return false;}
    for(size_t i=0;i<n;++i){checksum_^=data[i];checksum_*=16777619u;}
    bytes_+=(uint32_t)n;return true;
  }
  bool finish(uint32_t expected_fnv1a){
    if(failed_ || state_!=UpdateStatus::Receiving || bytes_!=expected_ || checksum_!=expected_fnv1a){failed_=true;state_=UpdateStatus::Fault;return false;}
    state_=UpdateStatus::Verified;return true;
  }
};
}
