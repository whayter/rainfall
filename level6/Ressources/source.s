# n function

0x08048454 <+0>:     push   %ebp
0x08048455 <+1>:     mov    %esp,%ebp
0x08048457 <+3>:     sub    $0x18,%esp
0x0804845a <+6>:     movl   $0x80485b0,(%esp)
0x08048461 <+13>:    call   0x8048370 <system@plt>
0x08048466 <+18>:    leave  
0x08048467 <+19>:    ret    

# m function

0x08048468 <+0>:     push   %ebp
0x08048469 <+1>:     mov    %esp,%ebp
0x0804846b <+3>:     sub    $0x18,%esp
0x0804846e <+6>:     movl   $0x80485d1,(%esp)
0x08048475 <+13>:    call   0x8048360 <puts@plt>
0x0804847a <+18>:    leave  
0x0804847b <+19>:    ret    

# main function

0x0804847c <+0>:     push   %ebp
0x0804847d <+1>:     mov    %esp,%ebp
0x0804847f <+3>:     and    $0xfffffff0,%esp
0x08048482 <+6>:     sub    $0x20,%esp
0x08048485 <+9>:     movl   $0x40,(%esp)
0x0804848c <+16>:    call   0x8048350 <malloc@plt>
0x08048491 <+21>:    mov    %eax,0x1c(%esp)
0x08048495 <+25>:    movl   $0x4,(%esp)
0x0804849c <+32>:    call   0x8048350 <malloc@plt>
0x080484a1 <+37>:    mov    %eax,0x18(%esp)
0x080484a5 <+41>:    mov    $0x8048468,%edx
0x080484aa <+46>:    mov    0x18(%esp),%eax
0x080484ae <+50>:    mov    %edx,(%eax)
0x080484b0 <+52>:    mov    0xc(%ebp),%eax
0x080484b3 <+55>:    add    $0x4,%eax
0x080484b6 <+58>:    mov    (%eax),%eax
0x080484b8 <+60>:    mov    %eax,%edx
0x080484ba <+62>:    mov    0x1c(%esp),%eax
0x080484be <+66>:    mov    %edx,0x4(%esp)
0x080484c2 <+70>:    mov    %eax,(%esp)
0x080484c5 <+73>:    call   0x8048340 <strcpy@plt>
0x080484ca <+78>:    mov    0x18(%esp),%eax
0x080484ce <+82>:    mov    (%eax),%eax
0x080484d0 <+84>:    call   *%eax
0x080484d2 <+86>:    leave  
0x080484d3 <+87>:    ret    