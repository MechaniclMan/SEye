; Listing generated by Microsoft (R) Optimizing Compiler Version 15.00.30729.01 

	TITLE	c:\Users\Admin\Desktop\Projects\SEye_Server\engine_player.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB OLDNAMES

PUBLIC	?SetLadderPoints@@3PAXA				; SetLadderPoints
PUBLIC	?GetColor@@3PAXA				; GetColor
PUBLIC	?GetPlayerCount@@3PAXA				; GetPlayerCount
PUBLIC	?Find_Team@@3P6APADH@ZA				; Find_Team
PUBLIC	?PlayerList@@3PAV?$SList@PAVcPlayer@@@@A	; PlayerList
PUBLIC	?Get_Color_For_Team@@3P6AXPAUVector3@@H@ZA	; Get_Color_For_Team
PUBLIC	?SetPlayerType@@3PAXA				; SetPlayerType
PUBLIC	?SetRung@@3PAXA					; SetRung
PUBLIC	?FindPlayer@@3P6APAVcPlayer@@H@ZA		; FindPlayer
PUBLIC	?TallyTeamSize@@3P6AHH@ZA			; TallyTeamSize
PUBLIC	??_C@_0BG@HDNGLABG@msg?5?$CFs?5switched?5teams?$AA@ ; `string'
?SetLadderPoints@@3PAXA DD 01H DUP (?)			; SetLadderPoints
?GetColor@@3PAXA DD 01H DUP (?)				; GetColor
?GetPlayerCount@@3PAXA DD 01H DUP (?)			; GetPlayerCount
?Find_Team@@3P6APADH@ZA DD 01H DUP (?)			; Find_Team
?PlayerList@@3PAV?$SList@PAVcPlayer@@@@A DD 01H DUP (?)	; PlayerList
?Get_Color_For_Team@@3P6AXPAUVector3@@H@ZA DD 01H DUP (?) ; Get_Color_For_Team
?SetPlayerType@@3PAXA DD 01H DUP (?)			; SetPlayerType
?SetRung@@3PAXA DD 01H DUP (?)				; SetRung
?FindPlayer@@3P6APAVcPlayer@@H@ZA DD 01H DUP (?)	; FindPlayer
?TallyTeamSize@@3P6AHH@ZA DD 01H DUP (?)		; TallyTeamSize
;	COMDAT ??_C@_0BG@HDNGLABG@msg?5?$CFs?5switched?5teams?$AA@
CONST	SEGMENT
??_C@_0BG@HDNGLABG@msg?5?$CFs?5switched?5teams?$AA@ DB 'msg %s switched t'
	DB	'eams', 00H					; `string'
PUBLIC	?Get_GameObj@@YAPAEH@Z				; Get_GameObj
; Function compile flags: /Ogtpy
; File c:\users\admin\desktop\projects\seye_server\engine_player.cpp
;	COMDAT ?Get_GameObj@@YAPAEH@Z
_TEXT	SEGMENT
?Get_GameObj@@YAPAEH@Z PROC				; Get_GameObj, COMDAT
; _PlayerID$ = eax

; 228  : 	cPlayer *x = FindPlayer(PlayerID);

	push	eax
	call	DWORD PTR ?FindPlayer@@3P6APAVcPlayer@@H@ZA ; FindPlayer
	add	esp, 4

; 229  : 	if ((x) && (x->Owner.Reference))

	test	eax, eax
	je	SHORT $LN1@Get_GameOb
	mov	eax, DWORD PTR [eax+20]
	test	eax, eax
	je	SHORT $LN1@Get_GameOb

; 230  : 	{
; 231  : 		return (GameObject *)x->Owner.Reference->obj;

	mov	eax, DWORD PTR [eax+4]

; 234  : }

	ret	0
$LN1@Get_GameOb:

; 232  : 	}
; 233  : 	return 0;

	xor	eax, eax

; 234  : }

	ret	0
?Get_GameObj@@YAPAEH@Z ENDP				; Get_GameObj
_TEXT	ENDS
PUBLIC	?InitEnginePlayer@@YAXI@Z			; InitEnginePlayer
; Function compile flags: /Ogtpy
;	COMDAT ?InitEnginePlayer@@YAXI@Z
_TEXT	SEGMENT
?InitEnginePlayer@@YAXI@Z PROC				; InitEnginePlayer, COMDAT

; 54   : {

	mov	eax, DWORD PTR ?Exe@@3HA		; Exe

; 55   : 	switch(exe)

	cmp	eax, 3
	ja	$LN1@InitEngine@5
	jmp	DWORD PTR $LN10@InitEngine@5[eax*4]
$LN5@InitEngine@5:

; 56   : 	{
; 57   : 		case 0: //game.exe
; 58   : 			GetColor = (void *)0x0040E530;

	mov	DWORD PTR ?GetColor@@3PAXA, 4252976	; GetColor, 0040e530H

; 59   : 			SetLadderPoints = (void *)0x0040FC90;

	mov	DWORD PTR ?SetLadderPoints@@3PAXA, 4258960 ; SetLadderPoints, 0040fc90H

; 60   : 			SetRung = (void *)0x00410790;

	mov	DWORD PTR ?SetRung@@3PAXA, 4261776	; SetRung, 00410790H

; 61   : 			FindPlayer = (Find_Player)0x004157E0;

	mov	DWORD PTR ?FindPlayer@@3P6APAVcPlayer@@H@ZA, 4282336 ; FindPlayer, 004157e0H

; 62   : 			SetPlayerType = (void *)0x0040D600;

	mov	DWORD PTR ?SetPlayerType@@3PAXA, 4249088 ; SetPlayerType, 0040d600H

; 63   : 			GetPlayerCount = (void *)0x00417040;

	mov	DWORD PTR ?GetPlayerCount@@3PAXA, 4288576 ; GetPlayerCount, 00417040H

; 64   : 			Get_Color_For_Team = (GetTeamColor)0x006D99E0;

	mov	DWORD PTR ?Get_Color_For_Team@@3P6AXPAUVector3@@H@ZA, 7182816 ; Get_Color_For_Team, 006d99e0H

; 65   : 			Find_Team = (FindTeam)0x0041DA10;

	mov	DWORD PTR ?Find_Team@@3P6APADH@ZA, 4315664 ; Find_Team, 0041da10H

; 66   : 			TallyTeamSize = (tts)0x004170D0;

	mov	DWORD PTR ?TallyTeamSize@@3P6AHH@ZA, 4288720 ; TallyTeamSize, 004170d0H

; 67   : 			PlayerList = (SList<cPlayer *> *)0x0081CFE8;

	mov	DWORD PTR ?PlayerList@@3PAV?$SList@PAVcPlayer@@@@A, 8507368 ; PlayerList, 0081cfe8H

; 115  : 			break;
; 116  : 	}
; 117  : }

	ret	0
$LN4@InitEngine@5:

; 68   : 			break;
; 69   : 		case 1: //server.dat
; 70   : 			GetColor = (void *)0x0040E530;

	mov	DWORD PTR ?GetColor@@3PAXA, 4252976	; GetColor, 0040e530H

; 71   : 			SetLadderPoints = (void *)0x0040FC90;

	mov	DWORD PTR ?SetLadderPoints@@3PAXA, 4258960 ; SetLadderPoints, 0040fc90H

; 72   : 			SetRung = (void *)0x00410790;

	mov	DWORD PTR ?SetRung@@3PAXA, 4261776	; SetRung, 00410790H

; 73   : 			FindPlayer = (Find_Player)0x004157E0;

	mov	DWORD PTR ?FindPlayer@@3P6APAVcPlayer@@H@ZA, 4282336 ; FindPlayer, 004157e0H

; 74   : 			SetPlayerType = (void *)0x0040D600;

	mov	DWORD PTR ?SetPlayerType@@3PAXA, 4249088 ; SetPlayerType, 0040d600H

; 75   : 			GetPlayerCount = (void *)0x00417040;

	mov	DWORD PTR ?GetPlayerCount@@3PAXA, 4288576 ; GetPlayerCount, 00417040H

; 76   : 			Get_Color_For_Team = (GetTeamColor)0x006D9280;

	mov	DWORD PTR ?Get_Color_For_Team@@3P6AXPAUVector3@@H@ZA, 7180928 ; Get_Color_For_Team, 006d9280H

; 77   : 			Find_Team = (FindTeam)0x0041DA10;

	mov	DWORD PTR ?Find_Team@@3P6APADH@ZA, 4315664 ; Find_Team, 0041da10H

; 78   : 			TallyTeamSize = (tts)0x004170D0;

	mov	DWORD PTR ?TallyTeamSize@@3P6AHH@ZA, 4288720 ; TallyTeamSize, 004170d0H

; 79   : 			PlayerList = (SList<cPlayer *> *)0x0081C1C8;

	mov	DWORD PTR ?PlayerList@@3PAV?$SList@PAVcPlayer@@@@A, 8503752 ; PlayerList, 0081c1c8H

; 115  : 			break;
; 116  : 	}
; 117  : }

	ret	0
$LN3@InitEngine@5:

; 80   : 			break;
; 81   : 		case 2: //RH73
; 82   : 			GetColor = (void *)0x080A74D4;

	mov	DWORD PTR ?GetColor@@3PAXA, 134902996	; GetColor, 080a74d4H

; 83   : 			SetLadderPoints = (void *)0x080A84B0;

	mov	DWORD PTR ?SetLadderPoints@@3PAXA, 134907056 ; SetLadderPoints, 080a84b0H

; 84   : 			SetRung = (void *)0x080A8560;

	mov	DWORD PTR ?SetRung@@3PAXA, 134907232	; SetRung, 080a8560H

; 85   : 			FindPlayer = (Find_Player)0x080A9CDC;

	mov	DWORD PTR ?FindPlayer@@3P6APAVcPlayer@@H@ZA, 134913244 ; FindPlayer, 080a9cdcH

; 86   : 			SetPlayerType = (void *)0x080A7438;

	mov	DWORD PTR ?SetPlayerType@@3PAXA, 134902840 ; SetPlayerType, 080a7438H

; 87   : 			GetPlayerCount = (void *)0x080AA7F0;

	mov	DWORD PTR ?GetPlayerCount@@3PAXA, 134916080 ; GetPlayerCount, 080aa7f0H

; 88   : 			Get_Color_For_Team = (GetTeamColor)0x08102AA8;

	mov	DWORD PTR ?Get_Color_For_Team@@3P6AXPAUVector3@@H@ZA, 135277224 ; Get_Color_For_Team, 08102aa8H

; 89   : 			Find_Team = (FindTeam)0x080BFBD4;

	mov	DWORD PTR ?Find_Team@@3P6APADH@ZA, 135003092 ; Find_Team, 080bfbd4H

; 90   : 			TallyTeamSize = (tts)0x080AA84C;

	mov	DWORD PTR ?TallyTeamSize@@3P6AHH@ZA, 134916172 ; TallyTeamSize, 080aa84cH

; 91   : 			PlayerList = (SList<cPlayer *> *)0x08B9B0C8;

	mov	DWORD PTR ?PlayerList@@3PAV?$SList@PAVcPlayer@@@@A, 146387144 ; PlayerList, 08b9b0c8H

; 115  : 			break;
; 116  : 	}
; 117  : }

	ret	0
$LN2@InitEngine@5:

; 92   : 			break;
; 93   : 		case 3: //RH8
; 94   : 			GetColor = (void *)0x080A2EE6;

	mov	DWORD PTR ?GetColor@@3PAXA, 134885094	; GetColor, 080a2ee6H

; 95   : 			SetLadderPoints = (void *)0x080A3BEE;

	mov	DWORD PTR ?SetLadderPoints@@3PAXA, 134888430 ; SetLadderPoints, 080a3beeH

; 96   : 			SetRung = (void *)0x080A3C8E;

	mov	DWORD PTR ?SetRung@@3PAXA, 134888590	; SetRung, 080a3c8eH

; 97   : 			FindPlayer = (Find_Player)0x080A510A;

	mov	DWORD PTR ?FindPlayer@@3P6APAVcPlayer@@H@ZA, 134893834 ; FindPlayer, 080a510aH

; 98   : 			SetPlayerType = (void *)0x080A2E50;

	mov	DWORD PTR ?SetPlayerType@@3PAXA, 134884944 ; SetPlayerType, 080a2e50H

; 99   : 			GetPlayerCount = (void *)0x080A5A62;

	mov	DWORD PTR ?GetPlayerCount@@3PAXA, 134896226 ; GetPlayerCount, 080a5a62H

; 100  : 			Get_Color_For_Team = (GetTeamColor)0x080F5EB8;

	mov	DWORD PTR ?Get_Color_For_Team@@3P6AXPAUVector3@@H@ZA, 135225016 ; Get_Color_For_Team, 080f5eb8H

; 101  : 			Find_Team = (FindTeam)0x080B82C4;

	mov	DWORD PTR ?Find_Team@@3P6APADH@ZA, 134972100 ; Find_Team, 080b82c4H

; 102  : 			TallyTeamSize = (tts)0x080A5AB6;

	mov	DWORD PTR ?TallyTeamSize@@3P6AHH@ZA, 134896310 ; TallyTeamSize, 080a5ab6H

; 103  : 			PlayerList = (SList<cPlayer *> *)0x089A2200;

	mov	DWORD PTR ?PlayerList@@3PAV?$SList@PAVcPlayer@@@@A, 144318976 ; PlayerList, 089a2200H

; 115  : 			break;
; 116  : 	}
; 117  : }

	ret	0
$LN1@InitEngine@5:

; 104  : 			break;
; 105  : 		default:
; 106  : 			GetColor = (void *)0;

	xor	eax, eax
	mov	DWORD PTR ?GetColor@@3PAXA, eax		; GetColor

; 107  : 			SetLadderPoints = (void *)0;

	mov	DWORD PTR ?SetLadderPoints@@3PAXA, eax	; SetLadderPoints

; 108  : 			SetRung = (void *)0;

	mov	DWORD PTR ?SetRung@@3PAXA, eax		; SetRung

; 109  : 			FindPlayer = (Find_Player)0;

	mov	DWORD PTR ?FindPlayer@@3P6APAVcPlayer@@H@ZA, eax ; FindPlayer

; 110  : 			SetPlayerType = (void *)0;

	mov	DWORD PTR ?SetPlayerType@@3PAXA, eax	; SetPlayerType

; 111  : 			GetPlayerCount = (void *)0;

	mov	DWORD PTR ?GetPlayerCount@@3PAXA, eax	; GetPlayerCount

; 112  : 			Get_Color_For_Team = (GetTeamColor)0;

	mov	DWORD PTR ?Get_Color_For_Team@@3P6AXPAUVector3@@H@ZA, eax ; Get_Color_For_Team

; 113  : 			Find_Team = (FindTeam)0;

	mov	DWORD PTR ?Find_Team@@3P6APADH@ZA, eax	; Find_Team

; 114  : 			TallyTeamSize = (tts)0;

	mov	DWORD PTR ?TallyTeamSize@@3P6AHH@ZA, eax ; TallyTeamSize

; 115  : 			break;
; 116  : 	}
; 117  : }

	ret	0
	npad	3
$LN10@InitEngine@5:
	DD	$LN5@InitEngine@5
	DD	$LN4@InitEngine@5
	DD	$LN3@InitEngine@5
	DD	$LN2@InitEngine@5
?InitEnginePlayer@@YAXI@Z ENDP				; InitEnginePlayer
PUBLIC	?Get_Team@@YAHH@Z				; Get_Team
; Function compile flags: /Ogtpy
;	COMDAT ?Get_Team@@YAHH@Z
_TEXT	SEGMENT
?Get_Team@@YAHH@Z PROC					; Get_Team, COMDAT
; _PlayerID$ = eax

; 238  : 	cPlayer *x = FindPlayer(PlayerID);

	push	eax
	call	DWORD PTR ?FindPlayer@@3P6APAVcPlayer@@H@ZA ; FindPlayer
	add	esp, 4

; 239  : 	if (!x)

	test	eax, eax
	jne	SHORT $LN1@Get_Team

; 244  : }

	ret	0
$LN1@Get_Team:

; 240  : 	{
; 241  : 		return 0;
; 242  : 	}
; 243  : 	return x->PlayerType.Get();

	lea	ecx, DWORD PTR [eax+1900]
	jmp	?Get@IntDataSafeClass@@QAEHXZ		; IntDataSafeClass::Get
?Get_Team@@YAHH@Z ENDP					; Get_Team
_TEXT	ENDS
PUBLIC	?Get_Player_ID@@YAJPAE@Z			; Get_Player_ID
; Function compile flags: /Ogtpy
;	COMDAT ?Get_Player_ID@@YAJPAE@Z
_TEXT	SEGMENT
?Get_Player_ID@@YAJPAE@Z PROC				; Get_Player_ID, COMDAT
; _obj$ = esi

; 207  : 	if (!Commands->Get_ID(obj) || !obj)

	mov	eax, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	ecx, DWORD PTR [eax+108]
	push	esi
	call	ecx
	add	esp, 4
	test	eax, eax
	je	SHORT $LN3@Get_Player
	test	esi, esi
	je	SHORT $LN3@Get_Player

; 210  : 	}
; 211  : 	GameObject *o = As_SoldierGameObj(obj);

	mov	edx, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	eax, DWORD PTR [edx+108]
	push	esi
	call	eax
	add	esp, 4
	test	eax, eax
	je	SHORT $LN3@Get_Player
	mov	edx, DWORD PTR [esi]
	mov	eax, DWORD PTR [edx+68]
	mov	ecx, esi
	call	eax

; 212  : 	if (!o)

	test	eax, eax

; 213  : 	{
; 214  : 		return -1;

	je	SHORT $LN3@Get_Player

; 215  : 	}
; 216  : 	char *c = (char *)o;
; 217  : 	c += 0x960;
; 218  : 	cPlayer *x = (cPlayer *)*(unsigned int *)c;

	mov	eax, DWORD PTR [eax+2400]

; 219  : 	if (!x)

	test	eax, eax

; 220  : 	{
; 221  : 		return -1;

	je	SHORT $LN3@Get_Player

; 222  : 	}
; 223  : 	return x->PlayerId;

	mov	eax, DWORD PTR [eax+1884]

; 224  : }

	ret	0
$LN3@Get_Player:

; 208  : 	{
; 209  : 		return -1;

	or	eax, -1

; 224  : }

	ret	0
?Get_Player_ID@@YAJPAE@Z ENDP				; Get_Player_ID
PUBLIC	?Get_Player_Name_By_ID@@YAPBDH@Z		; Get_Player_Name_By_ID
; Function compile flags: /Ogtpy
;	COMDAT ?Get_Player_Name_By_ID@@YAPBDH@Z
_TEXT	SEGMENT
?Get_Player_Name_By_ID@@YAPBDH@Z PROC			; Get_Player_Name_By_ID, COMDAT
; _PlayerID$ = eax

; 142  : 	cPlayer *x = FindPlayer(PlayerID);

	push	eax
	call	DWORD PTR ?FindPlayer@@3P6APAVcPlayer@@H@ZA ; FindPlayer
	add	esp, 4

; 143  : 	if (!x)

	test	eax, eax
	jne	SHORT $LN1@Get_Player@2

; 148  : }

	ret	0
$LN1@Get_Player@2:

; 144  : 	{
; 145  : 		return 0;
; 146  : 	}
; 147  : 	return WideCharToChar(x->PlayerName);

	mov	eax, DWORD PTR [eax+1880]
	push	eax
	call	?WideCharToChar@@YAPBDPB_W@Z		; WideCharToChar
	add	esp, 4

; 148  : }

	ret	0
?Get_Player_Name_By_ID@@YAPBDH@Z ENDP			; Get_Player_Name_By_ID
_TEXT	ENDS
PUBLIC	?Get_Player_Name@@YAPBDPAE@Z			; Get_Player_Name
; Function compile flags: /Ogtpy
;	COMDAT ?Get_Player_Name@@YAPBDPAE@Z
_TEXT	SEGMENT
?Get_Player_Name@@YAPBDPAE@Z PROC			; Get_Player_Name, COMDAT
; _obj$ = esi

; 121  : 	if (!Commands->Get_ID(obj) || !obj)

	mov	eax, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	ecx, DWORD PTR [eax+108]
	push	esi
	call	ecx
	add	esp, 4
	test	eax, eax
	je	SHORT $LN3@Get_Player@3
	test	esi, esi
	je	SHORT $LN3@Get_Player@3

; 124  : 	}
; 125  : 	GameObject *o = As_SoldierGameObj(obj);

	mov	edx, DWORD PTR ?Commands@@3PAUScriptCommands@@A ; Commands
	mov	eax, DWORD PTR [edx+108]
	push	esi
	call	eax
	add	esp, 4
	test	eax, eax
	je	SHORT $LN18@Get_Player@3
	mov	edx, DWORD PTR [esi]
	mov	eax, DWORD PTR [edx+68]
	mov	ecx, esi
	call	eax

; 126  : 	char *c = (char *)o;
; 127  : 	if (!o)

	test	eax, eax
	jne	SHORT $LN2@Get_Player@3
$LN18@Get_Player@3:

; 128  : 	{
; 129  : 		return newstr("None");

	push	OFFSET ??_C@_04OHJIHAFH@None?$AA@
	call	?newstr@@YAPADPBD@Z			; newstr
	add	esp, 4

; 138  : }

	ret	0
$LN2@Get_Player@3:

; 130  : 	}
; 131  : 	c += 0x960;
; 132  : 	cPlayer *x = (cPlayer *)*(unsigned int *)c;

	mov	eax, DWORD PTR [eax+2400]

; 133  : 	if (!x)

	test	eax, eax

; 134  : 	{
; 135  : 		return newstr("None");

	je	SHORT $LN18@Get_Player@3

; 136  : 	}
; 137  : 	return WideCharToChar(x->PlayerName);

	mov	eax, DWORD PTR [eax+1880]
	push	eax
	call	?WideCharToChar@@YAPBDPB_W@Z		; WideCharToChar
	add	esp, 4

; 138  : }

	ret	0
$LN3@Get_Player@3:

; 122  : 	{
; 123  : 		return newstr("None");

	cmp	DWORD PTR ?RenNew@@3P6APAXK@ZA, 0	; RenNew
	jne	SHORT $LN9@Get_Player@3
	call	?InitEngine@@YAXXZ			; InitEngine
$LN9@Get_Player@3:
	push	5
	call	DWORD PTR ?RenNew@@3P6APAXK@ZA		; RenNew
	mov	ecx, DWORD PTR ??_C@_04OHJIHAFH@None?$AA@
	mov	DWORD PTR [eax], ecx
	mov	dl, BYTE PTR ??_C@_04OHJIHAFH@None?$AA@+4
	mov	BYTE PTR [eax+4], dl
	add	esp, 4

; 138  : }

	ret	0
?Get_Player_Name@@YAPBDPAE@Z ENDP			; Get_Player_Name
END