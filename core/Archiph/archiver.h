#pragma once
#include "stdlibInclude.h"
#include "FileSystem.h"

//structures
struct head_table {
	uint32_t offset_table_offset;
	uint32_t filesCount;
	uint32_t max_path_length;
	uint32_t max_file_size;
	uint32_t total_size;
	uint32_t total_files_size;
	uint8_t  version;
};

struct metadata {
	uint32_t offset;
	uint32_t size;
	uint32_t compressed_size;
	uint8_t compression;
};


class Archive {
public:
	CFile 	toFile();
	CFile& 	getFile(int index);
	void 	addFile(const char* path);
	void 	addFile(CFile&& file);

public:
	static bool loadFromFile(Archive& archive, const char* filename);
private:
	std::vector<CFile> 			files;
};