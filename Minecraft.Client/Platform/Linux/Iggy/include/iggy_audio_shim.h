#ifndef IGGY_AUDIO_SHIM_H
#define IGGY_AUDIO_SHIM_H

#ifdef __cplusplus
extern "C" {
#endif

#define IGGY_AUDIO_OK 0

enum IggyAudioOutPort {
    Main = 0,
    Bgm = 1,
    Voice = 2,
    Personal = 3,
    PadSpk = 4,
    Audio3d = 126,
    Aux = 127,
};

enum IggyAudioOutParamAttr {
    None = 0,
    Restricted = 1,
    MixToMain = 2,
};

enum IggyAudioOutParamFormat {
    S16Mono = 0,
    S16Stereo = 1,
    S16_8CH = 2,
    FloatMono = 3,
    FloatStereo = 4,
    Float_8CH = 5,
    S16_8CH_Std = 6,
    Float_8CH_Std = 7
};

typedef union {
    struct {
        enum IggyAudioOutParamFormat data_format : 8;  // Bits 0-7
        unsigned reserve0                        : 8;  // Bits 8-15
        enum IggyAudioOutParamAttr attributes    : 4;  // Bits 16-19
        unsigned reserve1                        : 10; // Bits 20-29
        unsigned unused                          : 1;  // Bit 31 (Bit 30 is implicitly padding here)
    };
    unsigned raw; // "unpacks" the entire 32-bit value
} IggyAudioOutParamExtendedInformation;


typedef struct IggyAudioShimCallbacks {
    int (*iggyAudioOutOpen)(
        int user_id,
        enum IggyAudioOutPort port_type,
        int index,
        unsigned length,
        unsigned sample_rate,
        IggyAudioOutParamExtendedInformation param_type);

    int (*iggyAudioOutSetVolume)(int handle, int flag, int* vol);
    int (*iggyAudioOutClose)(int handle);
    int (*iggyAudioOutOutput)(int handle, void* ptr);
} IggyAudioShimCallbacks;

// Registers callback table used by the shim
int iggyAudioShimRegisterCallbacks(const IggyAudioShimCallbacks* callbacks);

#ifdef __cplusplus
}
#endif

#endif // IGGY_AUDIO_SHIM_H
