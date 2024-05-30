set disassembly-flavor intel
set pagination off

define si
	stepi
	echo Registers:\n
	info register $rax $rbx $rcx $rdx $rsp $rbp $rip $rdi $rsi
	echo \n---\n\n
	echo Stack:\n
	x/32gx $rsp
	echo \n---\n\n
	echo Following instructions:\n
	x/15i $rip
end

define ni
	nexti
	echo Registers:\n
	info register $rax $rbx $rcx $rdx $rsp $rbp $rip
	echo \n---\n\n
	echo Stack:\n
	x/32gx $rsp
	echo \n---\n\n
	echo Following instructions:\n
	x/15i $rip
end

define inc
	x/42i $rip
end

define data
	print $arg0
	echo ---\n
	x/5s $arg0
	echo ---\n
	x/32wx $arg0
	echo ---\n
	x/10i $arg0
	echo ---\n
	x/16d $arg0
end

define load_file
	continue
	set $rdi="/tmp/dummy.txt"
end

set breakpoint pending on
b main

# For file
b *0x4008a8
b *0x400989