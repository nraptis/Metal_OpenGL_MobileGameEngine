#include "AssetWadGameInterface.hpp"

AssetWadGameInterface::AssetWadGameInterface() {
    
}

AssetWadGameInterface::~AssetWadGameInterface() {
    
}

void AssetWadGameInterface::Load() {
    gImageBundler.StartBundle("bndl_progress_bars");
    gImageBundler.mKeepAllAlpha = true;
    
    mProgressBarEmpty.Load("progress_empty");
    mProgressBarFull.Load("progress_filled");
    mProgressBarShine.Load("progress_shine");
    mProgressBarStroke.Load("progress_stroke");
    
    gImageBundler.mRepeatH = true;
    mProgressLoopBubbles.Load("progress_loop_bubbles");
    mProgressLoopStripes.Load("progress_loop_stripes");
    gImageBundler.mRepeatH = false;
    
    gImageBundler.EndBundle();
    gImageBundler.mKeepAllAlpha = false;
}

void AssetWadGameInterface::Unload() {
    mProgressBarEmpty.Kill();
    mProgressBarFull.Kill();
    mProgressBarShine.Kill();
    mProgressBarStroke.Kill();
    mProgressLoopBubbles.Kill();
    mProgressLoopStripes.Kill();
}

