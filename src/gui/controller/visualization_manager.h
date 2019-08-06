// -----------------------------------------------------------------------------
//
// Copyright (C) The BioDynaMo Project.
// All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------

#ifndef GUI_VISUALIZATION_MANAGER_H_
#define GUI_VISUALIZATION_MANAGER_H_

#include "gui/view/visualization_frame.h"

namespace gui {

class VisManager {
 public:
  static VisManager& GetInstance() {
    static VisManager instance;
    return instance;
  }

  VisFrame* Init(const TGWindow* p) {
    fVisFrame = std::make_unique<VisFrame>(p);
    Pixel_t col;
    gClient->GetColorByName("black", col);
    fVisFrame->SetBackgroundColor(col);
    fVisFrame->Init();
    return fVisFrame.get();
  }

  void Update() {
    fVisFrame->Update();
  }

  void Reset() {
    fVisFrame->Reset();
  }

  void Enable(Bool_t flag = kTRUE) {
    enabled = flag;
    fVisFrame->EnableButtons(flag);
  }

  void SetRedCell(Long_t cellNumber, Bool_t flag) {
    Log::Info("Setting secretion cell:", cellNumber, ", flag:", flag);
    fVisFrame->SetRedCell(cellNumber, flag);
  }

  /// To be called from Execute() in bdm scheduler
  Bool_t IsEnabled() {
    return enabled;
  }

  void RedrawVisFrame() {
    fVisFrame->MapWindow();
    fVisFrame->Resize();
    fVisFrame->MapSubwindows();
    gClient->NeedRedraw(fVisFrame.get());
  }

 private:
  VisManager() {}
  VisManager(VisManager const&) = delete;
  VisManager& operator=(VisManager const&) = delete;

  std::unique_ptr<VisFrame> fVisFrame;
  Bool_t enabled = kFALSE;
};

}  // namespace gui

#endif  // GUI_VISUALIZATION_MANAGER_H_