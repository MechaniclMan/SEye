; Listing generated by Microsoft (R) Optimizing Compiler Version 15.00.30729.01 

	TITLE	c:\Users\Admin\Desktop\Projects\SEye_Server\plugin.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB OLDNAMES

PUBLIC	??_C@_05NAOIJFC@Error?$AA@			; `string'
PUBLIC	??_C@_0BO@HFAODDHO@Error?3?5Could?5not?5open?5Winsock?$AA@ ; `string'
EXTRN	_exit:PROC
EXTRN	__imp__MessageBoxA@16:PROC
EXTRN	__imp__WSAStartup@8:PROC
;	COMDAT ??_C@_0BO@HFAODDHO@Error?3?5Could?5not?5open?5Winsock?$AA@
CONST	SEGMENT
??_C@_0BO@HFAODDHO@Error?3?5Could?5not?5open?5Winsock?$AA@ DB 'Error: Cou'
	DB	'ld not open Winsock', 00H			; `string'
CONST	ENDS
;	COMDAT ??_C@_05NAOIJFC@Error?$AA@
CONST	SEGMENT
??_C@_05NAOIJFC@Error?$AA@ DB 'Error', 00H		; `string'
__bad_alloc_Message DD FLAT:??_C@_0P@GHFPNOJB@bad?5allocation?$AA@
PUBLIC	?Plugin_Unload@@YAXXZ				; Plugin_Unload
; Function compile flags: /Ogtpy
; File c:\users\admin\desktop\projects\seye_server\plugin.cpp
;	COMDAT ?Plugin_Unload@@YAXXZ
_TEXT	SEGMENT
?Plugin_Unload@@YAXXZ PROC				; Plugin_Unload, COMDAT

; 61   : 	SEye_Server::Unload();

	jmp	?Unload@SEye_Server@@SAXXZ		; SEye_Server::Unload
?Plugin_Unload@@YAXXZ ENDP				; Plugin_Unload
PUBLIC	_SSGM_Level_Loaded_Hook
; Function compile flags: /Ogtpy
;	COMDAT _SSGM_Level_Loaded_Hook
_TEXT	SEGMENT
_SSGM_Level_Loaded_Hook PROC				; COMDAT

; 74   : 	SEye_Server::Level_Loaded();

	jmp	?Level_Loaded@SEye_Server@@SAXXZ	; SEye_Server::Level_Loaded
_SSGM_Level_Loaded_Hook ENDP
_TEXT	ENDS
PUBLIC	_SSGM_Chat_Hook
; Function compile flags: /Ogtpy
;	COMDAT _SSGM_Chat_Hook
_TEXT	SEGMENT
_ID$ = 8						; size = 4
_Type$ = 12						; size = 4
_Msg$ = 16						; size = 4
_SSGM_Chat_Hook PROC					; COMDAT

; 69   : 	SEye_Server::ChatHook(ID, Type, Msg);

	mov	eax, DWORD PTR _Msg$[esp-4]
	mov	ecx, DWORD PTR _Type$[esp-4]
	push	eax
	mov	eax, DWORD PTR _ID$[esp]
	push	ecx
	call	?ChatHook@SEye_Server@@SAXHHPB_W@Z	; SEye_Server::ChatHook
	add	esp, 8

; 70   : }

	ret	0
_SSGM_Chat_Hook ENDP
_TEXT	ENDS
PUBLIC	?ObjectHookCall@@YAXPAXPAE@Z			; ObjectHookCall
; Function compile flags: /Ogtpy
;	COMDAT ?ObjectHookCall@@YAXPAXPAE@Z
_TEXT	SEGMENT
___formal$ = 8						; size = 4
_o$ = 12						; size = 4
?ObjectHookCall@@YAXPAXPAE@Z PROC			; ObjectHookCall, COMDAT

; 36   : 	SEye_Server::ObjectHook(o);

	mov	eax, DWORD PTR _o$[esp-4]
	jmp	?ObjectHook@SEye_Server@@SAXPAE@Z	; SEye_Server::ObjectHook
?ObjectHookCall@@YAXPAXPAE@Z ENDP			; ObjectHookCall
PUBLIC	?Plugin_Load@@YAXXZ				; Plugin_Load
; Function compile flags: /Ogtpy
;	COMDAT ?Plugin_Load@@YAXXZ
_TEXT	SEGMENT
_wsaData$ = -400					; size = 400
?Plugin_Load@@YAXXZ PROC				; Plugin_Load, COMDAT

; 41   : {

	push	ebp
	mov	ebp, esp
	and	esp, -8					; fffffff8H
	sub	esp, 400				; 00000190H

; 42   : 	ObjectCreateHookStruct *ObjectHookStruct = new ObjectCreateHookStruct;

	cmp	DWORD PTR ?RenNew@@3P6APAXK@ZA, 0	; RenNew
	jne	SHORT $LN4@Plugin_Loa
	call	?InitEngine@@YAXXZ			; InitEngine
$LN4@Plugin_Loa:
	push	8
	call	DWORD PTR ?RenNew@@3P6APAXK@ZA		; RenNew
	add	esp, 4

; 43   : 	ObjectHookStruct->hook = ObjectHookCall;
; 44   : 	ObjectHookStruct->data = 0;
; 45   : 	AddObjectCreateHook(ObjectHookStruct);

	push	eax
	mov	DWORD PTR [eax], OFFSET ?ObjectHookCall@@YAXPAXPAE@Z ; ObjectHookCall
	mov	DWORD PTR [eax+4], 0
	call	DWORD PTR ?AddObjectCreateHook@@3P6AHPAUObjectCreateHookStruct@@@ZA ; AddObjectCreateHook
	add	esp, 4

; 46   : 
; 47   : 	WSADATA wsaData;
; 48   : 	if(WSAStartup(0x202, &wsaData))

	lea	eax, DWORD PTR _wsaData$[esp+400]
	push	eax
	push	514					; 00000202H
	call	DWORD PTR __imp__WSAStartup@8
	test	eax, eax
	je	SHORT $LN1@Plugin_Loa

; 49   : 	{
; 50   : 		MessageBox(0, "Error: Could not open Winsock", "Error", MB_OK);

	push	0
	push	OFFSET ??_C@_05NAOIJFC@Error?$AA@
	push	OFFSET ??_C@_0BO@HFAODDHO@Error?3?5Could?5not?5open?5Winsock?$AA@
	push	0
	call	DWORD PTR __imp__MessageBoxA@16

; 51   : 		exit(0);

	push	0
	call	_exit
$LN8@Plugin_Loa:
$LN1@Plugin_Loa:

; 52   : 	}
; 53   : 
; 54   : 	SEye_Server::Load();

	call	?Load@SEye_Server@@SAXXZ		; SEye_Server::Load

; 55   : 	
; 56   : }

	mov	esp, ebp
	pop	ebp
	ret	0
$LN7@Plugin_Loa:
?Plugin_Load@@YAXXZ ENDP				; Plugin_Load
END
