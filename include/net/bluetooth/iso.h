/* SPDX-License-Identifier: GPL-2.0 */
/*
 * BlueZ - Bluetooth protocol stack for Linux
 *
 * Copyright (C) 2022 Intel Corporation
 */

#ifndef __ISO_H
#define __ISO_H

/* ISO defaults */
#define ISO_DEFAULT_MTU		251
#define ISO_MAX_NUM_BIS		0x1f

/* ISO socket broadcast address */
struct sockaddr_iso_bc {
	bdaddr_t	bc_bdaddr;
	__u8		bc_bdaddr_type;
	__u8		bc_sid;
	__u8		bc_num_bis;
	__u8		bc_bis[ISO_MAX_NUM_BIS];
};

/* ISO socket address */
struct sockaddr_iso {
	sa_family_t	iso_family;
	bdaddr_t	iso_bdaddr;
	__u8		iso_bdaddr_type;
	struct sockaddr_iso_bc iso_bc[];
};

#define ISO_CMSG_PKT_STATUS	0x01

struct bt_iso_pkt_status {
	__u32 timestamp;
	__u16 sn;
	__u8  ts;
	__u8  status;
} __packed;

#define SIOCBTREADISOTXINFO		(SIOCPROTOPRIVATE + 0)

/* ISO timing and packet information, both from previous Number of Completed
 * Packets event and LE Read ISO TX Sync commands.
 *
 * If flag BT_ISO_TX_INFO_FLAG_QUEUE is set on input to ioctl, a LE Read ISO TX
 * Sync command is queued.
 *
 * If flag BT_ISO_TX_INFO_FLAG_SYNC_PKT is set on input to ioctl, the pkt_*
 * fields correspond to the values at the completion of the previous LE Read ISO
 * TX Sync command.
 *
 * If no packet completed events, pkt_time=0. Otherwise, it indicates the
 * CLOCK_MONOTONIC time of Number of Completed Packets event.
 *
 * If no LE Read ISO TX Sync has completed, sync_time=0. Otherwise, it indicates
 * CLOCK_MONOTONIC time of LE Read ISO TX Sync command completion.
 *
 * The completion time in CLOCK_MONOTONIC for SDU with sequence number sn is
 * estimated as:
 *
 * sdu_time(sn) = pkt_time + ((u16)(sn - pkt_sn) + pkt_queue) * SDU_Interval_ns
 *
 * assuming sequential sn, and up to the accuracy of the Number of Completed
 * Packets event. Packet completion time is not necessarily the SDU reference
 * time. Since the controller may batch the Number of Completed Packets events,
 * the pkt_queue value may not be accurate.
 *
 * The sync_* values are as provided by the Controller. The timestamp and the
 * sequence numbers generally do not correspond to Host clock or sequence
 * numbers.
 */
struct bt_iso_tx_info {
	__u64	pkt_time;
	__u64	sync_time;
	__u16	pkt_sn;
	__u16	pkt_queue;
	__u32	sync_timestamp;
	__u32	sync_offset;
	__u16	sync_sn;
	__u8    flags;
} __packed;

#define BT_ISO_TX_INFO_FLAG_QUEUE	BIT(0)
#define BT_ISO_TX_INFO_FLAG_SYNC_PKT	BIT(1)

#endif /* __ISO_H */
