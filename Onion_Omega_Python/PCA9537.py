# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# PCA9537
# This code is designed to work with the PCA9537_I2CO4_IRFR3710 I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# PCA9537 address, 0x41(65)
# Select configuration register, 0x03(03)
#		0xFF(255)	All pins configured as inputs
i2c.writeByte(0x41, 0x03, 0xFF)

# Output to screen
print "All Pins State are HIGH"

time.sleep(0.5)

# PCA9537 address, 0x41(65)
# Read data back from 0x00(00), 1 byte
data = i2c.readBytes(0x41, 0x00, 1)

# Convert the data to 4-bits
data = (data & 0x0F)

for i in range(0, 4) :
	if (data & (2 ** i)) == 0 :
		print "I/O Pin %d State is LOW" %i
	else :
		print "I/O Pin %d State is HIGH" %i
		time.sleep(0.5)
