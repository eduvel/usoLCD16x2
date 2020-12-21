unsigned char heart[8] = {
	0b00000,
	0b01010,
	0b11111,
	0b11111,
	0b11111,
	0b01110,
	0b00100,
	0b00000
};

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
const char Frase[]="Gracias";

#define RS DDB1
#define ENA DDB4
#define DD_BUS DDRB
#define IO_BUS PORTB
#define DATA_BUS PORTD

void setPosicion(unsigned char);
void crearCaracter(unsigned char, unsigned char * );
void escribirCaracter(unsigned char);
void iniciarLCD();
void escribirComando(unsigned char);

int  main() {
  iniciarLCD();
  crearCaracter(0, heart);
  setPosicion(0);
  escribirCaracter(0);
  escribirCaracter(' ');
  escribirCaracter('A');
  escribirCaracter('V');
  escribirCaracter('R');
  
  setPosicion(64);
  unsigned char i=0;
  while(Frase[i]!='\0'){
	  escribirCaracter(Frase[i]);
	  i++;
  }
  while(1) {
		}
}
void crearCaracter(unsigned char direccion, unsigned char * caracter){
	_delay_ms(1);
    direccion<<=3;
    direccion+=0x40;
	
    DATA_BUS=direccion;
    IO_BUS&=~(1<<RS);
    IO_BUS|=(1<<ENA);
    _delay_us(1);
    IO_BUS&=~(1<<ENA);
    IO_BUS|=(1<<RS);
    
    _delay_us(100);
    DATA_BUS=direccion<<4;
    IO_BUS&=~(1<<RS);
    IO_BUS|=(1<<ENA);
    _delay_us(1);
    IO_BUS&=~(1<<ENA);
    IO_BUS|=(1<<RS);
    _delay_us(100);
    
	for(unsigned char i=0;i<=7;i++){  
		_delay_us(100);
		DATA_BUS=caracter[i];
		IO_BUS|=(1<<RS);
		IO_BUS|=(1<<ENA);
		_delay_us(1);
		IO_BUS&=~(1<<ENA);
		IO_BUS&=~(1<<RS);
    
		_delay_us(100);
		DATA_BUS=caracter[i]<<4;
		IO_BUS|=(1<<RS);
		IO_BUS|=(1<<ENA);
		_delay_us(1);
		IO_BUS&=~(1<<ENA);
		IO_BUS&=~(1<<RS);
		_delay_us(100);
  }
 }

void escribirCaracter(unsigned char dato){
   _delay_us(1);
  DATA_BUS=dato;
  IO_BUS|=(1<<RS);
  IO_BUS|=(1<<ENA);
  _delay_us(1);
  IO_BUS&=~(1<<ENA);
  IO_BUS&=~(1<<RS);
  _delay_us(100);
  DATA_BUS=dato<<4;
  IO_BUS|=(1<<RS);
  IO_BUS|=(1<<ENA);
  _delay_us(1);
  IO_BUS&=~(1<<ENA);
  IO_BUS&=~(1<<RS);
  _delay_us(100);
  }

void iniciarLCD(){
  DD_BUS=(1<<RS)|(1<<ENA);
  DDRD=0xFF;
  _delay_ms(20);
  DATA_BUS=0b00110000;
  IO_BUS&=~(1<<RS);;
  IO_BUS|=(1<<ENA);
  _delay_us(1);
  IO_BUS&=~(1<<ENA);
  IO_BUS|=(1<<RS);
  
  _delay_ms(5);
  DATA_BUS=0b00110000;
  IO_BUS&=~(1<<RS);;
  IO_BUS|=(1<<ENA);
  _delay_us(1);
  IO_BUS&=~(1<<ENA);
  IO_BUS|=(1<<RS);
  
  _delay_ms(100);
  DATA_BUS=0b00110000;
  IO_BUS&=~(1<<RS);;
  IO_BUS|=(1<<ENA);
  _delay_us(1);
  IO_BUS&=~(1<<ENA);
  IO_BUS|=(1<<RS);
  
  _delay_us(200);
  DATA_BUS=0b00100000;
  IO_BUS&=~(1<<RS);
  IO_BUS|=(1<<ENA);
  _delay_us(1);
  IO_BUS&=~(1<<ENA);
  IO_BUS|=(1<<RS);
  
  escribirComando(0b00101000);
  escribirComando(0b00001100);
  escribirComando(0b00000001);
  escribirComando(0b00000110);
}
  
 
void escribirComando(unsigned char dato){
    _delay_ms(1);
	DATA_BUS=dato;
	IO_BUS&=~(1<<RS);
	IO_BUS|=(1<<ENA);
	_delay_us(1);
	IO_BUS&=~(1<<ENA);
	IO_BUS|=(1<<RS);
  
	_delay_ms(1);
	DATA_BUS=dato<<4;
	IO_BUS&=~(1<<RS);
	IO_BUS|=(1<<ENA);
	_delay_us(1);
	IO_BUS&=~(1<<ENA);
	IO_BUS|=(1<<RS);
  
    }

void setPosicion(unsigned char direccion){
	direccion|=0x80;
	_delay_ms(1);
	DATA_BUS=direccion;
	IO_BUS&=~(1<<RS);
	IO_BUS|=(1<<ENA);
	_delay_us(1);
	IO_BUS&=~(1<<ENA);
	IO_BUS|=(1<<RS);
	
	_delay_ms(1);
	DATA_BUS=direccion<<4;
	IO_BUS&=~(1<<RS);
	IO_BUS|=(1<<ENA);
	_delay_us(1);
	IO_BUS&=~(1<<ENA);
	IO_BUS|=(1<<RS);
  
    }