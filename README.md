# Firmware Update Lab — educational C++11 streaming validator

Bounded streaming update-state engine with begin/append/finish/reset, size limits, sequential byte accounting and latched failures. FNV-1a is used **only to teach accidental-corruption checks**; it is not cryptographically secure.

Build and test: `cmake -S . -B build && cmake --build build && ctest --test-dir build --output-on-failure`.

**Arduino Uno / ESP32 limitations:** No flash writes, signatures, secure boot, partition switching, rollback, anti-rollback or power-loss recovery. Production OTA requires authenticated signed firmware and board-specific recovery. **Never install firmware based on this checksum.** Hardware not tested.