#pragma once
#include "archiver.h"

void loadAssetsFromPreparedArchive(Archive& assetArchive);

void loadArchiveFromMainDir(Archive& assetArchive);
void loadArchiveFromFile(Archive& assetArchive);
void saveArchiveForRelease(Archive& assetArchive);