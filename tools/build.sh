#!/bin/bash
set -e

PLATFORM=${1:-windows}
PROJECT_PATH=${2}
ENGINE_PATH=${3}
BUILD_PATH=${4}
PROJECT_NAME=${5}

DOCKER_BUILD_DIR="/workspace"
CONTAINER_PROJECT_PATH="../project"

echo "Building for $PLATFORM..."
echo "Engine:  $ENGINE_PATH"
echo "Project: $PROJECT_PATH"
echo "Build:   $BUILD_PATH"
echo "Name:    $PROJECT_NAME"

rsync -a --delete \
    --exclude 'build' \
    --exclude '.git' \
    --exclude '.CMakeFiles' \
    "$ENGINE_PATH/" \
    "$DOCKER_BUILD_DIR/"

rsync -a --delete \
    "$PROJECT_PATH/" \
    "$CONTAINER_PROJECT_PATH/"

cmake --preset "$PLATFORM" \
    -DPROJECT_PATH="$CONTAINER_PROJECT_PATH" \
    -DPROJECT_NAME="$PROJECT_NAME"

cmake --build "$DOCKER_BUILD_DIR/.CMakeFiles"

rsync -a --delete \
    "$DOCKER_BUILD_DIR/build/" \
    "$BUILD_PATH/"

echo "Build finished."