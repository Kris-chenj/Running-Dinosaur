.section .text
.globl draw_line_dino
.type draw_line_dino, @function
draw_line_dino:
	addi sp, sp, -4	#apply sp
	sw ra, 0(sp)	#store address
	add t0, x0, x0	#make t0 zero
	add t0, t0, a0	#t0 get the a0
	li a0, 0			#get agr
	li a1, 60		#get agr
	li a2, 160		#get agr
	li a3, 60		#get agr
	li a4, 0xffff	#get agr
	li a0, 0		#get agr
	li a1, 60		#get agr
	li a2, 160		#get agr
	li a3, 60		#get agr
	li a4, 0xffff	#get agr
    call LCD_DrawLine	#draw line
	add x0, x0, x0 	#get agr
	li a0, 20		#get agr
	li a1, 40		#get agr
	li a2, 39		#get agr
	li a3, 59		#get agr
	add a4, x0, t0	#get agr
	add t0, x0, x0	#back
	call LCD_ShowPic	#draw dino
    lw ra, 0(sp)	#load back
	addi sp, sp, 4
	ret				#return

