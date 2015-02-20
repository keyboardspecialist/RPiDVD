#pragma once

#include <stdint.h>

//NOTE: These are the physical addresses
#define MAILBOX_BASE    0x2000B880      /*receiving mail */
#define MAILBOX_POLL    0x2000B890
#define MAILBOX_SENDER  0x2000B894
#define MAILBOX_STATUS  0x2000B898
#define MAILBOX_CONFIG  0x2000B89C
#define MAILBOX_WRITE   0x2000B8A0

#define MAILBOX_EMPTY   0x40000000
#define MAILBOX_FULL    0x80000000


extern void mailbox_read    ( uint32_t mailbox, uint32_t* data );
extern void mailbox_write   ( uint32_t mailbox, uint32_t data  );