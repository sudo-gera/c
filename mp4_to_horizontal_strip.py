import cv2
from PIL import Image
import argparse
import math

MAX_WIDTH = 65500  # JPEG spec limit (safe for Wanda Mate)

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

def stitch_frames(frames, auto_wrap=False):
    if not frames:
        raise ValueError("No frames to stitch.")

    frame_width, frame_height = frames[0].size
    num_frames = len(frames)

    # Determine row layout
    frames_per_row = num_frames
    rows = 1

    if auto_wrap:
        max_frames_per_row = MAX_WIDTH // frame_width
        if max_frames_per_row == 0:
            raise ValueError("Single frame width exceeds max allowed image width.")

        frames_per_row = min(num_frames, max_frames_per_row)
        rows = math.ceil(num_frames / frames_per_row)

    total_width = frame_width * frames_per_row
    total_height = frame_height * rows

    if total_width > MAX_WIDTH and not auto_wrap:
        raise ValueError(f"Final image width ({total_width}px) exceeds {MAX_WIDTH}px. "
                         f"Use --auto-wrap to split into multiple rows.")

    result = Image.new('RGB', (total_width, total_height))
    for i, frame in enumerate(frames):
        row = i // frames_per_row
        col = i % frames_per_row
        x = col * frame_width
        y = row * frame_height
        result.paste(frame, (x, y))

    return result

def save_image_safe(img, path):
    if img.mode != 'RGB':
        img = img.convert('RGB')

    img.save(path, "JPEG", quality=85, optimize=True, progressive=False)

def main():
    parser = argparse.ArgumentParser(description="Convert MP4 prefix frames to horizontal JPG strip.")
    parser.add_argument('--video', required=True, help="Path to input video (MP4)")
    parser.add_argument('--fps', type=float, default=1.0, help="Frames per second to extract")
    parser.add_argument('--width', type=int, default=160, help="Width of each frame")
    parser.add_argument('--height', type=int, default=90, help="Height of each frame")
    parser.add_argument('--num-frames', type=int, required=True, help="Number of frames to extract from start")
    parser.add_argument('--output', default='output.jpg', help="Output JPG file name")
    parser.add_argument('--auto-wrap', action='store_true',
                        help="Automatically wrap frames into rows if image would exceed max width")

    args = parser.parse_args()

    print(f"Video: {args.video}")
    print(f"Extracting {args.num_frames} frames at {args.fps} FPS, resized to {args.width}x{args.height}")
    if args.auto_wrap:
        print("Auto-wrap is enabled: large images will wrap to multiple rows if needed.")

    frames = extract_frames(args.video, args.fps, args.width, args.height, args.num_frames)
    print(f"Frames extracted: {len(frames)}")

    stitched = stitch_frames(frames, auto_wrap=args.auto_wrap)

    print(f"Saving image to {args.output} (baseline JPEG, quality=85, progressive=False)")
    save_image_safe(stitched, args.output)
    print("Done.")

if __name__ == '__main__':
    main()
