void main_kernel(){
	char* video_memory = (char*) 0xb8000;
	*video_memory = 'A';
}
