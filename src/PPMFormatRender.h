#pragma once

#include "RenderIface.h"

class PPMRenderConfig : public RenderConfigIface
{
    
};

class PPMFormatRender: public RenderIface
{
public:
    void render();
    void setImageDim(uint64_t _width, uint64_t _height);
    void configRender(RenderConfigIface& _config);

    void setPixel(uint64_t _row, uint64_t _col, vec3& vec3);
    void setPixelRow(uint64_t _row, vector<vec3>& _data);
    void setPixelCol(uint64_t _col, vector<vec3>& _data);
    void setImage(std::vector<std::vector<vec3>>& _data);
 
private:
    PPMRenderConfig m_config;
};