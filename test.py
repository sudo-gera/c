import argparse
import json
import mimetypes
from pathlib import Path
from urllib.parse import urlparse, parse_qs, unquote
from http.server import HTTPServer, BaseHTTPRequestHandler

ROOT = Path(".")


class FileServer(BaseHTTPRequestHandler):
    def do_GET(self):
        query = parse_qs(urlparse(self.path).query)
        requested = query.get("path", [None])[0]

        if requested is None:
            self.send_error(400, "Missing ?path= parameter")
            return

        # Treat ?path= as relative to ROOT.
        path = (ROOT / unquote(requested).lstrip("/")).resolve()

        # # Prevent ../ from escaping ROOT.
        # try:
        #     path.relative_to(ROOT)
        # except ValueError:
        #     self.send_error(403, "Forbidden")
        #     return

        if not path.exists():
            self.send_error(404, "Not Found")
            return

        if path.is_dir():
            self.send_directory(path)
        else:
            self.send_file(path)

    def send_directory(self, path):
        entries = [
            {
                "name": p.name,
                "type": "directory" if p.is_dir() else "file",
                "size": p.stat().st_size if p.is_file() else None,
            }
            for p in sorted(path.iterdir(), key=lambda p: (not p.is_dir(), p.name.lower()))
        ]

        body = json.dumps(entries, indent=2).encode()

        self.send_response(200)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", len(body))
        self.end_headers()
        self.wfile.write(body)

    def send_file(self, path):
        body = path.read_bytes()
        content_type = mimetypes.guess_type(path.name)[0] or "application/octet-stream"

        self.send_response(200)
        self.send_header("Content-Type", content_type)
        self.send_header("Content-Length", len(body))
        self.end_headers()
        self.wfile.write(body)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", default='.')
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=8080)
    args = parser.parse_args()

    ROOT = Path(args.root).resolve()

    server = HTTPServer((args.host, args.port), FileServer)
    print(f"Serving {ROOT} on http://[{args.host}]:{args.port}")

    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass