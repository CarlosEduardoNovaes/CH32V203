
bin/firmware.elf:     file format elf32-littleriscv


Disassembly of section .init:

00000000 <jump_reset>:
   0:	16e0006f          	j	16e <reset_handler>

00000004 <init_data>:
   4:	00000013 00000013 00000013 00000013     ................
  14:	00000013 00000013 00000013 00000013     ................
  24:	00000013 00000013 00000013 00000013     ................
  34:	00100073                                s...

Disassembly of section .text:

00000134 <main>:
 134:	40011737          	lui	a4,0x40011
 138:	80070713          	addi	a4,a4,-2048 # 40010800 <_eusrstack+0x2000e000>
 13c:	435c                	lw	a5,4(a4)
 13e:	300006b7          	lui	a3,0x30000
 142:	6521                	lui	a0,0x8
 144:	0792                	slli	a5,a5,0x4
 146:	8391                	srli	a5,a5,0x4
 148:	8fd5                	or	a5,a5,a3
 14a:	c35c                	sw	a5,4(a4)
 14c:	0036f7b7          	lui	a5,0x36f
 150:	e000f5b7          	lui	a1,0xe000f
 154:	e8078793          	addi	a5,a5,-384 # 36ee80 <system.c.9c8fb052+0x36eb09>
 158:	4754                	lw	a3,12(a4)
 15a:	8ea9                	xor	a3,a3,a0
 15c:	c754                	sw	a3,12(a4)
 15e:	4590                	lw	a2,8(a1)
 160:	963e                	add	a2,a2,a5
 162:	4594                	lw	a3,8(a1)
 164:	8e91                	sub	a3,a3,a2
 166:	fe06cee3          	bltz	a3,162 <main+0x2e>
 16a:	b7fd                	j	158 <main+0x24>

0000016c <ADC1_2_IRQHandler>:
 16c:	a001                	j	16c <ADC1_2_IRQHandler>

0000016e <reset_handler>:
 16e:	13400793          	li	a5,308
 172:	20000197          	auipc	gp,0x20000
 176:	68e18193          	addi	gp,gp,1678 # 20000800 <__global_pointer$>
 17a:	20002117          	auipc	sp,0x20002
 17e:	68610113          	addi	sp,sp,1670 # 20002800 <_eusrstack>
 182:	457d                	li	a0,31
 184:	bc051073          	csrw	0xbc0,a0
 188:	08800513          	li	a0,136
 18c:	30051073          	csrw	mstatus,a0
 190:	458d                	li	a1,3
 192:	80459073          	csrw	0x804,a1
 196:	03800513          	li	a0,56
 19a:	8d4d                	or	a0,a0,a1
 19c:	30551073          	csrw	mtvec,a0
 1a0:	34179073          	csrw	mepc,a5
 1a4:	200007b7          	lui	a5,0x20000
 1a8:	200006b7          	lui	a3,0x20000
 1ac:	25000713          	li	a4,592
 1b0:	00078793          	mv	a5,a5
 1b4:	00068693          	mv	a3,a3
 1b8:	08d7e363          	bltu	a5,a3,23e <reset_handler+0xd0>
 1bc:	200007b7          	lui	a5,0x20000
 1c0:	20000737          	lui	a4,0x20000
 1c4:	00078793          	mv	a5,a5
 1c8:	00070713          	mv	a4,a4
 1cc:	06e7ee63          	bltu	a5,a4,248 <reset_handler+0xda>
 1d0:	400217b7          	lui	a5,0x40021
 1d4:	009f0737          	lui	a4,0x9f0
 1d8:	c798                	sw	a4,8(a5)
 1da:	40024737          	lui	a4,0x40024
 1de:	80070713          	addi	a4,a4,-2048 # 40023800 <_eusrstack+0x20021000>
 1e2:	4314                	lw	a3,0(a4)
 1e4:	0106e693          	ori	a3,a3,16
 1e8:	c314                	sw	a3,0(a4)
 1ea:	003c0737          	lui	a4,0x3c0
 1ee:	c3d8                	sw	a4,4(a5)
 1f0:	4398                	lw	a4,0(a5)
 1f2:	010006b7          	lui	a3,0x1000
 1f6:	8f55                	or	a4,a4,a3
 1f8:	c398                	sw	a4,0(a5)
 1fa:	4398                	lw	a4,0(a5)
 1fc:	00671693          	slli	a3,a4,0x6
 200:	fe06dde3          	bgez	a3,1fa <reset_handler+0x8c>
 204:	43d8                	lw	a4,4(a5)
 206:	46a1                	li	a3,8
 208:	00276713          	ori	a4,a4,2
 20c:	c3d8                	sw	a4,4(a5)
 20e:	400217b7          	lui	a5,0x40021
 212:	43d8                	lw	a4,4(a5)
 214:	8b31                	andi	a4,a4,12
 216:	fed71ee3          	bne	a4,a3,212 <reset_handler+0xa4>
 21a:	40022637          	lui	a2,0x40022
 21e:	4a18                	lw	a4,16(a2)
 220:	fe0006b7          	lui	a3,0xfe000
 224:	16fd                	addi	a3,a3,-1 # fdffffff <_eusrstack+0xddffd7ff>
 226:	8f75                	and	a4,a4,a3
 228:	ca18                	sw	a4,16(a2)
 22a:	4695                	li	a3,5
 22c:	e000f737          	lui	a4,0xe000f
 230:	c314                	sw	a3,0(a4)
 232:	4f98                	lw	a4,24(a5)
 234:	03c76713          	ori	a4,a4,60
 238:	cf98                	sw	a4,24(a5)
 23a:	30200073          	mret
 23e:	4310                	lw	a2,0(a4)
 240:	0711                	addi	a4,a4,4 # e000f004 <_eusrstack+0xc000c804>
 242:	c390                	sw	a2,0(a5)
 244:	0791                	addi	a5,a5,4 # 40021004 <_eusrstack+0x2001e804>
 246:	bf8d                	j	1b8 <reset_handler+0x4a>
 248:	0007a023          	sw	zero,0(a5)
 24c:	0791                	addi	a5,a5,4
 24e:	bfbd                	j	1cc <reset_handler+0x5e>
