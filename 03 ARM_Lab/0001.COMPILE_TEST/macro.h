#define	Macro_Set_Bit(dest, pos)				    ((dest) |=  ((unsigned)0x1<<(pos)))
#define	Macro_Clear_Bit(dest, pos)					((dest) &= ~((unsigned)0x1<<(pos)))
#define	Macro_Invert_Bit(dest, pos)				    ((dest) ^=  ((unsigned)0x1<<(pos)))

#define	Macro_Set_Area(dest, bits, pos)			    ((dest) |=  (((unsigned)bits)<<(pos)))
#define	Macro_Clear_Area(dest, bits, pos)			((dest) &= ~(((unsigned)bits)<<(pos)))
#define	Macro_Invert_Area(dest, bits, pos)			((dest) ^=  (((unsigned)bits)<<(pos)))

#define	Macro_Write_Block(dest, bits, data, pos)	((dest) = (((unsigned)dest) & ~(((unsigned)bits)<<(pos))) | (((unsigned)data)<<(pos)))
#define Macro_Extract_Area(dest, bits, pos)		    ((((unsigned)dest)>>(pos)) & (bits))

#define Macro_Check_Bit_Set(dest, pos)				((((unsigned)dest)>>(pos)) & 0x1)
#define Macro_Check_Bit_Clear(dest, pos)			(!((((unsigned)dest)>>(pos)) & 0x1))

/*
macro_set_bit : pos위치의 bit를 1로 set해라 >

#define	Macro_Set_Bit(dest, pos)				    ((dest) |=  ((unsigned)0x1<<(pos)))
#define	Macro_Clear_Bit(dest, pos)					((dest) &= ~((unsigned)0x1<<(pos)))
#define	Macro_Invert_Bit(dest, pos)				    ((dest) ^=  ((unsigned)0x1<<(pos)))

#define	Macro_Set_Area(dest, bits, pos)			    ((dest) |=  (((unsigned)bits)<<(pos)))
#define	Macro_Clear_Area(dest, bits, pos)			((dest) &= ~(((unsigned)bits)<<(pos)))
#define	Macro_Invert_Area(dest, bits, pos)			((dest) ^=  (((unsigned)bits)<<(pos)))

#define Macro_Set_Bit(dest, pos)  (dest |= (0x1 << pos))
#define Macro_Clear_Bit(dest, pos) (dest &= ~(0x1 << pos))
#define Macro_Invert_Bit(dest, pos) (dest ^= (0x1 << pos))




#define	Macro_Write_Block(dest, bits, data, pos)	((dest) = (((unsigned)dest) & ~(((unsigned)bits)<<(pos))) | (((unsigned)data)<<(pos)))
#define Macro_Extract_Area(dest, bits, pos)		    ((((unsigned)dest)>>(pos)) & (bits))

#define Macro_Check_Bit_Set(dest, pos)				((((unsigned)dest)>>(pos)) & 0x1)
#define Macro_Check_Bit_Clear(dest, pos)			(!((((unsigned)dest)>>(pos)) & 0x1))

#define	Macro_Write_Block(dest, bits, data, pos)    (dest = ((dest & ~(bits << pos)) | (data << pos) ) 
// dest 값을 pos부터 bits만큼 data로 덧씌우기

#define Macro_Extract_Area(dest, bits, pos)		    (dest = (dest & (bits << pos)))

Macro_Set_Bit(GPIOA->MODER, 5 + 1)  // 이런 식으로 식이 올 수도 있기 때문에.. + unsigned를 붙이는 이유.. 부호비트가 없으니 이상하게 될 가능성이 낮다!
// 실제 치환 결과: GPIOA->MODER |= (0x1 << 5 + 1)

*/