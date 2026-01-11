# Vision
Wiki [notion page](https://www.notion.so/crsucd/Vision-2a98a3eca2f080979dfbdb59448b942f)

environment python@3.11 `pip install -r requirements.txt`

publish video frame from camera `python publish_video_feed.py`

record by running `python record_video.py <camera index>`. The recorded videos are going to be saved in `./videos` folder.

If things didn't work, run the `python test_for_output_format.py <camera index>` to see if the camera support the required output format.