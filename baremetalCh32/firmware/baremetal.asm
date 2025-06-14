
firmware/baremetal.elf:     file format elf32-littleriscv


Disassembly of section .init:

00000000 <jump_reset>:
   0:	24c0006f          	j	24c <reset_handler>

00000004 <init_data>:
   4:	00000013 00000013 00000013 00000013     ................
  14:	00000013 00000013 00000013 00000013     ................
  24:	00000013 00000013 00000013 00000013     ................
  34:	00100073                                s...

Disassembly of section .text:

00000134 <main>:
 134:	40021737          	lui	a4,0x40021
 138:	009f06b7          	lui	a3,0x9f0
 13c:	c714                	sw	a3,8(a4)
 13e:	400247b7          	lui	a5,0x40024
 142:	8007a683          	lw	a3,-2048(a5) # 40023800 <_eusrstack+0x20021000>
 146:	003c05b7          	lui	a1,0x3c0
 14a:	01000637          	lui	a2,0x1000
 14e:	0106e693          	ori	a3,a3,16
 152:	80d7a023          	sw	a3,-2048(a5)
 156:	c34c                	sw	a1,4(a4)
 158:	431c                	lw	a5,0(a4)
 15a:	8fd1                	or	a5,a5,a2
 15c:	c31c                	sw	a5,0(a4)
 15e:	431c                	lw	a5,0(a4)
 160:	00679693          	slli	a3,a5,0x6
 164:	fe06dde3          	bgez	a3,15e <main+0x2a>
 168:	435c                	lw	a5,4(a4)
 16a:	400216b7          	lui	a3,0x40021
 16e:	4621                	li	a2,8
 170:	0027e793          	ori	a5,a5,2
 174:	c35c                	sw	a5,4(a4)
 176:	42dc                	lw	a5,4(a3)
 178:	8bb1                	andi	a5,a5,12
 17a:	fec79ee3          	bne	a5,a2,176 <main+0x42>
 17e:	40022637          	lui	a2,0x40022
 182:	4a1c                	lw	a5,16(a2)
 184:	fe000737          	lui	a4,0xfe000
 188:	177d                	addi	a4,a4,-1 # fdffffff <_eusrstack+0xddffd7ff>
 18a:	8ff9                	and	a5,a5,a4
 18c:	ca1c                	sw	a5,16(a2)
 18e:	4715                	li	a4,5
 190:	e000f7b7          	lui	a5,0xe000f
 194:	c398                	sw	a4,0(a5)
 196:	4e90                	lw	a2,24(a3)
 198:	40011737          	lui	a4,0x40011
 19c:	f00005b7          	lui	a1,0xf0000
 1a0:	03c66613          	ori	a2,a2,60
 1a4:	ce90                	sw	a2,24(a3)
 1a6:	80472683          	lw	a3,-2044(a4) # 40010804 <_eusrstack+0x2000e004>
 1aa:	30000637          	lui	a2,0x30000
 1ae:	6521                	lui	a0,0x8
 1b0:	8eed                	and	a3,a3,a1
 1b2:	80d72223          	sw	a3,-2044(a4)
 1b6:	80472683          	lw	a3,-2044(a4)
 1ba:	006de837          	lui	a6,0x6de
 1be:	060218b7          	lui	a7,0x6021
 1c2:	8ed1                	or	a3,a3,a2
 1c4:	80d72223          	sw	a3,-2044(a4)
 1c8:	80a72823          	sw	a0,-2032(a4)
 1cc:	81470593          	addi	a1,a4,-2028
 1d0:	d0080813          	addi	a6,a6,-768 # 6ddd00 <_data_lma+0x6dd9f4>
 1d4:	81070613          	addi	a2,a4,-2032
 1d8:	60088893          	addi	a7,a7,1536 # 6021600 <_data_lma+0x60212f4>
 1dc:	4198                	lw	a4,0(a1)
 1de:	8f49                	or	a4,a4,a0
 1e0:	c198                	sw	a4,0(a1)
 1e2:	4794                	lw	a3,8(a5)
 1e4:	96c2                	add	a3,a3,a6
 1e6:	4798                	lw	a4,8(a5)
 1e8:	8f15                	sub	a4,a4,a3
 1ea:	fe074ee3          	bltz	a4,1e6 <main+0xb2>
 1ee:	4218                	lw	a4,0(a2)
 1f0:	8f49                	or	a4,a4,a0
 1f2:	c218                	sw	a4,0(a2)
 1f4:	4794                	lw	a3,8(a5)
 1f6:	96c2                	add	a3,a3,a6
 1f8:	4798                	lw	a4,8(a5)
 1fa:	8f15                	sub	a4,a4,a3
 1fc:	fe074ee3          	bltz	a4,1f8 <main+0xc4>
 200:	4198                	lw	a4,0(a1)
 202:	8f49                	or	a4,a4,a0
 204:	c198                	sw	a4,0(a1)
 206:	4794                	lw	a3,8(a5)
 208:	96c2                	add	a3,a3,a6
 20a:	4798                	lw	a4,8(a5)
 20c:	8f15                	sub	a4,a4,a3
 20e:	fe074ee3          	bltz	a4,20a <main+0xd6>
 212:	4218                	lw	a4,0(a2)
 214:	8f49                	or	a4,a4,a0
 216:	c218                	sw	a4,0(a2)
 218:	4794                	lw	a3,8(a5)
 21a:	96c2                	add	a3,a3,a6
 21c:	4798                	lw	a4,8(a5)
 21e:	8f15                	sub	a4,a4,a3
 220:	fe074ee3          	bltz	a4,21c <main+0xe8>
 224:	4198                	lw	a4,0(a1)
 226:	8f49                	or	a4,a4,a0
 228:	c198                	sw	a4,0(a1)
 22a:	4794                	lw	a3,8(a5)
 22c:	96c2                	add	a3,a3,a6
 22e:	4798                	lw	a4,8(a5)
 230:	8f15                	sub	a4,a4,a3
 232:	fe074ee3          	bltz	a4,22e <main+0xfa>
 236:	4218                	lw	a4,0(a2)
 238:	8f49                	or	a4,a4,a0
 23a:	c218                	sw	a4,0(a2)
 23c:	4794                	lw	a3,8(a5)
 23e:	96c6                	add	a3,a3,a7
 240:	4798                	lw	a4,8(a5)
 242:	8f15                	sub	a4,a4,a3
 244:	fe074ee3          	bltz	a4,240 <main+0x10c>
 248:	bf51                	j	1dc <main+0xa8>

0000024a <ADC1_2_IRQHandler>:
 24a:	a001                	j	24a <ADC1_2_IRQHandler>

0000024c <reset_handler>:
 24c:	13400793          	li	a5,308
 250:	20000197          	auipc	gp,0x20000
 254:	5b018193          	addi	gp,gp,1456 # 20000800 <__global_pointer$>
 258:	20002117          	auipc	sp,0x20002
 25c:	5a810113          	addi	sp,sp,1448 # 20002800 <_eusrstack>
 260:	457d                	li	a0,31
 262:	bc051073          	csrw	0xbc0,a0
 266:	08800513          	li	a0,136
 26a:	30051073          	csrw	mstatus,a0
 26e:	458d                	li	a1,3
 270:	80459073          	csrw	0x804,a1
 274:	03800513          	li	a0,56
 278:	8d4d                	or	a0,a0,a1
 27a:	30551073          	csrw	mtvec,a0
 27e:	34179073          	csrw	mepc,a5
 282:	20000737          	lui	a4,0x20000
 286:	200007b7          	lui	a5,0x20000
 28a:	00070613          	mv	a2,a4
 28e:	00078793          	mv	a5,a5
 292:	02f67563          	bgeu	a2,a5,2bc <reset_handler+0x70>
 296:	fff78693          	addi	a3,a5,-1 # 1fffffff <_data_lma+0x1ffffcf3>
 29a:	8e91                	sub	a3,a3,a2
 29c:	9af1                	andi	a3,a3,-4
 29e:	30c00613          	li	a2,780
 2a2:	0691                	addi	a3,a3,4 # 40021004 <_eusrstack+0x2001e804>
 2a4:	00070713          	mv	a4,a4
 2a8:	96b2                	add	a3,a3,a2
 2aa:	30c00793          	li	a5,780
 2ae:	4390                	lw	a2,0(a5)
 2b0:	0791                	addi	a5,a5,4
 2b2:	0711                	addi	a4,a4,4 # 20000004 <_data_vma+0x4>
 2b4:	fec72e23          	sw	a2,-4(a4)
 2b8:	fed79be3          	bne	a5,a3,2ae <reset_handler+0x62>
 2bc:	30c00793          	li	a5,780
 2c0:	30c00713          	li	a4,780
 2c4:	40e78933          	sub	s2,a5,a4
 2c8:	40295913          	srai	s2,s2,0x2
 2cc:	00e78b63          	beq	a5,a4,2e2 <reset_handler+0x96>
 2d0:	30c00413          	li	s0,780
 2d4:	4481                	li	s1,0
 2d6:	401c                	lw	a5,0(s0)
 2d8:	0485                	addi	s1,s1,1
 2da:	0411                	addi	s0,s0,4
 2dc:	9782                	jalr	a5
 2de:	ff24ece3          	bltu	s1,s2,2d6 <reset_handler+0x8a>
 2e2:	30c00793          	li	a5,780
 2e6:	30c00713          	li	a4,780
 2ea:	40e78933          	sub	s2,a5,a4
 2ee:	40295913          	srai	s2,s2,0x2
 2f2:	00e78b63          	beq	a5,a4,308 <reset_handler+0xbc>
 2f6:	30c00413          	li	s0,780
 2fa:	4481                	li	s1,0
 2fc:	401c                	lw	a5,0(s0)
 2fe:	0485                	addi	s1,s1,1
 300:	0411                	addi	s0,s0,4
 302:	9782                	jalr	a5
 304:	ff24ece3          	bltu	s1,s2,2fc <reset_handler+0xb0>
 308:	30200073          	mret
