
bin/firmware.elf:     file format elf32-littleriscv


Disassembly of section .init:

00000000 <jump_reset>:
   0:	1e80006f          	j	1e8 <reset_handler>
   4:	0001                	nop
	...

00000008 <init_data>:
   8:	0013 0000 0013 0000 0013 0000 0013 0000     ................
  18:	0013 0000 0013 0000 0013 0000 0013 0000     ................
  28:	0013 0000 0013 0000 0013 0000 0013 0000     ................
  38:	0073 0010                                   s...

Disassembly of section .text:

00000138 <main>:
 138:	1141                	addi	sp,sp,-16
 13a:	c622                	sw	s0,12(sp)
 13c:	0800                	addi	s0,sp,16
 13e:	200007b7          	lui	a5,0x20000
 142:	0007a703          	lw	a4,0(a5) # 20000000 <_ZZ4mainE5var_a>
 146:	200007b7          	lui	a5,0x20000
 14a:	00e7a223          	sw	a4,4(a5) # 20000004 <_ZZ4mainE5var_b>
 14e:	4781                	li	a5,0
 150:	853e                	mv	a0,a5
 152:	4432                	lw	s0,12(sp)
 154:	0141                	addi	sp,sp,16
 156:	8082                	ret

00000158 <__libc_init_array>:
 158:	1101                	addi	sp,sp,-32
 15a:	ce06                	sw	ra,28(sp)
 15c:	cc22                	sw	s0,24(sp)
 15e:	1000                	addi	s0,sp,32
 160:	25000713          	li	a4,592
 164:	25000793          	li	a5,592
 168:	40f707b3          	sub	a5,a4,a5
 16c:	8789                	srai	a5,a5,0x2
 16e:	fef42423          	sw	a5,-24(s0)
 172:	fe042623          	sw	zero,-20(s0)
 176:	a831                	j	192 <__libc_init_array+0x3a>
 178:	25000713          	li	a4,592
 17c:	fec42783          	lw	a5,-20(s0)
 180:	078a                	slli	a5,a5,0x2
 182:	97ba                	add	a5,a5,a4
 184:	439c                	lw	a5,0(a5)
 186:	9782                	jalr	a5
 188:	fec42783          	lw	a5,-20(s0)
 18c:	0785                	addi	a5,a5,1
 18e:	fef42623          	sw	a5,-20(s0)
 192:	fec42703          	lw	a4,-20(s0)
 196:	fe842783          	lw	a5,-24(s0)
 19a:	fcf76fe3          	bltu	a4,a5,178 <__libc_init_array+0x20>
 19e:	25000713          	li	a4,592
 1a2:	25000793          	li	a5,592
 1a6:	40f707b3          	sub	a5,a4,a5
 1aa:	8789                	srai	a5,a5,0x2
 1ac:	fef42423          	sw	a5,-24(s0)
 1b0:	fe042623          	sw	zero,-20(s0)
 1b4:	a831                	j	1d0 <__libc_init_array+0x78>
 1b6:	25000713          	li	a4,592
 1ba:	fec42783          	lw	a5,-20(s0)
 1be:	078a                	slli	a5,a5,0x2
 1c0:	97ba                	add	a5,a5,a4
 1c2:	439c                	lw	a5,0(a5)
 1c4:	9782                	jalr	a5
 1c6:	fec42783          	lw	a5,-20(s0)
 1ca:	0785                	addi	a5,a5,1
 1cc:	fef42623          	sw	a5,-20(s0)
 1d0:	fec42703          	lw	a4,-20(s0)
 1d4:	fe842783          	lw	a5,-24(s0)
 1d8:	fcf76fe3          	bltu	a4,a5,1b6 <__libc_init_array+0x5e>
 1dc:	0001                	nop
 1de:	0001                	nop
 1e0:	40f2                	lw	ra,28(sp)
 1e2:	4462                	lw	s0,24(sp)
 1e4:	6105                	addi	sp,sp,32
 1e6:	8082                	ret

000001e8 <reset_handler>:
 1e8:	13800793          	li	a5,312
 1ec:	20000197          	auipc	gp,0x20000
 1f0:	61418193          	addi	gp,gp,1556 # 20000800 <__global_pointer$>
 1f4:	20002117          	auipc	sp,0x20002
 1f8:	60c10113          	addi	sp,sp,1548 # 20002800 <_eusrstack>
 1fc:	457d                	li	a0,31
 1fe:	bc051073          	csrw	0xbc0,a0
 202:	08800513          	li	a0,136
 206:	30051073          	csrw	mstatus,a0
 20a:	458d                	li	a1,3
 20c:	80459073          	csrw	0x804,a1
 210:	03c00513          	li	a0,60
 214:	8d4d                	or	a0,a0,a1
 216:	30551073          	csrw	mtvec,a0
 21a:	34179073          	csrw	mepc,a5
 21e:	25000493          	li	s1,592
 222:	200007b7          	lui	a5,0x20000
 226:	00078093          	mv	ra,a5
 22a:	a809                	j	23c <reset_handler+0x54>
 22c:	8726                	mv	a4,s1
 22e:	00470493          	addi	s1,a4,4
 232:	8786                	mv	a5,ra
 234:	00478093          	addi	ra,a5,4 # 20000004 <_ZZ4mainE5var_b>
 238:	4318                	lw	a4,0(a4)
 23a:	c398                	sw	a4,0(a5)
 23c:	80818793          	addi	a5,gp,-2040 # 20000008 <_edata>
 240:	fef0e6e3          	bltu	ra,a5,22c <reset_handler+0x44>
 244:	3f11                	jal	158 <__libc_init_array>
 246:	30200073          	mret
 24a:	0001                	nop

0000024c <ADC1_2_IRQHandler>:
 24c:	0001                	nop
 24e:	bffd                	j	24c <ADC1_2_IRQHandler>
