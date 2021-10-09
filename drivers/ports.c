// Standard port reading and writing

unsigned char port_byte_in(unsigned short port){
	unsigned char result;
	// set the result = al ( the output )
	// set edx = port
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void port_byte_out(unsigned short port, unsigned char data){
	__asm__("out %%al, %%dx" : : "a" (data) , "d" (port));
}

unsigned short port_word_in(unsigned short port){
	// basically similar to port_byte_in
	// uses ax instead of al
	unsigned short result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

void port_word_out(unsigned short port, unsigned short data){
	__asm__("out %%ax, %%dx" : : "a" (data) , "d" (port));
}

