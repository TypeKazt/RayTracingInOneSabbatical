#pragma once

#include "RenderIface.h"

class PPMFormatRender: public RenderIface
{

public:
    void render();
    void setImageWidthHeight(uint64_t _width, uint64_t _height);
    void setPixel(uint64_t _width, uint64_t _height, );


};