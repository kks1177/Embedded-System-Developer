import cv2

VIDEO_FORMAT_MP4V = cv2.VideoWriter_fourcc(*"mp4v") # DIVX MPEG-4 코덱 - mp4, avi
VIDEO_FORMAT_XVID = cv2.VideoWriter_fourcc(*"XVID") # XVID MPEG-4 코덱 - avi
VIDEO_FORMAT_FMP4 = cv2.VideoWriter_fourcc(*"FMP4") # FFMPEG MPEG-4 코덱 - avi
VIDEO_FORMAT_X264 = cv2.VideoWriter_fourcc(*"X264") # H.264/AVC 코덱 - x
VIDEO_FORMAT_MJPG = cv2.VideoWriter_fourcc(*"MJPG") # Motion-JPEG 코덱 - avi

