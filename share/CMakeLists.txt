# Copyright: Universidad Carlos III de Madrid (C) 2017
# Authors: Juan G Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later

set(applications)
set(contexts)

if(ENABLE_Playback)
    list(APPEND contexts contexts/Playback)
endif()

if(ENABLE_RealToSimControlboard)
    list(APPEND contexts contexts/RealToSimControlboard)
endif()
