#pragma once

#include "vec3.h"

#include "stdint.h"
#include <vector>


class RenderConfigIface
{
public:
    void setImageDim(uint64_t _width, uint64_t _height) { m_imageWidth = _width; m_imageHeight = _height; }
    uint64_t getImageWidth() { return m_imageWidth; }
    uint64_t getImageHeight() { return m_imageHeight; }

protected:
    uint64_t m_imageWidth;
    uint64_t m_imageHeight;
};

class RenderIface
{
public:
    void render();
    void configRender(RenderConfigIface& _config);

    void setPixel(uint64_t _row, uint64_t _col, color& vec3);
    void setPixelRow(uint64_t _row, std::vector<vec3>& _data);
    void setPixelCol(uint64_t _col, std::vector<vec3>& _data);
    void setImage(std::vector<std::vector<vec3> >& _data);

protected:
    std::vector<std::vector<vec3> > m_image;
};
