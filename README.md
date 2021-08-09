# RTSPServer for RTS3903N based YI Cameras
*While this repo is focused on Yi based cameras, it should compile and run on any RTS3903N based camera!*

## Important: Read all instructions on this page!
## Background
It took many hours of research to put this together. The SDK was very hard to find, and I luckily stumbled across it by
finding similar cameras (TP Link) that had shared the source due to GPL requirements.

**Important**: This method doesn't overwrite the existing flash, simply remove the SD card, and the 'hack' will be disabled.

## Known Compatible Firmware
- `7.1.00.25A_202002271051`
- `7.1.00.17A_201909271014`
- `7.0.00.73a_201812031453`
- [More info on the Wiki](https://github.com/cjj25/Yi-RTS3903N-RTSPServer/wiki/Tested-devices)
## Getting Started
- Download the latest tar.gz from the [releases page](https://github.com/cjj25/Yi-RTS3903N-RTSPServer/releases)
- Extract the contents to the root of a MicroSD card (minimum 2GB) that is FAT32 partitioned
- If you're using WiFi
  - This method will use the already stored WiFi credentials in the camera
  - You can overwrite the saved config by editing `wpa_supplicant_sample.conf` and renaming to `wpa_supplicant.conf` 
    - **Only replace SSID_NAME_OF_WIFI and WIFI_SECRET_KEY, unless you're using WEP encryption or open**
- Insert the SD and turn on
  1. On startup the script looks to see if a backup exists in /var/tmp/sd/backup (your SD card) and if not, it will create a backup and then restarts the camera.
  2. Please upload your firmware backup to this repository by creating a new issue and sharing a link
  3. If you have a pan/tilt camera, it will perform the usual calibration
  4. A telnet server is started (if not already done so by Yi) with username `root` and no password
  5. The stream grabber will start and the RTSPServer ***(don't try to connect too quickly - bug)***
  6. You'll probably have a pinkish tint on the picture, the IR cut (blocking IR light) will be performed after ***30 seconds*** to ensure any other binaries have finished taking control of the IR Cut
     >If the image isn't quite right (grey / too much pink), place your finger over the sensor on the front (make it very dark) and see what happens. If the logic is inverted, rename `invert_adc_rename_me` to `invert_adc` and restart the camera.
  7. Connect to RTSP via `rtsp://[YOUR_CAMERA_IP]/ch-1_0.h264`

### What's Working
- H264 encoded stream via `rtsp://[YOUR_CAMERA_IP]/ch0_0.h264`
- Telnet server open by default (root, no password)

### TODO:
- Add audio to the feed
- Control PTZ (pan/tilt) based cameras
- ONVIF
- Better documentation
- Create a flash version / permanent solution
## Developers / Compiling
- Install Docker
- Run `./compile.sh`
- This chipset is very capable has many features available for the encoder, see `stream.c` with calls to `manage_modes`
  - To discover more options see `rtsvideo.h` where `enum_rts_video_ctrl_id` is defined.
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

If this doesn't solve the issue, take a look at the `stream.c` where `sensor_sensitivity` is declared and replace `ADC_CHANNEL_0` with `ADC_CHANNEL_1`, `ADC_CHANNEL_2` or `ADC_CHANNEL_3`

## Credit
- The RTSPServer part of this repo was taken from another repo, full credit to be given to: 
  - `roleo` I believe is the original author[?]
  - `alienatedsec` I copied the modified version that repo
- [@rage2dev](https://github.com/rage2dev/) for sharing the [payload he discovered](https://github.com/rage2dev/YiOutdoor)

## Resources
- [Toolchain](https://github.com/cjj25/RTS3903N-rsdk-4.8.5-5281)
- [Compiled binaries / tools for debugging and test](https://github.com/cjj25/RTS3903N-Tools)
