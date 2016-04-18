#include "mcp3204.h"

#define MAX_ADC_VALUE 4095

MCP3204::MCP3204(uint8_t pin_cs, uint32_t spi_clk_freq)
	: ADCSPI(pin_cs, MAX_ADC_VALUE)
{
	// SPI Mode = 0 => CPOL = 0 & CPHA = 0
	settingsSPI = getSPISettings(spi_clk_freq, MSBFIRST, SPI_MODE0);
	pinMode(pin_cs, OUTPUT);
	digitalWrite(pin_cs, HIGH);
	SPI.begin();
}


uint16_t MCP3204::readChannel(uint8_t ch)
{
	uint8_t spi_tx = 0x06; // Refer to FIGURE 6-1 in MCP3204 datasheet.

	SPI.beginTransaction(settingsSPI);
	digitalWrite(pin_cs, LOW);

	SPI.transfer(spi_tx);

	spi_tx = ch << 6;
	uint8_t rx1 = SPI.transfer(spi_tx);

	uint8_t rx2 = SPI.transfer(0xFF);

	digitalWrite(pin_cs, HIGH);
	SPI.endTransaction();

	return ((rx1 & 0x0F) << 8) | rx2;
}

