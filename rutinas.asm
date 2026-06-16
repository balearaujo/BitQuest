bits 64
default rel 

global validar_mov
global cnt_monedas
global detectar_obj
global cnt_espacios
global puntaje
section .text

; es valido (1) o es pared (0) en rax
; rcx-direccion, rdx columnas ,r8-fila sig, r9 -columna sig
validar_mov:
    mov rax, r8      
    imul rax, rdx ;tam matriz 
    add rax, r9        
    movzx r10d, byte [rcx+ rax] 
    cmp r10b, 35 ; 35== '#'
    je .es_pared ; si es igual a # salta a la etiqueta d pared
    cmp r10b, 124; 124== '|'
    je .es_fuego; si es igual a | salta a la etiqueta d fuego 
    mov rax, 1 ; si no es pared, rax es igual a 1 y hace válido el movimiento       
    ret
;rax=0 y llega a paerd
.es_pared: 
    xor rax, rax        
    ret
.es_fuego:
    mov rax, 2
    ret

;fin validar mov

cnt_monedas:
    xor rax, rax        
    xor r10, r10      
    movzx r8d, r8b 

.ciclo:
    cmp r10, rdx     ;recorre las celdas  
    je .fin_monedas     ;si termina, salta a la etiqueta fin
    mov r11b, [rcx + r10]  
    cmp r11b, r8b       ;compara el caracter con M
    jne .siguiente_monedas
    inc rax         ;incrementa contador 
;   
.siguiente_monedas:
    inc r10 ; si no es igual el caracter, incrementa el indice de casillas recorridas
    jmp .ciclo ;repite el ciclo 
.fin_monedas:
    ret

;fin contar monedas

detectar_obj:
    mov rax, r8         
    imul rax, rdx       
    add rax, r9         
    
    movzx r10d, byte [rcx + rax] 
    mov r11b, [rsp + 40]         
    cmp r10b, r11b      ; compara si es el objeto buscado
    je .encontrado
    xor rax, rax        ; no esta (0) 
    ret
.encontrado:
    mov rax, 1          ; si esta(1)
    ret
;fin detectar objeto 

cnt_espacios:
    xor rax, rax        
    xor r10, r10    
    movzx r8d, r8b  
.ciclo_espacios:
    cmp r10, rdx     ;recorre las celdas  
    je .fin_espacios     ;si termina, salta a la etiqueta fin
    mov r11b, [rcx + r10]  
    cmp r11b, r8b       ;compara el caracter con M
    jne .siguiente_espacios
    inc rax         ;incrementa contador 
;   
.siguiente_espacios:
    inc r10 ; si no es igual el caracter, incrementa el indice de casillas recorridas
    jmp .ciclo_espacios ;repite el ciclo 
.fin_espacios:
    ret

;fin contar espacios 

puntaje:
    imul rcx, 150  ;monedas valen 150
    imul r8, 200    ;niveles completados valen 200
    add rcx, r8     ;puntos acumulados en rcx
    imul rdx, 2        ;cantidad de pasos *2
    sub rcx, rdx    ;restar al puntaje por cantidad de pasos realizados
    cmp rcx, 0
    jge .fin_puntaje
    xor rcx, rcx  ;en puntaje queda en 0 si el obtenido es menor a 0 

.fin_puntaje:
    mov rax, rcx
    ret
;fin puntaje
