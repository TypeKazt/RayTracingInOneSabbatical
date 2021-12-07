#include "PPMFormatRender.h"
#include <iostream>

void PPMFormatRender::render()
{
	std::cout << m_config.getPixelFormat() << std::endl;
	std::cout << m_config.getImageWidth() << " " << m_config.getImageHeight() << std::endl;
}

void PPMFormatRender::configRender(RenderConfigIface& _config)
{
	m_config = static_cast<PPMRenderConfig>(_config);
}

void PPMFormatRender::setPixel(uint64_t _row, uint64_t _col, vec3& vec3)
{
}

void PPMFormatRender::setPixelRow(uint64_t _row, std::vector<vec3>& _data)
{
}

void PPMFormatRender::setPixelCol(uint64_t _col, std::vector<vec3>& _data)
{
}

void PPMFormatRender::setImage(std::vector<std::vector<vec3>>& _data)
{
}

