import ipaddress

def parse_input_masks(mask_input):
    return [ipaddress.IPv4Network(mask.strip()) for mask in mask_input.split(',')]

def parse_exclude_ips(ip_input):
    return [ipaddress.IPv4Address(ip.strip()) for ip in ip_input.split(',')]

def exclude_ips_from_masks(masks, exclude_ips):
    remaining_subnets = []

    for network in masks:
        subnets_to_process = [network]
        for exclude_ip in exclude_ips:
            new_subnets = []
            for subnet in subnets_to_process:
                if exclude_ip in subnet:
                    # Split subnet into parts that exclude exclude_ip
                    new_subnets.extend(subnet.address_exclude(ipaddress.IPv4Network(f'{exclude_ip}/32')))
                else:
                    new_subnets.append(subnet)
            subnets_to_process = new_subnets
        remaining_subnets.extend(subnets_to_process)

    return remaining_subnets

def main():
    mask_input = input("Enter comma-separated IPv4 masks (CIDR notation):\n")
    ip_input = input("Enter comma-separated IPv4 addresses to exclude:\n")

    masks = parse_input_masks(mask_input)
    exclude_ips = parse_exclude_ips(ip_input)

    result_subnets = exclude_ips_from_masks(masks, exclude_ips)

    print("\nResulting IPv4 masks excluding specified IPs:")
    print(*result_subnets, sep=', ')
    # for subnet in result_subnets:
    #     print(subnet)

if __name__ == "__main__":
    main()
