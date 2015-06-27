.globl _addone
.def	_addone;	.scl	2;	.type 32;	.endef
_addone:
pushl %ebp
movl %esp, %ebp
subl $4, %esp
mov $1, %eax
movl %eax, -4(%ebp)
movl 8(%ebp),%eax
push %eax
movl -4(%ebp),%eax
pop %ecx
addl %ecx, %eax
leave
ret
leave
ret
.globl _foo
.def	_foo;	.scl	2;	.type 32;	.endef
_foo:
pushl %ebp
movl %esp, %ebp
subl $4, %esp
movl 8(%ebp),%eax
push %eax
call _addone
movl %eax, -4(%ebp)
movl -4(%ebp),%eax
push %eax
movl 8(%ebp),%eax
pop %ecx
imull %ecx, %eax
movl %eax, 12(%ebp)
movl 12(%ebp),%eax
push %eax
call _addone
leave
ret
leave
ret
