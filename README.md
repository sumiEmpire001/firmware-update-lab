# Firmware Update Lab — C++11 transfer validation core

A bounded, allocation-free firmware **transfer validator** for Arduino/ESP32 experiments. It rejects downgrade attempts, empty/oversized manifests, out-of-order chunks, null data, incomplete transfers and mismatched FNV-1a checksums. State transitions fail closed. The example only lights an LED after validating sample bytes.

## Host tests
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Hardware and security limitations
**Do not use this to install real firmware.** FNV-1a is a non-cryptographic corruption check, **not** authenticity or tamper protection. Production OTA requires signed images with trusted public keys, secure boot, protected anti-rollback state, A/B slots, power-loss recovery, watchdogs, flash alignment and transport authentication. This lab never writes flash or actuates devices. The Arduino example uses LED_BUILTIN; check board include paths and board support before compiling. Host CI checks C++ only, not board toolchains or hardware. No Python implementation existed in this previously planned repository.
