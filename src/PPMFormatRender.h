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
    void sumPixel(uint64_t _row, uint64_t _col, color& vec3, int samples);
    void setPixelRow(uint64_t _row, std::vector<vec3>& _data);
    void setPixelCol(uint64_t _col, std::vector<vec3>& _data);
    void setImage(std::vector<std::vector<vec3> >& _data);
 
private:
    PPMRenderConfig m_config;
};
