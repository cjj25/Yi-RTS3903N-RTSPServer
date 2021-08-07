# RTSPServer for RTS3903N based YI Cameras
*While this repo is focused on Yi based cameras, it should compile and run on any RTS3903N based camera!*

## Background
It took many hours of research to put this together. The SDK was very hard to find, and I luckily stumbled across it by
finding similar cameras (TP Link) that had shared the source due to GPL requirements.

**Important**: This method doesn't overwrite the existing flash, simply remove the SD card, and the 'hack' will be disabled.

## Getting Started
- Download the latest zip from the releases page
- Extract the contents to the root of a MicroSD card (minimum 2GB) that is FAT32 partitioned
- (Optional) If you're using WiFi, edit Factory/wpa_supplicant.conf and add your WiFi credentials
- Connect to RTSP via `rtsp://[YOUR_CAMERA_IP]/ch0_0.h264`
- Does the picture look normal? No, see troubleshooting below

### What's Working
- H264 encoded stream via `rtsp://[YOUR_CAMERA_IP]/ch0_0.h264`
- Telnet server open by default (root, no password)
- WiFi connection without having to go through the initial vendor pairing process
- Yi Camera
    - Tested with `7.1.00.25A_202002271051` and `7.1.00.17A_201909271014`

### TODO:
- Add audio to the feed
- Control PTZ (pan/tilt) based cameras
- ONVIF
- Better documentation
- Create a flash version / permanent solution
## Developers / Compiling
- Install Docker
- Run `./compile.sh`
- This chipset is very capable and there are many features / options available for the encoder see `stream.c` where there are
calls to `manage_modes`
  - To find out what options are available see `rtsvideo.h` where `enum_rts_video_ctrl_id` is defined.
- If you create / discover better settings to improve the picture quality, please push to this repo :)

## Video Quality
- See the `Developers/Compiling` section and tweak the settings in `stream.c` inside the `start_stream()` function - 
  if you find an improved configuration, **please push it to this repo**, so we can all benefit.
- Significant settings:
  - h264_attr.bps
  - RTS_VIDEO_CTRL_ID_NOISE_REDUCTION
  - RTS_VIDEO_CTRL_ID_LDC
  - RTS_VIDEO_CTRL_ID_DETAIL_ENHANCEMENT
  - RTS_VIDEO_CTRL_ID_3DNR **(Offers significant improvement but can't find the 'sweet' spot)**
  - RTS_VIDEO_CTRL_ID_IR_MODE **(If you're having issues with nightmode)**
## Troubleshooting
The RTS3903N has a dedicated ADC that's used for sensing the light, I've discovered that some cameras had their logic inverted
 and to get around this, do the following
- Create an empty file on the root of the sd card named `invert_adc` (exact path `/sdcard/invert_adc`)

If this doesn't solve the issue, take a look at the `stream.c` where `sensor_sensitivity` is declared.

## Credit
- The RTSPServer part of this repo was taken from another repo, full credit to be given to: 
  - `roleo` I believe is the original author[?]
  - `alienatedsec` I copied the modified version that repo

## Resources
- [Toolchain](https://github.com/cjj25/RTS3903N-rsdk-4.8.5-5281)
- [Compiled binaries / tools for debugging and test](https://github.com/cjj25/RTS3903N-Tools)
