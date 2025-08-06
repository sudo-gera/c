import cv2
import os
from PIL import Image

def extract_frames(video_path, frames_per_second=4):
    cap = cv2.VideoCapture(video_path)

    if not cap.isOpened():
        raise IOError("Could not open video file.")

    fps = cap.get(cv2.CAP_PROP_FPS)
    total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    duration_seconds = int(total_frames / fps)

    frame_indices = [int(i * fps / frames_per_second) for i in range(duration_seconds * frames_per_second)]
    frames = []

    for idx in frame_indices:
        cap.set(cv2.CAP_PROP_POS_FRAMES, idx)
        ret, frame = cap.read()
        if not ret:
            continue

        # Convert BGR (OpenCV) to RGB (Pillow)
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        img = Image.fromarray(frame_rgb)
        frames.append(img)

    cap.release()
    return frames

def join_frames_horizontally(frames):
    if not frames:
        raise ValueError("No frames to join.")

    frame_width, frame_height = frames[0].size
    total_width = frame_width * len(frames)
    print(total_width, frame_height)
    result = Image.new('RGB', (total_width, frame_height))

    for i, frame in enumerate(frames):
        result.paste(frame, (i * frame_width, 0))

    return result

def main():
    # input_video = 'input.mp4'
    # output_image = 'output.jpg'
    input_video = 'minecraft.mp4'
    output_image = 'minecraft.jpg'
    fps_to_extract = 4

    print("Extracting frames...")
    frames = extract_frames(input_video, fps_to_extract)

    print(f"Joining {len(frames)} frames horizontally...")
    final_image = join_frames_horizontally(frames)

    print(f"Saving to {output_image}...")
    final_image.save(output_image, quality=95)
    print("Done.")

if __name__ == '__main__':
    main()
