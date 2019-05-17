//
// Created by matth on 05/01/2019.
//

#ifndef NOVELRT_NOVELIMAGERECT_H
#define NOVELRT_NOVELIMAGERECT_H

#include "RGBAConfig.h"
#include "NovelRenderObject.h"

namespace NovelRT {

class NovelImageRect : public NovelRenderObject {
public:
  NovelImageRect(NovelLayeringService* layeringService, const float& screenScale,
                 const std::string_view imageDir, const NovelCommonArgs& args, NovelRenderingService* renderingService);

  void drawObject() const final;
  void setScale(const GeoVector<float>& value) final;

private:
  std::string _imageDir;
  int _imageHandle;
  NVGpaint _paint;
  int _width;
  int _height;

};

}
#endif //NOVELRT_NOVELIMAGERECT_H