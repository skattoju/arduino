/* Serial Communications Interface */
#ifndef SERIAL_H
#define SERIAL_H

void serial_init(unsigned int);
void _serial_write(unsigned char);
char serial_read();
void serial_print(const char* str[]);
void _serial_dbg(int);
void _serial_test(uint8_t data);

#endif
