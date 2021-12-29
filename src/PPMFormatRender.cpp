#include "PPMFormatRender.h"
#include "rtsabbatical.h"
#include <iostream>

void PPMFormatRender::render()
{
	std::cout << m_config.getPixelFormat() << std::endl;
	std::cout << m_config.getImageWidth() << " " << m_config.getImageHeight() << std::endl;
	std::cout << 255 << std::endl;

	for (auto iRow = m_image.begin(); iRow != m_image.end(); ++iRow)
	{
		for (auto iCol = iRow->begin(); iCol != iRow->end(); ++iCol)
		{
			std::cout << static_cast<int>(iCol->x()*255.99) << " "
				<< static_cast<int>(iCol->y()*255.99) << " "
				<< static_cast<int>(iCol->z()*255.99) << "\n";
		}
	}
}

void PPMFormatRender::configRender(PPMRenderConfig& _config)
{
	m_config = _config;
	m_image.resize(m_config.getImageHeight());
	uint64_t imageWidth = m_config.getImageWidth();
	for (auto i = m_image.begin(); i != m_image.end(); ++i)
	{
		i->resize(imageWidth);
	}
}

void PPMFormatRender::setPixel(uint64_t _row, uint64_t _col, color& _color)
{
	m_image[_row][_col] = _color;
}

void PPMFormatRender::sumPixel(uint64_t _row, uint64_t _col, color& _color)
{
		m_image[_row][_col] += _color;
}

void PPMFormatRender::avgPixel(uint64_t _row, uint64_t _col, int samples)
{
	auto colorScale = 1.0 / samples;
	auto summed = m_image[_row][_col]*colorScale;
	auto r = sqrt(summed.x());
	auto g = sqrt(summed.y());
	auto b = sqrt(summed.z());
	m_image[_row][_col] = vec3(r, g, b);
}

void PPMFormatRender::setPixelRow(uint64_t _row, std::vector<vec3>& _data)
{
}

void PPMFormatRender::setPixelCol(uint64_t _col, std::vector<vec3>& _data)
{
}

void PPMFormatRender::setImage(std::vector<std::vector<vec3> >& _data)
{
	for (uint64_t iRow = 0; iRow < m_image.size(); ++iRow)
	{
		for (uint64_t iCol = 0; iCol < m_image.size(); ++iCol)
		{
			m_image[iRow][iCol] = _data[iRow][iCol];
		}
	}
}

