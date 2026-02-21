#include "AnimatedImageResource.hpp"

using namespace Hyprgraphics;

CAnimatedImageResource::CAnimatedImageResource(const std::string& path) : m_path(path) {
    ;
}

void CAnimatedImageResource::render() {
    CAnimatedImage image{m_path};
    if (!image.success())
        return;

    const size_t FRAMECOUNT = image.frameCount();
    m_frames.clear();
    m_frames.reserve(FRAMECOUNT);

    for (size_t i = 0; i < FRAMECOUNT; ++i)
        m_frames.emplace_back(image.frame(i));

    if (m_frames.empty() || !m_frames[0].cairoSurface)
        return;

    m_loopCount          = image.loopCount();
    m_animated           = image.isAnimated();
    m_asset.cairoSurface = m_frames[0].cairoSurface;
    m_asset.pixelSize    = image.canvasSize();
}

const std::vector<SAnimatedImageFrame>& CAnimatedImageResource::frames() const {
    return m_frames;
}

uint32_t CAnimatedImageResource::loopCount() const {
    return m_loopCount;
}

bool CAnimatedImageResource::isAnimated() const {
    return m_animated;
}
