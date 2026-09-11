#include "IOSystem.h"

bool IOSystem::readBMP(TextureStruct& out, CFile& f) {
	if(f.isEmpty()) return false;

	const uint16_t bfType       = f.read<uint16_t>();
	const uint32_t bfSize       = f.read<uint32_t>();
	const uint16_t bfReserved1  = f.read<uint16_t>();
	const uint16_t bfReserved2  = f.read<uint16_t>();
	const uint32_t bfOffBits    = f.read<uint32_t>();
	
	if(bfType != 0x4D42) return false;
	
	const uint32_t biSize            = f.read<uint32_t>();
	const int32_t  biWidth           = f.read<int32_t>();
	const int32_t  biHeight          = f.read<int32_t>();
	const uint16_t biPlanes          = f.read<uint16_t>();
	const uint16_t biBitCount        = f.read<uint16_t>();
	const uint32_t biCompression     = f.read<uint32_t>();
	const uint32_t biSizeImage       = f.read<uint32_t>();
	const int32_t  biXPelsPerMeter   = f.read<int32_t>();
	const int32_t  biYPelsPerMeter   = f.read<int32_t>();
	const uint32_t biClrUsed         = f.read<uint32_t>();
	const uint32_t biClrImportant    = f.read<uint32_t>();

	if(biSize != 40) return false;
	if(biWidth <= 0 || biHeight == 0) return false;
	if(biPlanes != 1) return false;
	if(biBitCount != 24 && biBitCount != 32) return false;
	if(biCompression != 0)  return false;

	
	//move to main data
	seekCFile(f, bfOffBits, SEEK_SET);
	
	//set texture's data
	out.resize(biWidth, biHeight);
	int* pixels = out.getData();
	
	//helping values
	char temp = 0;
	unsigned int index = 0;
	
    for(int y = 0; y < biHeight; y++)  {
		// left_bottom_corner index -> left_to_corner index
		//index = (biHeight - y - 1) * biWidth;
		
        for(int x = 0; x < biWidth; x++)  {
			int r;
			readCFile(&r, biBitCount / 8, f);
			char* bytes = reinterpret_cast<char*>(&r);
			std::swap(bytes[0], bytes[2]);
			if(biBitCount < 32) {
				bytes[3] = 0xff;
			}
			pixels[index] = r;
			index++;
        }
		
		//skip offset
		int rowBytes = (biBitCount / 8) * biWidth;
		int padding = (4 - (rowBytes % 4)) % 4;
		seekCFile(f, padding, SEEK_CUR);
    }
	
	return true;
}

bool IOSystem::writeBMP(const TextureStruct& texture, CFile& file) {
	if(!texture.valid()) return false;
	file = createCFile();

	const uint16_t bitsPerPixel = 32;
	const uint32_t bytesPerPixel = bitsPerPixel / 8;

	const uint32_t rowSize = texture.width() * bytesPerPixel;
	const uint32_t imageSize = rowSize * texture.height();
	const uint32_t pixelOffset = 14 + 40;
	const uint32_t fileSize = pixelOffset + imageSize;

	file.write<uint16_t>(0x4D42);
	file.write<uint32_t>(fileSize);
	file.write<uint16_t>(0);
	file.write<uint16_t>(0);
	file.write<uint32_t>(pixelOffset);

	file.write<uint32_t>(40); 
	file.write<int32_t>(texture.width());
	file.write<int32_t>(texture.height());

	file.write<uint16_t>(1);
	file.write<uint16_t>(bitsPerPixel);
	file.write<uint32_t>(0); 
	file.write<uint32_t>(imageSize);

	file.write<int32_t>(0); 
	file.write<int32_t>(0);
	file.write<uint32_t>(0); 
	file.write<uint32_t>(0);

	uint32_t* pixels = (uint32_t*)texture.getData();
	for(int y = 0; y < texture.height(); ++y) {
		for(int x = 0; x < texture.width(); ++x) {
			uint32_t pixel = pixels[y * texture.width() + x];
			file.write<uint32_t>(pixel);
		}
	}
	return true;
}