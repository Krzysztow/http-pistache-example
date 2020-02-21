#!/bin/bash

function makeInDir() {
  local d="$1"
  echo "Creating directory $d and changing permissions"
  sudo mkdir -p "$d"
  sudo chmod a+rw "$d"
  echo "Finished"
}

set -e
set -u
set -x

BUILD_COMPILER_ARCH=$1
BUILD_DIR="`pwd`/build-${BUILD_COMPILER_ARCH}"

makeInDir "${BUILD_DIR}" "${BUILD_DIR}"
cd ${BUILD_DIR}

export CONAN_USER_HOME="/home/conan"
cmake --configure -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
cmake --build .

TARGET="bin/http-server"
echo "Build finished, target created in $TARGET"
