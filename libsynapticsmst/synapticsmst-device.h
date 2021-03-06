/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2015 Richard Hughes <richard@hughsie.com>
 * Copyright (C) 2016 Mario Limonciello <mario.limonciello@dell.com>
 * Copyright (C) 2017 Peichen Huang <peichenhuang@tw.synaptics.com>
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef __SYNAPTICSMST_DEVICE_H
#define __SYNAPTICSMST_DEVICE_H

#include <glib-object.h>
#include <gusb.h>

G_BEGIN_DECLS

#define SYNAPTICSMST_TYPE_DEVICE (synapticsmst_device_get_type ())
G_DECLARE_DERIVABLE_TYPE (SynapticsMSTDevice, synapticsmst_device, SYNAPTICSMST, DEVICE, GObject)

#define MAX_DP_AUX_NODES	3

struct _SynapticsMSTDeviceClass
{
	GObjectClass		parent_class;
	/*< private >*/
	void (*_as_reserved1)	(void);
	void (*_as_reserved2)	(void);
	void (*_as_reserved3)	(void);
	void (*_as_reserved4)	(void);
	void (*_as_reserved5)	(void);
	void (*_as_reserved6)	(void);
	void (*_as_reserved7)	(void);
	void (*_as_reserved8)	(void);
};

/**
 * SynapticsMSTDeviceKind:
 * @SYNAPTICSMST_DEVICE_KIND_UNKNOWN:		Type invalid or not known
 * @SYNAPTICSMST_DEVICE_KIND_DIRECT:		Directly addressable
 * @SYNAPTICSMST_DEVICE_KIND_REMOTE:		Requires remote register work
 *
 * The device type.
 **/
typedef enum {
	SYNAPTICSMST_DEVICE_KIND_UNKNOWN,
	SYNAPTICSMST_DEVICE_KIND_DIRECT,
	SYNAPTICSMST_DEVICE_KIND_REMOTE,
	/*< private >*/
	SYNAPTICSMST_DEVICE_KIND_LAST
} SynapticsMSTDeviceKind;

typedef enum {
	SYNAPTICSMST_DEVICE_BOARDID_EVB = 0x00,
	SYNAPTICSMST_DEVICE_BOARDID_X6 = 0x0110,
	SYNAPTICSMST_DEVICE_BOARDID_X7,
	SYNAPTICSMST_DEVICE_BOARDID_WD15_TB15_WIRE,
	SYNAPTICSMST_DEVICE_BOARDID_CTKM5_WIRELESS,
	SYNAPTICSMST_DEVICE_BOARDID_UNKNOW = 0xFFFF,
} SynapticsMSTDeviceBoardID;

SynapticsMSTDevice	*synapticsmst_device_new	(SynapticsMSTDeviceKind kind, guint8 aux_node, guint8 layer, guint16 rad);

/* helpers */
SynapticsMSTDeviceKind synapticsmst_device_kind_from_string	(const gchar	*kind);
const gchar	*synapticsmst_device_kind_to_string		(SynapticsMSTDeviceKind kind);
const gchar	*synapticsmst_device_boardID_to_string		(SynapticsMSTDeviceBoardID boardID);
const gchar *synapticsmst_device_aux_node_to_string (guint8 index);
gboolean synapticsmst_device_enable_remote_control (SynapticsMSTDevice *device, GError **error);
gboolean synapticsmst_device_disable_remote_control (SynapticsMSTDevice *device, GError **error);
gboolean synapticsmst_device_scan_cascade_device (SynapticsMSTDevice *device, guint8 tx_port);

/* getters */
SynapticsMSTDeviceKind synapticsmst_device_get_kind	(SynapticsMSTDevice	*device);
SynapticsMSTDeviceBoardID synapticsmst_device_get_boardID (SynapticsMSTDevice *device);
guint8 synapticsmst_device_get_aux_node	(SynapticsMSTDevice	*device);
const gchar	*synapticsmst_device_get_version	(SynapticsMSTDevice	*device);
const gchar *synapticsmst_device_get_chipID (SynapticsMSTDevice *device);
guint16 synapticsmst_device_get_rad (SynapticsMSTDevice *device);
guint8 synapticsmst_device_get_layer (SynapticsMSTDevice *device);
gboolean synapticsmst_device_get_flash_checksum (SynapticsMSTDevice *device, int length, int offset, guint32 *checksum, GError **error);

/* object methods */
gboolean	synapticsmst_device_enumerate_device(SynapticsMSTDevice *devices, GError **error);
gboolean	synapticsmst_device_write_firmware	(SynapticsMSTDevice	*device,
						 GBytes		*fw,
						 GError		**error);

G_END_DECLS

#endif /* __SYNAPTICSMST_DEVICE_H */
