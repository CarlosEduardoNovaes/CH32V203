
firmware/baremetal.elf:     file format elf32-littleriscv


Disassembly of section .init:

00000000 <jump_reset>:
   0:	2460006f          	j	246 <reset_handler>

Disassembly of section .text:

00000100 <main>:
 100:	40021737          	lui	a4,0x40021
 104:	009f06b7          	lui	a3,0x9f0
 108:	c714                	sw	a3,8(a4)
 10a:	400247b7          	lui	a5,0x40024
 10e:	8007a683          	lw	a3,-2048(a5) # 40023800 <_eusrstack+0x20021000>
 112:	003c05b7          	lui	a1,0x3c0
 116:	01000637          	lui	a2,0x1000
 11a:	0106e693          	ori	a3,a3,16
 11e:	80d7a023          	sw	a3,-2048(a5)
 122:	c34c                	sw	a1,4(a4)
 124:	431c                	lw	a5,0(a4)
 126:	8fd1                	or	a5,a5,a2
 128:	c31c                	sw	a5,0(a4)
 12a:	431c                	lw	a5,0(a4)
 12c:	00679693          	slli	a3,a5,0x6
 130:	fe06dde3          	bgez	a3,12a <main+0x2a>
 134:	435c                	lw	a5,4(a4)
 136:	400216b7          	lui	a3,0x40021
 13a:	4621                	li	a2,8
 13c:	0027e793          	ori	a5,a5,2
 140:	c35c                	sw	a5,4(a4)
 142:	42dc                	lw	a5,4(a3)
 144:	8bb1                	andi	a5,a5,12
 146:	fec79ee3          	bne	a5,a2,142 <main+0x42>
 14a:	40022637          	lui	a2,0x40022
 14e:	4a1c                	lw	a5,16(a2)
 150:	fe000737          	lui	a4,0xfe000
 154:	177d                	addi	a4,a4,-1 # fdffffff <_eusrstack+0xddffd7ff>
 156:	8ff9                	and	a5,a5,a4
 158:	ca1c                	sw	a5,16(a2)
 15a:	4715                	li	a4,5
 15c:	e000f7b7          	lui	a5,0xe000f
 160:	c398                	sw	a4,0(a5)
 162:	4e98                	lw	a4,24(a3)
 164:	e000e637          	lui	a2,0xe000e
 168:	6585                	lui	a1,0x1
 16a:	03c76713          	ori	a4,a4,60
 16e:	ce98                	sw	a4,24(a3)
 170:	10b62023          	sw	a1,256(a2) # e000e100 <_eusrstack+0xc000b900>
 174:	40011737          	lui	a4,0x40011
 178:	80472683          	lw	a3,-2044(a4) # 40010804 <_eusrstack+0x2000e004>
 17c:	f00005b7          	lui	a1,0xf0000
 180:	30000637          	lui	a2,0x30000
 184:	8eed                	and	a3,a3,a1
 186:	80d72223          	sw	a3,-2044(a4)
 18a:	80472683          	lw	a3,-2044(a4)
 18e:	6521                	lui	a0,0x8
 190:	006de837          	lui	a6,0x6de
 194:	8ed1                	or	a3,a3,a2
 196:	80d72223          	sw	a3,-2044(a4)
 19a:	060218b7          	lui	a7,0x6021
 19e:	80a72823          	sw	a0,-2032(a4)
 1a2:	81470593          	addi	a1,a4,-2028
 1a6:	d0080813          	addi	a6,a6,-768 # 6ddd00 <_data_lma+0x6dd9f8>
 1aa:	81070613          	addi	a2,a4,-2032
 1ae:	60088893          	addi	a7,a7,1536 # 6021600 <_data_lma+0x60212f8>
 1b2:	4198                	lw	a4,0(a1)
 1b4:	8f49                	or	a4,a4,a0
 1b6:	c198                	sw	a4,0(a1)
 1b8:	4794                	lw	a3,8(a5)
 1ba:	96c2                	add	a3,a3,a6
 1bc:	4798                	lw	a4,8(a5)
 1be:	8f15                	sub	a4,a4,a3
 1c0:	fe074ee3          	bltz	a4,1bc <main+0xbc>
 1c4:	4218                	lw	a4,0(a2)
 1c6:	8f49                	or	a4,a4,a0
 1c8:	c218                	sw	a4,0(a2)
 1ca:	4794                	lw	a3,8(a5)
 1cc:	96c2                	add	a3,a3,a6
 1ce:	4798                	lw	a4,8(a5)
 1d0:	8f15                	sub	a4,a4,a3
 1d2:	fe074ee3          	bltz	a4,1ce <main+0xce>
 1d6:	4198                	lw	a4,0(a1)
 1d8:	8f49                	or	a4,a4,a0
 1da:	c198                	sw	a4,0(a1)
 1dc:	4794                	lw	a3,8(a5)
 1de:	96c2                	add	a3,a3,a6
 1e0:	4798                	lw	a4,8(a5)
 1e2:	8f15                	sub	a4,a4,a3
 1e4:	fe074ee3          	bltz	a4,1e0 <main+0xe0>
 1e8:	4218                	lw	a4,0(a2)
 1ea:	8f49                	or	a4,a4,a0
 1ec:	c218                	sw	a4,0(a2)
 1ee:	4794                	lw	a3,8(a5)
 1f0:	96c2                	add	a3,a3,a6
 1f2:	4798                	lw	a4,8(a5)
 1f4:	8f15                	sub	a4,a4,a3
 1f6:	fe074ee3          	bltz	a4,1f2 <main+0xf2>
 1fa:	4198                	lw	a4,0(a1)
 1fc:	8f49                	or	a4,a4,a0
 1fe:	c198                	sw	a4,0(a1)
 200:	4794                	lw	a3,8(a5)
 202:	96c2                	add	a3,a3,a6
 204:	4798                	lw	a4,8(a5)
 206:	8f15                	sub	a4,a4,a3
 208:	fe074ee3          	bltz	a4,204 <main+0x104>
 20c:	4218                	lw	a4,0(a2)
 20e:	8f49                	or	a4,a4,a0
 210:	c218                	sw	a4,0(a2)
 212:	4794                	lw	a3,8(a5)
 214:	96c2                	add	a3,a3,a6
 216:	4798                	lw	a4,8(a5)
 218:	8f15                	sub	a4,a4,a3
 21a:	fe074ee3          	bltz	a4,216 <main+0x116>
 21e:	4198                	lw	a4,0(a1)
 220:	8f49                	or	a4,a4,a0
 222:	c198                	sw	a4,0(a1)
 224:	4794                	lw	a3,8(a5)
 226:	96c2                	add	a3,a3,a6
 228:	4798                	lw	a4,8(a5)
 22a:	8f15                	sub	a4,a4,a3
 22c:	fe074ee3          	bltz	a4,228 <main+0x128>
 230:	4218                	lw	a4,0(a2)
 232:	8f49                	or	a4,a4,a0
 234:	c218                	sw	a4,0(a2)
 236:	4794                	lw	a3,8(a5)
 238:	96c6                	add	a3,a3,a7
 23a:	4798                	lw	a4,8(a5)
 23c:	8f15                	sub	a4,a4,a3
 23e:	fe074ee3          	bltz	a4,23a <main+0x13a>
 242:	bf85                	j	1b2 <main+0xb2>

00000244 <ADC1_2_IRQHandler>:
 244:	a001                	j	244 <ADC1_2_IRQHandler>

00000246 <reset_handler>:
 246:	10000793          	li	a5,256
 24a:	20000197          	auipc	gp,0x20000
 24e:	5b618193          	addi	gp,gp,1462 # 20000800 <__global_pointer$>
 252:	20002117          	auipc	sp,0x20002
 256:	5ae10113          	addi	sp,sp,1454 # 20002800 <_eusrstack>
 25a:	457d                	li	a0,31
 25c:	bc051073          	csrw	0xbc0,a0
 260:	08800513          	li	a0,136
 264:	30051073          	csrw	mstatus,a0
 268:	458d                	li	a1,3
 26a:	80459073          	csrw	0x804,a1
 26e:	00400513          	li	a0,4
 272:	8d4d                	or	a0,a0,a1
 274:	30551073          	csrw	mtvec,a0
 278:	34179073          	csrw	mepc,a5
 27c:	20000737          	lui	a4,0x20000
 280:	200007b7          	lui	a5,0x20000
 284:	00070613          	mv	a2,a4
 288:	00078793          	mv	a5,a5
 28c:	02f67563          	bgeu	a2,a5,2b6 <reset_handler+0x70>
 290:	fff78693          	addi	a3,a5,-1 # 1fffffff <_data_lma+0x1ffffcf7>
 294:	8e91                	sub	a3,a3,a2
 296:	9af1                	andi	a3,a3,-4
 298:	30800613          	li	a2,776
 29c:	0691                	addi	a3,a3,4 # 40021004 <_eusrstack+0x2001e804>
 29e:	00070713          	mv	a4,a4
 2a2:	96b2                	add	a3,a3,a2
 2a4:	30800793          	li	a5,776
 2a8:	4390                	lw	a2,0(a5)
 2aa:	0791                	addi	a5,a5,4
 2ac:	0711                	addi	a4,a4,4 # 20000004 <_data_vma+0x4>
 2ae:	fec72e23          	sw	a2,-4(a4)
 2b2:	fed79be3          	bne	a5,a3,2a8 <reset_handler+0x62>
 2b6:	30800793          	li	a5,776
 2ba:	30800713          	li	a4,776
 2be:	40e78933          	sub	s2,a5,a4
 2c2:	40295913          	srai	s2,s2,0x2
 2c6:	00e78b63          	beq	a5,a4,2dc <reset_handler+0x96>
 2ca:	30800413          	li	s0,776
 2ce:	4481                	li	s1,0
 2d0:	401c                	lw	a5,0(s0)
 2d2:	0485                	addi	s1,s1,1
 2d4:	0411                	addi	s0,s0,4
 2d6:	9782                	jalr	a5
 2d8:	ff24ece3          	bltu	s1,s2,2d0 <reset_handler+0x8a>
 2dc:	30800793          	li	a5,776
 2e0:	30800713          	li	a4,776
 2e4:	40e78933          	sub	s2,a5,a4
 2e8:	40295913          	srai	s2,s2,0x2
 2ec:	00e78b63          	beq	a5,a4,302 <reset_handler+0xbc>
 2f0:	30800413          	li	s0,776
 2f4:	4481                	li	s1,0
 2f6:	401c                	lw	a5,0(s0)
 2f8:	0485                	addi	s1,s1,1
 2fa:	0411                	addi	s0,s0,4
 2fc:	9782                	jalr	a5
 2fe:	ff24ece3          	bltu	s1,s2,2f6 <reset_handler+0xb0>
 302:	30200073          	mret
	...
