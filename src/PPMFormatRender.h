#pragma once

#include "RenderIface.h"
#include <string>

static const std::string PPM_FORMAT_P3 = "P3";

class PPMRenderConfig : public RenderConfigIface
{
public:
    void setPixelFormat(std::string _format) { m_pixelFormat = _format; }
    std::string getPixelFormat() { return m_pixelFormat; }

private:
    std::string m_pixelFormat;
};

class PPMFormatRender: public RenderIface
{
public:
    void render();
    void configRender(PPMRenderConfig& _config);

    void setPixel(uint64_t _row, uint64_t _col, color& vec3);
    void sumPixel(uint64_t _row, uint64_t _col, color& vec3);
    void avgPixel(uint64_t _row, uint64_t _col, int samples);
    void setPixelRow(uint64_t _row, std::vector<vec3>& _data);
    void setPixelCol(uint64_t _col, std::vector<vec3>& _data);
    void setImage(std::vector<std::vector<vec3> >& _data);
 
private:
    PPMRenderConfig m_config;
};

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
