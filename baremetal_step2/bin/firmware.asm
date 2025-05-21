
bin/firmware.elf:     file format elf32-littleriscv


Disassembly of section .init:

00000000 <jump_reset>:
<<<<<<< HEAD
   0:	2260006f          	j	226 <reset_handler>

00000004 <init_data>:
   4:	00000013 00000013 00000013 00000013     ................
  14:	00000013 00000013 00000013 00000013     ................
  24:	00000013 00000013 00000013 00000013     ................
  34:	00100073                                s...

Disassembly of section .text:

00000134 <ADC1_2_IRQHandler>:
 134:	a001                	j	134 <ADC1_2_IRQHandler>

00000136 <main>:
 136:	40021737          	lui	a4,0x40021
 13a:	009f06b7          	lui	a3,0x9f0
 13e:	c714                	sw	a3,8(a4)
 140:	400247b7          	lui	a5,0x40024
 144:	8007a683          	lw	a3,-2048(a5) # 40023800 <_eusrstack+0x20021000>
 148:	003c05b7          	lui	a1,0x3c0
 14c:	01000637          	lui	a2,0x1000
 150:	0106e693          	ori	a3,a3,16
 154:	80d7a023          	sw	a3,-2048(a5)
 158:	c34c                	sw	a1,4(a4)
 15a:	431c                	lw	a5,0(a4)
 15c:	8fd1                	or	a5,a5,a2
 15e:	c31c                	sw	a5,0(a4)
 160:	431c                	lw	a5,0(a4)
 162:	00679693          	slli	a3,a5,0x6
 166:	fe06dde3          	bgez	a3,160 <main+0x2a>
 16a:	435c                	lw	a5,4(a4)
 16c:	400216b7          	lui	a3,0x40021
 170:	4621                	li	a2,8
 172:	0027e793          	ori	a5,a5,2
 176:	c35c                	sw	a5,4(a4)
 178:	42dc                	lw	a5,4(a3)
 17a:	8bb1                	andi	a5,a5,12
 17c:	fec79ee3          	bne	a5,a2,178 <main+0x42>
 180:	40022637          	lui	a2,0x40022
 184:	4a1c                	lw	a5,16(a2)
 186:	fe000737          	lui	a4,0xfe000
 18a:	177d                	addi	a4,a4,-1 # fdffffff <_eusrstack+0xddffd7ff>
 18c:	8ff9                	and	a5,a5,a4
 18e:	ca1c                	sw	a5,16(a2)
 190:	4715                	li	a4,5
 192:	e000f7b7          	lui	a5,0xe000f
 196:	c398                	sw	a4,0(a5)
 198:	4e98                	lw	a4,24(a3)
 19a:	40011637          	lui	a2,0x40011
 19e:	80060613          	addi	a2,a2,-2048 # 40010800 <_eusrstack+0x2000e000>
 1a2:	03c76713          	ori	a4,a4,60
 1a6:	ce98                	sw	a4,24(a3)
 1a8:	4258                	lw	a4,4(a2)
 1aa:	f00005b7          	lui	a1,0xf0000
 1ae:	300006b7          	lui	a3,0x30000
 1b2:	8f6d                	and	a4,a4,a1
 1b4:	c258                	sw	a4,4(a2)
 1b6:	4258                	lw	a4,4(a2)
 1b8:	65a1                	lui	a1,0x8
 1ba:	006de537          	lui	a0,0x6de
 1be:	8f55                	or	a4,a4,a3
 1c0:	c258                	sw	a4,4(a2)
 1c2:	06021837          	lui	a6,0x6021
 1c6:	ca0c                	sw	a1,16(a2)
 1c8:	d0050513          	addi	a0,a0,-768 # 6ddd00 <system.cxx.7b0de659+0x6dd73a>
 1cc:	60080813          	addi	a6,a6,1536 # 6021600 <system.cxx.7b0de659+0x602103a>
 1d0:	ca4c                	sw	a1,20(a2)
 1d2:	4794                	lw	a3,8(a5)
 1d4:	96aa                	add	a3,a3,a0
 1d6:	4798                	lw	a4,8(a5)
 1d8:	8f15                	sub	a4,a4,a3
 1da:	fe074ee3          	bltz	a4,1d6 <main+0xa0>
 1de:	ca0c                	sw	a1,16(a2)
 1e0:	4794                	lw	a3,8(a5)
 1e2:	96aa                	add	a3,a3,a0
 1e4:	4798                	lw	a4,8(a5)
 1e6:	8f15                	sub	a4,a4,a3
 1e8:	fe074ee3          	bltz	a4,1e4 <main+0xae>
 1ec:	ca4c                	sw	a1,20(a2)
 1ee:	4794                	lw	a3,8(a5)
 1f0:	96aa                	add	a3,a3,a0
 1f2:	4798                	lw	a4,8(a5)
 1f4:	8f15                	sub	a4,a4,a3
 1f6:	fe074ee3          	bltz	a4,1f2 <main+0xbc>
 1fa:	ca0c                	sw	a1,16(a2)
 1fc:	4794                	lw	a3,8(a5)
 1fe:	96aa                	add	a3,a3,a0
 200:	4798                	lw	a4,8(a5)
 202:	8f15                	sub	a4,a4,a3
 204:	fe074ee3          	bltz	a4,200 <main+0xca>
 208:	ca4c                	sw	a1,20(a2)
 20a:	4794                	lw	a3,8(a5)
 20c:	96aa                	add	a3,a3,a0
 20e:	4798                	lw	a4,8(a5)
 210:	8f15                	sub	a4,a4,a3
 212:	fe074ee3          	bltz	a4,20e <main+0xd8>
 216:	ca0c                	sw	a1,16(a2)
 218:	4794                	lw	a3,8(a5)
 21a:	96c2                	add	a3,a3,a6
 21c:	4798                	lw	a4,8(a5)
 21e:	8f15                	sub	a4,a4,a3
 220:	fe074ee3          	bltz	a4,21c <main+0xe6>
 224:	b775                	j	1d0 <main+0x9a>

00000226 <reset_handler>:
 226:	13600793          	li	a5,310
 22a:	20000197          	auipc	gp,0x20000
 22e:	5d618193          	addi	gp,gp,1494 # 20000800 <__global_pointer$>
 232:	20002117          	auipc	sp,0x20002
 236:	5ce10113          	addi	sp,sp,1486 # 20002800 <_eusrstack>
 23a:	457d                	li	a0,31
 23c:	bc051073          	csrw	0xbc0,a0
 240:	08800513          	li	a0,136
 244:	30051073          	csrw	mstatus,a0
 248:	458d                	li	a1,3
 24a:	80459073          	csrw	0x804,a1
 24e:	03800513          	li	a0,56
 252:	8d4d                	or	a0,a0,a1
 254:	30551073          	csrw	mtvec,a0
 258:	34179073          	csrw	mepc,a5
 25c:	20000737          	lui	a4,0x20000
 260:	200007b7          	lui	a5,0x20000
 264:	00070613          	mv	a2,a4
 268:	00078793          	mv	a5,a5
 26c:	02f67563          	bgeu	a2,a5,296 <startup_ch32v203.c.f0a6343f+0x52>
 270:	fff78693          	addi	a3,a5,-1 # 1fffffff <system.cxx.7b0de659+0x1ffffa39>
 274:	8e91                	sub	a3,a3,a2
 276:	9af1                	andi	a3,a3,-4
 278:	2e800613          	li	a2,744
 27c:	0691                	addi	a3,a3,4 # 30000004 <_eusrstack+0xfffd804>
 27e:	00070713          	mv	a4,a4
 282:	96b2                	add	a3,a3,a2
 284:	2e800793          	li	a5,744
 288:	4390                	lw	a2,0(a5)
 28a:	0791                	addi	a5,a5,4
 28c:	0711                	addi	a4,a4,4 # 20000004 <_data_vma+0x4>
 28e:	fec72e23          	sw	a2,-4(a4)
 292:	fed79be3          	bne	a5,a3,288 <startup_ch32v203.c.f0a6343f+0x44>
 296:	2e800793          	li	a5,744
 29a:	2e800713          	li	a4,744
 29e:	40e78933          	sub	s2,a5,a4
 2a2:	40295913          	srai	s2,s2,0x2
 2a6:	00e78b63          	beq	a5,a4,2bc <startup_ch32v203.c.f0a6343f+0x78>
 2aa:	2e800413          	li	s0,744
 2ae:	4481                	li	s1,0
 2b0:	401c                	lw	a5,0(s0)
 2b2:	0485                	addi	s1,s1,1
 2b4:	0411                	addi	s0,s0,4
 2b6:	9782                	jalr	a5
 2b8:	ff24ece3          	bltu	s1,s2,2b0 <startup_ch32v203.c.f0a6343f+0x6c>
 2bc:	2e800793          	li	a5,744
 2c0:	2e800713          	li	a4,744
 2c4:	40e78933          	sub	s2,a5,a4
 2c8:	40295913          	srai	s2,s2,0x2
 2cc:	00e78b63          	beq	a5,a4,2e2 <startup_ch32v203.c.f0a6343f+0x9e>
 2d0:	2e800413          	li	s0,744
 2d4:	4481                	li	s1,0
 2d6:	401c                	lw	a5,0(s0)
 2d8:	0485                	addi	s1,s1,1
 2da:	0411                	addi	s0,s0,4
 2dc:	9782                	jalr	a5
 2de:	ff24ece3          	bltu	s1,s2,2d6 <startup_ch32v203.c.f0a6343f+0x92>
 2e2:	30200073          	mret
	...
=======
   0:	1c80006f          	j	1c8 <reset_handler>
   4:	0001                	nop
	...

00000008 <init_data>:
   8:	0013 0000 0013 0000 0013 0000 0013 0000     ................
  18:	0013 0000 0013 0000 0013 0000 0013 0000     ................
  28:	0013 0000 0013 0000 0013 0000 0013 0000     ................
  38:	0073 0010                                   s...

Disassembly of section .text:

00000138 <__libc_init_array>:
 138:	1101                	addi	sp,sp,-32
 13a:	ce06                	sw	ra,28(sp)
 13c:	cc22                	sw	s0,24(sp)
 13e:	1000                	addi	s0,sp,32
 140:	3f400713          	li	a4,1012
 144:	3f400793          	li	a5,1012
 148:	40f707b3          	sub	a5,a4,a5
 14c:	8789                	srai	a5,a5,0x2
 14e:	fef42423          	sw	a5,-24(s0)
 152:	fe042623          	sw	zero,-20(s0)
 156:	a831                	j	172 <__libc_init_array+0x3a>
 158:	3f400713          	li	a4,1012
 15c:	fec42783          	lw	a5,-20(s0)
 160:	078a                	slli	a5,a5,0x2
 162:	97ba                	add	a5,a5,a4
 164:	439c                	lw	a5,0(a5)
 166:	9782                	jalr	a5
 168:	fec42783          	lw	a5,-20(s0)
 16c:	0785                	addi	a5,a5,1
 16e:	fef42623          	sw	a5,-20(s0)
 172:	fec42703          	lw	a4,-20(s0)
 176:	fe842783          	lw	a5,-24(s0)
 17a:	fcf76fe3          	bltu	a4,a5,158 <__libc_init_array+0x20>
 17e:	3f400713          	li	a4,1012
 182:	3f400793          	li	a5,1012
 186:	40f707b3          	sub	a5,a4,a5
 18a:	8789                	srai	a5,a5,0x2
 18c:	fef42423          	sw	a5,-24(s0)
 190:	fe042623          	sw	zero,-20(s0)
 194:	a831                	j	1b0 <__libc_init_array+0x78>
 196:	3f400713          	li	a4,1012
 19a:	fec42783          	lw	a5,-20(s0)
 19e:	078a                	slli	a5,a5,0x2
 1a0:	97ba                	add	a5,a5,a4
 1a2:	439c                	lw	a5,0(a5)
 1a4:	9782                	jalr	a5
 1a6:	fec42783          	lw	a5,-20(s0)
 1aa:	0785                	addi	a5,a5,1
 1ac:	fef42623          	sw	a5,-20(s0)
 1b0:	fec42703          	lw	a4,-20(s0)
 1b4:	fe842783          	lw	a5,-24(s0)
 1b8:	fcf76fe3          	bltu	a4,a5,196 <__libc_init_array+0x5e>
 1bc:	0001                	nop
 1be:	0001                	nop
 1c0:	40f2                	lw	ra,28(sp)
 1c2:	4462                	lw	s0,24(sp)
 1c4:	6105                	addi	sp,sp,32
 1c6:	8082                	ret

000001c8 <reset_handler>:
 1c8:	23400793          	li	a5,564
 1cc:	20000197          	auipc	gp,0x20000
 1d0:	63418193          	addi	gp,gp,1588 # 20000800 <__global_pointer$>
 1d4:	20002117          	auipc	sp,0x20002
 1d8:	62c10113          	addi	sp,sp,1580 # 20002800 <_eusrstack>
 1dc:	457d                	li	a0,31
 1de:	bc051073          	csrw	0xbc0,a0
 1e2:	08800513          	li	a0,136
 1e6:	30051073          	csrw	mstatus,a0
 1ea:	458d                	li	a1,3
 1ec:	80459073          	csrw	0x804,a1
 1f0:	03c00513          	li	a0,60
 1f4:	8d4d                	or	a0,a0,a1
 1f6:	30551073          	csrw	mtvec,a0
 1fa:	34179073          	csrw	mepc,a5
 1fe:	3f400493          	li	s1,1012
 202:	200007b7          	lui	a5,0x20000
 206:	00078093          	mv	ra,a5
 20a:	a809                	j	21c <reset_handler+0x54>
 20c:	8726                	mv	a4,s1
 20e:	00470493          	addi	s1,a4,4
 212:	8786                	mv	a5,ra
 214:	00478093          	addi	ra,a5,4 # 20000004 <_data_vma+0x4>
 218:	4318                	lw	a4,0(a4)
 21a:	c398                	sw	a4,0(a5)
 21c:	200007b7          	lui	a5,0x20000
 220:	00078793          	mv	a5,a5
 224:	fef0e4e3          	bltu	ra,a5,20c <reset_handler+0x44>
 228:	3f01                	jal	138 <__libc_init_array>
 22a:	30200073          	mret
 22e:	0001                	nop

00000230 <ADC1_2_IRQHandler>:
 230:	0001                	nop
 232:	bffd                	j	230 <ADC1_2_IRQHandler>

00000234 <main>:
 234:	1141                	addi	sp,sp,-16
 236:	c606                	sw	ra,12(sp)
 238:	c422                	sw	s0,8(sp)
 23a:	0800                	addi	s0,sp,16
 23c:	2845                	jal	2ec <SYS_init>
 23e:	2825                	jal	276 <_ZN6pinledW6pinled4initEv>
 240:	2849                	jal	2d2 <_ZN6pinledW6pinled7turnOffEv>
 242:	289d                	jal	2b8 <_ZN6pinledW6pinled6turnOnEv>
 244:	00dbc7b7          	lui	a5,0xdbc
 248:	a0078513          	addi	a0,a5,-1536 # dbba00 <system.cxx.7b0de659+0xdbb37b>
 24c:	22b5                	jal	3b8 <DLY_ticks>
 24e:	2051                	jal	2d2 <_ZN6pinledW6pinled7turnOffEv>
 250:	00dbc7b7          	lui	a5,0xdbc
 254:	a0078513          	addi	a0,a5,-1536 # dbba00 <system.cxx.7b0de659+0xdbb37b>
 258:	2285                	jal	3b8 <DLY_ticks>
 25a:	28b9                	jal	2b8 <_ZN6pinledW6pinled6turnOnEv>
 25c:	00dbc7b7          	lui	a5,0xdbc
 260:	a0078513          	addi	a0,a5,-1536 # dbba00 <system.cxx.7b0de659+0xdbb37b>
 264:	2a91                	jal	3b8 <DLY_ticks>
 266:	20b5                	jal	2d2 <_ZN6pinledW6pinled7turnOffEv>
 268:	060217b7          	lui	a5,0x6021
 26c:	60078513          	addi	a0,a5,1536 # 6021600 <system.cxx.7b0de659+0x6020f7b>
 270:	22a1                	jal	3b8 <DLY_ticks>
 272:	0001                	nop
 274:	b7f9                	j	242 <main+0xe>

00000276 <_ZN6pinledW6pinled4initEv>:
 276:	1141                	addi	sp,sp,-16
 278:	c622                	sw	s0,12(sp)
 27a:	0800                	addi	s0,sp,16
 27c:	400117b7          	lui	a5,0x40011
 280:	80078793          	addi	a5,a5,-2048 # 40010800 <_eusrstack+0x2000e000>
 284:	43d4                	lw	a3,4(a5)
 286:	400117b7          	lui	a5,0x40011
 28a:	80078793          	addi	a5,a5,-2048 # 40010800 <_eusrstack+0x2000e000>
 28e:	f0000737          	lui	a4,0xf0000
 292:	8f75                	and	a4,a4,a3
 294:	c3d8                	sw	a4,4(a5)
 296:	400117b7          	lui	a5,0x40011
 29a:	80078793          	addi	a5,a5,-2048 # 40010800 <_eusrstack+0x2000e000>
 29e:	43d4                	lw	a3,4(a5)
 2a0:	400117b7          	lui	a5,0x40011
 2a4:	80078793          	addi	a5,a5,-2048 # 40010800 <_eusrstack+0x2000e000>
 2a8:	30000737          	lui	a4,0x30000
 2ac:	8f55                	or	a4,a4,a3
 2ae:	c3d8                	sw	a4,4(a5)
 2b0:	0001                	nop
 2b2:	4432                	lw	s0,12(sp)
 2b4:	0141                	addi	sp,sp,16
 2b6:	8082                	ret

000002b8 <_ZN6pinledW6pinled6turnOnEv>:
 2b8:	1141                	addi	sp,sp,-16
 2ba:	c622                	sw	s0,12(sp)
 2bc:	0800                	addi	s0,sp,16
 2be:	400117b7          	lui	a5,0x40011
 2c2:	80078793          	addi	a5,a5,-2048 # 40010800 <_eusrstack+0x2000e000>
 2c6:	6721                	lui	a4,0x8
 2c8:	cbd8                	sw	a4,20(a5)
 2ca:	0001                	nop
 2cc:	4432                	lw	s0,12(sp)
 2ce:	0141                	addi	sp,sp,16
 2d0:	8082                	ret

000002d2 <_ZN6pinledW6pinled7turnOffEv>:
 2d2:	1141                	addi	sp,sp,-16
 2d4:	c622                	sw	s0,12(sp)
 2d6:	0800                	addi	s0,sp,16
 2d8:	400117b7          	lui	a5,0x40011
 2dc:	80078793          	addi	a5,a5,-2048 # 40010800 <_eusrstack+0x2000e000>
 2e0:	6721                	lui	a4,0x8
 2e2:	cb98                	sw	a4,16(a5)
 2e4:	0001                	nop
 2e6:	4432                	lw	s0,12(sp)
 2e8:	0141                	addi	sp,sp,16
 2ea:	8082                	ret

000002ec <SYS_init>:
 2ec:	1141                	addi	sp,sp,-16
 2ee:	c606                	sw	ra,12(sp)
 2f0:	c422                	sw	s0,8(sp)
 2f2:	0800                	addi	s0,sp,16
 2f4:	400217b7          	lui	a5,0x40021
 2f8:	009f0737          	lui	a4,0x9f0
 2fc:	c798                	sw	a4,8(a5)
 2fe:	2825                	jal	336 <CLK_init_HSI_PLL>
 300:	400227b7          	lui	a5,0x40022
 304:	4b94                	lw	a3,16(a5)
 306:	400227b7          	lui	a5,0x40022
 30a:	fe000737          	lui	a4,0xfe000
 30e:	177d                	addi	a4,a4,-1 # fdffffff <_eusrstack+0xddffd7ff>
 310:	8f75                	and	a4,a4,a3
 312:	cb98                	sw	a4,16(a5)
 314:	e000f7b7          	lui	a5,0xe000f
 318:	4715                	li	a4,5
 31a:	c398                	sw	a4,0(a5)
 31c:	400217b7          	lui	a5,0x40021
 320:	4f98                	lw	a4,24(a5)
 322:	400217b7          	lui	a5,0x40021
 326:	03c76713          	ori	a4,a4,60
 32a:	cf98                	sw	a4,24(a5)
 32c:	0001                	nop
 32e:	40b2                	lw	ra,12(sp)
 330:	4422                	lw	s0,8(sp)
 332:	0141                	addi	sp,sp,16
 334:	8082                	ret

00000336 <CLK_init_HSI_PLL>:
 336:	1141                	addi	sp,sp,-16
 338:	c622                	sw	s0,12(sp)
 33a:	0800                	addi	s0,sp,16
 33c:	400247b7          	lui	a5,0x40024
 340:	80078793          	addi	a5,a5,-2048 # 40023800 <_eusrstack+0x20021000>
 344:	4398                	lw	a4,0(a5)
 346:	400247b7          	lui	a5,0x40024
 34a:	80078793          	addi	a5,a5,-2048 # 40023800 <_eusrstack+0x20021000>
 34e:	01076713          	ori	a4,a4,16
 352:	c398                	sw	a4,0(a5)
 354:	400217b7          	lui	a5,0x40021
 358:	003c0737          	lui	a4,0x3c0
 35c:	c3d8                	sw	a4,4(a5)
 35e:	400217b7          	lui	a5,0x40021
 362:	4394                	lw	a3,0(a5)
 364:	400217b7          	lui	a5,0x40021
 368:	01000737          	lui	a4,0x1000
 36c:	8f55                	or	a4,a4,a3
 36e:	c398                	sw	a4,0(a5)
 370:	0001                	nop
 372:	400217b7          	lui	a5,0x40021
 376:	4398                	lw	a4,0(a5)
 378:	020007b7          	lui	a5,0x2000
 37c:	8ff9                	and	a5,a5,a4
 37e:	0017b793          	seqz	a5,a5
 382:	0ff7f793          	zext.b	a5,a5
 386:	f7f5                	bnez	a5,372 <CLK_init_HSI_PLL+0x3c>
 388:	400217b7          	lui	a5,0x40021
 38c:	43d8                	lw	a4,4(a5)
 38e:	400217b7          	lui	a5,0x40021
 392:	00276713          	ori	a4,a4,2
 396:	c3d8                	sw	a4,4(a5)
 398:	0001                	nop
 39a:	400217b7          	lui	a5,0x40021
 39e:	43dc                	lw	a5,4(a5)
 3a0:	8bb1                	andi	a5,a5,12
 3a2:	17e1                	addi	a5,a5,-8 # 40020ff8 <_eusrstack+0x2001e7f8>
 3a4:	00f037b3          	snez	a5,a5
 3a8:	0ff7f793          	zext.b	a5,a5
 3ac:	f7fd                	bnez	a5,39a <CLK_init_HSI_PLL+0x64>
 3ae:	0001                	nop
 3b0:	0001                	nop
 3b2:	4432                	lw	s0,12(sp)
 3b4:	0141                	addi	sp,sp,16
 3b6:	8082                	ret

000003b8 <DLY_ticks>:
 3b8:	7179                	addi	sp,sp,-48
 3ba:	d622                	sw	s0,44(sp)
 3bc:	1800                	addi	s0,sp,48
 3be:	fca42e23          	sw	a0,-36(s0)
 3c2:	e000f7b7          	lui	a5,0xe000f
 3c6:	479c                	lw	a5,8(a5)
 3c8:	fdc42703          	lw	a4,-36(s0)
 3cc:	97ba                	add	a5,a5,a4
 3ce:	fef42623          	sw	a5,-20(s0)
 3d2:	0001                	nop
 3d4:	e000f7b7          	lui	a5,0xe000f
 3d8:	4798                	lw	a4,8(a5)
 3da:	fec42783          	lw	a5,-20(s0)
 3de:	40f707b3          	sub	a5,a4,a5
 3e2:	83fd                	srli	a5,a5,0x1f
 3e4:	0ff7f793          	zext.b	a5,a5
 3e8:	f7f5                	bnez	a5,3d4 <DLY_ticks+0x1c>
 3ea:	0001                	nop
 3ec:	0001                	nop
 3ee:	5432                	lw	s0,44(sp)
 3f0:	6145                	addi	sp,sp,48
 3f2:	8082                	ret
>>>>>>> c8de80b9b0cb1787b04404e7e3866979d5adc571
