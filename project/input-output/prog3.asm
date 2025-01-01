.386
.model flat, stdcall
option casemap :none

include masm32\include\windows.inc
include masm32\include\kernel32.inc
include masm32\include\masm32.inc
include masm32\include\user32.inc
include masm32\include\msvcrt.inc
includelib masm32\lib\kernel32.lib
includelib masm32\lib\masm32.lib
includelib masm32\lib\user32.lib
includelib masm32\lib\msvcrt.lib

.DATA
;===User Data================================================================================
	_aaa2_	dd	0
	_aaaa_	dd	0
	_bbbb_	dd	0
	_ccc1_	dd	0
	_ccc2_	dd	0
	_xxxx_	dd	0

	String_0	db	"Input A: ", 0
	String_1	db	"Input B: ", 0
	String_2	db	"FOR TO DO", 0
	String_3	db	13, 10, 0
	String_4	db	13, 10, "FOR DOWNTO DO", 0
	String_5	db	13, 10, 0
	String_6	db	13, 10, "WHILE A MUL B: ", 0
	String_7	db	13, 10, "REPEAT UNTIL A MUL B: ", 0

;===Addition Data============================================================================
	hConsoleInput	dd	?
	hConsoleOutput	dd	?
	endBuff			db	5 dup (?)
	msg1310			db	13, 10, 0

	CharsReadNum	dd	?
	InputBuf		db	15 dup (?)
	OutMessage		db	"%d", 0
	ResMessage		db	20 dup (?)

.CODE
start:
invoke AllocConsole
invoke GetStdHandle, STD_INPUT_HANDLE
mov hConsoleInput, eax
invoke GetStdHandle, STD_OUTPUT_HANDLE
mov hConsoleOutput, eax
	invoke WriteConsoleA, hConsoleOutput, ADDR String_0, SIZEOF String_0 - 1, 0, 0
	call Input_
	mov _aaaa_, eax
	invoke WriteConsoleA, hConsoleOutput, ADDR String_1, SIZEOF String_1 - 1, 0, 0
	call Input_
	mov _bbbb_, eax
	invoke WriteConsoleA, hConsoleOutput, ADDR String_2, SIZEOF String_2 - 1, 0, 0
	push _aaaa_
	pop _aaa2_
forPasStart1:
	push _bbbb_
	push _aaa2_
	call Less_
	call Not_
	pop eax
	cmp eax, 0
	je forPasEnd1
	invoke WriteConsoleA, hConsoleOutput, ADDR String_3, SIZEOF String_3 - 1, 0, 0
	push _aaa2_
	push _aaa2_
	call Mul_
	call Output_
	push _aaa2_
	push dword ptr 1
	call Add_
	pop _aaa2_
	jmp forPasStart1
forPasEnd1:
	invoke WriteConsoleA, hConsoleOutput, ADDR String_4, SIZEOF String_4 - 1, 0, 0
	push _bbbb_
	pop _aaa2_
forPasStart2:
	push _aaaa_
	push _aaa2_
	call Greate_
	call Not_
	pop eax
	cmp eax, 0
	je forPasEnd2
	invoke WriteConsoleA, hConsoleOutput, ADDR String_5, SIZEOF String_5 - 1, 0, 0
	push _aaa2_
	push _aaa2_
	call Mul_
	call Output_
	push _aaa2_
	push dword ptr 1
	call Sub_
	pop _aaa2_
	jmp forPasStart2
forPasEnd2:
	invoke WriteConsoleA, hConsoleOutput, ADDR String_6, SIZEOF String_6 - 1, 0, 0
	push dword ptr 0
	pop _xxxx_
	push dword ptr 0
	pop _ccc1_
whileStart2:
	push _ccc1_
	push _aaaa_
	call Less_
	pop eax
	cmp eax, 0
	je whileEnd2
	push dword ptr 0
	pop _ccc2_
whileStart1:
	push _ccc2_
	push _bbbb_
	call Less_
	pop eax
	cmp eax, 0
	je whileEnd1
	push _xxxx_
	push dword ptr 1
	call Add_
	pop _xxxx_
	push _ccc2_
	push dword ptr 1
	call Add_
	pop _ccc2_
	jmp whileStart1
whileEnd1:
	push _ccc1_
	push dword ptr 1
	call Add_
	pop _ccc1_
	jmp whileStart2
whileEnd2:
	push _xxxx_
	call Output_
	invoke WriteConsoleA, hConsoleOutput, ADDR String_7, SIZEOF String_7 - 1, 0, 0
	push dword ptr 0
	pop _xxxx_
	push dword ptr 1
	pop _ccc1_
repeatStart2:
	push dword ptr 1
	pop _ccc2_
repeatStart1:
	push _xxxx_
	push dword ptr 1
	call Add_
	pop _xxxx_
	push _ccc2_
	push dword ptr 1
	call Add_
	pop _ccc2_
	push _ccc2_
	push _bbbb_
	call Greate_
	call Not_
	pop eax
	cmp eax, 0
	je repeatEnd1
	jmp repeatStart1
repeatEnd1:
	push _ccc1_
	push dword ptr 1
	call Add_
	pop _ccc1_
	push _ccc1_
	push _aaaa_
	call Greate_
	call Not_
	pop eax
	cmp eax, 0
	je repeatEnd2
	jmp repeatStart2
repeatEnd2:
	push _xxxx_
	call Output_
exit_label:
invoke WriteConsoleA, hConsoleOutput, ADDR msg1310, SIZEOF msg1310 - 1, 0, 0
invoke ReadConsoleA, hConsoleInput, ADDR endBuff, 5, 0, 0
invoke ExitProcess, 0


;===Procedure Add============================================================================
Add_ PROC
	mov eax, [esp + 8]
	add eax, [esp + 4]
	mov [esp + 8], eax
	pop ecx
	pop eax
	push ecx
	ret
Add_ ENDP
;============================================================================================


;===Procedure Greate=========================================================================
Greate_ PROC
	pushf
	pop cx

	mov eax, [esp + 8]
	cmp eax, [esp + 4]
	jle greate_false
	mov eax, 1
	jmp greate_fin
greate_false:
	mov eax, 0
greate_fin:
	push cx
	popf

	mov [esp + 8], eax
	pop ecx
	pop eax
	push ecx
	ret
Greate_ ENDP
;============================================================================================


;===Procedure Input==========================================================================
Input_ PROC
	invoke ReadConsoleA, hConsoleInput, ADDR InputBuf, 13, ADDR CharsReadNum, 0
	invoke crt_atoi, ADDR InputBuf
	ret
Input_ ENDP
;============================================================================================


;===Procedure Less===========================================================================
Less_ PROC
	pushf
	pop cx

	mov eax, [esp + 8]
	cmp eax, [esp + 4]
	jge less_false
	mov eax, 1
	jmp less_fin
less_false:
	mov eax, 0
less_fin:
	push cx
	popf

	mov [esp + 8], eax
	pop ecx
	pop eax
	push ecx
	ret
Less_ ENDP
;============================================================================================


;===Procedure Mul============================================================================
Mul_ PROC
	mov eax, [esp + 8]
	imul dword ptr [esp + 4]
	mov [esp + 8], eax
	pop ecx
	pop eax
	push ecx
	ret
Mul_ ENDP
;============================================================================================


;===Procedure Not============================================================================
Not_ PROC
	pushf
	pop cx

	mov eax, [esp + 4]
	cmp eax, 0
	jnz not_false
not_t1:
	mov eax, 1
	jmp not_fin
not_false:
	mov eax, 0
not_fin:
	push cx
	popf

	mov [esp + 4], eax
	ret
Not_ ENDP
;============================================================================================


;===Procedure Output=========================================================================
Output_ PROC value: dword
	invoke wsprintf, ADDR ResMessage, ADDR OutMessage, value
	invoke WriteConsoleA, hConsoleOutput, ADDR ResMessage, eax, 0, 0
	ret 4
Output_ ENDP
;============================================================================================


;===Procedure Sub============================================================================
Sub_ PROC
	mov eax, [esp + 8]
	sub eax, [esp + 4]
	mov [esp + 8], eax
	pop ecx
	pop eax
	push ecx
	ret
Sub_ ENDP
;============================================================================================
end start
