#include <iot13v.h>
#include <macros.h>
#define uchar  unsigned char 
#define uint  unsigned int 
#define Min 20 ///�������Сֵ
#define Max 45 ///��������ֵ
static uint volatile LASTADCVAL = 0;

#define ADCEN  1
/*΢�뼶��ʱ����*/
void delay_us(uint time)
{     
  	 do
	 {
		time--;
	 }	
  	 while (time>1);
}	  


//IO�ڳ�ʼ��
void port_init(void)
{
	PORTB = 0x07;
 	DDRB = (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(0<<PB4);	//I/O״̬


}

//ADCתʼ������
void adc_init(void)
{
     ADCSRA = 0x00;  //disable adc
     ADCMUX = 0x42;  //ʹ��VCC��Ϊ�ο���ѹ��ѡ��ADC3��PB3������ͨ��
     ACSR  = 0x80;   //����ģ��Ƚ��������͹���
     ADCSRB = 0x00;  //ADC����ת��ģʽ
     ADCSRA = 0xEA;  //ʹ��ADC��ʼת�����Զ�����ʹ��,ʹ��ת�������ж�,4��Ƶ
}

//ADCת�������ж�
#pragma interrupt_handler adc_isr:10
void adc_isr(void)
{

     uint value;
     value=ADCL;          
     value|=(uint)ADCH << 8; 
	 LASTADCVAL=value;
}

//call this routine to initialize all peripherals
void init_devices(void)
{
    //stop errant interrupts until set up
    CLI(); //disable all interrupts
    port_init();
    adc_init();
    MCUCR = 0x00;
    TIMSK0 = 0x00; //timer interrupt sources
    GIMSK = 0x00; //interrupt sources
    SEI(); //re-enable interrupts
    //all peripherals are now initialized
}


void main(void)
{
 	 uchar i,cnt;
 	uint tmpADC,avgADC; 
	unsigned long ADCsum;
	
    init_devices();
	delay_us(200);

    
    while(1)
    {
		   ADCsum = 0;
	 	   for(i = 0; i < 200; i++)
		   {
	 	    tmpADC = LASTADCVAL;
		     ADCsum += tmpADC;
			 delay_us(100);//6ms
		  	}		
			avgADC = (uint)(ADCsum/200);
			if(avgADC > Max)
				PORTB &=~ (1<<3); 

			if(avgADC < Min)
			    PORTB |= (1<<3); 

   	  } 	 
}