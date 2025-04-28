
app:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	endbr64
    1004:	sub    $0x8,%rsp
    1008:	mov    0x2fe1(%rip),%rax        # 3ff0 <__gmon_start__@Base>
    100f:	test   %rax,%rax
    1012:	je     1016 <_init+0x16>
    1014:	call   *%rax
    1016:	add    $0x8,%rsp
    101a:	ret

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	push   0x2fa2(%rip)        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	jmp    *0x2fa4(%rip)        # 3fd0 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	nopl   0x0(%rax)

Disassembly of section .plt.got:

0000000000001030 <__cxa_finalize@plt>:
    1030:	endbr64
    1034:	jmp    *0x2f9e(%rip)        # 3fd8 <__cxa_finalize@GLIBC_2.2.5>
    103a:	nopw   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001040 <main>:
    1040:	endbr64
    1044:	mov    0x2fc6(%rip),%eax        # 4010 <_ZL8fake_reg>
    104a:	and    $0xffffef00,%eax
    104f:	or     $0x21,%eax
    1052:	mov    %eax,0x2fb8(%rip)        # 4010 <_ZL8fake_reg>
    1058:	xor    %eax,%eax
    105a:	ret
    105b:	nopl   0x0(%rax,%rax,1)

0000000000001060 <_start>:
    1060:	endbr64
    1064:	xor    %ebp,%ebp
    1066:	mov    %rdx,%r9
    1069:	pop    %rsi
    106a:	mov    %rsp,%rdx
    106d:	and    $0xfffffffffffffff0,%rsp
    1071:	push   %rax
    1072:	push   %rsp
    1073:	xor    %r8d,%r8d
    1076:	xor    %ecx,%ecx
    1078:	lea    -0x3f(%rip),%rdi        # 1040 <main>
    107f:	call   *0x2f5b(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.34>
    1085:	hlt
    1086:	cs nopw 0x0(%rax,%rax,1)

0000000000001090 <deregister_tm_clones>:
    1090:	lea    0x2f81(%rip),%rdi        # 4018 <__TMC_END__>
    1097:	lea    0x2f7a(%rip),%rax        # 4018 <__TMC_END__>
    109e:	cmp    %rdi,%rax
    10a1:	je     10b8 <deregister_tm_clones+0x28>
    10a3:	mov    0x2f3e(%rip),%rax        # 3fe8 <_ITM_deregisterTMCloneTable@Base>
    10aa:	test   %rax,%rax
    10ad:	je     10b8 <deregister_tm_clones+0x28>
    10af:	jmp    *%rax
    10b1:	nopl   0x0(%rax)
    10b8:	ret
    10b9:	nopl   0x0(%rax)

00000000000010c0 <register_tm_clones>:
    10c0:	lea    0x2f51(%rip),%rdi        # 4018 <__TMC_END__>
    10c7:	lea    0x2f4a(%rip),%rsi        # 4018 <__TMC_END__>
    10ce:	sub    %rdi,%rsi
    10d1:	mov    %rsi,%rax
    10d4:	shr    $0x3f,%rsi
    10d8:	sar    $0x3,%rax
    10dc:	add    %rax,%rsi
    10df:	sar    $1,%rsi
    10e2:	je     10f8 <register_tm_clones+0x38>
    10e4:	mov    0x2f0d(%rip),%rax        # 3ff8 <_ITM_registerTMCloneTable@Base>
    10eb:	test   %rax,%rax
    10ee:	je     10f8 <register_tm_clones+0x38>
    10f0:	jmp    *%rax
    10f2:	nopw   0x0(%rax,%rax,1)
    10f8:	ret
    10f9:	nopl   0x0(%rax)

0000000000001100 <__do_global_dtors_aux>:
    1100:	endbr64
    1104:	cmpb   $0x0,0x2f09(%rip)        # 4014 <completed.0>
    110b:	jne    1138 <__do_global_dtors_aux+0x38>
    110d:	push   %rbp
    110e:	cmpq   $0x0,0x2ec2(%rip)        # 3fd8 <__cxa_finalize@GLIBC_2.2.5>
    1116:	mov    %rsp,%rbp
    1119:	je     1127 <__do_global_dtors_aux+0x27>
    111b:	mov    0x2ee6(%rip),%rdi        # 4008 <__dso_handle>
    1122:	call   1030 <__cxa_finalize@plt>
    1127:	call   1090 <deregister_tm_clones>
    112c:	movb   $0x1,0x2ee1(%rip)        # 4014 <completed.0>
    1133:	pop    %rbp
    1134:	ret
    1135:	nopl   (%rax)
    1138:	ret
    1139:	nopl   0x0(%rax)

0000000000001140 <frame_dummy>:
    1140:	endbr64
    1144:	jmp    10c0 <register_tm_clones>
    1149:	nopl   0x0(%rax)

0000000000001150 <_ZGIW4math>:
    1150:	endbr64
    1154:	ret
    1155:	cs nopw 0x0(%rax,%rax,1)
    115f:	nop

0000000000001160 <_ZGIW3reg>:
    1160:	endbr64
    1164:	ret

Disassembly of section .fini:

0000000000001168 <_fini>:
    1168:	endbr64
    116c:	sub    $0x8,%rsp
    1170:	add    $0x8,%rsp
    1174:	ret
