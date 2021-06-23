// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_CHANNELSTATE_H
#define NOVELRT_CHANNELSTATE_H

namespace NovelRT::Experimental::Audio
{
  enum class ChannelState
  {
    Initialise,
    Loading,
    ToPlay,
    Playing,
    Pausing,
    Paused,
    Stopping,
    Stopped
  };
}

#endif
