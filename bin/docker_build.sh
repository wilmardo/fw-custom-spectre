#!/usr/bin/env bash
# Build (or reuse) a disposable amd64 Ubuntu 24.04 container with the ARM toolchain,
# Java, mass-storage image tools, and 32-bit multilib installed, then run the
# firmware build in it.
#
# Useful on macOS since compile_firmware.sh relies on GNU `realpath --relative-to`,
# which BSD/macOS realpath doesn't support.
#
# Forced to --platform=linux/amd64 (emulated via QEMU on Apple Silicon) because two
# pieces of the rusEFI build are x86-only and have no arm64 equivalent:
#   - the PC simulator is compiled with `-m32`, and arm64 GCC has no x86 multilib at all
#   - misc/encedo_hex2dfu/hex2dfu.bin is a prebuilt x86_64 ELF (used for the .srec step)
#
# Usage:
#   bin/docker_build.sh                  # runs ./compile_firmware.sh
#   bin/docker_build.sh ./compile_firmware.sh clean
#   bin/docker_build.sh bash             # drop into a shell in the container

set -euo pipefail

IMAGE_TAG=spectre-fw-builder
REPO_ROOT=$(cd "$(dirname "$0")/.."; pwd -P)
PLATFORM=linux/amd64

docker build --platform "$PLATFORM" -t "$IMAGE_TAG" -f - "$REPO_ROOT" <<'EOF'
FROM ubuntu:24.04
RUN dpkg --add-architecture i386 && apt-get update -qq && apt-get install -y -qq \
      gcc-arm-none-eabi make git python3 zip curl bc \
      default-jdk-headless dosfstools p7zip-full mtools \
      gcc-multilib g++-multilib libc6-dbg:i386 \
    && rm -rf /var/lib/apt/lists/*
EOF

if [ "$#" -eq 0 ]; then
  set -- ./compile_firmware.sh
fi

docker run --rm --platform "$PLATFORM" -v "$REPO_ROOT:/work" -w /work "$IMAGE_TAG" "$@"
