#ifndef WRAPGL_SHAPES_HPP
#define WRAPGL_SHAPES_HPP
#include <glm/glm.hpp> // IWYU pragma: keep
#include <vector>

struct Rectangle {
  glm::vec2 pos;
  glm::vec2 dim;
  Rectangle() : pos(0), dim(0) {}
  Rectangle(const glm::vec2 pos, const glm::vec2 dim) : pos(pos), dim(dim) {}
  Rectangle(const float x, const float y, const float width, const float height)
      : pos(x, y), dim(width, height) {}
  Rectangle(const Rectangle &r) : pos(r.pos), dim(r.dim) {}

  glm::vec2 bl() const { return pos; }
  glm::vec2 br() const { return glm::vec2(pos.x + dim.x, pos.y); }
  glm::vec2 tl() const { return glm::vec2(pos.x, pos.y + dim.y); }
  glm::vec2 tr() const { return pos + dim; }

  bool operator==(const Rectangle &r) const {
    return pos == r.pos && dim == r.dim;
  }
  bool operator!=(const Rectangle &r) const { return !(*this == r); }

  std::vector<float> inBuffer() const {
    return {bl().x, bl().y, br().x, br().y, tl().x, tl().y, tr().x, tr().y};
  }
};
#endif
