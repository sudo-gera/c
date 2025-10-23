#!/usr/bin/env python3
import argparse
import ipaddress
import sys
from tqdm import tqdm


def invert_networks(networks, version, show_progress=False):
    """Return complement networks (inverse of input)."""
    if version == 4:
        full = ipaddress.IPv4Network("0.0.0.0/0")
    else:
        full = ipaddress.IPv6Network("::/0")

    nets = [n for n in networks if n.version == version]

    if not nets:
        # Nothing excluded → return the full space
        return [full]

    # Collapse overlapping/adjacent
    nets = list(ipaddress.collapse_addresses(nets))

    # Start with the whole space
    result = [full]

    iterator = tqdm(nets, desc=f"Excluding IPv{version}", unit="net") if show_progress else nets

    # Subtract each net
    for net in iterator:
        new_result = []
        for r in result:
            if r.subnet_of(net):
                # r completely covered → drop it
                continue
            if net.subnet_of(r):
                # net inside r → split r
                new_result.extend(r.address_exclude(net))
            else:
                # disjoint → keep as is
                new_result.append(r)
        result = new_result

    return result


def main():
    parser = argparse.ArgumentParser(
        description="Invert IPv4/IPv6 CIDR masks to get complement networks."
    )
    parser.add_argument(
        "masks",
        nargs="?",
        help="Comma-separated list of CIDR networks (e.g. 192.168.0.0/24,2001:db8::/32). "
             "If omitted, masks are read from stdin (one per line).",
    )
    parser.add_argument("--ipv4-only", action="store_true", help="Print only IPv4 inverted masks")
    parser.add_argument("--ipv6-only", action="store_true", help="Print only IPv6 inverted masks")
    parser.add_argument("--progress", action="store_true", help="Show progress bar")

    args = parser.parse_args()

    if args.ipv4_only and args.ipv6_only:
        print("Error: --ipv4-only and --ipv6-only cannot be used together.", file=sys.stderr)
        sys.exit(1)

    # Read input networks
    lines = sys.stdin.readlines()
    if args.masks:
        mask_strings = [m.strip() for m in args.masks.split(",") if m.strip()]
    else:
        # Read from stdin
        mask_strings = [line.strip() for line in tqdm(lines) if line.strip()]

    networks = []
    for m in mask_strings:
        try:
            networks.append(ipaddress.ip_network(m, strict=False))
        except ValueError:
            print(f"Invalid network: {m}", file=sys.stderr)
            sys.exit(1)

    if not args.ipv6_only:
        for n in invert_networks(networks, 4, show_progress=args.progress):
            print(n)

    if not args.ipv4_only:
        for n in invert_networks(networks, 6, show_progress=args.progress):
            print(n)


if __name__ == "__main__":
    main()
