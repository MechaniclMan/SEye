; Listing generated by Microsoft (R) Optimizing Compiler Version 15.00.30729.01 

	TITLE	c:\Users\Admin\Desktop\Projects\SEye_Server\engine_script.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB OLDNAMES

PUBLIC	?Attach_Script_Building@@YAXPBD0H@Z		; Attach_Script_Building
; Function compile flags: /Ogtpy
; File c:\users\admin\desktop\projects\seye_server\engine_script.cpp
;	COMDAT ?Attach_Script_Building@@YAXPBD0H@Z
_TEXT	SEGMENT
?Attach_Script_Building@@YAXPBD0H@Z PROC		; Attach_Script_Building, COMDAT

; 269  : {

	push	ecx

; 270  : 	GenericSLNode *x = BuildingGameObjList->HeadNode;

	mov	eax, DWORD PTR ?BuildingGameObjList@@3PAV?$SList@E@@A ; BuildingGameObjList
	push	edi
	mov	edi, DWORD PTR [eax+4]

; 271  : 	while (x)

	test	edi, edi
	je	SHORT $LN4@Attach_Scr
	push	esi
	npad	1
$LL5@Attach_Scr:

; 272  : 	{
; 273  : 		GameObject *o = (GameObject *)x->NodeData;

	mov	esi, DWORD PTR [edi+4]

; 274  : 		if ((o) && As_BuildingGameObj(o))

	test	esi, esi
	je	SHORT $LN2@Attach_Scr
	mov	ecx, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	edx, DWORD PTR [ecx+108]
	push	esi
	call	edx
	add	esp, 4
	test	eax, eax
	je	SHORT $LN2@Attach_Scr
	mov	eax, DWORD PTR [esi]
	mov	edx, DWORD PTR [eax+64]
	mov	ecx, esi
	call	edx
	test	eax, eax
	je	SHORT $LN2@Attach_Scr

; 275  : 		{
; 276  : 			if ((Get_Object_Type(o) == team) || (team == 2))

	mov	eax, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	ecx, DWORD PTR [eax+108]
	push	esi
	call	ecx
	add	esp, 4
	test	eax, eax
	je	SHORT $LN13@Attach_Scr
	mov	edx, DWORD PTR [esi]
	mov	eax, DWORD PTR [edx+60]
	mov	ecx, esi
	call	eax
$LN13@Attach_Scr:

; 277  : 			{
; 278  : 				Commands->Attach_Script(o,script,params);

	mov	ecx, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	edx, DWORD PTR [ecx+120]
	push	OFFSET ??_C@_00CNPNBAHC@?$AA@
	push	OFFSET ??_C@_0BF@MCAOHKKL@SEye_Building_Update?$AA@
	push	esi
	call	edx
	add	esp, 12					; 0000000cH
$LN2@Attach_Scr:

; 279  : 			}
; 280  : 		}
; 281  : 		x = x->NodeNext;

	mov	edi, DWORD PTR [edi]
	test	edi, edi
	jne	SHORT $LL5@Attach_Scr
	pop	esi
$LN4@Attach_Scr:
	pop	edi

; 282  : 	}
; 283  : }

	pop	ecx
	ret	0
?Attach_Script_Building@@YAXPBD0H@Z ENDP		; Attach_Script_Building
_TEXT	ENDS
PUBLIC	?Is_Script_Attached@@YA_NPAEPBD@Z		; Is_Script_Attached
; Function compile flags: /Ogtpy
;	COMDAT ?Is_Script_Attached@@YA_NPAEPBD@Z
_TEXT	SEGMENT
_script$ = 8						; size = 4
?Is_Script_Attached@@YA_NPAEPBD@Z PROC			; Is_Script_Attached, COMDAT
; _obj$ = edi

; 168  : 	if (!Commands->Get_ID(obj) || !obj)

	mov	eax, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	ecx, DWORD PTR [eax+108]
	push	ebp
	mov	ebp, DWORD PTR _script$[esp]
	push	edi
	call	ecx
	add	esp, 4
	test	eax, eax
	je	SHORT $LN5@Is_Script_
	test	edi, edi
	je	SHORT $LN5@Is_Script_
	push	ebx

; 171  : 	}
; 172  : 	SimpleDynVecClass<GameObjObserverClass *> *observers = &((ScriptableGameObj *)obj)->Observers;
; 173  : 	int x = observers->Count();

	mov	ebx, DWORD PTR [edi+1784]
	push	esi

; 174  : 	for (int i = 0;i < x;i++)

	xor	esi, esi
	test	ebx, ebx
	jle	SHORT $LN2@Is_Script_
	npad	7
$LL4@Is_Script_:

; 175  : 	{
; 176  : 		if (!_stricmp((*observers)[i]->Get_Name(),script))

	mov	edx, DWORD PTR [edi+1776]
	mov	ecx, DWORD PTR [edx+esi*4]
	mov	eax, DWORD PTR [ecx]
	mov	edx, DWORD PTR [eax+4]
	push	ebp
	call	edx
	push	eax
	call	__stricmp
	add	esp, 8
	test	eax, eax
	je	SHORT $LN14@Is_Script_
	inc	esi
	cmp	esi, ebx
	jl	SHORT $LL4@Is_Script_
$LN2@Is_Script_:
	pop	esi
	pop	ebx

; 179  : 		}
; 180  : 	}
; 181  : 	return false;

	xor	al, al
	pop	ebp

; 182  : }

	ret	0
$LN14@Is_Script_:
	pop	esi
	pop	ebx

; 177  : 		{
; 178  : 			return true;

	mov	al, 1
	pop	ebp

; 182  : }

	ret	0
$LN5@Is_Script_:

; 169  : 	{
; 170  : 		return false;

	xor	al, al
	pop	ebp

; 182  : }

	ret	0
?Is_Script_Attached@@YA_NPAEPBD@Z ENDP			; Is_Script_Attached
_TEXT	ENDS
PUBLIC	?Remove_Script@@YAXPAEPBD@Z			; Remove_Script
; Function compile flags: /Ogtpy
;	COMDAT ?Remove_Script@@YAXPAEPBD@Z
_TEXT	SEGMENT
?Remove_Script@@YAXPAEPBD@Z PROC			; Remove_Script, COMDAT
; _obj$ = edi

; 29   : 	if (!Commands->Get_ID(obj) || !obj)

	mov	eax, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	ecx, DWORD PTR [eax+108]
	push	edi
	call	ecx
	add	esp, 4
	test	eax, eax
	je	SHORT $LN5@Remove_Scr
	test	edi, edi
	je	SHORT $LN5@Remove_Scr
	push	ebx

; 30   : 	{
; 31   : 		return;
; 32   : 	}
; 33   : 	SimpleDynVecClass<GameObjObserverClass *> *observers = &((ScriptableGameObj *)obj)->Observers;
; 34   : 	int x = observers->Count();

	mov	ebx, DWORD PTR [edi+1784]
	push	esi

; 35   : 	for (int i = 0;i < x;i++)

	xor	esi, esi
	test	ebx, ebx
	jle	SHORT $LN20@Remove_Scr
$LL4@Remove_Scr:

; 36   : 	{
; 37   : 		if (!_stricmp((*observers)[i]->Get_Name(),script))

	mov	edx, DWORD PTR [edi+1776]
	mov	ecx, DWORD PTR [edx+esi*4]
	mov	eax, DWORD PTR [ecx]
	mov	edx, DWORD PTR [eax+4]
	push	OFFSET ??_C@_0BE@KDALBFM@SEye_Vehicle_Update?$AA@
	call	edx
	push	eax
	call	__stricmp
	add	esp, 8
	test	eax, eax
	jne	SHORT $LN3@Remove_Scr

; 38   : 		{
; 39   : 			((ScriptImpClass*)(*observers)[i])->Destroy_Script();

	mov	eax, DWORD PTR ?RequestDestroyScript@ScriptImpClass@@0P6AXPAVScriptClass@@@ZA ; ScriptImpClass::RequestDestroyScript
	test	eax, eax
	je	SHORT $LN3@Remove_Scr
	mov	ecx, DWORD PTR [edi+1776]
	mov	edx, DWORD PTR [ecx+esi*4]
	push	edx
	call	eax
	add	esp, 4
$LN3@Remove_Scr:
	inc	esi
	cmp	esi, ebx
	jl	SHORT $LL4@Remove_Scr
$LN20@Remove_Scr:
	pop	esi
	pop	ebx
$LN5@Remove_Scr:

; 40   : 		}
; 41   : 	}
; 42   : }

	ret	0
?Remove_Script@@YAXPAEPBD@Z ENDP			; Remove_Script
PUBLIC	?Attach_Script_Once@@YAXPAEPBD1@Z		; Attach_Script_Once
; Function compile flags: /Ogtpy
;	COMDAT ?Attach_Script_Once@@YAXPAEPBD1@Z
_TEXT	SEGMENT
?Attach_Script_Once@@YAXPAEPBD1@Z PROC			; Attach_Script_Once, COMDAT
; _obj$ = eax
; _script$ = esi

; 185  : {

	push	edi
	mov	edi, eax

; 186  : 	if (!Commands->Get_ID(obj) || !obj)

	mov	eax, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	ecx, DWORD PTR [eax+108]
	push	edi
	call	ecx
	add	esp, 4
	test	eax, eax
	je	SHORT $LN2@Attach_Scr@2
	test	edi, edi
	je	SHORT $LN2@Attach_Scr@2

; 187  : 	{
; 188  : 		return;
; 189  : 	}
; 190  : 	if (!Is_Script_Attached(obj,script))

	push	esi
	call	?Is_Script_Attached@@YA_NPAEPBD@Z	; Is_Script_Attached
	add	esp, 4
	test	al, al
	jne	SHORT $LN2@Attach_Scr@2

; 191  : 	{
; 192  : 		Commands->Attach_Script(obj,script,params);

	mov	edx, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	eax, DWORD PTR [edx+120]
	push	OFFSET ??_C@_00CNPNBAHC@?$AA@
	push	esi
	push	edi
	call	eax
	add	esp, 12					; 0000000cH
$LN2@Attach_Scr@2:
	pop	edi

; 193  : 	}
; 194  : }

	ret	0
?Attach_Script_Once@@YAXPAEPBD1@Z ENDP			; Attach_Script_Once
END
