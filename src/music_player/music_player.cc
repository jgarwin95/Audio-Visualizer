//
// Created by garwi on 11/27/2020.
//

#include "music_player/music_player.h"

namespace music_visualizer {

void MusicPlayer::LoadMusic(const fs::path& path) {
  auto ctx = audio::Context::master();

  audio::SourceFileRef sourceFile = audio::load( loadFile(path), ctx->getSampleRate() );
  // load the entire sound file into a BufferRef, and construct a BufferPlayerNode with this.
  audio::BufferRef buffer = sourceFile->loadBuffer();
  buffer_player_node_ = ctx->makeNode( new audio::BufferPlayerNode( buffer ) );

  // add a monitor node to retrieve measure of volume
  monitor_node_ = ctx->makeNode( new audio::MonitorNode() );

  // connect and enable the Context
  buffer_player_node_ >> monitor_node_ >> ctx->getOutput();
  ctx->enable();
}

void MusicPlayer::PlayMusic() {
  buffer_player_node_->start();
}

float MusicPlayer::GetRMSVolume() {
  return monitor_node_->getVolume();
}

} //namespace music_visualizer
