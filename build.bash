#!/bin/bash
set -e

# set this to the root of your Retro68 build folder, e.g. ~/src/Retro68-build/
RETRO68_PATH=~/Documents/Code/Retro68-build/

################################################################################
echo "Building Fix-a-Fork-Carbon (PowerPC-only)..."

echo "Cleaning out previous builds..."
rm -rf build-ppc
mkdir build-ppc

echo "Compiling..."
cmake -S . -B build-ppc -DCMAKE_TOOLCHAIN_FILE=$RETRO68_PATH/toolchain/powerpc-apple-macos/cmake/retroppc.toolchain.cmake
cmake --build build-ppc

echo "Rez everything up..."

$RETRO68_PATH/toolchain/bin/Rez -DCFRAG_NAME="\"fix-a-fork-carbon\"" -t APPL -c FAF  --data build-ppc/fix-a-fork-carbon.pef build-ppc/fix-a-fork-carbon.r.rsrc.bin

echo "Finished building!"


