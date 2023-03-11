qemu-system-aarch64 \                                                       \
  -cpu cortex-a57 \                                                         \
  -device rtl8139,netdev=net0 \                                             \
  -device virtio-scsi-device \                                              \
  -device scsi-cd,drive=cdrom \                                             \
  -device virtio-blk-device,drive=hd0 \                                     \
  -drive "file=/Users/gera/Downloads/ubuntu-22.04.2-live-server-arm64.iso,id=cdrom,if=none,media=cdrom" \                       \
  -m 2G \                                                                   \
  -machine virt \                                                           \
  -netdev user,id=net0 \                                                    \
  -nographic \                                                              \
  -smp 2 \                                                                  \
;                                                                           \
