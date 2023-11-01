.section .text
.globl end_game
.type end_game, @function
end_game:
	addi sp, sp, -4	#apply sp
	sw ra, 0(sp)	#store address
	add t0, x0, x0	#make t0 zero
	add t0, t0, a0	#t0 get the menu
	add t1, x0, x0	#make t1 zero
	add t1, t1, a1	#t1 get the menu1
	li a0, 54			#get agr
	li a1, 21			#get agr
	add a2, x0, t0		#get agr
	li a3, 0xF800		#get agr
	add x0, x0, x0		#clear
	li a0, 54			#get agr
	li a1, 21			#get agr
	add a2, x0, t0		#get agr
	li a3, 0xF800		#get agr
	add x0, x0, x0		#clear
    call LCD_ShowString	#draw string
	li a0, 35			#get agr
	li a1, 40			#get agr
	add a2, x0, t1		#get agr
	li a3, 0x001F		#get agr
	add x0, x0, x0		#clear
	li a0, 35			#get agr
	li a1, 40			#get agr
	add a2, x0, t1		#get agr
	li a3, 0x001F		#get agr
	add x0, x0, x0		#clear
    #call LCD_ShowString	#draw string
	li a0, 0			#back
	li a0, 2000			#set time
	#call delay_1ms		#delay
	li a0, 0			#back
	li a0, 0x0000		#clear
	#call LCD_Clear		#clear
	add x0, x0, x0		#clear
    lw ra, 0(sp)		#load back
	addi sp, sp, 4
	ret					#return

