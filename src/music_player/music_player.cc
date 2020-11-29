//
// Created by garwi on 11/27/2020.
//

#include "music_player/music_player.h"

namespace music_visualizer {

void MusicPlayer::LoadMusic(const fs::path& path) {
  /*
  audio::SourceFileRef sourceFile = audio::load(loadFile(path));
  music_ = audio::Voice::create( sourceFile );
  */

  auto ctx = audio::Context::master();

  audio::SourceFileRef sourceFile = audio::load( loadFile(path), ctx->getSampleRate() );
  // load the entire sound file into a BufferRef, and construct a BufferPlayerNode with this.
  audio::BufferRef buffer = sourceFile->loadBuffer();
  mBufferPlayerNode_ = ctx->makeNode( new audio::BufferPlayerNode( buffer ) );

  // add a spectral to reduce the volume
  mMonitorSpectralNode_ = ctx->makeNode( new audio::MonitorSpectralNode() );
  monitor_node_ = ctx->makeNode( new audio::MonitorNode() );

  // connect and enable the Context
  mBufferPlayerNode_ >> monitor_node_ >> ctx->getOutput();
  ctx->enable();
}

void MusicPlayer::PlayMusic() {
  mBufferPlayerNode_->start();
  //music_->start();
}

float MusicPlayer::GetDecibelLevel() {
  //return audio::linearToDecibel(monitor_node_->getVolume())/100;
  return monitor_node_->getVolume();
  //return audio::linearToDecibel(mMonitorSpectralNode_->getSpectralCentroid())/100;
}

} //namespace music_visualizer
