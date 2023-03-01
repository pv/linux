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
	__u8  ts;
	__u8  sn;
	__u8  status;
};

#define SIOCBTISOTXINFO		(SIOCPROTOPRIVATE + 0)

/* ISO timing and packet information, both from packet completion and
 * LE Read ISO TX Sync, at a point of time immediately after completion
 * of the read sync command.
 */
struct bt_iso_tx_info {
	__u64	time;
	__u64	pkt_time;
	__u16	pkt_sn;
	__u16	pkt_queue;
	__u32	sync_timestamp;
	__u32	sync_offset;
	__u16	sync_sn;
};

#endif /* __ISO_H */
