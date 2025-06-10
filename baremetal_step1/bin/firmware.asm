
bin/firmware.elf:     file format elf32-littleriscv


Disassembly of section .init:

00000000 <jump_reset>:
   0:	1580006f          	j	158 <reset_handler>

00000004 <init_data>:
   4:	00000013 00000013 00000013 00000013     ................
  14:	00000013 00000013 00000013 00000013     ................
  24:	00000013 00000013 00000013 00000013     ................
  34:	00100073                                s...

Disassembly of section .text:

00000134 <main>:
 134:	200006b7          	lui	a3,0x20000
 138:	200007b7          	lui	a5,0x20000
 13c:	0047a783          	lw	a5,4(a5) # 20000004 <_ZZ4mainE5var_a>
 140:	0006a603          	lw	a2,0(a3) # 20000000 <_ZZ4mainE5var_b>
 144:	4501                	li	a0,0
 146:	0786                	slli	a5,a5,0x1
 148:	00161713          	slli	a4,a2,0x1
 14c:	9732                	add	a4,a4,a2
 14e:	97ba                	add	a5,a5,a4
 150:	00f6a023          	sw	a5,0(a3)
 154:	8082                	ret

00000156 <ADC1_2_IRQHandler>:
 156:	a001                	j	156 <ADC1_2_IRQHandler>

00000158 <reset_handler>:
 158:	13400793          	li	a5,308
 15c:	20000197          	auipc	gp,0x20000
 160:	6a418193          	addi	gp,gp,1700 # 20000800 <__global_pointer$>
 164:	20002117          	auipc	sp,0x20002
 168:	69c10113          	addi	sp,sp,1692 # 20002800 <_eusrstack>
 16c:	457d                	li	a0,31
 16e:	bc051073          	csrw	0xbc0,a0
 172:	08800513          	li	a0,136
 176:	30051073          	csrw	mstatus,a0
 17a:	458d                	li	a1,3
 17c:	80459073          	csrw	0x804,a1
 180:	03800513          	li	a0,56
 184:	8d4d                	or	a0,a0,a1
 186:	30551073          	csrw	mtvec,a0
 18a:	34179073          	csrw	mepc,a5
 18e:	20000737          	lui	a4,0x20000
 192:	00070613          	mv	a2,a4
 196:	80818793          	addi	a5,gp,-2040 # 20000008 <_edata>
 19a:	02f67563          	bgeu	a2,a5,1c4 <add.cxxm.9c1928d1+0x15>
 19e:	fff78693          	addi	a3,a5,-1
 1a2:	8e91                	sub	a3,a3,a2
 1a4:	9af1                	andi	a3,a3,-4
 1a6:	21400613          	li	a2,532
 1aa:	0691                	addi	a3,a3,4
 1ac:	96b2                	add	a3,a3,a2
 1ae:	00070713          	mv	a4,a4
 1b2:	21400793          	li	a5,532
 1b6:	4390                	lw	a2,0(a5)
 1b8:	0791                	addi	a5,a5,4
 1ba:	0711                	addi	a4,a4,4 # 20000004 <_ZZ4mainE5var_a>
 1bc:	fec72e23          	sw	a2,-4(a4)
 1c0:	fed79be3          	bne	a5,a3,1b6 <add.cxxm.9c1928d1+0x7>
 1c4:	21400793          	li	a5,532
 1c8:	21400713          	li	a4,532
 1cc:	40e78933          	sub	s2,a5,a4
 1d0:	40295913          	srai	s2,s2,0x2
 1d4:	00e78b63          	beq	a5,a4,1ea <add.cxxm.9c1928d1+0x3b>
 1d8:	21400413          	li	s0,532
 1dc:	4481                	li	s1,0
 1de:	401c                	lw	a5,0(s0)
 1e0:	0485                	addi	s1,s1,1
 1e2:	0411                	addi	s0,s0,4
 1e4:	9782                	jalr	a5
 1e6:	ff24ece3          	bltu	s1,s2,1de <add.cxxm.9c1928d1+0x2f>
 1ea:	21400793          	li	a5,532
 1ee:	21400713          	li	a4,532
 1f2:	40e78933          	sub	s2,a5,a4
 1f6:	40295913          	srai	s2,s2,0x2
 1fa:	00e78b63          	beq	a5,a4,210 <startup_ch32v203.c.f2a871ac+0x11>
 1fe:	21400413          	li	s0,532
 202:	4481                	li	s1,0
 204:	401c                	lw	a5,0(s0)
 206:	0485                	addi	s1,s1,1
 208:	0411                	addi	s0,s0,4
 20a:	9782                	jalr	a5
 20c:	ff24ece3          	bltu	s1,s2,204 <startup_ch32v203.c.f2a871ac+0x5>
 210:	30200073          	mret
