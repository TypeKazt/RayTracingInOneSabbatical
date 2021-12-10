#include "PPMFormatRender.h"

static const int imageHeight = 256;
static const int imageWidth = 256;

int main()
{
	PPMRenderConfig config;
	config.setImageDim(imageWidth, imageHeight);
	config.setPixelFormat(PPM_FORMAT_P3);

	PPMFormatRender ppm;
	ppm.configRender(config);

}