/*
 * Main file for the whole OS
 */

void kmain() {
  char *video_memory = (char *)0xb8000;
  char *start_msg = "Kernel Loaded";
  int i = 0;
  while (start_msg[i] != 0) {
    video_memory[2 * i] = start_msg[i];
    i++;
  }
}
