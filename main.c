#include <stdio.h>
#include <sys/ioctl.h>
#include <asm/ioctl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include "./consts.h"

;
void main()
{
  // KVM layer
  int kvm_fd = open("/dev/kvm", O_RDWR);
  int version = ioctl(kvm_fd, _IO(KVM_ID, KVM_GET_API_VERSION_seq), 0);
  printf("KVM version: %d\n", version);

  // Create VM
  int vm_fd = ioctl(kvm_fd, _IO(KVM_ID, KVM_CREATE_VM_seq), 0);

// Create VM Memory
#define RAM_SIZE 0x10000
  void *mem_region = mmap(NULL, RAM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
  struct kvm_userspace_memory_region mem = {
      .slot = 0,
      .guest_phys_addr = 0,
      .memory_size = RAM_SIZE,
      .userspace_addr = (uintptr_t)mem_region,
  };
  ioctl(vm_fd, _IOW(KVM_ID, KVM_SET_USER_MEMORY_REGION_seq, struct kvm_userspace_memory_region), &mem);

  // Create VCPU
  // int vcpu_fd = ioctl(vm_fd, KVM_CREATE_VCPU, 0);
}
