#define STB_IMAGE_IMPLEMENTATION
#include "texture.hpp"
#include "glad/glad.h"

GL::Texture2D::Texture2D(unsigned int textureId) : m_TextureId(textureId) {}

GL::Texture2D::~Texture2D() { glDeleteTextures(1, &m_TextureId); }

constexpr unsigned int glInternalFormat(const GL::TextureFormat format) {
  return (format == GL::TextureFormat::RGBA8) * GL_RGBA8;
}

GL::Texture2D GL::Texture2D::create(const glm::uvec2 dimensions,
                                    const GL::TextureFormat format,
                                    const unsigned int levels) {
  unsigned int textureId;
  glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
  if (format != GL::TextureFormat::RGBA8)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTextureStorage2D(textureId, levels, glInternalFormat(format), dimensions.x,
                     dimensions.y);

  return GL::Texture2D(textureId);
}

// NOTE: You may not always want to sample using unsigned normalized floats.
// And thus you must support integer and signed normalized floats as well.
// But find how wrapgl will do that later. none of the business now...
// Also, i'm enough diverted from life. I had to make a freaking video series,
// But then logo and fingerprint-connected and now wrapgl...
constexpr unsigned int
glInternalFormatWithNumberOf8bitChannels(const unsigned int noc) {
  return (noc == 1) * GL_R8 + (noc == 2) * GL_RG8 + (noc == 3) * GL_RGB8 +
         (noc == 4) * GL_RGBA8;
}

constexpr unsigned int
glExternalFormatWithNumberOf8bitChannels(const unsigned int noc) {
  return (noc == 1) * GL_RED + (noc == 2) * GL_RG + (noc == 3) * GL_RGB +
         (noc == 4) * GL_RGBA;
}

GL::Texture2D GL::Texture2D::loadFromFile(const std::filesystem::path &path,
                                          const unsigned int levels) {
  STB::ImageData data = STB::ImageData::load(path);

  unsigned int textureId;
  glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
  glTextureStorage2D(
      textureId, levels,
      glInternalFormatWithNumberOf8bitChannels(data.getForcedChannels()),
      data.getDimension().x, data.getDimension().y);

  if (data.getForcedChannels() != 4)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTextureSubImage2D(
      textureId, 0, 0, 0, data.getDimension().x, data.getDimension().y,
      glExternalFormatWithNumberOf8bitChannels(data.getForcedChannels()),
      GL_UNSIGNED_BYTE, data.getDataPtr());

  return Texture2D(textureId);
}

constexpr unsigned int glDir(const GL::WrapDirection dir) {
  return (dir == GL::WrapDirection::S) * GL_TEXTURE_WRAP_S +
         (dir == GL::WrapDirection::T) * GL_TEXTURE_WRAP_T +
         (dir == GL::WrapDirection::R) * GL_TEXTURE_WRAP_R;
}

constexpr unsigned int glMode(const GL::WrapMode mode) {
  return (mode == GL::WrapMode::REPEAT) * GL_REPEAT +
         (mode == GL::WrapMode::MIRRORED_REPEAT) * GL_MIRRORED_REPEAT +
         (mode == GL::WrapMode::CLAMP_TO_EDGE) * GL_CLAMP_TO_EDGE +
         (mode == GL::WrapMode::MIRRORED_CLAMP_TO_EDGE) *
             GL_MIRROR_CLAMP_TO_EDGE +
         (mode == GL::WrapMode::CLAMP_TO_BORDER) * GL_CLAMP_TO_BORDER;
}

void GL::Texture2D::updateWrap(const GL::WrapDirection dir,
                               const GL::WrapMode mode) const {
  glTextureParameteri(m_TextureId, glDir(dir), glMode(mode));
}

constexpr unsigned int glFilterMode(const GL::MinFilterMode mode) {
  return (mode == GL::MinFilterMode::LINEAR) * GL_LINEAR +
         (mode == GL::MinFilterMode::LINEAR_MIPMAP_LINEAR) *
             GL_LINEAR_MIPMAP_LINEAR +
         (mode == GL::MinFilterMode::LINEAR_MIPMAP_NEAREST) *
             GL_LINEAR_MIPMAP_NEAREST +
         (mode == GL::MinFilterMode::NEAREST) * GL_NEAREST +
         (mode == GL::MinFilterMode::NEAREST_MIPMAP_NEAREST) *
             GL_NEAREST_MIPMAP_NEAREST +
         (mode == GL::MinFilterMode::NEAREST_MIPMAP_LINEAR) *
             GL_NEAREST_MIPMAP_LINEAR;
}

constexpr unsigned int glFilterMode(const GL::MagFilterMode mode) {
  return (mode == GL::MagFilterMode::LINEAR) * GL_LINEAR +
         (mode == GL::MagFilterMode::NEAREST) * GL_NEAREST;
}

void GL::Texture2D::updateMinFilter(const GL::MinFilterMode mode) const {

  glTextureParameteri(m_TextureId, GL_TEXTURE_MIN_FILTER, glFilterMode(mode));
}

void GL::Texture2D::updateMagFilter(const GL::MagFilterMode mode) const {
  glTextureParameteri(m_TextureId, GL_TEXTURE_MAG_FILTER, glFilterMode(mode));
}

constexpr unsigned int glExternalFormat(const GL::TextureFormat format) {
  return (format == GL::TextureFormat::RGBA8) * GL_RGBA;
}

constexpr unsigned int glFormatType(const GL::TextureFormat format) {
  return (format == GL::TextureFormat::RGBA8) * GL_UNSIGNED_BYTE;
}

void GL::Texture2D::update(const void *const textureData,
                           const GL::TextureFormat format,
                           const glm::uvec2 offset, const glm::uvec2 dimension,
                           const unsigned int level) const {
  glTextureSubImage2D(m_TextureId, level, offset.x, offset.y, dimension.x,
                      dimension.y, glExternalFormat(format),
                      glFormatType(format), textureData);
}

void GL::Texture2D::generateMipmaps() const {
  glGenerateTextureMipmap(m_TextureId);
}

void GL::Texture2D::bind(const unsigned int index) const {
  glBindTextureUnit(index, m_TextureId);
}
