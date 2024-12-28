//------------------------------------------------------------------------
// Copyright(c) 2024 Dad Design.
//      Gestion d'une liaison SPI vers un écran 
//------------------------------------------------------------------------
#include "TFT_SPI.h"

#if TFT_CONTROLEUR_TFT == 7735
    #include "ST7735_Defines.h"
#elif TFT_CONTROLEUR_TFT == 7789
    #include "ST7789_Defines.h"
#endif
namespace DadGFX {
//***********************************************************************************
// TFT_SPI
//  Gestion de la liaison SPI
//*********************************************************************************** 

// --------------------------------------------------------------------------
// Initialisation du SPI
void TFT_SPI::Init_TFT_SPI(){
    // Configuration du SPI
    m_spi_config.periph     = _TFT_SPI_PORT;
    m_spi_config.mode       = SpiHandle::Config::Mode::MASTER;
    m_spi_config.direction  = SpiHandle::Config::Direction::TWO_LINES_TX_ONLY;
    m_spi_config.datasize   = 8;
    
    switch(_TFT_SPI_MODE) {
        case SPIMode::Mode3 :
            m_spi_config.clock_polarity = SpiHandle::Config::ClockPolarity::HIGH;
            m_spi_config.clock_phase    = SpiHandle::Config::ClockPhase::TWO_EDGE;
        break;
        case SPIMode::Mode2 :
            m_spi_config.clock_polarity = SpiHandle::Config::ClockPolarity::LOW;
            m_spi_config.clock_phase    = SpiHandle::Config::ClockPhase::TWO_EDGE;
        break;
        case SPIMode::Mode1 :
            m_spi_config.clock_polarity = SpiHandle::Config::ClockPolarity::HIGH;
            m_spi_config.clock_phase    = SpiHandle::Config::ClockPhase::ONE_EDGE;
        break;
        case SPIMode::Mode0 :
        default :
            m_spi_config.clock_polarity = SpiHandle::Config::ClockPolarity::LOW;
            m_spi_config.clock_phase    = SpiHandle::Config::ClockPhase::ONE_EDGE;
        break;
    }
    
    m_spi_config.nss            = SpiHandle::Config::NSS::SOFT;
    m_spi_config.baud_prescaler = SpiHandle::Config::BaudPrescaler::TFT_SPI_BaudPrescaler;

    m_spi_config.pin_config.sclk = _TFT_SCLK;
    m_spi_config.pin_config.miso = dsy_gpio_pin();
    m_spi_config.pin_config.mosi = _TFT_MOSI;
    m_spi_config.pin_config.nss  = dsy_gpio_pin();
        
    // TFT control pin config
    m_dc.Init(_TFT_DC, GPIO::Mode::OUTPUT, GPIO::Pull::NOPULL, GPIO::Speed::VERY_HIGH);
    m_reset.Init(_TFT_RST, GPIO::Mode::OUTPUT, GPIO::Pull::NOPULL, GPIO::Speed::VERY_HIGH);
    m_dc.Write(true);
    m_reset.Write(true);

    // Initialize SPI
    m_spi.Init(m_spi_config);
    
    // Reset LCD
    m_reset.Write(false);
    System::Delay(50);
    m_reset.Write(true);
    System::Delay(50);

    Initialise();
}
 
// Set the display image orientation to 0, 1, 2 or 3
void  TFT_SPI::setTFTRotation(Rotation r){
    SendCommand(TFT_MADCTL);
    switch (r) {
    case Rotation::Degre_0 : // Portrait
        SendData(TFT_MAD_COLOR_ORDER);
        break;
    case Rotation::Degre_90 : // Landscape (Portrait + 90)
        SendData(TFT_MAD_MX | TFT_MAD_MV | TFT_MAD_COLOR_ORDER);
        break;
    case Rotation::Degre_180 : // Inverter portrait
        SendData(TFT_MAD_MX | TFT_MAD_MY | TFT_MAD_COLOR_ORDER);
        break;
    case Rotation::Degre_270 : // Inverted landscape
        SendData(TFT_MAD_MV | TFT_MAD_MY | TFT_MAD_COLOR_ORDER);
        break;
    }
}
} // DadGFX