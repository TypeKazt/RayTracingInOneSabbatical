#pragma once

#include "stdint.h"
#include <vector>
#include "vec3.h"


class RenderConfigIface
{
public:

private:

};

class RenderIface
{
public:
    void render();
    void setImageWidthHeight(uint64_t _width, uint64_t _height);
    void setPixel(uint64_t _width, uint64_t _height, );
    void setPixelRow(uint64_t _row, vector<vec3>& _data);
    void setPixelRow(uint64_t _col, vector<vec3>& _data);
    void configRender(RenderConfig& _config);
};