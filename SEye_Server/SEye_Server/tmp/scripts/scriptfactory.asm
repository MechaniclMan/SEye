; Listing generated by Microsoft (R) Optimizing Compiler Version 15.00.30729.01 

	TITLE	c:\Users\Admin\Desktop\Projects\SEye_Server\scriptfactory.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB OLDNAMES

PUBLIC	??_R4ScriptFactory@@6B@				; ScriptFactory::`RTTI Complete Object Locator'
PUBLIC	??_GScriptFactory@@UAEPAXI@Z			; ScriptFactory::`scalar deleting destructor'
PUBLIC	??_7ScriptFactory@@6B@				; ScriptFactory::`vftable'
EXTRN	__purecall:PROC
EXTRN	??_EScriptFactory@@UAEPAXI@Z:PROC		; ScriptFactory::`vector deleting destructor'
;	COMDAT ??_7ScriptFactory@@6B@
CONST	SEGMENT
??_7ScriptFactory@@6B@ DD FLAT:??_R4ScriptFactory@@6B@	; ScriptFactory::`vftable'
	DD	FLAT:??_EScriptFactory@@UAEPAXI@Z
	DD	FLAT:__purecall
CONST	ENDS
;	COMDAT ??_R4ScriptFactory@@6B@
rdata$r	SEGMENT
??_R4ScriptFactory@@6B@ DD 00H				; ScriptFactory::`RTTI Complete Object Locator'
	DD	00H
	DD	00H
	DD	FLAT:??_R0?AVScriptFactory@@@8
	DD	FLAT:??_R3ScriptFactory@@8
PUBLIC	?SetNext@ScriptFactory@@QAEXPAV1@@Z		; ScriptFactory::SetNext
; Function compile flags: /Ogtpy
; File c:\users\admin\desktop\projects\seye_server\scriptfactory.cpp
;	COMDAT ?SetNext@ScriptFactory@@QAEXPAV1@@Z
_TEXT	SEGMENT
?SetNext@ScriptFactory@@QAEXPAV1@@Z PROC		; ScriptFactory::SetNext, COMDAT
; _this$ = eax
; _link$ = ecx

; 47   : 	next = link;

	mov	DWORD PTR [eax+4], ecx

; 48   : }

	ret	0
?SetNext@ScriptFactory@@QAEXPAV1@@Z ENDP		; ScriptFactory::SetNext
_TEXT	ENDS
PUBLIC	?GetName@ScriptFactory@@QAEPADXZ		; ScriptFactory::GetName
; Function compile flags: /Ogtpy
;	COMDAT ?GetName@ScriptFactory@@QAEPADXZ
_TEXT	SEGMENT
?GetName@ScriptFactory@@QAEPADXZ PROC			; ScriptFactory::GetName, COMDAT
; _this$ = eax

; 30   : 	return name;

	mov	eax, DWORD PTR [eax+8]

; 31   : }

	ret	0
?GetName@ScriptFactory@@QAEPADXZ ENDP			; ScriptFactory::GetName
_TEXT	ENDS
PUBLIC	?GetNext@ScriptFactory@@QAEPAV1@XZ		; ScriptFactory::GetNext
; Function compile flags: /Ogtpy
;	COMDAT ?GetNext@ScriptFactory@@QAEPAV1@XZ
_TEXT	SEGMENT
?GetNext@ScriptFactory@@QAEPAV1@XZ PROC			; ScriptFactory::GetNext, COMDAT
; _this$ = eax

; 25   : 	return next;

	mov	eax, DWORD PTR [eax+4]

; 26   : }

	ret	0
?GetNext@ScriptFactory@@QAEPAV1@XZ ENDP			; ScriptFactory::GetNext
PUBLIC	??1ScriptFactory@@UAE@XZ			; ScriptFactory::~ScriptFactory
; Function compile flags: /Ogtpy
;	COMDAT ??1ScriptFactory@@UAE@XZ
_TEXT	SEGMENT
??1ScriptFactory@@UAE@XZ PROC				; ScriptFactory::~ScriptFactory, COMDAT
; _this$ = ecx

; 40   : 	ScriptRegistrar::UnregisterScript(this);

	mov	eax, DWORD PTR ?mScriptFactories@ScriptRegistrar@@0PAVScriptFactory@@A ; ScriptRegistrar::mScriptFactories
	push	esi
	push	edi
	xor	edi, edi
	xor	esi, esi
	mov	DWORD PTR [ecx], OFFSET ??_7ScriptFactory@@6B@
	cmp	eax, edi
	je	SHORT $LN16@ScriptFact
$LL7@ScriptFact:
	mov	edx, DWORD PTR [eax+4]
	cmp	eax, ecx
	jne	SHORT $LN12@ScriptFact
	cmp	esi, edi
	jne	SHORT $LN4@ScriptFact
	mov	DWORD PTR ?mScriptFactories@ScriptRegistrar@@0PAVScriptFactory@@A, edx ; ScriptRegistrar::mScriptFactories
	jmp	SHORT $LN12@ScriptFact
$LN4@ScriptFact:
	mov	DWORD PTR [esi+4], edx
$LN12@ScriptFact:
	mov	esi, eax
	mov	eax, edx
	cmp	edx, edi
	jne	SHORT $LL7@ScriptFact
$LN16@ScriptFact:

; 41   : 	name = 0;
; 42   : 	params = 0;

	mov	DWORD PTR [ecx+12], edi
	mov	DWORD PTR [ecx+8], edi
	pop	edi
	pop	esi

; 43   : }

	ret	0
??1ScriptFactory@@UAE@XZ ENDP				; ScriptFactory::~ScriptFactory
; Function compile flags: /Ogtpy
_TEXT	ENDS
;	COMDAT ??_GScriptFactory@@UAEPAXI@Z
_TEXT	SEGMENT
___flags$ = 8						; size = 4
??_GScriptFactory@@UAEPAXI@Z PROC			; ScriptFactory::`scalar deleting destructor', COMDAT
; _this$ = ecx
	push	esi
	mov	esi, ecx
	call	??1ScriptFactory@@UAE@XZ		; ScriptFactory::~ScriptFactory
	test	BYTE PTR ___flags$[esp], 1
	je	SHORT $LN6@scalar@5
	push	esi
	call	DWORD PTR ?RenDelete@@3P6AXPAX@ZA	; RenDelete
	add	esp, 4
$LN6@scalar@5:
	mov	eax, esi
	pop	esi
	ret	4
??_GScriptFactory@@UAEPAXI@Z ENDP			; ScriptFactory::`scalar deleting destructor'
_TEXT	ENDS
PUBLIC	??0ScriptFactory@@QAE@PAD0@Z			; ScriptFactory::ScriptFactory
; Function compile flags: /Ogtpy
;	COMDAT ??0ScriptFactory@@QAE@PAD0@Z
_TEXT	SEGMENT
??0ScriptFactory@@QAE@PAD0@Z PROC			; ScriptFactory::ScriptFactory, COMDAT
; _this$ = eax
; _n$ = ecx

; 17   : 	name = n;
; 18   : 	params = p;
; 19   : 	next = 0;
; 20   : 	ScriptRegistrar::RegisterScript(this);

	mov	edx, DWORD PTR ?mScriptFactories@ScriptRegistrar@@0PAVScriptFactory@@A ; ScriptRegistrar::mScriptFactories
	mov	DWORD PTR [eax], OFFSET ??_7ScriptFactory@@6B@
	mov	DWORD PTR [eax+8], ecx
	mov	DWORD PTR [eax+12], OFFSET ??_C@_00CNPNBAHC@?$AA@
	mov	DWORD PTR [eax+4], edx
	mov	DWORD PTR ?mScriptFactories@ScriptRegistrar@@0PAVScriptFactory@@A, eax ; ScriptRegistrar::mScriptFactories

; 21   : }

	ret	0
??0ScriptFactory@@QAE@PAD0@Z ENDP			; ScriptFactory::ScriptFactory
END
