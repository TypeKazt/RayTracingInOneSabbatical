#include "PPMFormatRender.h"
#include "vec3.h"

static const int imageHeight = 256;
static const int imageWidth = 256;

int main()
{
	PPMRenderConfig config;
	config.setImageDim(imageWidth, imageHeight);
	config.setPixelFormat(PPM_FORMAT_P3);

	PPMFormatRender ppm;
	ppm.configRender(config);

	for (int i = 0; i < imageWidth; ++i)
	{
		for (int j = 0; j < imageHeight; ++j)
		{
			color pixel(imageWidth - i, imageHeight - j, 100);
			ppm.setPixel(j, i, pixel);
		}
	}
	ppm.render();

	return 0;
}