#include "PPMFormatRender.h"
#include <iostream>

void PPMFormatRender::render()
{
	std::cout << m_config.getPixelFormat() << std::endl;
	std::cout << m_config.getImageWidth() << " " << m_config.getImageHeight() << std::endl;

	for (auto iRow = m_image.begin(); iRow != m_image.end(); ++iRow)
	{
		for (auto iCol = iRow->begin(); iCol != iRow->end(); ++iCol)
		{
			std::cout << static_cast<uint8_t>(iCol->x()) << " "
				<< static_cast<uint8_t>(iCol->y()) << " "
				<< static_cast<uint8_t>(iCol->z()) << "    ";
		}
		std::cout << std::endl;
	}
}

void PPMFormatRender::configRender(PPMRenderConfig& _config)
{
	m_config = _config;
	m_image.resize(m_config.getImageWidth());
	for (auto i : m_image)
	{
		i.resize(m_config.getImageHeight());
	}
}

void PPMFormatRender::setPixel(uint64_t _row, uint64_t _col, vec3& vec3)
{
	m_image[_row][_col] = vec3;
}

void PPMFormatRender::setPixelRow(uint64_t _row, std::vector<vec3>& _data)
{
}

void PPMFormatRender::setPixelCol(uint64_t _col, std::vector<vec3>& _data)
{
}

void PPMFormatRender::setImage(std::vector<std::vector<vec3>>& _data)
{
	for (uint64_t iRow = 0; iRow < m_image.size(); ++iRow)
	{
		for (uint64_t iCol = 0; iCol < m_image.size(); ++iCol)
		{
			m_image[iRow][iCol] = _data[iRow][iCol];
		}
	}
}

