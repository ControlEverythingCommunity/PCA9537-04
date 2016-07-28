// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// PCA9537
// This code is designed to work with the PCA9537_I2CO4_IRFR3710 I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <math.h>

void main()
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0)
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, PCA9537 I2C address is 0x41(65)
	ioctl(file, I2C_SLAVE, 0x41);

	// Select configuration register(0x03)
	// All pins configured as inputs(0xFF)
	char config[2] = {0};
	config[0] = 0x03;
	config[1] = 0xFF;
	if(write(file, config, 2) != 2)
	{
		printf("Error : Input/Output error \n");
		exit(1);
	}

	// Output to screen
	printf("All Pins State are HIGH \n");
	sleep(1);

	// Read 1 byte of data
	char data[1] = {0};
	if(read(file, data, 1) != 1)
	{
		printf("Error : Input/output Error \n");
	}
	else
	{
		// Output to screen
		int data1 = (data[0] & 0x0F);
		
		for(int i=0; i<4; i++)
		{
			if((data1 & ((int)Math.pow(2, i))) == 0)
			{
				printf("I/O Pin %d State is LOW \n", i);
			}
			else
			{
				printf("I/O Pin %d State is HIGH \n", i);
				sleep(0.5);
			}
		}
	}
}