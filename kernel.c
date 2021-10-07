void main_kernel(){
	char* video_memory = (char*) 0xb8000;
	char* msg = "THIS BETTER FUCKING WORK";
	int i = 0;
	while (msg[i] != 0){
		*(video_memory + 2*i) = *(msg + i);
		i++;
	}
}
