; -----------------------------------------------------------------------------------------------------------	
; Variable Declear
; -----------------------------------------------------------------------------------------------------------	
_DATA SEGMENT
	hello_msg db "Hello world", 0
	messageboxtext db "Hello From Main.asm", 0
	info_msg  db "Info", 0
_DATA ENDS

; -----------------------------------------------------------------------------------------------------------	
; Code Segment
; -----------------------------------------------------------------------------------------------------------	
_TEXT	SEGMENT

; Needed windows functions to show a MessageBox
EXTERN MessageBoxA: PROC
EXTERN GetForegroundWindow: PROC

; Functions Definitions
PUBLIC hello_world_asm
PUBLIC Main

hello_world_asm PROC
	push rbp ; save frame pointer
	mov rbp, rsp ; fix stack pointer
	;sub rsp, 8 * (4 + 2) ; allocate shadow register area + 2 QWORDs for stack alignment
	sub rsp, 32
	; Get a window handle
	call GetForegroundWindow
	add rsp, 32
	mov rcx, rax ; rax contains window handle

	; WINUSERAPI int WINAPI MessageBoxA(
	;  RCX =>  _In_opt_ HWND hWnd,
	;  RDX =>  _In_opt_ LPCSTR lpText,
	;  R8  =>  _In_opt_ LPCSTR lpCaption,
	;  R9  =>  _In_ UINT uType);

	mov rdx, offset messageboxtext
	mov r8, offset info_msg
	mov r9, 0 ; MB_OK

	sub rsp, 32
	;and rsp, not 8 ; align stack to 16 bytes prior to API call
	;sub rsp, 8 ; mess up the alignment
	call MessageBoxA
	add rsp, 32
	; epilog. restore stack pointer
	mov rsp, rbp
	pop rbp
	ret	
hello_world_asm ENDP

Main PROC
	push rbp ; save frame pointer
	mov rbp, rsp ; fix stack pointer
	mov al, 3
Main ENDP


_TEXT	ENDS

END