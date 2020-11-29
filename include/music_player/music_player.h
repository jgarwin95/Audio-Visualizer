//
// Created by garwi on 11/27/2020.
//

#ifndef MUSIC_VISUALIZER_SRC_MUSIC_PLAYER_MUSIC_PLAYER_H_
#define MUSIC_VISUALIZER_SRC_MUSIC_PLAYER_MUSIC_PLAYER_H_

#include "cinder/audio/Voice.h"
#include "cinder/audio/audio.h"

using namespace ci;

namespace music_visualizer {

class MusicPlayer {
 public:
  MusicPlayer() = default;
  void LoadMusic(const fs::path& path);
  void PlayMusic();
  float GetDecibelLevel();

 private:
  audio::VoiceRef music_;
  audio::MonitorSpectralNode		spectral_node_;
  audio::MonitorSpectralNodeRef	mMonitorSpectralNode_;
  audio::MonitorNodeRef monitor_node_;
  audio::BufferPlayerNodeRef		mBufferPlayerNode_;
};

} //namespace music_visualizer

#endif //MUSIC_VISUALIZER_SRC_MUSIC_PLAYER_MUSIC_PLAYER_H_
