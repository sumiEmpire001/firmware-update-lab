# UpdateVerifier C++11 reference

Streaming firmware-transfer integrity exercise using FNV-1a and length bounds. FNV is NOT cryptographically secure: do not use this for firmware trust, OTA flashing, or production updates. Production requires authenticated signatures, rollback protection and bootloader validation.

Build on a host: `cmake -S cpp -B build && cmake --build build && ctest --test-dir build --output-on-failure`.

The header is standard C++11 and suitable for Arduino Uno / ESP32 algorithm integration, but no device firmware or GPIO sketch is included. For board use, supply validated sensor/input data, watchdogs and fail-safe outputs. Hardware and board toolchain builds are unverified.
