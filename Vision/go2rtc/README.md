## Quick Start

1. **Enter the directory:**
```bash
cd go2rtc

```


2. **Start the service:**
```bash
docker compose up -d

```

---

## How to View Streams

### 1. Direct Web Browser Link:

Direct to WebRTC

> `http://<NANO_IP>:1984/webrtc.html?src=<CAMERA_NAME>&media=video+audio`

### 2. Universal Player:

Includes a UI with fallback modes (MSE/HLS) if WebRTC is blocked.

> `http://<NANO_IP>:1984/stream.html?src=<CAMERA_NAME>`

---

## Adding & Managing Cameras

Configuration is handled in `go2rtc.yaml`.

### 1. Add a new camera

Open `go2rtc.yaml` and add your device under the `streams` section:

```yaml
streams:
  my_new_camera: 
    - ffmpeg:device?video=/dev/video2&input_format=h264&video_size=1920x1080#video=copy

```

### 2. Apply Changes

```bash
docker restart go2rtc

```

---

## Developer API

For integration into ROS2 nodes.

| Feature | Endpoint | Method |
| --- | --- | --- |
| **List Streams** | `http://<NANO_IP>:1984/api/streams` | GET |
| **WebRTC Handshake** | `http://<NANO_IP>:1984/api/webrtc?src=<NAME>` | POST (SDP) |
| **System Stats** | `http://<NANO_IP>:1984/api/stack` | GET |

---
