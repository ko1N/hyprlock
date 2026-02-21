#pragma once

#include <hyprgraphics/image/AnimatedImage.hpp>
#include <hyprgraphics/resource/resources/AsyncResource.hpp>

#include <cstdint>
#include <string>
#include <vector>

class CAnimatedImageResource : public Hyprgraphics::IAsyncResource {
  public:
    CAnimatedImageResource(const std::string& path);
    virtual ~CAnimatedImageResource() = default;

    virtual void                                          render();

    const std::vector<Hyprgraphics::SAnimatedImageFrame>& frames() const;
    uint32_t                                              loopCount() const;
    bool                                                  isAnimated() const;

  private:
    std::string                                    m_path;
    std::vector<Hyprgraphics::SAnimatedImageFrame> m_frames;
    uint32_t                                       m_loopCount = 0;
    bool                                           m_animated  = false;
};
