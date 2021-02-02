[355605.420537] p1test: loading out-of-tree module taints kernel.
[355605.421007] p1test: module verification failed: signature and/or required key missing - tainting kernel
[355605.423335] p1test init
[355605.423421] BUG: unable to handle page fault for address: ffffec0000000000
[355605.424221] #PF: supervisor read access in kernel mode
[355605.424692] #PF: error_code(0x0000) - not-present page
[355605.425083] PGD 0 P4D 0 
[355605.425463] Oops: 0000 [#1] SMP PTI
[355605.425864] CPU: 0 PID: 296321 Comm: insmod Tainted: G           OE     5.8.0 #3
[355605.426241] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 07/29/2019
[355605.427166] RIP: 0010:hello_init+0x32/0x1000 [p1test]
[355605.427713] Code: c6 3c 90 a4 c0 48 c7 c7 43 90 a4 c0 48 89 e5 41 54 49 bc 0a 00 00 00 00 ec ff ff 53 bb fb ff 3f 00 48 c1 e3 2a e8 51 08 99 c0 <0f> be 33 48 c7 c7 4e 90 a4 c0 48 ff c3 e8 3f 08 99 c0 4c 39 e3 75
[355605.429543] RSP: 0018:ffffc900031afc68 EFLAGS: 00010246
[355605.430054] RAX: 000000000000000b RBX: ffffec0000000000 RCX: ffff888139e18cd8
[355605.430480] RDX: 0000000000000000 RSI: 0000000000000027 RDI: ffff888139e18cd0
[355605.431167] RBP: ffffc900031afc78 R08: 0000000000000729 R09: 0000000000000004
[355605.431711] R10: 0000000000000000 R11: 0000000000000001 R12: ffffec000000000a
[355605.432209] R13: ffff888085d69d30 R14: ffffffffc0a4a000 R15: 0000000000000000
[355605.432635] FS:  00007f7ba9079540(0000) GS:ffff888139e00000(0000) knlGS:0000000000000000
[355605.433053] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
[355605.433486] CR2: ffffec0000000000 CR3: 00000000b14d6006 CR4: 00000000003606f0
[355605.433946] Call Trace:
[355605.434413]  ? 0xffffffffc0789000
[355605.435159]  do_one_initcall+0x4a/0x200
[355605.435663]  ? _cond_resched+0x1a/0x50
[355605.436115]  ? kmem_cache_alloc_trace+0x168/0x240
[355605.436668]  do_init_module+0x62/0x270
[355605.437103]  load_module+0x2466/0x2720
[355605.437832]  ? security_kernel_post_read_file+0x5c/0x70
[355605.438286]  __do_sys_finit_module+0xbe/0x120
[355605.438990]  __x64_sys_finit_module+0x1a/0x20
[355605.439377]  do_syscall_64+0x52/0xc0
[355605.439758]  entry_SYSCALL_64_after_hwframe+0x44/0xa9
[355605.440124] RIP: 0033:0x7f7ba91b567d
[355605.440511] Code: 00 c3 66 2e 0f 1f 84 00 00 00 00 00 90 f3 0f 1e fa 48 89 f8 48 89 f7 48 89 d6 48 89 ca 4d 89 c2 4d 89 c8 4c 8b 4c 24 08 0f 05 <48> 3d 01 f0 ff ff 73 01 c3 48 8b 0d bb f7 0c 00 f7 d8 64 89 01 48
[355605.441691] RSP: 002b:00007ffd9ddcabc8 EFLAGS: 00000246 ORIG_RAX: 0000000000000139
[355605.442196] RAX: ffffffffffffffda RBX: 0000557f80024780 RCX: 00007f7ba91b567d
[355605.442685] RDX: 0000000000000000 RSI: 0000557f7ef20358 RDI: 0000000000000003
[355605.443075] RBP: 0000000000000000 R08: 0000000000000000 R09: 00007f7ba9289580
[355605.443463] R10: 0000000000000003 R11: 0000000000000246 R12: 0000557f7ef20358
[355605.443872] R13: 0000000000000000 R14: 0000557f80024750 R15: 0000000000000000
[355605.444248] Modules linked in: p1test(OE+) ufs qnx4 hfsplus hfs minix ntfs msdos jfs xfs cpuid vsock_loopback vmw_vsock_virtio_transport_common vmw_vsock_vmci_transport vsock dm_multipath scsi_dh_rdac scsi_dh_emc scsi_dh_alua snd_ens1371 snd_ac97_codec btusb btrtl gameport btbcm snd_rawmidi btintel bluetooth intel_rapl_msr snd_seq_device intel_rapl_common ac97_bus snd_pcm rapl joydev input_leds snd_timer vmw_balloon ecdh_generic serio_raw snd ecc soundcore vmw_vmci mac_hid sch_fq_codel ip_tables x_tables autofs4 btrfs blake2b_generic raid10 raid456 async_raid6_recov async_memcpy async_pq async_xor async_tx xor raid6_pq libcrc32c raid1 raid0 multipath linear hid_generic usbhid hid vmwgfx ttm drm_kms_helper syscopyarea sysfillrect sysimgblt fb_sys_fops cec rc_core drm crct10dif_pclmul crc32_pclmul ghash_clmulni_intel e1000 aesni_intel psmouse crypto_simd ahci libahci cryptd glue_helper mptspi mptscsih mptbase scsi_transport_spi pata_acpi i2c_piix4
[355605.448398] CR2: ffffec0000000000
[355605.448858] ---[ end trace c5259a96b1c2c22c ]---
[355605.449304] RIP: 0010:hello_init+0x32/0x1000 [p1test]
[355605.450165] Code: c6 3c 90 a4 c0 48 c7 c7 43 90 a4 c0 48 89 e5 41 54 49 bc 0a 00 00 00 00 ec ff ff 53 bb fb ff 3f 00 48 c1 e3 2a e8 51 08 99 c0 <0f> be 33 48 c7 c7 4e 90 a4 c0 48 ff c3 e8 3f 08 99 c0 4c 39 e3 75
[355605.453111] RSP: 0018:ffffc900031afc68 EFLAGS: 00010246
[355605.453862] RAX: 000000000000000b RBX: ffffec0000000000 RCX: ffff888139e18cd8
[355605.454304] RDX: 0000000000000000 RSI: 0000000000000027 RDI: ffff888139e18cd0
[355605.454759] RBP: ffffc900031afc78 R08: 0000000000000729 R09: 0000000000000004
[355605.455198] R10: 0000000000000000 R11: 0000000000000001 R12: ffffec000000000a
[355605.455707] R13: ffff888085d69d30 R14: ffffffffc0a4a000 R15: 0000000000000000
[355605.456160] FS:  00007f7ba9079540(0000) GS:ffff888139e00000(0000) knlGS:0000000000000000
[355605.456620] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
[355605.457070] CR2: ffffec0000000000 CR3: 00000000b14d6006 CR4: 00000000003606f0