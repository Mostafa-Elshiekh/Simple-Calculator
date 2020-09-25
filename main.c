/*
 * wait keypad.c
 *
 * Created: 9/17/2020 3:10:58 PM
 * Author : Mostafa Mahmoud
 */ 
#include <avr/io.h>
#include <avr/delay.h>
#define F_CPU  1000000UL
#include <driver lcd.c>
#include <keypad driver.c>
#include <GPIOs driver.c>
#define  A 0x39
#define  B 0x36
#define  C 0x33
#define  D 0x30
#define  output 1
#define input 0
int main(void)
{
		uint8_t  count=0;
		/* Replace with your application code */
		Port_Direction(B,output);                          	           //DDRB=0xff
		for(count=0;count<2;count++)             		           //DDRA|=(1<<0)|(1<<1)
		{
			Pin_Direction(A,count,output);
		}
		
		for(count=0;count<4;count++)          	                        //DDRD=0x0F
		{
			Pin_Direction(D,count,output);
		}
		for(count=0;count<4;count++)  		                       //PORTD|=(1<<0)|(1<<1)|(1<<2)|(1<<3)

		{
			Port_Write(D,count);
		}
		
		lcd_init();
		uint8_t   i=0 ,j=0;
		uint8_t  arr1[100] , arr2[100];
		uint8_t  result=0;
		uint8_t  var1,var2;
		lcd_print("enter the nums");
		while (1)
		{
				if(keypad()!='N'  && keypad()!='C')           // nums in keypad except(C-clear and Anything else)
				{
					lcd_command(0xC);                     //display on , cursor off 
					lcd_go_to(2,1+i);
					lcd_out(keypad());
					arr1[i]=(keypad());                   //store all Clicks in arr1
					if(i==1 )                            //store the first 2 digits in the var1
					{
						var1=(arr1[i-1]*10)+arr1[i]; //to make Every two numbers , one number Consists of 2 digit
					}
					if(i==4)                            //store the seconder 2 digits in the var2
					{
						var2=(arr1[i-1]*10)+arr1[i];
					}
					
					 if(keypad()=='=' && arr1[i-3]=='+')   //summation   operation
					 {
							 result=var1+var2;
							 if(result<10)
							 {
								 lcd_out(result-48+16+48);
							 }
							 else
							 {
								 lcd_num(result-48+16);
							 }
				        }
				         if(keypad()=='=' && arr1[i-3]=='-')//subtraction operation
					  {
							 result=var1-var2;
							  if(result<10)
							  {
								  lcd_out(result+48);
							  }
							  else
							  {
								  lcd_num(result);
							  }
					  }
					  
					  if(keypad()=='=' && arr1[i-3]=='*')    //multiplication  operation
					  {
							  var1=var1-16;
							  var2=var2-16;
							  result=var1 * var2;
							  if(result<10)
							  {
								  lcd_out(result+48);
							  }
							  else
							  {
								  lcd_num(result);
							  }
					  }
					  if(keypad()=='=' && arr1[i-3]=='/') // Division operation
					  {
							  var1=var1-16;
							  var2=var2-16;
							  if(var2==0)
							  {
								  lcd_go_to(3,-3);
								  lcd_print("it is not valid ");
							  }
							  else
								 {
								 result=var1 / var2;
								  if(result<10)
								  {
									  lcd_out(result+48);
								  }
							  }
					  }
					  
					  i++;		  
					  _delay_ms(600);
				        }	  			
				  	else if(keypad()=='C')                                // if  the Click (C -clear)
				  			{
					  			i=0;                          // to return the first index in arr1
					  			result=0;                     // to clear this var
					  			lcd_command(0x1);             // to clear LCD
					  			lcd_go_to(1,1);
					  			lcd_print("enter the nums");
					  			_delay_ms(100);
					  			
				  			}
				}
		
		return 0  ;
 }
				  
