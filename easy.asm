.286
.model tiny
.code
org 100h
locals @@

;--------------------------------------

Start:  jmp Main
        PasswordBuffer db PasswordLength dup(?)

Main:   mov si, offset PasswordBuffer
        call GetLine

        mov si, offset PasswordBuffer
        call CalculateHash

        cmp ax, CorrectPasswordHash
        je @@Correct

        mov dx, offset IncorrectPhraze
        call Puts
        call Exit

@@Correct:
        mov dx, offset CorrectPhraze
        call Puts
        call Exit

Exit:   mov ax, 4c00h
        int 21h

;--------------------------------------
; Puts '$' terminated string located in dx

Puts:   mov ah, 09h
        int 21h

        ret

;--------------------------------------
; Gets line until '\n' symbol by symbol
; Entry:        SI - buffer_ptr
; Destroy:      SI, AX
GetLine:
        xor ax, ax
        mov ah, 01h

@@While:
        int 21h
        cmp al, 0dh     ; while al != '\n'
        je @@RetL

        mov [si], al
        inc si
        jmp @@While

@@RetL: ret

;--------------------------------------
; Calculates line (pointed by SI) hash, returns it in AX
; Entry:        SI - buffer_ptr
; Destroy:      AX, BX, CX, SI

CalculateHash:
        xor ax, ax
        xor bx, bx
	xor cx, cx

@@While:
	mov cl, [si]
        add ax, cx
        inc si
        inc bx
        cmp bx, PasswordLength
        jne @@While

        ret
;--------------------------------------

PasswordLength      equ 10
CorrectPasswordHash equ 1055
CorrectPhraze       db  "Password is correct, but anyway suck my cock $"
IncorrectPhraze     db  "Incorrect password, idi nahui $"

;--------------------------------------

end     Start
