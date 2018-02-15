      TITLE   CpuAsm.asm: 
;------------------------------------------------------------------------------
;*
;*   Copyright (c) 2008 - 2013, Intel Corporation. All rights reserved.<BR>
;*   This program and the accompanying materials                          
;*   are licensed and made available under the terms and conditions of the BSD License         
;*   which accompanies this distribution.  The full text of the license may be found at        
;*   http://opensource.org/licenses/bsd-license.php                                            
;*                                                                                             
;*   THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
;*   WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             
;*   
;*    CpuAsm.asm
;*  
;*   Abstract:
;*
;------------------------------------------------------------------------------

    .code

;------------------------------------------------------------------------------
; VOID
; LoadTask (
;   UINT16 Selector
;   );
;------------------------------------------------------------------------------
LoadTask PROC PUBLIC
    mov     eax, ecx
    ltr     ax
    ret
LoadTask ENDP

END

