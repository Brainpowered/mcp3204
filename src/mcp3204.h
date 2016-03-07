#pragma once

#include "adc.h"

class MCP3204 : public ADCSPI
{
public:
	MCP3204(uint8_t pin_cs, uint32_t spi_clk_freq = DEFAULT_SPI_CLK_FREQ);
	~MCP3204();
	virtual uint16_t readChannel(uint8_t ch);
};

