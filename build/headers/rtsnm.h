/*!
 * \mainpage IPCam Network Development Guide
 *
 * \section Introduction
 *
 * librtsnm is a library that helps you to develop your network application using realtek's soc camera
 *
 * \section Features
 *
 * 1.Support configure Ethernet
 *
 * 2.Support configure Wireless network card(RTL8188EUS/RTL8192EUS/RTL8811AU/RTL8812AU)
 *
 * 3.Support WIFI WPS(WI-FI Protect Setup) function
 *
 * \section Start
 *
 * Some example programs can be found in the examples subdirectory
 *
 * \example rtsnm_example.c
 *
 * Realtek Semiconductor Corp.
 *
 * Copyright (C) 2014      Hurray Niu <hurray_niu@realsil.com.cn>
 *
 */

#ifndef __RTSNM_H__
#define __RTSNM_H__

#include <arpa/inet.h>

enum nm_msg_type {
/*eth msg*/
	MSG_BR_ENABLE,
	MSG_ETH_TYPE,
	MSG_ETH_MAC,
	MSG_WAN_INFO,
	MSG_LAN_INFO,
	MSG_DDNS_INFO,
	MSG_PPPOE_INFO,
	MSG_UPNP_INFO,
	MSG_BONJR_INFO,
	MSG_IPFILTER_INFO,
	MSG_IPV6_INFO,
	MSG_QOS_INFO,
	MSG_WAN_FLASH,
/*wlan msg*/
	MSG_SCAN_COUNT,
	MSG_SCAN_INFO,
	MSG_STA_INFO,
	MSG_SOFTAP_INFO,
	MSG_CREAT_STA_PIN,
	MSG_CREAT_SOFTAP_PIN,
	MSG_MAX_TYPENUM,
	MSG_NM_UNKNOWN = 255,
};

#define ERR_DOMAIN_NETWORK 0x02000000

enum nm_lib_err_type {
/*eth msg*/
	ERR_NM_BR = ERR_DOMAIN_NETWORK | (MSG_BR_ENABLE << 16),
	ERR_NM_ETHTYPE = ERR_DOMAIN_NETWORK | (MSG_ETH_TYPE << 16),
	ERR_NM_MACADDR = ERR_DOMAIN_NETWORK | (MSG_ETH_MAC << 16),
	ERR_NM_WAN = ERR_DOMAIN_NETWORK | (MSG_WAN_INFO << 16),
	ERR_NM_LAN = ERR_DOMAIN_NETWORK | (MSG_LAN_INFO << 16),
	ERR_NM_DDNS = ERR_DOMAIN_NETWORK | (MSG_DDNS_INFO << 16),
	ERR_NM_PPPOE = ERR_DOMAIN_NETWORK | (MSG_PPPOE_INFO << 16),
	ERR_NM_UPNP = ERR_DOMAIN_NETWORK | (MSG_UPNP_INFO << 16),
	ERR_NM_BNJ = ERR_DOMAIN_NETWORK | (MSG_BONJR_INFO << 16),
	ERR_NM_IPF = ERR_DOMAIN_NETWORK | (MSG_IPFILTER_INFO << 16),
	ERR_NM_IPV6 = ERR_DOMAIN_NETWORK | (MSG_IPV6_INFO << 16),
	ERR_NM_QOS = ERR_DOMAIN_NETWORK | (MSG_QOS_INFO << 16),
	ERR_NM_WANFLASH = ERR_DOMAIN_NETWORK | (MSG_WAN_FLASH << 16),
/*wlan*/
	ERR_NM_SCANCNT = ERR_DOMAIN_NETWORK | (MSG_SCAN_COUNT << 16),
	ERR_NM_SCANINFO = ERR_DOMAIN_NETWORK | (MSG_SCAN_INFO << 16),
	ERR_NM_STA = ERR_DOMAIN_NETWORK | (MSG_STA_INFO << 16),
	ERR_NM_SOFTAP = ERR_DOMAIN_NETWORK | (MSG_SOFTAP_INFO << 16),
	ERR_NM_STAPIN = ERR_DOMAIN_NETWORK | (MSG_CREAT_STA_PIN << 16),
	ERR_NM_SOFTAPPIN = ERR_DOMAIN_NETWORK | (MSG_CREAT_SOFTAP_PIN << 16),
	ERR_NM_UNKNOWN = ERR_DOMAIN_NETWORK | (MSG_NM_UNKNOWN << 16),
};

enum nm_lib_err {
	ERR_NM_ENOENT = 1,  /* No such file or directory */
	ERR_NM_EIO,         /* I/O error */
	ERR_NM_EBADF,       /* Bad file number */
	ERR_NM_ENOMEM,      /* Out of memory */
	ERR_NM_EFAULT,      /* Bad address */
	ERR_NM_EBUSY,       /* Device or resource busy */
	ERR_NM_EINVAL,      /* Invalid argument */
	ERR_NM_ENOTTY,      /* Not a typewriter */
};

#define ERR_NM(type, errno) ((type) | (errno))

/**
 * Get IPCam's network related information.
 *
 * @param[in] msg_type	the type of information which to get
 * @param[in] rsp_buf	memory to storage requested information
 * @param[in] rsp_len	length of request information
 *
 * @return >=0:success <0:fail
 *
 * rts_nm_get_info() is used to get the IPCam's network related
 * informations, before use this funtion you should malloc enough memory
 * to storage the requested informations.
 */
int rts_nm_get_info(int msg_type, void *rsp_buf, int rsp_len);
#define rts_nm_get_info(msg_type, rsp_buf, rsp_len) \
		({ \
			int rtsnm_lcl_get(int type, void *buf, int len); \
			rtsnm_lcl_get(msg_type, rsp_buf, rsp_len); \
		}) \

/**
 * Set IPCam's network related information.
 *
 * @param[in] msg_type	type of information which to set
 * @param[in] req_buf	memory of information which to set
 * @param[in] req_len	length of information which to set
 *
 * @return >=0:success <0:fail
 *
 * rts_nm_set_info() is used to set the IPCam's network related
 * informations.
 */
int rts_nm_set_info(int msg_type, void *req_buf, int req_len);
#define rts_nm_set_info(msg_type, req_buf, req_len) \
		({ \
			int rtsnm_lcl_set(int type, void *buf, int len); \
			rtsnm_lcl_set(msg_type, req_buf, req_len); \
		}) \

enum {
	IP_ADDR,
	DST_IP_ADDR,
	SUBNET_MASK,
	DEFAULT_GATEWAY,
	HW_ADDR
} ADDR_T;

enum nm_net_ifname {
	WAN_PORT,
	LAN_PORT
};

enum nm_ap_mode {
	WISP_MODE = 0,
	BRIDGE_MODE
};

enum nm_ip_mode {
	STATIC_MODE,
	DHCP_MODE
};

enum nm_filter_type {
	WHITE_LIST,
	BLACK_LIST
};

enum nm_wps_type {
	WPS_DISABLE,
	WPS_PIN,
	WPS_PBC
};

enum nm_auth_type {
	OPEN_MODE,
	WEP_MODE,
	WPA_MODE,
	WPA2_MODE,
	WPA_WPA2_MODE
};

enum nm_cipher_type {
	AES_MODE,
	TKIP_MODE,
	AES_TKIP_MODE
};

struct nm_wan {
	int dhcpc;
	struct in_addr ipaddr;
	struct in_addr netmask;
	struct in_addr gateway;
	struct in_addr dns1;
	struct in_addr dns2;
};

struct nm_lan {
	int dhcpd;
	struct in_addr ipaddr;
	struct in_addr netmask;
	struct in_addr begin_ip;
	struct in_addr end_ip;
};

struct nm_pppoe {
	int enable;
	char username[32];
	char password[32];
	int status;
	struct in_addr ipaddr;
};


struct nm_ddns {
	int enable;
	int type;
	char domain[32];
	char username[32];
	char password[32];
};

struct nm_upnp {
	int enable;
	char friendlyname[64];
};

struct nm_bonjour {
	int enable;
	char hostname[64];
};

struct nm_ipfilter {
	int enable;
	int mode;
	int index;
	char ipf_buf[512];
};

struct nm_qos {
	int enable;
	int dscp;
};

struct nm_scan_info {
	char	essid[32];
	char	bssid[20];
	int	channel;
	int	signal;
	char	flag[64];
};

struct nm_sta {
	int	enable;
	char	essid[32];
	int	auth;
	int	cipher;
	int	index;
	char	password[64];
	int	wps_enable;
	int	wps_pbc;
	char	wps_pin[9];
	int	state;
};

struct nm_softap {
	int	enable;
	char	essid[32];
	int	channel;
	int	protocol;
	int	hide;
	int	auth;
	int	cipher;
	int	index;
	char	password[64];
	int	wps_enable;
	int	wps_pbc;
	char	wps_pin[9];
};

enum nm_status_type {
	DISABLE_MODE,
	CONNECT_MODE,
	WAIT_KEY_MODE,
	SCAN_MODE
};

enum nm_eth_type {
	WAN_MODE,
	LAN_MODE
};

struct nm_ipv6 {
	int	dhcp;
	struct	in6_addr ipaddr;
	struct	in6_addr netmask;
	struct	in6_addr gateway;
	char	ext_ipbuf[256];
};


#endif
