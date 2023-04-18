/* sound_trigger_prop_intf.h
 *
 * Interface for sound trigger related communication
 * across modules.
 *
 * Copyright (c) 2014, 2016-2020, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef SOUND_TRIGGER_PROP_INTF_H
#define SOUND_TRIGGER_PROP_INTF_H

#include <hardware/sound_trigger.h>
#include "tinyalsa/asoundlib.h"
#include "soundtrigger.h"

#define MAKE_HAL_VERSION(maj, min) ((((maj) & 0xff) << 8) | ((min) & 0xff))
#define MAJOR_VERSION(ver) (((ver) & 0xff00) >> 8)
#define MINOR_VERSION(ver) ((ver) & 0x00ff)

/* Proprietary interface version used for compatibility with AHAL */
#define STHAL_PROP_API_VERSION_2_0 MAKE_HAL_VERSION(2, 0)
#define STHAL_PROP_API_CURRENT_VERSION STHAL_PROP_API_VERSION_2_0

struct sthw_extn_fptrs {
    int (*set_parameters)(const struct sound_trigger_hw_device *dev,
                          sound_model_handle_t sound_model_handle,
                          const char *kv_pairs);
    size_t (*get_buffer_size)(const struct sound_trigger_hw_device *dev,
                              sound_model_handle_t sound_model_handle);
    int (*read_buffer)(const struct sound_trigger_hw_device *dev,
                       sound_model_handle_t sound_model_handle,
                       unsigned char *buf,
                       size_t bytes);
    int (*stop_buffering)(const struct sound_trigger_hw_device *dev,
                          sound_model_handle_t sound_model_handle);
    int (*get_param_data)(const struct sound_trigger_hw_device *dev,
                          sound_model_handle_t sound_model_handle,
                          const char *param,
                          void *payload,
                          size_t payload_size,
                          size_t *param_data_size);
};
typedef struct sthw_extn_fptrs sthw_extn_fptrs_t;

/* STHAL version queried by AHAL */
typedef int (*sound_trigger_hw_get_version_t)();

/* STHAL extn interface functionality called by qti wrapper */
typedef void (*sthw_extn_get_fptrs_t)(sthw_extn_fptrs_t *fptrs);

/* AHAL callback which is called by STHAL */
typedef void (*audio_hw_call_back_t)(sound_trigger_event_type_t event,
                          sound_trigger_event_info_t* config);

/* AHAL function which is called by STHAL */
typedef int (*audio_hw_acdb_init_t)(int snd_card_num);

/* AHAL function which is called by STHAL */
typedef int (*audio_hw_acdb_init_v2_t)(struct mixer *mixer);

/* AHAL extn util function which is called by STHAL */
typedef int (*audio_hw_get_snd_card_num_t)();

/* AHAL extn util function which is called by STHAL */
typedef int (*audio_hw_open_snd_mixer_t)(struct mixer **mixer);

/* AHAL extn util function which is called by STHAL */
typedef void (*audio_hw_close_snd_mixer_t)(struct mixer *mixer);
#endif /* SOUND_TRIGGER_PROP_INTF_H */
