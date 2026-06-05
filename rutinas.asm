bits 64
default rel 

global validar_mov
section .text

; es valido (1) o es pared (0) en rax
; rcx-direccion, rdx-fila, r8-columna

validar_mov:
    mov rax, rdx       
    imul rax, 15 ;tam de mi matriz (prueba)
    add rax, r8         
    movzx r10d, byte [rcx+ rax] 
    cmp r10b, 35 ; 35== '#'
    je .es_pared ; si es igual a # salta a la etiqueta d pared
    mov rax, 1 ; si no es pared, rax es igual a 1 y hace válido el movimiento       
    ret

;rax=0 y llega a paerd
.es_pared: 
    xor rax, rax        
    ret
;fin
