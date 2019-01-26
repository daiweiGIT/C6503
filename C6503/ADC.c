#include <iot13v.h>
#include <macros.h>
#define uchar  unsigned char 
#define uint  unsigned int 
#define Min 20 ///光起控最小值
#define Max 45 ///光起控最大值
static uint volatile LASTADCVAL = 0;

#define ADCEN  1
/*微秒级延时程序*/
void delay_us(uint time)
{     
  	 do
	 {
		time--;
	 }	
  	 while (time>1);
}	  


//IO口初始化
void port_init(void)
{
	PORTB = 0x07;
 	DDRB = (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(0<<PB4);	//I/O状态


}

//ADC转始化设置
void adc_init(void)
{
     ADCSRA = 0x00;  //disable adc
     ADCMUX = 0x42;  //使用VCC作为参考电压，选择ADC3（PB3）输入通道
     ACSR  = 0x80;   //禁用模拟比较器，降低功耗
     ADCSRB = 0x00;  //ADC连续转换模式
     ADCSRA = 0xEA;  //使能ADC开始转换，自动触发使能,使能转换结束中断,4分频
}

//ADC转换结束中断
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