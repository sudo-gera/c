import cv2
from PIL import Image
import argparse

MAX_WIDTH = 65500  # Max allowed width for stitched image

def extract_frames(video_path, fps, width, height, num_frames):
    cap = cv2.VideoCapture(video_path)
    if not cap.isOpened():
        raise IOError(f"Could not open video: {video_path}")

    video_fps = cap.get(cv2.CAP_PROP_FPS)
    frame_interval = int(video_fps / fps)
    if frame_interval <= 0:
        raise ValueError("Requested FPS is too high for this video.")

    frames = []
    frame_idx = 0
    extracted = 0

    while extracted < num_frames:
        ret, frame = cap.read()
        if not ret:
            break

        if frame_idx % frame_interval == 0:
            resized = cv2.resize(frame, (width, height))
            rgb = cv2.cvtColor(resized, cv2.COLOR_BGR2RGB)
            pil_img = Image.fromarray(rgb)
            frames.append(pil_img)
            extracted += 1

        frame_idx += 1

    cap.release()
    return frames

def stitch_frames_horizontally(frames):
    if not frames:
        raise ValueError("No frames to stitch.")

    frame_width, frame_height = frames[0].size
    total_width = frame_width * len(frames)

    if total_width > MAX_WIDTH:
        raise ValueError(f"Final image width ({total_width}px) exceeds the limit of {MAX_WIDTH}px.")

    result = Image.new('RGB', (total_width, frame_height))
    x_offset = 0
    for frame in frames:
        result.paste(frame, (x_offset, 0))
        x_offset += frame_width

    return result

def main():
    parser = argparse.ArgumentParser(description="Convert MP4 prefix frames to horizontal JPG strip.")
    parser.add_argument('--video', required=True, help="Path to input video (MP4)")
    parser.add_argument('--fps', type=float, default=1.0, help="Frames per second to extract")
    parser.add_argument('--width', type=int, default=160, help="Width of each frame")
    parser.add_argument('--height', type=int, default=90, help="Height of each frame")
    parser.add_argument('--num-frames', type=int, required=True, help="Number of frames to extract from start")
    parser.add_argument('--output', default='output.jpg', help="Output JPG file name")

    args = parser.parse_args()

    print(f"Video: {args.video}")
    print(f"Extracting {args.num_frames} frames at {args.fps} fps")
    print(f"Frame resolution: {args.width}x{args.height}")

    frames = extract_frames(args.video, args.fps, args.width, args.height, args.num_frames)

    print(f"Frames extracted: {len(frames)}")

    stitched_image = stitch_frames_horizontally(frames)
    stitched_image.save(args.output, "JPEG")
    print(f"Saved horizontal image to: {args.output}")

if __name__ == '__main__':
    main()
