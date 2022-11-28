#include <linux/types.h>

// I know i could import <sys/kvm.h> but that would be too easy
// KVM ioctl id
const int KVM_ID = 0xAE;

// sequence numbers
const int KVM_GET_API_VERSION_seq = 0x00;
const int KVM_CREATE_VM_seq = 0x01;
const int KVM_SET_USER_MEMORY_REGION_seq = 0x46;

const struct kvm_userspace_memory_region
{
  __u32 slot;
  __u32 flags;
  __u64 guest_phys_addr;
  __u64 memory_size;    /* bytes */
  __u64 userspace_addr; /* start of the userspace allocated memory */
}