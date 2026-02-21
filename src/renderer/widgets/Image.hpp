#pragma once

#include "IWidget.hpp"
#include "../../defines.hpp"
#include "../../helpers/Color.hpp"
#include "../../helpers/Math.hpp"
#include "../../config/ConfigDataValues.hpp"
#include "../../core/Timer.hpp"
#include "Shadowable.hpp"
#include <string>
#include <filesystem>
#include <unordered_map>
#include <any>
#include <cstdint>
#include <vector>

struct SPreloadedAsset;
class COutput;

class CImage : public IWidget {
  public:
    CImage() = default;
    ~CImage();

    void         registerSelf(const ASP<CImage>& self);

    virtual void configure(const std::unordered_map<std::string, std::any>& props, const SP<COutput>& pOutput);
    virtual bool draw(const SRenderData& data);
    virtual void onAssetUpdate(ResourceID id, ASP<CTexture> newAsset);

    virtual CBox getBoundingBoxWl() const;
    virtual void onClick(uint32_t button, bool down, const Vector2D& pos);
    virtual void onHover(const Vector2D& pos);

    void         reset();

    void         renderUpdate();
    void         onTimerUpdate();
    void         plantTimer();

    void         onAnimationTimerUpdate();
    void         plantAnimationTimer(uint32_t delayMs);
    void         resetAnimationState();
    void         initializeAnimationPlayback();

  private:
    AWP<CImage>                     m_self;

    CFramebuffer                    imageFB;

    int                             size     = 0;
    int                             rounding = 0;
    double                          border   = 0;
    double                          angle    = 0;
    CGradientValueData              color;
    Vector2D                        pos;
    Vector2D                        configPos;

    std::string                     halign, valign, path;

    bool                            firstRender = true;

    int                             reloadTime;
    std::string                     reloadCommand;
    std::string                     onclickCommand;

    std::filesystem::file_time_type modificationTime;
    size_t                          m_imageRevision = 0;

    ASP<CTimer>                     imageTimer;
    ASP<CTimer>                     animationTimer;

    struct SAnimationFrame {
        ASP<CTexture> texture;
        uint32_t      durationMs = 0;
    };

    std::vector<SAnimationFrame> animationFrames;
    uint32_t                     animationLoopCount     = 0;
    uint32_t                     animationLoopsComplete = 0;
    size_t                       animationFrameIndex    = 0;
    bool                         animationInitialized   = false;

    Vector2D                     viewport;
    std::string                  stringPort;

    ResourceID                   resourceID        = 0;
    bool                         m_pendingResource = false;

    ASP<CTexture>                asset = nullptr;
    CShadowable                  shadow;
};
