#ifndef WRAPGL_TEXTURE_HPP
#define WRAPGL_TEXTURE_HPP
#include "glm/glm.hpp" // IWYU pragma: keep
#include <vector>
extern "C" {
#include "stbi_image.h"
}
#include <filesystem>
#include <stdexcept>

namespace STB {
inline void setFlipVerticallyOnLoad(const bool flag) {
  stbi_set_flip_vertically_on_load(flag);
}

class ImageData {
private:
  unsigned char *m_Data;
  glm::uvec2 m_Dimension;
  unsigned int m_NumOfColorChannels;
  unsigned int m_ForcedChannels;

  ImageData(unsigned char *const data, const glm::uvec2 dimension,
            const unsigned int numOfColorChannels,
            const unsigned int forcedChannels)
      : m_Data(nullptr), m_Dimension(dimension),
        m_NumOfColorChannels(numOfColorChannels),
        m_ForcedChannels(forcedChannels) {
    m_Data = data;
  }

public:
  static ImageData load(const std::filesystem::path &path,
                        const unsigned int requiredChannels = 0) {
    glm::ivec2 dim;
    int noc;
    unsigned char *imageData = stbi_load(path.c_str(), &dim.x, &dim.y, &noc,
                                         static_cast<int>(requiredChannels));

    if (!imageData) {
      std::string errMsg = "Failed to load image using stb at path: ";
      errMsg += path;
      throw std::runtime_error(errMsg);
    }

    return ImageData(imageData, dim, static_cast<unsigned int>(noc),
                     requiredChannels + static_cast<unsigned int>(
                                            (requiredChannels == 0) * noc));
  }

public:
  ImageData() = delete;
  ImageData(const ImageData &other) = delete;
  ImageData &operator=(const ImageData &) = delete;

  ~ImageData() { stbi_image_free(m_Data); }

  const unsigned char *getDataPtr() const { return m_Data; }
  constexpr glm::uvec2 getDimension() const { return m_Dimension; }
  constexpr unsigned int getNumberOfChannels() const {
    return m_NumOfColorChannels;
  }
  constexpr unsigned int getForcedChannels() const { return m_ForcedChannels; }
};

} // namespace STB

namespace GL {
enum class TextureFormat { RGBA8, R8, RG8, RGB8, BGR8, BGRA8 };
enum class WrapDirection { S, T, R };
enum class WrapMode {
  CLAMP_TO_EDGE,
  CLAMP_TO_BORDER,
  MIRRORED_REPEAT,
  REPEAT,
  MIRRORED_CLAMP_TO_EDGE
};
enum class ScaleFilter { MIN, MAG };
enum class MinFilterMode {
  NEAREST,
  LINEAR,
  NEAREST_MIPMAP_NEAREST,
  LINEAR_MIPMAP_NEAREST,
  NEAREST_MIPMAP_LINEAR,
  LINEAR_MIPMAP_LINEAR
};
enum class MagFilterMode { NEAREST, LINEAR };

class Texture2D {
private:
  unsigned int m_TextureId;

  Texture2D(unsigned int textureId);

public:
  static Texture2D
  create(const glm::uvec2 dimensions,
         const GL::TextureFormat format = GL::TextureFormat::RGBA8,
         const unsigned int levels = 1);

  static Texture2D loadFromFile(const std::filesystem::path &path,
                                const unsigned int levels = 1);

  static std::vector<float> getDefaultRectTexCoords() {
    return {0, 0, 1, 0, 0, 1, 1, 1};
  }

public:
  Texture2D() = delete;
  ~Texture2D();

  void updateWrap(const GL::WrapDirection dir, const GL::WrapMode mode) const;
  void updateMinFilter(const GL::MinFilterMode mode) const;
  void updateMagFilter(const GL::MagFilterMode mode) const;

  void update(const void *const textureData, const GL::TextureFormat format,
              const glm::uvec2 offset, const glm::uvec2 dimensions,
              const unsigned int level = 0) const;
  void generateMipmaps() const;
  void bind(const unsigned int index) const;

  unsigned int getWidth() const;
  unsigned int getHeight() const;
  glm::uvec2 getDimension() const;
};

} // namespace GL

#endif
