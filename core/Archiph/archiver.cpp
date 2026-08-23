#include "archiver.h"

head_table readArchiveHeadTable(CFile& file) {
    return {
        file.read<uint32_t>(),
        file.read<uint32_t>(),
        file.read<uint32_t>(),
        file.read<uint32_t>(),
        file.read<uint32_t>(),
        file.read<uint32_t>(),
        file.read<uint8_t>()
    };
}

bool Archive::loadFromFile(Archive& archive, const char* filename) {
    CFile file = openCFile(filename);
    if (file.isEmpty()) return false;

    uint64_t signature = 0;
    if (readCFile(&signature, sizeof(signature), file)) return false;
    if (signature != 0x4352416E61627255ULL) return false;

    head_table hTable;
    if (readCFile(&hTable, sizeof(hTable), file)) return false;
    if (hTable.version != 1) return false;
    if (hTable.filesCount == 0) return false;

    std::vector<metadata> metadataTable(hTable.filesCount);
    for(auto& meta : metadataTable) {
        if(readCFile(&meta, sizeof(meta), file)) return false;
    }

	archive.files.clear();
    archive.files.reserve(hTable.filesCount);
    printf("hTable.filesCount %d\n", hTable.filesCount);
    for (size_t i = 0; i < hTable.filesCount; ++i) {
        const metadata& meta = metadataTable[i];
        CFile outputFile = createCFile();
        seekCFile(file, static_cast<int>(meta.offset), SEEK_SET);
        if (meta.compressed_size > 0) {
            std::vector<char> buffer(meta.compressed_size);
            if (readCFile(buffer.data(), static_cast<int>(meta.compressed_size), file)) return false;
            writeCFile(buffer.data(), static_cast<int>(meta.compressed_size), outputFile);
            seekCFile(outputFile, 0, SEEK_SET);
        }
        archive.files.push_back(std::move(outputFile));
    }
    return true;
}





CFile Archive::toFile() {
    CFile archive = createCFile();

    constexpr uint64_t signature = 0x4352416E61627255ULL;

    head_table hTable{};
    hTable.filesCount = files.size();
    hTable.max_path_length = 0;
    hTable.max_file_size = 0;
    hTable.total_files_size = 0;
    hTable.version = 1;
    for (size_t i = 0; i < hTable.filesCount; ++i) {
        const CFile& inputFile = files[i];
        const uint32_t pathLength = 0;
        const uint32_t fileSize = static_cast<uint32_t>(inputFile.size());
        hTable.max_path_length = std::max(hTable.max_path_length, pathLength);
        hTable.max_file_size = std::max(hTable.max_file_size, fileSize);
        hTable.total_files_size += fileSize;
    }


    std::vector<metadata> mTable(files.size());
    for (size_t i = 0; i < files.size(); ++i) {
        metadata& meta = mTable[i];

        meta.offset = 0;
        meta.size = static_cast<uint32_t>(files[i].size());
        meta.compressed_size = meta.size;
        meta.compression = 0;
    }

    const uint32_t signatureSize = sizeof(signature);
    const uint32_t headTableSize = sizeof(head_table);
    const uint32_t metadataSize = static_cast<uint32_t>(mTable.size() * sizeof(metadata));
    const uint32_t metadataStart = signatureSize + headTableSize;

    uint32_t fileOffset = metadataStart + metadataSize;;
    for (metadata& meta : mTable) {
        meta.offset = fileOffset;
        fileOffset += meta.compressed_size;
    }
    
    writeCFile(&signature, sizeof(signature), archive);
    writeCFile(&hTable, sizeof(hTable), archive);
    if (!mTable.empty()) {
        writeCFile(mTable.data(), metadataSize, archive);
    }
    for (size_t i = 0; i < files.size(); ++i) {
        CFile& inputFile = files[i];
        const int fileSize = inputFile.size();
        if (fileSize <= 0) continue;

        seekCFile(inputFile, 0, SEEK_SET );
        writeCFile(inputFile.getPtr(), fileSize, archive);
    }
    return archive;
}




CFile& Archive::getFile(int index) {
	return files[index];
}

void Archive::addFile(CFile&& file) {
	if(file.isEmpty()) return;
    files.push_back(std::move(file));
}

void Archive::addFile(const char* path) {
	CFile file = openCFile(path);
	if(file.isEmpty()) return;
	
	files.push_back(std::move(file));
}