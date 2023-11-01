.section .text
.globl draw_ready
.type draw_ready, @function
draw_ready:
	addi sp, sp, -4	#apply sp
	sw ra, 0(sp)	#store address
	add t0, x0, x0	#make t0 zero
	add t0, t0, a0	#t0 get the menu
	add t1, x0, x0	#make t1 zero
	add t1, t1, a1	#t1 get the menu1
	add t2, x0, x0	#make t1 zero
	add t2, t2, a2	#t1 get the menu1
	li a0, 45			#get agr
	li a1, 12			#get agr
	add a2, x0, t0		#get agr
	li a3, 0x07E0		#get agr
	add x0, x0, x0		#clear
	li a0, 45			#get agr
	li a1, 12			#get agr
	add a2, x0, t0		#get agr
	li a3, 0x07E0		#get agr
	add x0, x0, x0		#clear
    call LCD_ShowString	#draw string
	li a0, 26			#get agr
	li a1, 42			#get agr
	add a2, x0, t1		#get agr
	li a3, 0x07E0		#get agr
	add x0, x0, x0		#clear
	li a0, 26			#get agr
	li a1, 42			#get agr
	add a2, x0, t1		#get agr
	li a3, 0x07E0		#get agr
	add x0, x0, x0		#clear
    call LCD_ShowString	#draw string
	li a0, 125			#get agr
	li a1, 42			#get agr
	add a2, x0, t2		#get agr
	li a3, 0x07E0		#get agr
	add x0, x0, x0		#clear
	li a0, 125			#get agr
	li a1, 42			#get agr
	add a2, x0, t2		#get agr
	li a3, 0x07E0		#get agr
	add x0, x0, x0		#clear
    call LCD_ShowString	#draw string
	add x0, x0, x0		#clear
    lw ra, 0(sp)		#load back
	addi sp, sp, 4
	ret					#return
